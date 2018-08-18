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
#include "cin_glob.h"
#include "rt_in.h"
#include "rt_draw.h"

void CinematicDelay ( void )
{
   CalcTics();
}

int GetCinematicTime ( void )
{
   return GetTicCount ();
}

bool CinematicAbort( void )
{
   return (IN_CheckAck ());
}

void ClearCinematicAbort( void )
{
   IN_StartAck ();
}
