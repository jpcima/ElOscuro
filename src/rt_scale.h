/*
Copyright (C) 1994-1995 Apogee Software, Ltd.
Copyright (C) 2002-2015 icculus.org, GNU/Linux port
Copyright (C) 2018-2019 Marc-Alexandre Espiaut

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

#include <stdint.h>

#include "rt_draw.h"

extern int32_t dc_invscale;
extern int32_t dc_iscale;
extern int32_t dc_texturemid;
extern int32_t dc_yh;
extern int32_t dc_yl;
extern int32_t sprtopoffset;
extern int32_t transparentlevel;
extern uint8_t* dc_source;

void DrawNormalSprite (int32_t, int32_t, int32_t);
void DrawPositionedScaledSprite (int32_t, int32_t, int32_t, int32_t, int32_t);
void DrawScreenSizedSprite (int32_t);
void DrawScreenSprite (int32_t, int32_t, int32_t);
void DrawUnScaledSprite (int32_t, int32_t, int32_t, int32_t);
void R_DrawWallColumn (uint8_t*);
void ScaleMaskedPost (uint8_t*, uint8_t*);
void ScaleShape (visobj_t*);
void ScaleSolidShape (visobj_t*);
void ScaleTransparentPost (uint8_t*, uint8_t*, int32_t);
void ScaleTransparentShape (visobj_t*);
void ScaleWeapon (int32_t, int32_t, int32_t);
void SetLightLevel (int32_t);
