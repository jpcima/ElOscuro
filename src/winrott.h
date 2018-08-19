/*
Copyright (C) 2002-2015 icculus.org, GNU/Linux port
Copyright (C) 2018 Marc-Alexandre Espiaut

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#pragma once

#include <stdbool.h>
#include <stdint.h>

extern int32_t g_swidth;  // bna val 800
extern int32_t g_sheight; // bna val 600
extern int32_t g_sbwide;
extern int32_t g_swidth_bytes; // default screen width in bytes
extern int32_t g_healthx;
extern int32_t g_healthy;
extern int32_t g_ammox;
extern int32_t g_ammoy;
extern int32_t g_focal_width;

void move_screen(bool, bool, bool, bool);
void set_rott_screen_res (int32_t, int32_t);

