/*
 Minetest World Manager: Manage Minetest worlds.
 Copyright (C) 2016  YuGiOhJCJ

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdarg.h> /* for va_list */
#include <stdio.h> /* for fprintf */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
static const char *minetest_world_manager_print_author_mail = NULL;
static const char *minetest_world_manager_print_author_name = NULL;
static const char *minetest_world_manager_print_author_url = NULL;
static const char *minetest_world_manager_print_program_filename = NULL;
static const char *minetest_world_manager_print_program_name = NULL;
static const char *minetest_world_manager_print_program_version = NULL;
void minetest_world_manager_print_error(const char *file, int line, const char *format, ...)
{
	va_list args;
#ifdef MAINTAINER_VERSION
	fprintf(stderr, "%s:%s:%d: ", minetest_world_manager_print_program_filename, file, line);
#else
	fprintf(stderr, "%s: ", minetest_world_manager_print_program_filename);
#endif
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	fprintf(stderr, "\n");
}
void minetest_world_manager_print_help()
{
	printf("Usage: %s [OPTION]... [DIRECTORY]...\n", minetest_world_manager_print_program_filename);
	printf("Manage the Minetest worlds located at DIRECTORY(ies).\n");
	printf("\n");
	printf("Options:\n");
	printf("\t-b, --base64-password\n");
	printf("\t\tset PASSWORD as an encrypted password encoded with base64 instead of a raw password\n");
	printf("\t-d, --display-players\n");
	printf("\t\tdisplay the selected player(s)\n");
	printf("\t-e, --end-time=END-TIME\n");
	printf("\t\tselect player(s) with a last login time less than or equal to END-TIME\n");
	printf("\t-h, --help\n");
	printf("\t\tdisplay this help and exit\n");
	printf("\t-n, --name=NAME\n");
	printf("\t\tselect player(s) with a name equal to NAME\n");
	printf("\t-p, --password=PASSWORD\n");
	printf("\t\tselect player(s) with a password equal to PASSWORD\n");
	printf("\t-q, --privileges=PRIVILEGES\n");
	printf("\t\tselect player(s) with privileges equal to PRIVILEGES\n");
	printf("\t-r, --remove-players\n");
	printf("\t\tremove the selected player(s)\n");
	printf("\t-s, --start-time=START-TIME\n");
	printf("\t\tselect player(s) with a last login time greater than or equal to START-TIME\n");
	printf("\t-t, --time=TIME\n");
	printf("\t\tselect player(s) with a last login time equal to TIME\n");
	printf("\t-u, --unformatted-time\n");
	printf("\t\tset END-TIME, TIME and START-TIME as seconds since 1970-01-01T00:00:00Z instead of a formatted time (YYYY-MM-DDThh:mm:ddZ)\n");
	printf("\t-v, --version\n");
	printf("\t\toutput version information and exit\n");
	printf("\n");
	printf("Examples:\n");
	printf("\t%s -d ~/.minetest/worlds/myworld\n", minetest_world_manager_print_program_filename);
	printf("\t\tdisplay all the players in the specified world\n");
	printf("\t%s -dr ~/.minetest/worlds/myfirstworld ~/.minetest/worlds/mysecondworld\n", minetest_world_manager_print_program_filename);
	printf("\t\tdisplay and remove all the players in the specified worlds\n");
	printf("\t%s -dn MyName -p MyPassword -q shout,interact -t 2016-06-21T17:53:33Z ~/.minetest/worlds/myworld\n", minetest_world_manager_print_program_filename);
	printf("\t\tdisplay the player(s) having the specified name, raw password, privileges and formatted last login time in the specified world\n");
	printf("\t%s -dbun MyName -p \"#1#F/pzuCHU2mNqcEfQMWGPpw#Viqzle5l/EguzI8NqwrUNgAd0S008rCZv7E//ekeWG726FN1V4SZClEgwUK+lVBW3cTesEIUhPutycVwMh5LwjCOc/tcON4rVzjNFM37wHHj8qD/BWhSJuTWuJ16vNeVkLo5FfVCK4yHkf2HlIBrb5F3J6xi2sxn4AB482XpXceoEYujneb7z+iwsCJt/QJhLYqslYBEQ4kNYUeQDH8W/ldk/f5EonQ876dn7PwxDZigDzdjYAH+z0X2Yz25K2HL/NrVox7WNgjiuHuR0scxZECEy9+n4GqZyqJyYzk/Qv6C/1HxGqJXeuet0RtcCpAOiwY3NE96rf3BgNejB2UOZw\" -q shout,interact -t 1466524413 ~/.minetest/worlds/myworld\n", minetest_world_manager_print_program_filename);
	printf("\t\tdisplay the player(s) having the specified name, encrypted and encoded password, privileges and unformatted last login time in the specified world\n");
	printf("\t%s -rs 2016-06-21T00:00:00Z -e 2016-06-21T23:59:59Z ~/.minetest/worlds/myworld\n", minetest_world_manager_print_program_filename);
	printf("\t\tremove the players(s) having the last login time between the two specified formatted times in the specified world\n");
	printf("\n");
	printf("Report bugs to %s <%s> %s.\n", minetest_world_manager_print_author_name, minetest_world_manager_print_author_mail, minetest_world_manager_print_author_url);
}
void minetest_world_manager_print_initialize(const char *author_mail, const char *author_name, const char *author_url, const char *program_filename, const char *program_name, const char *program_version)
{
	minetest_world_manager_print_author_mail = author_mail;
	minetest_world_manager_print_author_name = author_name;
	minetest_world_manager_print_author_url = author_url;
	minetest_world_manager_print_program_filename = program_filename;
	minetest_world_manager_print_program_name = program_name;
	minetest_world_manager_print_program_version = program_version;
}
void minetest_world_manager_print_version()
{
	printf("%s %s\n", minetest_world_manager_print_program_name, minetest_world_manager_print_program_version);
	printf("\n");
	printf("Copyright (C) 2016 %s.\n", minetest_world_manager_print_author_name);
	printf("This is free software; see the source for copying conditions.\n");
	printf("There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
	printf("\n");
	printf("Written by %s <%s> %s.\n", minetest_world_manager_print_author_name, minetest_world_manager_print_author_mail, minetest_world_manager_print_author_url);
}
