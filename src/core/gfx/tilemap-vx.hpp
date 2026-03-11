/*
** tilemapvx.h
**
** This file is part of mkxp, further modified for mkshot-z.
**
** Copyright (C) 2026 mkshot-z contributors <https://github.com/mkshot-org>
** Copyright (C) 2014 - 2021 Amaryllis Kulla <ancurio@mapleshrine.eu>
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

struct TilemapVXPrivate;

class TilemapVX : public Disposable
{
public:
	class BitmapArray
	{
	public:
		void set(int i, Bitmap *bitmap);
		Bitmap *get(int i) const;

	private:
		BitmapArray() {}
		~BitmapArray() {}

		TilemapVXPrivate *p;
		friend class TilemapVX;
		friend struct TilemapVXPrivate;
	};

	TilemapVX(Viewport *viewport = 0);
	~TilemapVX();

	void update();

	BitmapArray &getBitmapArray();

	DECL_ATTR( Viewport,   Viewport* )
	DECL_ATTR( MapData,    Table*    )
	DECL_ATTR( FlashData,  Table*    )
	DECL_ATTR( Flags,      Table*    )
	DECL_ATTR( Visible,    bool      )
	DECL_ATTR( OX,         int       )
	DECL_ATTR( OY,         int       )

private:
	TilemapVXPrivate *p;
	BitmapArray bmProxy;

	void releaseResources();
	const char *klassName() const { return "tilemap"; }
};


