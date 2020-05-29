/***********************************************************************
 Freeciv - Copyright (C) 1996 - A Kjeldberg, L Gregersen, P Unold
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
***********************************************************************/

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif

#include <stdlib.h>

/* client */
#include "tilespec.h"

/* gui main header */
#include "gui_stub.h"

#include "graphics.h"

struct sprite *intro_gfx_sprite;

/************************************************************************//**
  Return whether the client supports given view type
****************************************************************************/
bool gui_is_view_supported(enum ts_type type)
{
  /* PORTME */
  return FALSE;
}

/************************************************************************//**
  Load the introductory graphics.
****************************************************************************/
void load_intro_gfx(void)
{
  /* PORTME */
  intro_gfx_sprite = load_gfxfile(tileset_main_intro_filename(tileset));
}

/************************************************************************//**
  Load the cursors (mouse substitute sprites), including a goto cursor,
  an airdrop cursor, a nuke cursor, and a patrol cursor.
****************************************************************************/
void load_cursors(void)
{
  /* PORTME */
}

/************************************************************************//**
  Frees the introductory sprites.
****************************************************************************/
void gui_free_intro_radar_sprites(void)
{
  if (intro_gfx_sprite) {
    free_sprite(intro_gfx_sprite);
    intro_gfx_sprite = NULL;
  }
}