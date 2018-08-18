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

#include <stdint.h>

extern int32_t iGLOBAL_SCREENWIDTH;   // bna val 800
extern int32_t iGLOBAL_SCREENHEIGHT;  // bna val 600
extern int32_t iGLOBAL_SCREENBWIDE;
extern int32_t iG_SCREENWIDTH;        // default screen width in bytes
extern int32_t iGLOBAL_HEALTH_X;
extern int32_t iGLOBAL_HEALTH_Y;
extern int32_t iGLOBAL_AMMO_X;
extern int32_t iGLOBAL_AMMO_Y;
extern int32_t iGLOBAL_FOCALWIDTH;

void EnableScreenStretch (void);
void DisableScreenStretch (void);
