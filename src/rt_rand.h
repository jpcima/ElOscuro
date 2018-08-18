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

#include <stdint.h>

#include "develop.h"

void InitializeRNG (void);
int32_t GetRandomSeed (void);

#if RANDOMTEST
int32_t GameRNG (int8_t*, int32_t);
#define GameRandomNumber(string, val) GameRNG(string, val)

int32_t RNG (int8_t*, int32_t);
#define RandomNumber(string, val) RNG(string, val)
#else
int32_t GameRNG (void);
#define GameRandomNumber(string, val) GameRNG()

int32_t RNG (void);
#define RandomNumber(string, val) RNG()
#endif

void SetRNGindex (int32_t);
int32_t GetRNGindex (void);

