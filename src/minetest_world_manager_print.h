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
#ifndef minetest_world_manager_print_h
#define minetest_world_manager_print_h
void minetest_world_manager_print_error(const char *file, int line, const char *format, ...);
void minetest_world_manager_print_help();
void minetest_world_manager_print_initialize(const char *author_mail, const char *author_name, const char *author_url, const char *program_filename, const char *program_name, const char *program_version);
void minetest_world_manager_print_version();
#endif
