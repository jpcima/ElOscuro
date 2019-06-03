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
//***************************************************************************
//
//    MODEXLIB.C - various utils palette funcs and modex stuff
//
//***************************************************************************

#ifndef _modexlib_public
#define _modexlib_public

#include <SDL2/SDL.h>
#include "winrott.h"
#include "rt_def.h"

void EnableScreenStretch (void);
void DisableScreenStretch (void);
/*
int g_swidth;//bna val 800
int g_sheight;//bna val 600


#define MAXSCREENHEIGHT    600//     200*2
#define MAXSCREENWIDTH     800//     320*2
#define SCREENBWIDE        800*(96/320)//     96*2
#define MAXVIEWWIDTH       800//     320*2
#define SCREENWIDTH        800*(96/320)//     96*2              // default screen width in bytes
*/
//***************************************************************************
//
//    Video (ModeX) Constants
//
//***************************************************************************

extern  bool StretchScreen;//bn�++

//extern  int      ylookup[MAXSCREENHEIGHT];      // Table of row offsets
extern  int      ylookup[600];      // just set to max res
extern  int      linewidth;
extern  byte    *page1start;
extern  byte    *page2start;
extern  byte    *page3start;
extern  int      screensize;
extern  byte    *bufferofs;
extern  byte    *displayofs;
extern  bool  graphicsmode;
extern SDL_Surface * sdl_surface;

void  GraphicsMode ( void );
void  SetTextMode ( void );
void  VL_SetVGAPlaneMode ( void );
void  VL_ClearBuffer (byte *buf, byte color);
void  VL_ClearVideo (byte color);
void  VL_DePlaneVGA (void);
void  VL_CopyDisplayToHidden ( void );
void  VL_CopyBufferToAll ( byte *buffer );
void  VL_CopyPlanarPage ( byte * src, byte * dest );
void  VL_CopyPlanarPageToMemory ( byte * src, byte * dest );
void  XFlipPage ( void );
void  WaitVBL( void );
void  TurnOffTextCursor ( void );

#ifdef __WATCOMC__
#pragma aux VGAWRITEMAP =      \
        "mov    eax,01H"       \
        "mov    edx,03c5h"     \
        "shl    eax,cl"        \
        "out    dx,al"         \
        parm    [ecx]          \
        modify exact [eax edx]

#pragma aux VGAMAPMASK =       \
        "mov    edx,03c5h"     \
        "out    dx,al"         \
        parm    [eax]          \
        modify exact [edx]

#pragma aux VGAREADMAP =      \
        "shl    eax,08H"      \
        "mov    edx,03ceh"    \
        "add    eax,04H"      \
        "out    dx,ax"        \
        parm    [eax]         \
        modify exact [eax edx]
#endif

#define VGAMAPMASK(a)
#define VGAREADMAP(a)
#define VGAWRITEMAP(a)

#endif
