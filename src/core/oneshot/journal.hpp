/*
** journal.hpp
**
** This file is part of ModShot-mkxp-z, further modified for mkshot-z.
**
** Copyright (C) 2026 sevenleftslash <sevenleftslash@proton.me>
** Copyright (C) 2024 hat_kid <https://github.com/thehatkid>
**
** ModShot-mkxp-z is licensed under GPLv2 or later.
** mkshot-z is licensed under GPLv3-or-later.
*/

#ifndef ONESHOT_JOURNAL_H
#define ONESHOT_JOURNAL_H

struct JournalPrivate;

class Journal
{
private:
	JournalPrivate *p;

public:
	Journal();
	~Journal();

	bool isActive() const;
	void set(const char *name);
	void setLang(const char *lang);

	void nikoPrepare();
	void nikoStart();
};

#endif // ONESHOT_JOURNAL_H
