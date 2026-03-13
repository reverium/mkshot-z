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


struct Serializable
{
	virtual int serialSize() const = 0;
	virtual void serialize(char *buffer) const = 0;
};

template<class C>
C *deserialize(const char *data)
{
	return C::deserialize(data);
}


