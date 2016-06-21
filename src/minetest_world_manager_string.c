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
#include <ctype.h> /* for tolower */
#include <stdlib.h> /* for NULL */
#include <string.h> /* for strlen */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
#include "minetest_world_manager_string.h" /* for minetest_world_manager_string_get_field */
char *minetest_world_manager_string_get_field(const char *string, int field_number, char delim)
{
	char *field = NULL;
	int field_current_number = 1;
	int pos_start = 0;
	int pos_current = 0;
	int pos_end = 0;
	int index = 0;
	int field_size = 0;
	while(field_current_number < field_number)
	{
		if(string[pos_current] == delim)
			field_current_number++;
		if(string[pos_current] == '\0')
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to find the field number \"%d\" in the \"%s\" string.", field_number, string);
			return NULL;
		}
		pos_current++;
	}
	pos_start = pos_current;
	while(1)
	{
		if(string[pos_current] == delim)
		{
			pos_current--;
			break;
		}
		if(string[pos_current] == '\0')
			break;
		pos_current++;
	}
	pos_end = pos_current;
	if(string[pos_start] != delim && string[pos_end] != delim)
		field_size = pos_end - pos_start + 1;
	field = malloc(sizeof(char) * (field_size + 1));
	if(field == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the field number \"%d\" of the \"%s\" string.", field_number, string);
		return NULL;
	}
	if(string[pos_start] != delim && string[pos_end] != delim)
	{
		pos_current = pos_start;
		while(pos_current <= pos_end)
		{
			field[index] = string[pos_current];
			pos_current++;
			index++;
		}
	}
	field[index] = '\0';
	return field;
}
const char *minetest_world_manager_string_plural(const char *word_singular, const char *word_plural, int number)
{
	if(number == 1)
		return word_singular;
	else
		return word_plural;
}
char *minetest_world_manager_string_tolower(const char *string)
{
	int index = 0;
	int len = 0;
	char *result = NULL;
	len = strlen(string);
	result = malloc(sizeof(char) * (len + 1));
	if(result == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the string containing lower case letters.");
		return NULL;
	}
	for(; index < len; index++)
		result[index] = tolower(string[index]);
	result[len] = '\0';
	return result;
}
