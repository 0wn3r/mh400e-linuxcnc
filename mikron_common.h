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

#ifndef __MIKRON_COMMON_H__
#define __MIKRON_COMMON_H__

/* description of a particular gear/speed setting */
typedef struct
{
    unsigned key;
    unsigned value;
} pair_t;


/* Each gear is described by shaft positions:
 *      10 9 8 7 6 5 4 3 2 1 0          
 * msb "fast" "slow" "b3_f" "b3_m" "b3_b" "b2_f" "b2_m" "b2_b" "b1_f" "b1_m" "b1_b" lsb
 */
#define GET_BLOCK_ONE_BACKWARD(mask)            (mask & 1)
#define GET_BLOCK_ONE_MIDDLE(mask)              ((mask >> 1) & 1)
#define GET_BLOCK_ONE_FORWARD(mask)             ((mask >> 2) & 1)
#define GET_BLOCK_TWO_BACKWARD(mask)            ((mask >> 3) & 1)
#define GET_BLOCK_TWO_MIDDLE(mask)              ((mask >> 4) & 1)
#define GET_BLOCK_TWO_FORWARD(mask)             ((mask >> 5) & 1)
#define GET_BLOCK_THREE_BACKWARD(mask)          ((mask >> 6) & 1)
#define GET_BLOCK_THREE_MIDDLE(mask)            ((mask >> 7) & 1)
#define GET_BLOCK_THREE_FORWARD(mask)           ((mask >> 8) & 1)
#define GET_MOTOR_SLOW(mask)                    ((mask >> 9) & 1)
#define GET_MOTOR_FAST(mask)                    ((mask >> 10) & 1)

/* lookup table from rpm to gearbox status pin values */
static pair_t mikron_gears[] =
{  /* rpm   bitmask                msb 10 9 8 7 6 5 4 3 2 1 0 lsb */
    { 0,    128      },              /*   neutral         0 1 0 */
    { 40,   802    },              /*   0 1 1 0 0 1 0 0 0 1 0 */
    { 50,   804    },              /*   0 1 1 0 0 1 0 0 1 0 0 */
    { 63,   801    },              /*   0 1 1 0 0 1 0 0 0 0 1 */
    { 80,   778    },              /*   0 1 1 0 0 0 0 1 0 1 0 */
    { 100,  780    },              /*   0 1 1 0 0 0 0 1 1 0 0 */
    { 125,  777    },              /*   0 1 1 0 0 0 0 1 0 0 1 */
    { 160,  786    },              /*   0 1 1 0 0 0 1 0 0 1 0 */
    { 200,  788    },              /*   0 1 1 0 0 0 1 0 1 0 0 */
    { 250,  785    },              /*   0 1 1 0 0 0 1 0 0 0 1 */
    { 315,  610    },              /*   0 1 0 0 1 1 0 0 0 1 0 */
    { 400,  612    },              /*   0 1 0 0 1 1 0 0 1 0 0 */
    { 500,  609    },              /*   0 1 0 0 1 1 0 0 0 0 1 */
    { 630,  586    },              /*   0 1 0 0 1 0 0 1 0 1 0 */
    { 800,  588    },              /*   0 1 0 0 1 0 0 1 1 0 0 */
    { 1000, 585    },              /*   0 1 0 0 1 0 0 1 0 0 1 */
    { 1250, 594    },              /*   0 1 0 0 1 0 1 0 0 1 0 */
    { 1600, 596    },              /*   0 1 0 0 1 0 1 0 1 0 0 */
    { 2000, 593    },              /*   0 1 0 0 1 0 1 0 0 0 1 */
    { 2500, 1106   },              /*   1 0 0 0 1 0 1 0 0 1 0 */
    { 3150, 1108   },              /*   1 0 0 0 1 0 1 0 1 0 0 */
    { 4000, 1105   }               /*   1 0 0 0 1 0 1 0 0 0 1 */
};

/* total number of selectable gears including neutral */
#define MIKRON_NUM_GEARS        (sizeof(mikron_gears)/sizeof(pair_t))
/* max gear index in array */
#define MIKRON_MAX_GEAR_INDEX       MIKRON_NUM_GEARS - 1
/* index of neutral gear */
#define MIKRON_NEUTRAL_GEAR_INDEX   0
/* min spindle rpm > 0 supported by the MIKRON */
#define MIKRON_MIN_RPM              40
/* index of the first non 0 rpm setting in the gears array */
#define MIKRON_MIN_RPM_INDEX        1
/* max spindle rpm supported by the MIKRON */
#define MIKRON_MAX_RPM              4000

#endif//__MIKRON_COMMON_H__
