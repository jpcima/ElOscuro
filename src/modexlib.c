/*
Copyright (C) 1994-1995 Apogee Software, Ltd.

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

#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <stdlib.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#include "modexlib.h"
#include "rt_util.h"
#include "rt_net.h" // for GamePaused
#include "myprint.h"

static void StretchMemPicture ();
// GLOBAL VARIABLES

bool StretchScreen=0;//bná++
extern bool g_aimcross;
extern bool sdl_fullscreen;
extern int g_xcenter;
extern int g_ycenter;
char 	   *iG_buf_center;
  
int    linewidth;
//int    ylookup[MAXSCREENHEIGHT];
int    ylookup[600];//just set to max res
byte  *page1start;
byte  *page2start;
byte  *page3start;
int    screensize;
byte  *bufferofs;
byte  *displayofs;
bool graphicsmode=false;
char        *bufofsTopLimit;
char        *bufofsBottomLimit;

void DrawCenterAim ();

#ifndef STUB_FUNCTION

/* rt_def.h isn't included, so I just put this here... */
#if !defined(ANSIESC)
#define STUB_FUNCTION fprintf(stderr,"STUB: %s at " __FILE__ ", line %d, thread %d\n",__FUNCTION__,__LINE__,getpid())
#else
#define STUB_FUNCTION
#endif

#endif

/*
====================
=
= GraphicsMode
=
====================
*/
///static SDL_Surface *sdl_surface = NULL;
///static SDL_Surface *unstretch_sdl_surface = NULL;

SDL_Surface *sdl_surface = NULL;
SDL_Surface *unstretch_sdl_surface = NULL;
SDL_Surface *temp = NULL;
SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *sdl_texture = NULL;

void GraphicsMode ( void )
{
  Uint32 flags = 0;

  if (SDL_InitSubSystem (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
      Error ("Could not initialize SDL\n");
    }

  SDL_SetRelativeMouseMode (SDL_TRUE);

  SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
  if (sdl_fullscreen)
    flags = SDL_WINDOW_FULLSCREEN_DESKTOP;

  window = SDL_CreateWindow ("Rise of the Triad", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 200, flags);

  if (window == NULL)
    {
      Error ("Could not set video mode\n");
      exit (1);
    }

  renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);

  sdl_texture = SDL_CreateTexture (renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 320, 200);

  sdl_surface = SDL_CreateRGBSurface (0, 320, 200, 8, 0, 0, 0, 0);

  SDL_SetSurfaceRLE (sdl_surface, 1);

  SDL_RenderSetLogicalSize (renderer, 320, 200);
}

/*
====================
=
= SetTextMode
=
====================
*/
void SetTextMode ( void )
{
	if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_INIT_VIDEO) {
		if (sdl_surface != NULL) {
			SDL_FreeSurface(sdl_surface);
	
			sdl_surface = NULL;
		}
		
		SDL_QuitSubSystem (SDL_INIT_VIDEO);
	}
}

/*
====================
=
= TurnOffTextCursor
=
====================
*/
void TurnOffTextCursor ( void )
{
}

/*
====================
=
= WaitVBL
=
====================
*/
void WaitVBL( void )
{
	SDL_Delay (16667/1000);
}

/*
=======================
=
= VL_SetVGAPlaneMode
=
=======================
*/

void VL_SetVGAPlaneMode ( void )
{
   int i,offset;

    GraphicsMode();

//
// set up lookup tables
//
//bna--   linewidth = 320;
   linewidth = g_swidth;

   offset = 0;

   for (i=0;i<g_sheight;i++)
      {
      ylookup[i]=offset;
      offset += linewidth;
      }

//    screensize=MAXSCREENHEIGHT*MAXSCREENWIDTH;
    screensize=g_sheight*g_swidth;



    page1start=sdl_surface->pixels;
    page2start=sdl_surface->pixels;
    page3start=sdl_surface->pixels;
    displayofs = page1start;
    bufferofs = page2start;

	g_xcenter = g_swidth / 2;
	g_ycenter = (g_sheight / 2)+10 ;//+10 = move aim down a bit

	iG_buf_center = bufferofs + (screensize/2);//(g_ycenter*g_swidth);//+g_xcenter;

	bufofsTopLimit =  bufferofs + screensize - g_swidth;
	bufofsBottomLimit = bufferofs + g_swidth;

    // start stretched
    EnableScreenStretch();
    XFlipPage ();
}

