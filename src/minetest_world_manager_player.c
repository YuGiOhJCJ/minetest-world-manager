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
#include <limits.h> /* for LONG_MAX */
#include <stdio.h> /* for sprintf */
#include <stdlib.h> /* for malloc */
#include <string.h> /* for strlen */
#include "minetest_world_manager_base64.h" /* for minetest_world_manager_base64_encode */
#include "minetest_world_manager_player.h" /* for minetest_world_manager_player_is_selected */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
#include "minetest_world_manager_sha1.h" /* for minetest_world_manager_sha1_t */
#include "minetest_world_manager_time.h" /* for minetest_world_manager_time_formatted_time_to_long_int */
static int minetest_world_manager_player_is_selected_return(int value, unsigned char *digest, char *digest_encoded, char *salt)
{
	if(digest != NULL)
	{
		free(digest);
		digest = NULL;
	}
	if(digest_encoded != NULL)
	{
		free(digest_encoded);
		digest_encoded = NULL;
	}
	if(salt != NULL)
	{
		free(salt);
		salt = NULL;
	}
	return value;
}
int minetest_world_manager_player_is_selected(int base64, const char *end_time, const char *name, const char *password, const char *privileges, const char *start_time, const char *time, int unformatted_time, const char *field_name, const char *field_password, const char *field_privileges, const char *field_time)
{
	unsigned char *digest = NULL;
	char *digest_encoded = NULL;
	char *salt = NULL;
	if(name != NULL)
		if(strcmp(name, field_name) != 0)
			return minetest_world_manager_player_is_selected_return(1, digest, digest_encoded, salt);
	if(password != NULL)
	{
		if(base64 == -1)
		{
			minetest_world_manager_sha1_t sha1;
			if(name == NULL)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to encrypt the password because the name is not provided.");
				return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
			}
			salt = malloc(sizeof(char) * (strlen(name) + strlen(password) + 1));
			if(salt == NULL)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s%s\" salt.", name, password);
				return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
			}
			if(sprintf(salt, "%s%s", name, password) < 0)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the \"%s%s\" salt.", name, password);
				return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
			}
			if(minetest_world_manager_sha1_initialize(&sha1) == -1)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to initialize the sha1 structure.");
				return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
			}
			if(minetest_world_manager_sha1_add_bytes(&sha1, salt, strlen(salt)) == -1)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to add the \"%s\" salt to the sha1 structure.", salt);
				return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
			}
			digest = minetest_world_manager_sha1_get_digest(&sha1);
			if(digest == NULL)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the digest from the sha1 structure.");
				return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
			}
			digest_encoded = minetest_world_manager_base64_encode(digest, 20);
			if(digest_encoded == NULL)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to encode the digest with base64.");
				return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
			}
			if(strcmp(digest_encoded, field_password) != 0)
				return minetest_world_manager_player_is_selected_return(1, digest, digest_encoded, salt);
		}
		else
			if(strcmp(password, field_password) != 0)
				return minetest_world_manager_player_is_selected_return(1, digest, digest_encoded, salt);
	}
	if(privileges != NULL)
		if(strcmp(privileges, field_privileges) != 0)
			return minetest_world_manager_player_is_selected_return(1, digest, digest_encoded, salt);
	if(time != NULL)
	{
		start_time = time;
		end_time = time;
	}
	if(start_time != NULL || end_time != NULL)
	{
		long int field_time_number = 0;
		long int start_time_number = 0;
		long int end_time_number = 0;
		char *endptr = NULL;
		if(start_time == NULL)
			start_time_number = 0;
		else
		{
			if(unformatted_time == 0)
			{
				errno = 0;
				start_time_number = strtol(start_time, &endptr, 10);
				if(errno != 0 || *endptr != '\0')
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" start time to a long integer.", start_time);
					return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
				}
			}
			else
			{
				if(minetest_world_manager_time_formatted_time_to_long_int(start_time, &start_time_number) == -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" start time to a long integer.", start_time);
					return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
				}
			}
		}
		if(end_time == NULL)
			end_time_number = LONG_MAX;
		else
		{
			if(unformatted_time == 0)
			{
				errno = 0;
				end_time_number = strtol(end_time, &endptr, 10);
				if(errno != 0 || *endptr != '\0')
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" end time to a long integer.", end_time);
					return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
				}
			}
			else
			{
				if(minetest_world_manager_time_formatted_time_to_long_int(end_time, &end_time_number) == -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" end time to a long integer.", end_time);
					return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
				}
			}
		}
		errno = 0;
		field_time_number = strtol(field_time, &endptr, 10);
		if(errno != 0 || *endptr != '\0')
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert \"%s\" to a long integer.", field_time);
			return minetest_world_manager_player_is_selected_return(-1, digest, digest_encoded, salt);
		}
		if(start_time_number > field_time_number || end_time_number < field_time_number)
			return minetest_world_manager_player_is_selected_return(1, digest, digest_encoded, salt);
	}
	return minetest_world_manager_player_is_selected_return(0, digest, digest_encoded, salt);
}
