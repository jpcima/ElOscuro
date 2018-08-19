/*
Copyright (C) 2002 John R. Hall
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
// Byte order conversion routines.
#include <stdint.h>

#include "lumpy.h"
#include "rt_def.h"

typedef void (*converter_t) (void*, int32_t);

#define DEFINE_CONVERTER(type)                \
void cvt_##type(void* lmp, int32_t num) {     \
  type* recs = (type*)lmp;                    \
  for (int32_t i = 0; i < num; ++i, ++recs) { \
    CONVERT_ENDIAN_##type(recs);              \
  }                                           \
}

DEFINE_CONVERTER (cfont_t);
DEFINE_CONVERTER (font_t);
DEFINE_CONVERTER (lbm_t);
DEFINE_CONVERTER (lpic_t);
DEFINE_CONVERTER (patch_t);
DEFINE_CONVERTER (pic_t);
DEFINE_CONVERTER (transpatch_t);

// Returns converter for the designated type
converter_t
cvt_for_type (int32_t type)
{
  switch (type)
    {
    case cache_pic_t:
      return cvt_pic_t;
      break;
    case cache_lpic_t:
      return cvt_lpic_t;
      break;
    case cache_font_t:
      return cvt_font_t;
      break;
    case cache_lbm_t:
      return cvt_lbm_t;
      break;
    case cache_patch_t:
      return cvt_patch_t;
      break;
    case cache_transpatch_t:
      return cvt_transpatch_t;
      break;
    case cache_cfont_t:
      return cvt_cfont_t;
      break;
    default:
      return 0;
      break;
    }
}

