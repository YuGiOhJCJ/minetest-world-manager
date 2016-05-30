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
#include <getopt.h> /* for option */
#include <stdio.h> /* for printf */
#include <stdlib.h> /* for exit */
#include <string.h> /* for strlen */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_help */
#include "minetest_world_manager_string.h" /* for minetest_world_manager_string_plural */
#include "minetest_world_manager_world.h" /* for minetest_world_manager_world_manage */
typedef struct
{
	char *name;
	char *end_time;
	char *password;
	char *privileges;
	char *start_time;
	char *time;
} minetest_world_manager_main_variables_t;
static void minetest_world_manager_main_exit(int status, minetest_world_manager_main_variables_t *variables)
{
	if(variables->name != NULL)
	{
		free(variables->name);
		variables->name = NULL;
	}
	if(variables->end_time != NULL)
	{
		free(variables->end_time);
		variables->end_time = NULL;
	}
	if(variables->password != NULL)
	{
		free(variables->password);
		variables->password = NULL;
	}
	if(variables->privileges != NULL)
	{
		free(variables->privileges);
		variables->privileges = NULL;
	}
	if(variables->start_time != NULL)
	{
		free(variables->start_time);
		variables->start_time = NULL;
	}
	if(variables->time != NULL)
	{
		free(variables->time);
		variables->time = NULL;
	}
	exit(status);
}
static void minetest_world_manager_main_variables_initialize(minetest_world_manager_main_variables_t *variables)
{
	variables->name = NULL;
	variables->end_time = NULL;
	variables->password = NULL;
	variables->privileges = NULL;
	variables->start_time = NULL;
	variables->time = NULL;
}
int main(int argc, char **argv)
{
	int opt = '\0';
	int counter_managed = 0;
	const char *word_world[] = {"world", "worlds"};
	const char *word_have[] = {"has", "have"};
	const char *word_player[] = {"player", "players"};
	const struct option longopts[] =
	{
		{"base64-password",  no_argument,       NULL, 'b'},
		{"display-players",  no_argument,       NULL, 'd'},
		{"end-time",         required_argument, NULL, 'e'},
		{"help",             no_argument,       NULL, 'h'},
		{"name",             required_argument, NULL, 'n'},
		{"password",         required_argument, NULL, 'p'},
		{"privileges",       required_argument, NULL, 'q'},
		{"remove-players",   no_argument,       NULL, 'r'},
		{"start-time",       required_argument, NULL, 's'},
		{"time",             required_argument, NULL, 't'},
		{"unformatted-time", required_argument, NULL, '1'},
		{"version",          no_argument,       NULL, 'v'},
		{0,                  0,                 0,    0}
	};
	int base64 = -1;
	int display_players = -1;
	int remove_players = -1;
	int unformatted_time = -1;
	int counter_removed = 0;
	int counter_displayed = 0;
	minetest_world_manager_main_variables_t variables;
	minetest_world_manager_main_variables_initialize(&variables);
	minetest_world_manager_print_initialize(PACKAGE_BUGREPORT, "YuGiOhJCJ", PACKAGE_URL, argv[0], PACKAGE_NAME, PACKAGE_VERSION);
	opterr = 0;
	while((opt = getopt_long(argc, argv, "bde:hn:p:q:rs:t:uv", longopts, NULL)) != -1)
	{
		switch(opt)
		{
			case 'b':
				if(base64 != -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -b option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				base64 = 0;
				break;
			case 'd':
				if(display_players != -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -d option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				display_players = 0;
				break;
			case 'e':
				if(variables.end_time != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -e option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				if(variables.time != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -e option cannot be used with the -t option.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				variables.end_time = realloc(variables.end_time, sizeof(char) * (strlen(optarg) + 1));
				if(variables.end_time == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s\" option argument.", optarg);
					minetest_world_manager_main_exit(EXIT_SUCCESS, &variables);
				}
				strcpy(variables.end_time, optarg);
				break;
			case 'h':
				minetest_world_manager_print_help();
				minetest_world_manager_main_exit(EXIT_SUCCESS, &variables);
			case 'n':
				if(variables.name != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -n option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				variables.name = realloc(variables.name, sizeof(char) * (strlen(optarg) + 1));
				if(variables.name == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s\" option argument.", optarg);
					minetest_world_manager_main_exit(EXIT_SUCCESS, &variables);
				}
				strcpy(variables.name, optarg);
				break;
			case 'p':
				if(variables.password != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -p option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				variables.password = realloc(variables.password, sizeof(char) * (strlen(optarg) + 1));
				if(variables.password == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s\" option argument.", optarg);
					minetest_world_manager_main_exit(EXIT_SUCCESS, &variables);
				}
				strcpy(variables.password, optarg);
				break;
			case 'q':
				if(variables.privileges != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -q option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				variables.privileges = realloc(variables.privileges, sizeof(char) * (strlen(optarg) + 1));
				if(variables.privileges == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s\" option argument.", optarg);
					minetest_world_manager_main_exit(EXIT_SUCCESS, &variables);
				}
				strcpy(variables.privileges, optarg);
				break;
			case 'r':
				if(remove_players != -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -r option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				remove_players = 0;
				break;
			case 's':
				if(variables.start_time != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -s option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				if(variables.time != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -s option cannot be used with the -t option.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				variables.start_time = realloc(variables.start_time, sizeof(char) * (strlen(optarg) + 1));
				if(variables.start_time == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s\" option argument.", optarg);
					minetest_world_manager_main_exit(EXIT_SUCCESS, &variables);
				}
				strcpy(variables.start_time, optarg);
				break;
			case 't':
				if(variables.time != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -t option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				if(variables.end_time != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -t option cannot be used with the -e option.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				if(variables.start_time != NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -t option cannot be used with the -s option.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				variables.time = realloc(variables.time, sizeof(char) * (strlen(optarg) + 1));
				if(variables.time == NULL)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to allocate memory for the \"%s\" option argument.", optarg);
					minetest_world_manager_main_exit(EXIT_SUCCESS, &variables);
				}
				strcpy(variables.time, optarg);
				break;
			case 'u':
				if(unformatted_time != -1)
				{
					minetest_world_manager_print_error(__FILE__, __LINE__, "The -u option cannot be used several times.");
					minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
				}
				unformatted_time = 0;
				break;
			case 'v':
				minetest_world_manager_print_version();
				minetest_world_manager_main_exit(EXIT_SUCCESS, &variables);
			default:
				minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to recognize the '%s' option.", argv[optind - 1]);
				minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
		}
	}
	counter_managed = argc - optind;
	while(optind < argc)
	{
		int counter = -1;
		counter = minetest_world_manager_world_manage(argv[optind], base64, display_players, variables.end_time, variables.name, variables.password, variables.privileges, remove_players, variables.start_time, variables.time, unformatted_time);
		if(counter == -1)
		{
			minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to manage the Minetest world located at \"%s\".", argv[optind]);
			minetest_world_manager_main_exit(EXIT_FAILURE, &variables);
		}
		if(display_players == 0)
			counter_displayed += counter;
		if(remove_players == 0)
			counter_removed += counter;
		optind++;
	}
	printf("%d %s %s been displayed.\n", counter_displayed, minetest_world_manager_string_plural(word_player[0], word_player[1], counter_displayed), minetest_world_manager_string_plural(word_have[0], word_have[1], counter_displayed));
	printf("%d %s %s been removed.\n", counter_removed, minetest_world_manager_string_plural(word_player[0], word_player[1], counter_removed), minetest_world_manager_string_plural(word_have[0], word_have[1], counter_removed));
	printf("%d Minetest %s %s been managed.\n", counter_managed, minetest_world_manager_string_plural(word_world[0], word_world[1], counter_managed), minetest_world_manager_string_plural(word_have[0], word_have[1], counter_managed));
	minetest_world_manager_main_exit(EXIT_SUCCESS, &variables);
	return EXIT_SUCCESS;
}
