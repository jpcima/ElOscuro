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

#define MSG_PERMANENT   0x80
#define MSG_NODELETE    0x40
#define MSG_PRIORITY(x) ((x) & 0x3f)

#define PERMANENT_MSG(x)  ((x) & MSG_PERMANENT)
#define DELETABLE_MSG(x)  ((x) & MSG_NODELETE)

#define MSG_MODEM            (1 | MSG_PERMANENT)
#define MSG_SYSTEM            2
#define MSG_REMOTERIDICULE    3
#define MSG_REMOTE           (4 | MSG_NODELETE)
#define MSG_GAME             (5 | MSG_NODELETE)
#define MSG_DOOR              6
#define MSG_CHEAT             7
#define MSG_NAMEMENU         (8 | MSG_PERMANENT | MSG_NODELETE)
#define MSG_QUIT              9
#define MSG_MACRO            10
#define MSG_BONUS1           11
#define MSG_BONUS            12
#define MSG_MSGSYSTEM        13

#define MAXMSGS 15

typedef struct msgt
{
  uint8_t active;
  uint8_t flags;
  int32_t tictime;
  int8_t* text;
} messagetype;

extern messagetype Messages[MAXMSGS];
extern bool MessagesEnabled;

int32_t AddMessage (int8_t*, int32_t);
void DeleteMessage (int32_t);
void DeletePriorityMessage (int32_t);
void DrawMessages (void);
void FinishModemMessage (int32_t, bool);
void InitializeMessages (void);
void ModemMessageDeleteChar (int32_t);
void ResetMessageTime (void);
void RestoreMessageBackground (void);
int32_t StringLength (int8_t*);
void UpdateModemMessage (int32_t, int8_t);
