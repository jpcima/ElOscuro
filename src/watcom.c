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
#include <stdint.h>
	
int32_t
FixedMul (int32_t a, int32_t b)
{
  int64_t scratch1 = (int64_t) a * (int64_t) b + (int64_t) 0x8000;
  return (scratch1 >> 16) & 0xffffffff;
}

int32_t
FixedMulShift (int32_t a, int32_t b, int32_t shift)
{
  int64_t x = a;
  int64_t y = b;
  int64_t z = x * y;

  return (((uint64_t) z) >> shift) & 0xffffffff;
}

int32_t
FixedDiv2 (int32_t a, int32_t b)
{
  int64_t x = (int32_t) a;
  int64_t y = (int32_t) b;
  int64_t z = x * 65536 / y;

  return (z) & 0xffffffff;
}

int32_t
FixedScale (int32_t orig, int32_t factor, int32_t divisor)
{
  int64_t x = orig;
  int64_t y = factor;
  int64_t z = divisor;

  int64_t w = (x * y) / z;

  return (w) & 0xffffffff;
}

