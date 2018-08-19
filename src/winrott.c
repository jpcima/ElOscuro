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
// Routines from winrott needed for the highres support for the SDL port
#include <stdbool.h>
#include <stdint.h>

#include "rt_view.h"

int32_t g_swidth = 640;  //bna val 800
int32_t g_sheight = 480; //bna val 600
int32_t g_sbwide = 0;
int32_t g_swidth_bytes = 0; // default screen width in bytes

int32_t g_healthx = 0;
int32_t g_healthy = 0;
int32_t g_ammox = 0;
int32_t g_ammoy = 0;

int32_t g_focal_width = 0;
double g_fpfocal_width = 0;

double g_top_yz_anglelimit = 0;

int32_t g_xcenter = 0;
int32_t g_ycenter = 0;

bool g_aimcross = 0;

#define FINEANGLES 2048

void
set_rott_screen_res (int32_t width, int32_t height)
{

  g_swidth = width;
  g_sheight = height;

  g_sbwide = g_swidth * (96 / 320);
  g_swidth_bytes = g_swidth * (96 / 320);; // default screen width in bytes

  if (g_swidth == 320)
    {
      g_focal_width = 160;
      g_fpfocal_width = 160.0;
      g_healthx = 20;
      g_healthy = 185;
      g_ammox = 300;
      g_ammoy = 184;

      g_top_yz_anglelimit = (44 * FINEANGLES / 360);;
    }
  if (g_swidth == 640)
    {
      g_focal_width = 180;
      g_fpfocal_width = 180.0;
      g_healthx = 40;    //20*2;
      g_healthy = 466;   //(185*2)+16;
      g_ammox = 600;     //300*2;
      g_ammoy = 464;     //480-16;

      g_top_yz_anglelimit = (42 * FINEANGLES / 360);;
    }
  if (g_swidth == 800)
    {
      g_focal_width = 200;
      g_fpfocal_width = 200.0;
      g_healthx = 40;    //20*2;
      g_healthy = 585;   //(185/200)*600;
      g_ammox = 750;     //(300/320)*800;
      g_ammoy = 584;     //600-16;

      g_top_yz_anglelimit = (90 * FINEANGLES / 360);;
    }
}

void
move_screen (bool up, bool down, bool left, bool right)
{
  uint8_t* b = ((uint8_t*) bufferofs) + (((g_sheight - viewheight) / 2) * g_swidth) + ((g_swidth - viewwidth) / 2);
  if (viewsize == 8)
    {
      b += 8 * g_swidth;
    }

  int32_t start_x = 3;              // Take 3 pixels to the right
  int32_t start_y = 3;              // Take 3 lines down

  int32_t start_offset = start_y * g_swidth;
  if ((down && right) || (up && left))
    {
      start_offset += start_x;
    }

  if (up)
    {
      if (left)
        {
          for (uint8_t* y_center = b; y_center < b + ((viewheight - start_y) * g_swidth); y_center += g_swidth)
            {
              memcpy (y_center, y_center + start_offset, viewwidth - start_x);
            }
        }
      if (right)
        {
          for (uint8_t* y_center = b; y_center < b + ((viewheight - start_y) * g_swidth); y_center += g_swidth)
            {
              memcpy (y_center + start_x, y_center + start_offset, viewwidth - start_x);
            }
        }
    }
  if (down)
    {
      if (left)
        {
          for (uint8_t* y_center = b + ((viewheight - start_y - 1) * g_swidth); y_center > b; y_center -= g_swidth)
            {
              memcpy (y_center + start_offset, y_center + start_x, viewwidth - start_x);
            }
        }
      if (right)
        {
          for (uint8_t* y_center = b + ((viewheight - start_y - 1) * g_swidth); y_center > b; y_center -= g_swidth)
            {
              memcpy (y_center + start_offset, y_center, viewwidth - start_x);
            }
        }
    }
}

