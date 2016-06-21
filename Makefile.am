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
SUBDIRS = src
dist_doc_DATA = AUTHORS ChangeLog COPYING INSTALL NEWS README TODO
.PHONY: edit
edit:
	gvim -p `find . -name *.c -o -name *.h -o -name Makefile.am -o -name configure.ac | sort` $(dist_doc_DATA)
maintainer-clean-local:
	rm -rfv aclocal.m4 compile configure depcomp install-sh missing `find . -name Makefile.in`
