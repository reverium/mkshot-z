/*
** plane.h
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


#include "util/disposable.hpp"
#include "core/gfx/viewport.hpp"

class Bitmap;
struct Color;
struct Tone;

struct PlanePrivate;

class Plane : public ViewportElement, public Disposable
{
public:
	Plane(Viewport *viewport = 0);
	~Plane();

	DECL_ATTR( Bitmap,    Bitmap* )
	DECL_ATTR( OX,        int     )
	DECL_ATTR( OY,        int     )
	DECL_ATTR( ZoomX,     float   )
	DECL_ATTR( ZoomY,     float   )
	DECL_ATTR( Opacity,   int     )
	DECL_ATTR( BlendType, int     )
	DECL_ATTR( Color,     Color&  )
	DECL_ATTR( Tone,      Tone&   )
	DECL_ATTR( SrcRect,   Rect&   )

	void initDynAttribs();

private:
	PlanePrivate *p;

	void draw();
	void onGeometryChange(const Scene::Geometry &);

	void releaseResources();
	const char *klassName() const { return "plane"; }

	ABOUT_TO_ACCESS_DISP
};


