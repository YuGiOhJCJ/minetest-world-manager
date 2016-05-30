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
#include <stdlib.h> /* for strtol */
#include <string.h> /* for strlen */
#include <time.h> /* for tm */
#include "minetest_world_manager_print.h" /* for minetest_world_manager_print_error */
#include "minetest_world_manager_time.h" /* for minetest_world_manager_time_formatted_time_to_long_int */
int minetest_world_manager_time_formatted_time_to_long_int(const char *formatted_time, long int *time_number)
{
	struct tm time_structure;
	char year[5] = {'\0'};
	char month[3] = {'\0'};
	char day[3] = {'\0'};
	char hour[3] = {'\0'};
	char minute[3] = {'\0'};
	char second[3] = {'\0'};
	long int year_number = 0;
	long int month_number = 0;
	long int day_number = 0;
	long int hour_number = 0;
	long int minute_number = 0;
	long int second_number = 0;
	char *endptr = NULL;
	if(strlen(formatted_time) != 20)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "The \"%s\" time length is not equal to 20.", formatted_time);
		return -1;
	}
	year[0] = formatted_time[0];
	year[1] = formatted_time[1];
	year[2] = formatted_time[2];
	year[3] = formatted_time[3];
	month[0] = formatted_time[5];
	month[1] = formatted_time[6];
	day[0] = formatted_time[8];
	day[1] = formatted_time[9];
	hour[0] = formatted_time[11];
	hour[1] = formatted_time[12];
	minute[0] = formatted_time[14];
	minute[1] = formatted_time[15];
	second[0] = formatted_time[17];
	second[1] = formatted_time[18];
	errno = 0;
	year_number = strtol(year, &endptr, 10);
	if(errno != 0 || *endptr != '\0')
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" year to a long integer.", year);
		return -1;
	}
	errno = 0;
	month_number = strtol(month, &endptr, 10);
	if(errno != 0 || *endptr != '\0')
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" month to a long integer.", month);
		return -1;
	}
	errno = 0;
	day_number = strtol(day, &endptr, 10);
	if(errno != 0 || *endptr != '\0')
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" day to a long integer.", day);
		return -1;
	}
	errno = 0;
	hour_number = strtol(hour, &endptr, 10);
	if(errno != 0 || *endptr != '\0')
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" hour to a long integer.", hour);
		return -1;
	}
	errno = 0;
	minute_number = strtol(minute, &endptr, 10);
	if(errno != 0 || *endptr != '\0')
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" minute to a long integer.", minute);
		return -1;
	}
	errno = 0;
	second_number = strtol(second, &endptr, 10);
	if(errno != 0 || *endptr != '\0')
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" second to a long integer.", second);
		return -1;
	}
	time_structure.tm_year = year_number - 1900;
	time_structure.tm_mon = month_number - 1;
	time_structure.tm_mday = day_number;
	time_structure.tm_hour = hour_number;
	time_structure.tm_min = minute_number;
	time_structure.tm_sec = second_number;
	time_structure.tm_isdst = -1;
	*time_number = mktime(&time_structure);
	if(*time_number == -1)
	{
		minetest_world_manager_print_error(__FILE__, __LINE__, "Unable to convert the \"%s\" time to a long integer.", formatted_time);
		return -1;
	}
	return 0;
}
