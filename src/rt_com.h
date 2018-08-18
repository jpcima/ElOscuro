/*
Copyright (C) 1994-1995 Apogee Software, Ltd.
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

#include "rottnet.h"

#define MAXPACKET	512

extern int32_t badpacket;
extern int32_t consoleplayer;
extern int32_t controlsynctime;
extern uint8_t ROTTpacket[MAXCOMBUFFERSIZE];

void ComSetTime (void);
int32_t GetTransitTime (int32_t);
void InitROTTNET (void);
bool ReadPacket (void);
void WritePacket (void*, int32_t, int32_t);

