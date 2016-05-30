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
#include <stdio.h> /* for FILE */
#include <stdlib.h> /* for realloc */
#include <string.h> /* for strlen */
#include "minetest_world_manager_file.h" /* for minetest_world_manager_file_read_line */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
char *minetest_world_manager_file_read_line(FILE *file)
{
	int line_size = 0;
	char *line = NULL;
	int character = 0;
	while(1)
	{
		line_size++;
		line = realloc(line, sizeof(char) * (line_size + 1));
		if(line == NULL)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the line.");
			return NULL;
		}
		character = fgetc(file);
		if(character == EOF && ferror(file))
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to read a character from a file.");
			return NULL;
		}
		if(character == '\n' || character == EOF)
			break;
		line[line_size - 1] = character;
	}
	line[line_size - 1] = '\0';
	return line;
}
int minetest_world_manager_file_remove_player_file(const char *world_path, const char *name)
{
	char *player_file_path = NULL;
	player_file_path = malloc(sizeof(char) * (strlen(world_path) + 1 + 7 + 1 + strlen(name) + 1));
	if(player_file_path == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s/players/%s\" player file path.", world_path, name);
		return -1;
	}
	if(sprintf(player_file_path, "%s/players/%s", world_path, name) < 0)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the \"%s/players/%s\" player file path.", world_path, name);
		free(player_file_path);
		return -1;
	}
	if(remove(player_file_path) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to remove the \"%s\" player file.", player_file_path);
		free(player_file_path);
		return -1;
	}
	free(player_file_path);
	return 0;
}
int minetest_world_manager_file_write_line(FILE *file, const char *line)
{
	int index = 0;
	int line_size = strlen(line);
	while(index < line_size)
	{
		if(fputc(line[index], file) == EOF)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to write the \"%c\" character of the \"%s\" line to a file.", line[index], line);
			return -1;
		}
		index++;
	}
	if(fputc('\n', file) == EOF)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to write the \"\\n\" character to a file.");
		return -1;
	}
	return 0;
}
