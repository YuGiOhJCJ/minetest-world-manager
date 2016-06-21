/*
 * Secure Remote Password 6a implementation
 * https://github.com/est31/csrp-gmp
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 YuGiOhJCJ <yugiohjcj@1s.fr>
 * Copyright (c) 2015 est31 <MTest31@outlook.com>
 * Copyright (c) 2010, 2013 Tom Cocagne
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#include <gmp.h> /* for mpz_init */
#include <openssl/sha.h> /* for SHA1_Init */
#include <stdio.h> /* for fopen */
#include <stdlib.h> /* for free */
#include <string.h> /* for memcpy */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
#include "minetest_world_manager_srp.h" /* for minetest_world_manager_srp_create_salted_verification_key */
#include "minetest_world_manager_string.h" /* for minetest_world_manager_string_get_field */
#define minetest_world_manager_srp_rand_buff_max 128
typedef struct
{
	mpz_t n;
	mpz_t g;
} minetest_world_manager_srp_ng_constant_t;
static int minetest_world_manager_srp_calculate_x(mpz_t result, const unsigned char *salt, size_t salt_len, const char *username, const unsigned char *password, size_t password_len);
static int minetest_world_manager_srp_create_salted_verification_return(int value, minetest_world_manager_srp_ng_constant_t *ng, mpz_t v, mpz_t x);
static void minetest_world_manager_srp_delete_ng(minetest_world_manager_srp_ng_constant_t *ng);
static char *minetest_world_manager_srp_get_prime();
static int minetest_world_manager_srp_h_ns(mpz_t result, const unsigned char *n, size_t len_n, const unsigned char *bytes, size_t len_bytes);
static void minetest_world_manager_srp_mpz_from_bin(const unsigned char *s, size_t len, mpz_t ret);
static int minetest_world_manager_srp_mpz_num_bytes(const mpz_t op);
static void minetest_world_manager_srp_mpz_to_bin(const mpz_t op, unsigned char *to);
static minetest_world_manager_srp_ng_constant_t *minetest_world_manager_srp_new_ng();
static int minetest_world_manager_srp_calculate_x(mpz_t result, const unsigned char *salt, size_t salt_len, const char *username, const unsigned char *password, size_t password_len)
{
	unsigned char ucp_hash[SHA512_DIGEST_LENGTH];
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, username, strlen(username));
	SHA256_Update(&ctx, ":", 1);
	SHA256_Update(&ctx, password, password_len);
	SHA256_Final(ucp_hash, &ctx);
	return minetest_world_manager_srp_h_ns(result, salt, salt_len, ucp_hash, SHA256_DIGEST_LENGTH);
}
static int minetest_world_manager_srp_create_salted_verification_return(int value, minetest_world_manager_srp_ng_constant_t *ng, mpz_t v, mpz_t x)
{
	if(ng != NULL)
	{
		minetest_world_manager_srp_delete_ng(ng);
		ng = NULL;
	}
	if(v != NULL)
	{
		mpz_clear(v);
		v = NULL;
	}
	if(x != NULL)
	{
		mpz_clear(x);
		x = NULL;
	}
	return value;
}
static void minetest_world_manager_srp_delete_ng(minetest_world_manager_srp_ng_constant_t *ng)
{
	if(ng != NULL)
	{
		if(ng->n != NULL)
			mpz_clear(ng->n);
		if(ng->g != NULL)
			mpz_clear(ng->g);
		free(ng);
		ng = NULL;
	}
}
static char *minetest_world_manager_srp_get_prime()
{
	char *result = NULL;
	const char *n01 = "AC6BDB41324A9A9BF166DE5E1389582FAF72B6651987EE07FC319294";
	const char *n02 = "3DB56050A37329CBB4A099ED8193E0757767A13DD52312AB4B03310D";
	const char *n03 = "CD7F48A9DA04FD50E8083969EDB767B0CF6095179A163AB3661A05FB";
	const char *n04 = "D5FAAAE82918A9962F0B93B855F97993EC975EEAA80D740ADBF4FF74";
	const char *n05 = "7359D041D5C33EA71D281E446B14773BCA97B43A23FB801676BD207A";
	const char *n06 = "436C6481F1D2B9078717461A5B9D32E688F87748544523B524B0D57D";
	const char *n07 = "5EA77A2775D2ECFA032CFBDBF52FB3786160279004E57AE6AF874E73";
	const char *n08 = "03CE53299CCC041C7BC308D82A5698F3A8D0C38271AE35F8E9DBFBB6";
	const char *n09 = "94B5C803D89F7AE435DE236D525F54759B65E372FCD68EF20FA7111F";
	const char *n10 = "9E4AFF73";
	result = malloc(sizeof(char) * (strlen(n01) + strlen(n02) + strlen(n03) + strlen(n04) + strlen(n05) + strlen(n06) + strlen(n07) + strlen(n08) + strlen(n09) + strlen(n10) + 1));
	if(result == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s%s%s%s%s%s%s%s%s%s\" string containing the hexadecimal value for the prime.", n01, n02, n03, n04, n05, n06, n07, n08, n09, n10);
		return NULL;
	}
	if(sprintf(result, "%s%s%s%s%s%s%s%s%s%s", n01, n02, n03, n04, n05, n06, n07, n08, n09, n10) < 0)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the \"%s%s%s%s%s%s%s%s%s%s\" string containing the hexadecimal value for the prime.", n01, n02, n03, n04, n05, n06, n07, n08, n09, n10);
		free(result);
		return NULL;
	}
	return result;
}
static int minetest_world_manager_srp_h_ns(mpz_t result, const unsigned char *n, size_t len_n, const unsigned char *bytes, size_t len_bytes)
{
	unsigned char buff[SHA512_DIGEST_LENGTH];
	size_t nbytes = len_n + len_bytes;
	unsigned char *bin = (unsigned char *) malloc(nbytes);
	if(bin == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory to calculate x.");
		return -1;
	}
	memcpy(bin, n, len_n);
	memcpy(bin + len_n, bytes, len_bytes);
	SHA256(bin, nbytes, buff);
	free(bin);
	minetest_world_manager_srp_mpz_from_bin(buff, SHA256_DIGEST_LENGTH, result);
	return 0;
}
static void minetest_world_manager_srp_mpz_from_bin(const unsigned char *s, size_t len, mpz_t ret)
{
	mpz_import(ret, len, 1, 1, 1, 0, s);
}
static int minetest_world_manager_srp_mpz_num_bytes(const mpz_t op)
{
	return (mpz_sizeinbase(op, 2) + 7) / 8;
}
static void minetest_world_manager_srp_mpz_to_bin(const mpz_t op, unsigned char *to)
{
	mpz_export(to, NULL, 1, 1, 1, 0, op);
}
static minetest_world_manager_srp_ng_constant_t *minetest_world_manager_srp_new_ng()
{
	int rv = 0;
	char *n_hex = NULL;
	char *g_hex = NULL;
	minetest_world_manager_srp_ng_constant_t *ng = malloc(sizeof(minetest_world_manager_srp_ng_constant_t));
	if(ng == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the structure for the prime and the generator.");
		return NULL;
	}
	mpz_init(ng->n);
	mpz_init(ng->g);
	n_hex = minetest_world_manager_srp_get_prime();
	if(n_hex == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the hexadecimal value for the prime.");
		minetest_world_manager_srp_delete_ng(ng);
		return NULL;
	}
	g_hex = "2";
	rv = mpz_set_str(ng->n, n_hex, 16);
	rv = rv | mpz_set_str(ng->g, g_hex, 16);
	if(rv)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" string to an hexadecimal.");
		minetest_world_manager_srp_delete_ng(ng);
		free(n_hex);
		return NULL;
	}
	free(n_hex);
	return ng;
}
int minetest_world_manager_srp_create_salted_verification_key(const char *username_for_verifier, const unsigned char *password, size_t len_password, unsigned char **bytes_s, size_t *len_s, unsigned char **bytes_v, size_t *len_v)
{
	minetest_world_manager_srp_ng_constant_t *ng = NULL;
	mpz_t v;
	mpz_t x;
	mpz_init(v);
	mpz_init(x);
	ng = minetest_world_manager_srp_new_ng();
	if(ng == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the group parameters.");
		return minetest_world_manager_srp_create_salted_verification_return(-1, ng, v, x);
	}
	if(minetest_world_manager_srp_calculate_x(x, *bytes_s, *len_s, username_for_verifier, password, len_password) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to calculate x.");
		return minetest_world_manager_srp_create_salted_verification_return(-1, ng, v, x);
	}
	mpz_powm(v, ng->g, x, ng->n);
	*len_v = minetest_world_manager_srp_mpz_num_bytes(v);
	*bytes_v = (unsigned char *) malloc(*len_v);
	if(*bytes_v == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the key.");
		return minetest_world_manager_srp_create_salted_verification_return(-1, ng, v, x);
	}
	minetest_world_manager_srp_mpz_to_bin(v, *bytes_v);
	return minetest_world_manager_srp_create_salted_verification_return(0, ng, v, x);
}
