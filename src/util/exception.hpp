/*
** exception.h
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


#include <string>
#include <stdio.h>
#include <stdarg.h>

struct Exception
{
	enum Type
	{
		RGSSError,
		NoFileError,
		IOError,

		/* Already defined by ruby */
		TypeError,
		ArgumentError,

		/* New types introduced in mkxp */
		PHYSFSError,
		SDLError,
		MKShotError
	};

	Type type;
	std::string msg;

	Exception(Type type, const char *format, ...)
	    : type(type)
	{
		va_list ap;
		va_start(ap, format);

		msg.resize(512);
		vsnprintf(&msg[0], msg.size(), format, ap);

		va_end(ap);
	}
};


