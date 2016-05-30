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
#ifndef minetest_world_manager_file_h
#define minetest_world_manager_file_h
char *minetest_world_manager_file_read_line(FILE *file);
int minetest_world_manager_file_remove_player_file(const char *world_path, const char *name);
int minetest_world_manager_file_write_line(FILE *file, const char *line);
#endif
