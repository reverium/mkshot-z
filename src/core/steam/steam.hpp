#pragma once


#include <string>

struct SteamPrivate;

class Steam
{
private:
	friend struct SharedStatePrivate;

	SteamPrivate *p;

	Steam();
	~Steam();

public:
	void unlock(const char *name);
	void lock(const char *name);
	bool isUnlocked(const char *name);

	const std::string &userName() const;
	const std::string &lang() const;
};


