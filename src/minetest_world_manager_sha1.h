/* minetest_world_manager_sha1.h

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
#ifndef minetest_world_manager_sha1_h
#define minetest_world_manager_sha1_h
typedef unsigned int Uint32;
typedef struct
{
	Uint32 h0, h1, h2, h3, h4;
	unsigned char bytes[64];
	int unprocessed_bytes;
	Uint32 size;
} minetest_world_manager_sha1_t;
int minetest_world_manager_sha1_add_bytes(minetest_world_manager_sha1_t *sha1, const char *data, int num);
unsigned char *minetest_world_manager_sha1_get_digest(minetest_world_manager_sha1_t *sha1);
int minetest_world_manager_sha1_initialize(minetest_world_manager_sha1_t *sha1);
#endif
