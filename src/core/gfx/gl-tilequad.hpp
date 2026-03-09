/*
** tilequad.h
**
** This file is part of mkxp, further modified for mkshot-z.
**
** Copyright (C) mkshot-z contributors <https://github.com/mkshot-org>
** Copyright (C) 2013 - 2021 Amaryllis Kulla <ancurio@mapleshrine.eu>
**
** mkxp is licensed under GPLv2 or later.
** mkshot-z is licensed under GPLv3 or later.
*/

#pragma once


#include "core/etc/internal.hpp"

/* Tiled Quads
 *
 * These functions enable drawing a tiled subrectangle
 * of a texture,
 * but no advanced stuff like rotation, scaling etc.
*/

#include "core/glx/quadarray.hpp"

namespace TileQuads
{
	/* Calculate needed quad counts */
	int oneDimCount(int tileDimension,
	                int destDimension);
	int twoDimCount(int tileW, int tileH,
	                int destW, int destH);

	/* Build tiling quads */
	int buildH(const IntRect &sourceRect,
	           int width, int x, int y,
	           Vertex *verts);

	int buildV(const IntRect &sourceRect,
	           int height, int ox, int oy,
	           Vertex *verts);

	int build(const IntRect &sourceRect,
	          const IntRect &destRect,
	          Vertex *verts);

	/* Build a quad "frame" (see Window cursor_rect) */
	int buildFrame(const IntRect &rect,
	               Vertex vert[36]);

	int buildFrameSource(const IntRect &rect,
	                     Vertex vert[36]);
}


