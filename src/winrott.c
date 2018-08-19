/* Routines from winrott needed for the highres support for the SDL port */
#include <stdlib.h>
#include <string.h>
#include "winrott.h"
#include "modexlib.h"

int g_swidth = 640;  //bna val 800
int g_sheight = 480; //bna val 600
int g_sbwide;
int g_swidth_bytes;             // default screen width in bytes

int g_healthx;
int g_healthy;
int g_ammox;
int g_ammoy;

int g_focal_width;
double g_fpfocal_width;

double g_top_yz_anglelimit;

int g_xcenter;
int g_ycenter;

bool iG_aimCross = 0;

extern int viewheight;
extern int viewwidth;
extern int viewsize;

#define FINEANGLES                        2048

void
SetRottScreenRes (int Width, int Height)
{

  g_swidth = Width;
  g_sheight = Height;

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
  uint8_t *b = ((uint8_t *) bufferofs) + (((g_sheight - viewheight) / 2) * g_swidth) + ((g_swidth - viewwidth) / 2);
  if (viewsize == 8)
    {
      b += 8 * g_swidth;
    }

  int start_x = 3;              // Take 3 pixels to the right
  int start_y = 3;              // Take 3 lines down
  int start_offset = start_y * g_swidth;
  if ((down && right) || (up && left))
    {
      start_offset += start_x;
    }

  if (up)
    {
      if (left)
        {
          for (uint8_t * y_center = b; y_center < b + ((viewheight - start_y) * g_swidth); y_center += g_swidth)
            {
              memcpy (y_center, y_center + start_offset, viewwidth - start_x);
            }
        }
      if (right)
        {
          for (uint8_t * y_center = b; y_center < b + ((viewheight - start_y) * g_swidth); y_center += g_swidth)
            {
              memcpy (y_center + start_x, y_center + start_offset, viewwidth - start_x);
            }
        }
    }
  if (down)
    {
      if (left)
        {
          for (uint8_t * y_center = b + ((viewheight - start_y - 1) * g_swidth); y_center > b; y_center -= g_swidth)
            {
              memcpy (y_center + start_offset, y_center + start_x, viewwidth - start_x);
            }
        }
      if (right)
        {
          for (uint8_t * y_center = b + ((viewheight - start_y - 1) * g_swidth); y_center > b; y_center -= g_swidth)
            {
              memcpy (y_center + start_offset, y_center, viewwidth - start_x);
            }
        }
    }
}
