/*
** vertex.h
**
** This file is part of mkxp, further modified for mkshot-z.
**
** Copyright (C) 2026 sevenleftslash <sevenleftslash@proton.me>
** Copyright (C) 2014 - 2021 Amaryllis Kulla <ancurio@mapleshrine.eu>
**
** mkxp is licensed under GPLv2 or later.
** mkshot-z is licensed under GPLv3 or later.
*/

#pragma once


#include "core/etc/internal.hpp"
#include "core/gfx/fun.hpp"
#include "core/gfx/shader.hpp"

/* Simple Vertex */
struct SVertex
{
	Vec2 pos;
	Vec2 texPos;
};

/* Color Vertex */
struct CVertex
{
	Vec2 pos;
	Vec4 color;

	CVertex();
};

struct Vertex
{
	Vec2 pos;
	Vec2 texPos;
	Vec4 color;

	Vertex();
};

struct VertexAttribute
{
	Shader::Attribute index;
	GLint size;
	GLenum type;
	const GLvoid *offset;
};

template<class VertType>
struct VertexTraits
{
	static const VertexAttribute *attr;
	static const GLsizei attrCount;
};


