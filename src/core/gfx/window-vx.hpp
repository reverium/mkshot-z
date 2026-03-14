/*
** This file is part of mkxp, further modified for mkshot-z.
**
** Copyright (C) 2026 Team Reverium <https://github.com/reverium>
** Copyright (C) 2014 - 2021 Amaryllis Kulla <ancurio@mapleshrine.eu>
**
** mkxp is licensed under GPLv2 or later.
** mkshot-z is licensed under GPLv3 or later.
*/

#pragma once


#include "core/gfx/viewport.hpp"
#include "util/disposable.hpp"

#include "util/util.hpp"

class Bitmap;
struct Rect;
struct Tone;

struct WindowVXPrivate;

class WindowVX : public ViewportElement, public Disposable
{
public:
	WindowVX(Viewport *viewport = 0);
	WindowVX(int x, int y, int width, int height);
	~WindowVX();

	void update();

	void move(int x, int y, int width, int height);
	bool isOpen() const;
	bool isClosed() const;

	DECL_ATTR( Windowskin,      Bitmap* )
	DECL_ATTR( Contents,        Bitmap* )
	DECL_ATTR( CursorRect,      Rect&   )
	DECL_ATTR( Active,          bool    )
	DECL_ATTR( ArrowsVisible,   bool    )
	DECL_ATTR( Pause,           bool    )
	DECL_ATTR( X,               int     )
	DECL_ATTR( Y,               int     )
	DECL_ATTR( Width,           int     )
	DECL_ATTR( Height,          int     )
	DECL_ATTR( OX,              int     )
	DECL_ATTR( OY,              int     )
	DECL_ATTR( Padding,         int     )
	DECL_ATTR( PaddingBottom,   int     )
	DECL_ATTR( Opacity,         int     )
	DECL_ATTR( BackOpacity,     int     )
	DECL_ATTR( ContentsOpacity, int     )
	DECL_ATTR( Openness,        int     )
	DECL_ATTR( Tone,            Tone&   )

	void initDynAttribs();

private:
	WindowVXPrivate *p;

	void draw();
	void onGeometryChange(const Scene::Geometry &);

	void releaseResources();
	const char *klassName() const { return "window"; }

	ABOUT_TO_ACCESS_DISP
};


