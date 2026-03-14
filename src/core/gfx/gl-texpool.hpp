/*
** This file is part of mkxp, further modified for mkshot-z.
**
** Copyright (C) 2026 Team Reverium <https://github.com/reverium>
** Copyright (C) 2013 - 2021 Amaryllis Kulla <ancurio@mapleshrine.eu>
**
** mkxp is licensed under GPLv2 or later.
** mkshot-z is licensed under GPLv3 or later.
*/

#pragma once


#include "core/gfx/util.hpp"

struct TexPoolPrivate;

class TexPool
{
public:
	TexPool(uint32_t maxMemSize = 20000000 /* 20 MB */);
	~TexPool();

	TEXFBO request(int width, int height);
	void release(TEXFBO &obj);

	void disable();

private:
	TexPoolPrivate *p;
};


