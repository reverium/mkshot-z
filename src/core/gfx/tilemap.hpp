/*
** tilemap.h
**
** This file is part of mkxp, further modified for mkshot-z.
**
** Copyright (C) 2026 mkshot-z contributors <https://github.com/mkshot-org>
** Copyright (C) 2013 - 2021 Amaryllis Kulla <ancurio@mapleshrine.eu>
**
** mkxp is licensed under GPLv2 or later.
** mkshot-z is licensed under GPLv3 or later.
*/

#pragma once


#include "util/disposable.hpp"

#include "util/util.hpp"

class Viewport;
class Bitmap;
class Table;

struct Color;
struct Tone;

struct TilemapPrivate;

class Tilemap : public Disposable
{
public:
	class Autotiles
	{
	public:
		void set(int i, Bitmap *bitmap);
		Bitmap *get(int i) const;

	private:
		Autotiles() {}
		~Autotiles() {}

		TilemapPrivate *p;
		friend class Tilemap;
		friend struct TilemapPrivate;
	};

	Tilemap(Viewport *viewport = 0);
	~Tilemap();

	void update();

	Autotiles &getAutotiles();
	Viewport *getViewport() const;

	DECL_ATTR( Tileset,    Bitmap*   )
	DECL_ATTR( MapData,    Table*    )
	DECL_ATTR( FlashData,  Table*    )
	DECL_ATTR( Priorities, Table*    )
	DECL_ATTR( Visible,    bool      )
	DECL_ATTR( Wrapping,   bool      )
	DECL_ATTR( OX,         int       )
	DECL_ATTR( OY,         int       )

	DECL_ATTR( Opacity,   int     )
	DECL_ATTR( BlendType, int     )
	DECL_ATTR( Color,     Color&  )
	DECL_ATTR( Tone,      Tone&   )

	void initDynAttribs();

private:
	TilemapPrivate *p;
	Autotiles atProxy;

	void releaseResources();
	const char *klassName() const { return "tilemap"; }
};


