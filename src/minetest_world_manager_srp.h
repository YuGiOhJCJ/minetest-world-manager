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
#ifndef minetest_world_manager_srp_h
#define minetest_world_manager_srp_h
int minetest_world_manager_srp_create_salted_verification_key(const char *username_for_verifier, const unsigned char *password, size_t len_password, unsigned char **bytes_s, size_t *len_s, unsigned char **bytes_v, size_t *len_v);
#endif
