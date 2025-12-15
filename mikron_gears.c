/*
LinuxCNC component for controlling the MAHO MH400E gearbox.

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

#include "mikron_gears.h"

/* Group all data that is required to operate */
static struct
{
    hal_bit_t *do_block_one_forward;
    hal_bit_t *do_block_one_middle;
    hal_bit_t *do_block_one_backward;
    hal_bit_t *do_block_two_forward;
    hal_bit_t *do_block_two_middle;
    hal_bit_t *do_block_two_backward;
    hal_bit_t *do_block_three_forward;
    hal_bit_t *do_block_three_middle;
    hal_bit_t *do_block_three_backward;
    hal_bit_t *do_motor_slow;
    hal_bit_t *do_motor_fast;
} g_request_data;


/* One time setup function to prepare data structures related to gearbox 
 * switching*/
FUNCTION(gearbox_setup)
{
    /* Populate data structures that will be used be the state functions
     * when shifting gears */

    g_request_data.do_block_one_forward = &block_one_forward;
    g_request_data.do_block_one_middle = &block_one_middle;
    g_request_data.do_block_one_backward = &block_one_backward;
    g_request_data.do_block_two_forward = &block_two_forward;
    g_request_data.do_block_two_middle = &block_two_middle;
    g_request_data.do_block_two_backward = &block_two_backward;
    g_request_data.do_block_three_forward = &block_three_forward;
    g_request_data.do_block_three_middle = &block_three_middle;
    g_request_data.do_block_three_backward = &block_three_backward;
    g_request_data.do_motor_slow = &motor_slow;
    g_request_data.do_motor_fast = &motor_fast;
}

static void set_gear_request(pair_t *target_gear)
{
    *g_request_data.do_block_one_forward = GET_BLOCK_ONE_FORWARD(target_gear->value);
    *g_request_data.do_block_one_middle = GET_BLOCK_ONE_MIDDLE(target_gear->value);
    *g_request_data.do_block_one_backward = GET_BLOCK_ONE_BACKWARD(target_gear->value);
    *g_request_data.do_block_two_forward = GET_BLOCK_TWO_FORWARD(target_gear->value);
    *g_request_data.do_block_two_middle = GET_BLOCK_TWO_MIDDLE(target_gear->value);
    *g_request_data.do_block_two_backward = GET_BLOCK_TWO_BACKWARD(target_gear->value);
    *g_request_data.do_block_three_forward = GET_BLOCK_THREE_FORWARD(target_gear->value);
    *g_request_data.do_block_three_middle = GET_BLOCK_THREE_MIDDLE(target_gear->value);
    *g_request_data.do_block_three_backward = GET_BLOCK_THREE_BACKWARD(target_gear->value);
    *g_request_data.do_motor_slow = GET_MOTOR_SLOW(target_gear->value);
    *g_request_data.do_motor_fast = GET_MOTOR_FAST(target_gear->value);
}