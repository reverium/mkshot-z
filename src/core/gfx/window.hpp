/*
** This file is part of mkxp, further modified for mkshot-z.
**
** Copyright (C) 2026 mkshot-z contributors <https://github.com/mkshot-org>
** Copyright (C) 2013 - 2021 Amaryllis Kulla <ancurio@mapleshrine.eu>
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

struct WindowPrivate;

class Window : public ViewportElement, public Disposable
{
public:
	Window(Viewport *viewport = 0);
	~Window();

	void update();

	DECL_ATTR( Windowskin,      Bitmap* )
	DECL_ATTR( Contents,        Bitmap* )
	DECL_ATTR( Stretch,         bool    )
	DECL_ATTR( CursorRect,      Rect&   )
	DECL_ATTR( Active,          bool    )
	DECL_ATTR( Pause,           bool    )
	DECL_ATTR( X,               int     )
	DECL_ATTR( Y,               int     )
	DECL_ATTR( Width,           int     )
	DECL_ATTR( Height,          int     )
	DECL_ATTR( OX,              int     )
	DECL_ATTR( OY,              int     )
	DECL_ATTR( Opacity,         int     )
	DECL_ATTR( BackOpacity,     int     )
	DECL_ATTR( ContentsOpacity, int     )

	void initDynAttribs();

private:
	WindowPrivate *p;

	void draw();
	void onGeometryChange(const Scene::Geometry &);
	void setZ(int value);
	void setVisible(bool value);

	void onViewportChange();

	void releaseResources();
	const char *klassName() const { return "window"; }

	ABOUT_TO_ACCESS_DISP
};


