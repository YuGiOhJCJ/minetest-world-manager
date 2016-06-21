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
#include "minetest_world_manager_password.h" /* for minetest_world_manager_password_get_base64_key */
#include "minetest_world_manager_player.h" /* for minetest_world_manager_player_is_selected */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
#include "minetest_world_manager_sha1.h" /* for minetest_world_manager_sha1_t */
#include "minetest_world_manager_srp.h" /* for minetest_world_manager_srp_create_salted_verification_key */
#include "minetest_world_manager_string.h" /* for minetest_world_manager_string_tolower */
#include "minetest_world_manager_time.h" /* for minetest_world_manager_time_formatted_time_to_long_int */
static int minetest_world_manager_player_is_selected_return(int value, char *base64_key, char *base64_password, char *base64_password_to_check, char *base64_salt, char *base64_srp_key, char *base64_srp_salt, unsigned char *digest, char *digest_encoded, char *name_lower, char *salt, unsigned char *srp_key);
static int minetest_world_manager_player_is_selected_return(int value, char *base64_key, char *base64_password, char *base64_password_to_check, char *base64_salt, char *base64_srp_key, char *base64_srp_salt, unsigned char *digest, char *digest_encoded, char *name_lower, char *salt, unsigned char *srp_key)
{
	if(base64_key != NULL)
	{
		free(base64_key);
		base64_key = NULL;
	}
	if(base64_password != NULL)
	{
		free(base64_password);
		base64_password = NULL;
	}
	if(base64_password_to_check != NULL)
	{
		free(base64_password_to_check);
		base64_password_to_check = NULL;
	}
	if(base64_salt != NULL)
	{
		free(base64_salt);
		base64_salt = NULL;
	}
	if(base64_srp_key != NULL)
	{
		free(base64_srp_key);
		base64_srp_key = NULL;
	}
	if(base64_srp_salt != NULL)
	{
		free(base64_srp_salt);
		base64_srp_salt = NULL;
	}
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
	if(name_lower != NULL)
	{
		free(name_lower);
		name_lower = NULL;
	}
	if(salt != NULL)
	{
		free(salt);
		salt = NULL;
	}
	if(srp_key != NULL)
	{
		free(srp_key);
		srp_key = NULL;
	}
	return value;
}
int minetest_world_manager_player_is_selected(int base64, const char *end_time, const char *name, const char *password, const char *privileges, const char *start_time, const char *time, int unformatted_time, const char *field_name, const char *field_password, const char *field_privileges, const char *field_time)
{
	char *base64_key = NULL;
	char *base64_password = NULL;
	char *base64_password_to_check = NULL;
	char *base64_salt = NULL;
	char *base64_srp_salt = NULL;
	char *base64_srp_key = NULL;
	unsigned char *digest = NULL;
	char *digest_encoded = NULL;
	char *name_lower = NULL;
	char *salt = NULL;
	unsigned char *srp_key = NULL;
	if(name != NULL)
		if(strcmp(name, field_name) != 0)
			return minetest_world_manager_player_is_selected_return(1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
	if(password != NULL)
	{
		if(base64 == -1)
		{
			if(name == NULL)
			{
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to check the password because the provided name is null.");
				return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
			}
			if(minetest_world_manager_password_has_base64_key_and_base64_salt(field_password) == 1)
			{
				minetest_world_manager_sha1_t sha1;
				salt = malloc(sizeof(char) * (strlen(name) + strlen(password) + 1));
				if(salt == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s%s\" salt.", name, password);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				if(sprintf(salt, "%s%s", name, password) < 0)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the \"%s%s\" salt.", name, password);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				if(minetest_world_manager_sha1_initialize(&sha1) == -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to initialize the sha1 structure.");
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				if(minetest_world_manager_sha1_add_bytes(&sha1, salt, strlen(salt)) == -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to add the \"%s\" salt to the sha1 structure.", salt);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				digest = minetest_world_manager_sha1_get_digest(&sha1);
				if(digest == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the digest from the sha1 structure.");
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				digest_encoded = minetest_world_manager_base64_encode(digest, 20);
				if(digest_encoded == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to encode the digest with base64.");
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				if(strcmp(digest_encoded, field_password) != 0)
					return minetest_world_manager_player_is_selected_return(1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
			}
			else
			{
				size_t len_srp_key = 0;
				size_t len_srp_salt = 0;
				unsigned char *srp_salt = NULL;
				name_lower = minetest_world_manager_string_tolower(name);
				if(name_lower == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" name to lower cases.", name);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				base64_salt = minetest_world_manager_password_get_base64_salt(field_password);
				if(base64_salt == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the salt from the \"%s\" password.", field_password);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				base64_key = minetest_world_manager_password_get_base64_key(field_password);
				if(base64_key == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the key from the \"%s\" password.", field_password);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				base64_password = malloc(sizeof(char) * (3 + strlen(base64_salt) + 1 + strlen(base64_key) + 1));
				if(base64_password == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"#1#%s#%s\" password.", base64_salt, base64_key);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				if(sprintf(base64_password, "#1#%s#%s", base64_salt, base64_key) < 0)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the \"#1#%s#%s\" password.", base64_salt, base64_key);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				salt = minetest_world_manager_base64_decode(base64_salt, &len_srp_salt);
				if(salt == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to decode with base64 the \"%s\" salt.", base64_salt);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				srp_salt = (unsigned char *) salt;
				if(minetest_world_manager_srp_create_salted_verification_key(name_lower, (const unsigned char *) password, strlen(password), &srp_salt, &len_srp_salt, &srp_key, &len_srp_key) == -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the salt and the key.");
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				if(srp_salt == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the salt.");
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				base64_srp_salt = minetest_world_manager_base64_encode(srp_salt, len_srp_salt);
				if(base64_srp_salt == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to encode with base64 the salt.");
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				if(srp_key == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the key.");
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				base64_srp_key = minetest_world_manager_base64_encode(srp_key, len_srp_key);
				if(base64_srp_key == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to encode with base64 the key.");
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				base64_password_to_check = malloc(sizeof(char) * (3 + strlen(base64_srp_salt) + 1 + strlen(base64_srp_key) + 1));
				if(base64_password_to_check == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the password to check.");
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				if(sprintf(base64_password_to_check, "#1#%s#%s", base64_srp_salt, base64_srp_key) < 0)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to create the \"#1#%s#%s\" password to check.", base64_srp_salt, base64_srp_key);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
				if(strcmp(base64_password, base64_password_to_check) != 0)
				{
					return minetest_world_manager_player_is_selected_return(1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
			}
		}
		else
			if(strcmp(password, field_password) != 0)
				return minetest_world_manager_player_is_selected_return(1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
	}
	if(privileges != NULL)
		if(strcmp(privileges, field_privileges) != 0)
			return minetest_world_manager_player_is_selected_return(1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
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
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
			}
			else
			{
				if(minetest_world_manager_time_formatted_time_to_long_int(start_time, &start_time_number) == -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" start time to a long integer.", start_time);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
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
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
			}
			else
			{
				if(minetest_world_manager_time_formatted_time_to_long_int(end_time, &end_time_number) == -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" end time to a long integer.", end_time);
					return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
				}
			}
		}
		errno = 0;
		field_time_number = strtol(field_time, &endptr, 10);
		if(errno != 0 || *endptr != '\0')
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert \"%s\" to a long integer.", field_time);
			return minetest_world_manager_player_is_selected_return(-1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
		}
		if(start_time_number > field_time_number || end_time_number < field_time_number)
			return minetest_world_manager_player_is_selected_return(1, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
	}
	return minetest_world_manager_player_is_selected_return(0, base64_key, base64_password, base64_password_to_check, base64_salt, base64_srp_key, base64_srp_salt, digest, digest_encoded, name_lower, salt, srp_key);
}
