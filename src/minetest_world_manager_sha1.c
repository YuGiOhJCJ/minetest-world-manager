/* minetest_world_manager_sha1.c

Copyright (c) 2016 YuGiOhJCJ
Copyright (c) 2005 Michael D. Leonhard

http://yugiohjcj.1s.fr/
http://tamale.net/

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memcpy */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
#include "minetest_world_manager_sha1.h" /* for minetest_world_manager_sha1_t */
static unsigned char *minetest_world_manager_sha1_get_digest_return(unsigned char *digest)
{
	if(digest != NULL)
		free(digest);
	return NULL;
}
static Uint32 minetest_world_manager_sha1_lrot(Uint32 x, int bits)
{
	return (x << bits) | (x >> (32 - bits));
}
static int minetest_world_manager_sha1_process(minetest_world_manager_sha1_t *sha1)
{
	int t;
	Uint32 a, b, c, d, e, K, f, W[80];
	Uint32 temp;
	if(sha1->unprocessed_bytes != 64)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to process SHA1 because 'sha1->unprocessed_bytes' is not equal to 64.");
		return -1;
	}
	a = sha1->h0;
	b = sha1->h1;
	c = sha1->h2;
	d = sha1->h3;
	e = sha1->h4;
	for(t = 0; t < 16; t++)
		W[t] = (sha1->bytes[t * 4] << 24) + (sha1->bytes[t * 4 + 1] << 16) + (sha1->bytes[t * 4 + 2] << 8) + sha1->bytes[t * 4 + 3];
	for(; t< 80; t++)
		W[t] = minetest_world_manager_sha1_lrot(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1);
	for(t = 0; t < 80; t++)
	{
		if(t < 20)
		{
			K = 0x5a827999;
			f = (b & c) | ((b ^ 0xFFFFFFFF) & d);
		}
		else if(t < 40)
		{
			K = 0x6ed9eba1;
			f = b ^ c ^ d;
		}
		else if(t < 60)
		{
			K = 0x8f1bbcdc;
			f = (b & c) | (b & d) | (c & d);
		}
		else
		{
			K = 0xca62c1d6;
			f = b ^ c ^ d;
		}
		temp = minetest_world_manager_sha1_lrot(a, 5) + f + e + W[t] + K;
		e = d;
		d = c;
		c = minetest_world_manager_sha1_lrot(b, 30);
		b = a;
		a = temp;
	}
	sha1->h0 += a;
	sha1->h1 += b;
	sha1->h2 += c;
	sha1->h3 += d;
	sha1->h4 += e;
	sha1->unprocessed_bytes = 0;
	return 0;
}
static int minetest_world_manager_sha1_store_big_endian_uint32(unsigned char *byte, Uint32 num)
{
	if(byte == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to save to memory in big-endian order for SHA1 because 'byte' is equal to NULL.");
		return -1;
	}
	byte[0] = (unsigned char) (num >> 24);
	byte[1] = (unsigned char) (num >> 16);
	byte[2] = (unsigned char) (num >> 8);
	byte[3] = (unsigned char) num;
	return 0;
}
int minetest_world_manager_sha1_add_bytes(minetest_world_manager_sha1_t *sha1, const char *data, int num)
{
	if(data == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to add bytes for SHA1 because 'data' is equal to NULL.");
		return -1;
	}
	if(num < 0)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to add bytes for SHA1 because 'num' is less than 0.");
		return -1;
	}
	sha1->size += num;
	while(num > 0)
	{
		int needed;
		int to_copy;
		needed = 64 - sha1->unprocessed_bytes;
		if(needed <= 0)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to add bytes for SHA1 because 'needed' is less than or equal to 0.");
			return -1;
		}
		to_copy = (num < needed) ? num : needed;
		memcpy(sha1->bytes + sha1->unprocessed_bytes, data, to_copy);
		num -= to_copy;
		data += to_copy;
		sha1->unprocessed_bytes += to_copy;
		if(sha1->unprocessed_bytes == 64)
		{
			if(minetest_world_manager_sha1_process(sha1) == -1)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to process SHA1.");
				return -1;
			}
		}
	}
	return 0;
}
unsigned char *minetest_world_manager_sha1_get_digest(minetest_world_manager_sha1_t *sha1)
{
	Uint32 totalBitsL = sha1->size << 3;
	Uint32 totalBitsH = sha1->size >> 29;
	unsigned char footer[64] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	int needed_zeros = 0;
	unsigned char *digest = NULL;
	if(minetest_world_manager_sha1_add_bytes(sha1, "\x80", 1) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to add bytes for SHA1.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	if(sha1->unprocessed_bytes > 56)
		if(minetest_world_manager_sha1_add_bytes(sha1, (char*) footer, 64 - sha1->unprocessed_bytes) == -1)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to add bytes for SHA1.");
			return minetest_world_manager_sha1_get_digest_return(digest);
		}
	if(sha1->unprocessed_bytes > 56)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the digest for SHA1 because 'sha1->unprocessed_bytes' is more than 56.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	needed_zeros = 56 - sha1->unprocessed_bytes;
	if(minetest_world_manager_sha1_store_big_endian_uint32(footer + needed_zeros, totalBitsH) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to store file size (in bits) in big-endian format for SHA1.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	if(minetest_world_manager_sha1_store_big_endian_uint32(footer + needed_zeros + 4, totalBitsL) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to store file size (in bits) in big-endian format for SHA1.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	if(minetest_world_manager_sha1_add_bytes(sha1, (char*) footer, needed_zeros + 8) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to add bytes for SHA1.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	digest = (unsigned char*) malloc(20);
	if(minetest_world_manager_sha1_store_big_endian_uint32(digest, sha1->h0) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to copy the digest bytes for SHA1.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	if(minetest_world_manager_sha1_store_big_endian_uint32(digest + 4, sha1->h1) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to copy the digest bytes for SHA1.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	if(minetest_world_manager_sha1_store_big_endian_uint32(digest + 8, sha1->h2) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to copy the digest bytes for SHA1.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	if(minetest_world_manager_sha1_store_big_endian_uint32(digest + 12, sha1->h3) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to copy the digest bytes for SHA1.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	if(minetest_world_manager_sha1_store_big_endian_uint32(digest + 16, sha1->h4) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to copy the digest bytes for SHA1.");
		return minetest_world_manager_sha1_get_digest_return(digest);
	}
	return digest;
}
int minetest_world_manager_sha1_initialize(minetest_world_manager_sha1_t *sha1)
{
	if(sizeof(Uint32) * 5 != 20)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to initialize SHA1 because the size of Uint32 is not correct.");
		return -1;
	}
	sha1->h0 = 0x67452301;
	sha1->h1 = 0xefcdab89;
	sha1->h2 = 0x98badcfe;
	sha1->h3 = 0x10325476;
	sha1->h4 = 0xc3d2e1f0;
	sha1->unprocessed_bytes = 0;
	sha1->size = 0;
	return 0;
}
