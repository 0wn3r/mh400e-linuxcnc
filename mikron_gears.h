/*
LinuxCNC component for controlling the MIKRON gearbox.

Copyright (C) 2018 Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

/* Functions related to gear switching. */

#ifndef __MIKRON_GEARS_H__
#define __MIKRON_GEARS_H__

#include "mikron_common.h"

/* One time setup function to prepare data structures related to gearbox 
 * switching*/
FUNCTION(gearbox_setup);

/* Set gear request */
static void set_gear_request(pair_t *target_gear);

/* really ugly way of keeping more order and splitting the sources,
 * halcompile does not allow to link multipe source files together, so
 * ultimately all sources need to be included by the .comp directly */
#include "mikron_gears.c"

#endif//__MIKRON_GEARS_H__
