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
#include <string.h> /* for strlen */
#include "minetest_world_manager_password.h" /* for minetest_world_manager_password_get_base64_key */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
#include "minetest_world_manager_string.h" /* for minetest_world_manager_string_get_field */
char *minetest_world_manager_password_get_base64_key(const char *password)
{
	char *key = minetest_world_manager_string_get_field(password, 4, '#');
	if(key == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the key from the \"%s\" password.", password);
		return NULL;
	}
	return key;
}
char *minetest_world_manager_password_get_base64_salt(const char *password)
{
	char *salt = minetest_world_manager_string_get_field(password, 3, '#');
	if(salt == NULL)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to get the salt from the \"%s\" password.", password);
		return NULL;
	}
	return salt;
}
int minetest_world_manager_password_has_base64_key_and_base64_salt(const char *password)
{
	if(strlen(password) < 3)
		return 1;
	if(password[0] != '#' || password[1] != '1' || password[2] != '#')
		return 1;
	return 0;
}
