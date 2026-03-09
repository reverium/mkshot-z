/*
** apple.h
**
** This file is part of ModShot-mkxp-z, further modified for mkshot-z.
**
** Copyright (C) mkshot-z contributors <https://github.com/mkshot-org>
** Copyright (C) 2024 hat_kid <https://github.com/thehatkid>
**
** ModShot-mkxp-z is licensed under GPLv2 or later.
** mkshot-z is licensed under GPLv3-or-later.
*/

#ifndef ONESHOT_APPLE_H
#define ONESHOT_APPLE_H

#include <string>

namespace OneshotApple
{
	void desktopImageSet(std::string path, double red, double blue, double green);
	void desktopImageReset();
	void desktopImageCache();
}

#endif // ONESHOT_APPLE_H
