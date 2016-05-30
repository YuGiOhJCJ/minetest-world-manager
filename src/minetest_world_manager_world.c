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
#include <errno.h> /* for errno */
#include <stdio.h> /* for printf */
#include <stdlib.h> /* for free */
#include <string.h> /* for strlen */
#include <time.h> /* for localtime */
#include "minetest_world_manager_file.h" /* for minetest_world_manager_file_read_line */
#include "minetest_world_manager_player.h" /* for minetest_world_manager_player_is_selected */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
#include "minetest_world_manager_string.h" /* for minetest_world_manager_string_get_field */
static int minetest_world_manager_world_manage_return(int value, char *file_path, char *file_path_new, FILE *file, FILE *file_new, char *line, char *field_name, char *field_password, char *field_privileges, char *field_time)
{
	if(file_path != NULL)
	{
		free(file_path);
		file_path = NULL;
	}
	if(file_path_new != NULL)
	{
		free(file_path_new);
		file_path_new = NULL;
	}
	if(file != NULL)
	{
		fclose(file);
		file = NULL;
	}
	if(file_new != NULL)
	{
		fclose(file_new);
		file_new = NULL;
	}
	if(line != NULL)
	{
		free(line);
		line = NULL;
	}
	if(field_name != NULL)
	{
		free(field_name);
		field_name = NULL;
	}
	if(field_password != NULL)
	{
		free(field_password);
		field_password = NULL;
	}
	if(field_privileges != NULL)
	{
		free(field_privileges);
		field_privileges = NULL;
	}
	if(field_time != NULL)
	{
		free(field_time);
		field_time = NULL;
	}
	return value;
}
int minetest_world_manager_world_manage(const char *world_path, int base64, int display_players, const char *end_time, const char *name, const char *password, const char *privileges, int remove_players, const char *start_time, const char *time, int unformatted_time)
{
	char *file_path = NULL;
	char *file_path_new = NULL;
	const char *file_name = "auth.txt";
	FILE *file = NULL;
	FILE *file_new = NULL;
	char *line = NULL;
	char *field_name = NULL;
	char *field_password = NULL;
	char *field_privileges = NULL;
	char *field_time = NULL;
	int counter = 0;
	time_t field_time_number = 0;
	struct tm *time_structure = NULL;
	file_path = malloc(sizeof(char) * (strlen(world_path) + 1 + strlen(file_name) + 1));
	if(file_path == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s/%s\" file path.", world_path, file_name);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	if(sprintf(file_path, "%s/%s", world_path, file_name) < 0)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the \"%s/%s\" file path.", world_path, file_name);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	file = fopen(file_path, "r");
	if(file == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to open the \"%s\" file for reading.", file_path);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	file_path_new = malloc(sizeof(char) * (strlen(world_path) + 1 + strlen(file_name) + 4 + 1));
	if(file_path_new == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s/%s.new\" file path.", world_path, file_name);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	if(sprintf(file_path_new, "%s/%s.new", world_path, file_name) < 0)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the \"%s/%s.new\" file path.", world_path, file_name);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	file_new = fopen(file_path_new, "w");
	if(file_new == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to open the \"%s\" file for writing.", file_path_new);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	while(1)
	{
		int result = -1;
		char *endptr = NULL;
		line = minetest_world_manager_file_read_line(file);
		if(line == NULL)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to read a line from the \"%s\" file.", file_path);
			return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
		}
		if(strlen(line) == 0)
		{
			free(line);
			line = NULL;
			break;
		}
		field_name = minetest_world_manager_string_get_field(line, 1);
		if(field_name == NULL)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the name from the \"%s\" line of the \"%s\" file.", line, file_path);
			return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
		}
		field_password = minetest_world_manager_string_get_field(line, 2);
		if(field_password == NULL)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the password from the \"%s\" line of the \"%s\" file.", line, file_path);
			return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
		}
		field_privileges = minetest_world_manager_string_get_field(line, 3);
		if(field_privileges == NULL)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the privileges from the \"%s\" line of the \"%s\" file.", line, file_path);
			return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
		}
		field_time = minetest_world_manager_string_get_field(line, 4);
		if(field_time == NULL)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the time from the \"%s\" line of the \"%s\" file.", line, file_path);
			return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
		}
		errno = 0;
		field_time_number = strtol(field_time, &endptr, 10);
		if(errno != 0 || *endptr != '\0')
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" time to a long integer for the Minetest world located at \"%s\".", field_time, world_path);
			return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
		}
		time_structure = localtime(&field_time_number);
		if(time_structure == NULL)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" time to a structure for the Minetest world located at \"%s\".", field_time, world_path);
			return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
		}
		result = minetest_world_manager_player_is_selected(base64, end_time, name, password, privileges, start_time, time, unformatted_time, field_name, field_password, field_privileges, field_time);
		if(result == -1)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to check if the player is selected for the Minetest world located at \"%s\".", world_path);
			return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
		}
		if(result == 0)
		{
			counter++;
			if(display_players == 0)
			{
				printf("%d. \n", counter);
				printf("\t* Name: \"%s\"\n", field_name);
				printf("\t* Password: \"%s\"\n", field_password);
				printf("\t* Privileges: \"%s\"\n", field_privileges);
				printf("\t* Last login time: \"%s\" (%04d-%02d-%02dT%02d:%02d:%02dZ)\n", field_time, 1900 + time_structure->tm_year, 1 + time_structure->tm_mon, time_structure->tm_mday, time_structure->tm_hour, time_structure->tm_min, time_structure->tm_sec);
			}
			if(remove_players == 0)
			{
				if(minetest_world_manager_file_remove_player_file(world_path, field_name) == -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to remove the player file for the \"%s\" player in the Minetest world located at \"%s\".", field_name, world_path);
					return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
				}
			}
		}
		if(result == 1 || remove_players == -1)
		{
			if(minetest_world_manager_file_write_line(file_new, line) == -1)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to write the \"%s\" line to the \"%s\" file.", line, file_path_new);
				return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
			}
		}
		free(field_name);
		field_name = NULL;
		free(field_password);
		field_password = NULL;
		free(field_privileges);
		field_privileges = NULL;
		free(field_time);
		field_time = NULL;
		free(line);
		line = NULL;
	}
	if(fclose(file) != 0)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to close the \"%s\" file.", file_path);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	file = NULL;
	if(fclose(file_new) != 0)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to close the \"%s\" file.", file_path_new);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	file_new = NULL;
	if(remove(file_path) == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to remove the \"%s\" file.", file_path);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	if(rename(file_path_new, file_path))
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to rename the \"%s\" file to \"%s\".", file_path_new, file_path);
		return minetest_world_manager_world_manage_return(-1, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
	}
	return minetest_world_manager_world_manage_return(counter, file_path, file_path_new, file, file_new, line, field_name, field_password, field_privileges, field_time);
}
