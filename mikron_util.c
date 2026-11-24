/*
LinuxCNC component for controlling the MAHO MIKRON gearbox.

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


static int select_gear_stepless(double rpm, int cur_index, double f_base,
                                double f_max, double f_hold)
{
    int i;
    const double eps = 1e-6;

    if (cur_index >= MIKRON_MIN_RPM_INDEX && cur_index <= (int)MIKRON_MAX_GEAR_INDEX)
    {
        double c = mikron_gears[cur_index].key;
        if (rpm >= c * f_hold / f_base - eps &&
            rpm <= c * f_max / f_base + eps)
        {
            return cur_index;
        }
    }

    for (i = MIKRON_MIN_RPM_INDEX; i <= (int)MIKRON_MAX_GEAR_INDEX; i++)
    {
        if (mikron_gears[i].key * f_max / f_base >= rpm - eps)
        {
            return i;
        }
    }
    return MIKRON_MAX_GEAR_INDEX;
}
