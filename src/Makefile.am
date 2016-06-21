# Minetest World Manager: Manage Minetest worlds.
# Copyright (C) 2016  YuGiOhJCJ
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
bin_PROGRAMS = minetest-world-manager
minetest_world_manager_SOURCES = minetest_world_manager_main.c minetest_world_manager_base64.c minetest_world_manager_file.c minetest_world_manager_password.c minetest_world_manager_player.c minetest_world_manager_print.c minetest_world_manager_sha1.c minetest_world_manager_srp.c minetest_world_manager_string.c minetest_world_manager_time.c minetest_world_manager_world.c
minetest_world_manager_CFLAGS = @MAINTAINER_CFLAGS@
minetest_world_manager_LDFLAGS = -lgmp -lcrypto
