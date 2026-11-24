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

/*
Various utilities and helper functions.
Unfortunately it is not possible to provide halcompile with multiple
sources, so we have to go the somewhat ugly way of implementing those
functions directly in the header files.
*/

#ifndef __MIKRON_UTIL_H__
#define __MIKRON_UTIL_H__

#include <rtapi.h>

/* Select the gear for a stepless speed request (VFD driven motor).
 *
 * The gear table speeds are synchronous speeds at base_freq. A speed rpm
 * runs in gear c at f = base_freq * rpm / c.
 *
 * The current gear (cur, gear table index, < MIKRON_MIN_RPM_INDEX if none)
 * is kept while f stays within [hold_freq, max_freq]. Otherwise the lowest
 * gear that reaches rpm at max_freq is returned. rpm must be > 0; it is not
 * clamped here.
 *
 * Returns the gear table index.
 */
static int select_gear_stepless(double rpm, int cur, double base_freq,
                                double max_freq, double hold_freq);

/* really ugly way of keeping more order and splitting the sources,
 * halcompile does not allow to link multipe source files together, so
 * ultimately all sources need to be included by the .comp directly */
#include <mikron_util.c>

#endif//__MIKRON_UTIL_H__