/*
=======================
=
= VL_CopyPlanarPage
=
=======================
*/
void VL_CopyPlanarPage ( byte * src, byte * dest )
{
      memcpy(dest,src,screensize);
}

/*
=======================
=
= VL_CopyPlanarPageToMemory
=
=======================
*/
void VL_CopyPlanarPageToMemory ( byte * src, byte * dest )
{
      memcpy(dest,src,screensize);
}

/*
=======================
=
= VL_CopyBufferToAll
=
=======================
*/
void VL_CopyBufferToAll ( byte *buffer )
{
}

/*
=======================
=
= VL_CopyDisplayToHidden
=
=======================
*/
void VL_CopyDisplayToHidden ( void )
{
   VL_CopyBufferToAll ( displayofs );
}

/*
=================
=
= VL_ClearBuffer
=
= Fill the entire video buffer with a given color
=
=================
*/

void VL_ClearBuffer (byte *buf, byte color)
{
  memset((byte *)buf,color,screensize);
}

/*
=================
=
= VL_ClearVideo
=
= Fill the entire video buffer with a given color
=
=================
*/

void VL_ClearVideo (byte color)
{
  memset (sdl_surface->pixels, color, g_swidth*g_sheight);
}

/*
=================
=
= VL_DePlaneVGA
=
=================
*/

void VL_DePlaneVGA (void)
{
}

//int32_t hudRescaleFactor = 1;
void
RenderSurface (void)
{
  SDL_Texture *newTex = SDL_CreateTextureFromSurface (renderer, sdl_surface);

  if (newTex == NULL)
  {
    Error ("CreateTextureFromSurface failed: %s\n", SDL_GetError ());
    exit (1);
  }

  SDL_RenderClear (renderer);

  SDL_RenderCopy (renderer, newTex, NULL, NULL);
  /*
  if (!StretchScreen && hudRescaleFactor > 1 && doRescaling)
  {
    if (SHOW_TOP_STATUS_BAR ())
      RescaleAreaOfTexture (renderer,
                            newTex,
                            (SDL_Rect){(320 - 320) >> 1, 0, 320, 16},
                            (SDL_Rect){(320 - (320 * hudRescaleFactor)) >> 1, 0, 320 * hudRescaleFactor, 16 * hudRescaleFactor}
    );                          //Status Bar
    if (SHOW_BOTTOM_STATUS_BAR ())
      RescaleAreaOfTexture (renderer,
                            newTex,
                            (SDL_Rect){(320 - 320) >> 1, 200 - 16, 320, 16},
                            (SDL_Rect){(320 - (320 * hudRescaleFactor)) >> 1, 200 - 16 * hudRescaleFactor, 320 * hudRescaleFactor, 16 * hudRescaleFactor}
    );                          //Bottom Bar

  }
  */
  SDL_RenderPresent (renderer);

  SDL_DestroyTexture (newTex);

}

/* C version of rt_vh_a.asm */

void VH_UpdateScreen (void)
{ 	

	if (StretchScreen){//bna++
		StretchMemPicture ();
	}else{
		DrawCenterAim ();
	}
	//SDL_UpdateRect (SDL_GetVideoSurface (), 0, 0, 0, 0);
  RenderSurface();
}


/*
=================
=
= XFlipPage
=
=================
*/

void XFlipPage ( void )
{
 	if (StretchScreen){//bna++
		StretchMemPicture ();
	}else{
		DrawCenterAim ();
	}
  //SDL_UpdateRect (sdl_surface, 0, 0, 0, 0);
  RenderSurface();
 
}

void EnableScreenStretch(void)
{
   int i,offset;
   
   if (g_swidth <= 320 || StretchScreen) return;
   
   if (unstretch_sdl_surface == NULL)
   {
      /* should really be just 320x200, but there is code all over the
         places which crashes then */
      unstretch_sdl_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
         g_swidth, g_sheight, 8, 0, 0, 0, 0);
   }
	
   displayofs = unstretch_sdl_surface->pixels +
	(displayofs - (byte *)sdl_surface->pixels);
   bufferofs  = unstretch_sdl_surface->pixels;
   page1start = unstretch_sdl_surface->pixels;
   page2start = unstretch_sdl_surface->pixels;
   page3start = unstretch_sdl_surface->pixels;
   StretchScreen = 1;	
}

void DisableScreenStretch(void)
{
   if (g_swidth <= 320 || !StretchScreen) return;
	
   displayofs = sdl_surface->pixels +
	(displayofs - (byte *)unstretch_sdl_surface->pixels);
   bufferofs  = sdl_surface->pixels;
   page1start = sdl_surface->pixels;
   page2start = sdl_surface->pixels;
   page3start = sdl_surface->pixels;
   StretchScreen = 0;
}


// bna section -------------------------------------------
static void StretchMemPicture ()
{
  SDL_Rect src;
  SDL_Rect dest;
	
  src.x = 0;
  src.y = 0;
  src.w = 320;
  src.h = 200;
  
  dest.x = 0;
  dest.y = 0;
  dest.w = g_swidth;
  dest.h = g_sheight;
  SDL_SoftStretch(unstretch_sdl_surface, &src, sdl_surface, &dest);
}

// bna function added start
extern	bool ingame;
int		iG_playerTilt;

void DrawCenterAim ()
{
	int x;

	int percenthealth = (locplayerstate->health * 10) / MaxHitpointsForCharacter(locplayerstate);
	int color = percenthealth < 3 ? egacolor[RED] : percenthealth < 4 ? egacolor[YELLOW] : egacolor[GREEN];

	if (g_aimcross && !GamePaused){
		if (( ingame == true )&&(g_swidth>320)){
			  if ((iG_playerTilt <0 )||(iG_playerTilt >g_sheight/2)){
					iG_playerTilt = -(2048 - iG_playerTilt);
			  }
			  if (g_swidth == 640){ x = iG_playerTilt;iG_playerTilt=x/2; }
			  iG_buf_center = bufferofs + ((g_ycenter-iG_playerTilt)*g_swidth);//+g_xcenter;

			  for (x=g_xcenter-10;x<=g_xcenter-4;x++){
				  if ((iG_buf_center+x < bufofsTopLimit)&&(iG_buf_center+x > bufofsBottomLimit)){
					 *(iG_buf_center+x) = color;
				  }
			  }
			  for (x=g_xcenter+4;x<=g_xcenter+10;x++){
				  if ((iG_buf_center+x < bufofsTopLimit)&&(iG_buf_center+x > bufofsBottomLimit)){
					 *(iG_buf_center+x) = color;
				  }
			  }
			  for (x=10;x>=4;x--){
				  if (((iG_buf_center-(x*g_swidth)+g_xcenter) < bufofsTopLimit)&&((iG_buf_center-(x*g_swidth)+g_xcenter) > bufofsBottomLimit)){
					 *(iG_buf_center-(x*g_swidth)+g_xcenter) = color;
				  }
			  }
			  for (x=4;x<=10;x++){
				  if (((iG_buf_center+(x*g_swidth)+g_xcenter) < bufofsTopLimit)&&((iG_buf_center+(x*g_swidth)+g_xcenter) > bufofsBottomLimit)){
					 *(iG_buf_center+(x*g_swidth)+g_xcenter) = color;
				  }
			  }
		}
	}
}
// bna function added end




// bna section -------------------------------------------



