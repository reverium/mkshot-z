/*
** graphics.h
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


#include "util/util.hpp"
#include "core/gfx/util.hpp"

class Scene;
class Bitmap;
class Disposable;
struct RGSSThreadData;
struct GraphicsPrivate;
struct AtomicFlag;
struct THEORAPLAY_VideoFrame;
struct Movie;

class Graphics
{
public:
    double getDelta();
    double lastUpdate();
    
	void update(bool checkForShutdown = true);
	void freeze();
	void transition(int duration = 8,
	                const char *filename = "",
	                int vague = 40);
	void frameReset();

	DECL_ATTR( FrameRate,  int )
	DECL_ATTR( FrameCount, int )
	DECL_ATTR( Brightness, int )

	void wait(int duration);
	void fadeout(int duration);
	void fadein(int duration);

	Bitmap *snapToBitmap();

	int width() const;
	int height() const;
	int widthHires() const;
	int heightHires() const;
	bool isPingPongFramebufferActive() const;
    int displayContentWidth() const;
    int displayContentHeight() const;
    int displayWidth() const;
    int displayHeight() const;
	void resizeScreen(int width, int height);
    void resizeWindow(int width, int height, bool center=false);
	void drawMovieFrame(const THEORAPLAY_VideoFrame* video, Bitmap *videoBitmap);
	bool updateMovieInput(Movie *movie);
	void playMovie(const char *filename, int volume, bool skippable);
	void screenshot(const char *filename);

	void reset();
    void center();

    /* Non-standard extension */
    DECL_ATTR( Fullscreen, bool )
    DECL_ATTR( ShowCursor, bool )
    DECL_ATTR( Scale,    double )
    DECL_ATTR( Frameskip, bool )
    DECL_ATTR( FixedAspectRatio, bool )
    DECL_ATTR( Smooth, bool )
    DECL_ATTR( SmoothScaling, int )
    DECL_ATTR( IntegerScaling, bool )
    DECL_ATTR( LastMileScaling, bool )
    DECL_ATTR( Threadsafe, bool )
    double averageFrameRate();

	/* <internal> */
	Scene *getScreen() const;
	/* Repaint screen with static image until exitCond
	 * is set. Observes reset flag on top of shutdown
	 * if "checkReset" */
	void repaintWait(const AtomicFlag &exitCond,
	                 bool checkReset = true);
    
    void lock(bool force = false);
    void unlock(bool force = false);

	const TEX::ID &obscuredTex() const;

private:
	Graphics(RGSSThreadData *data);
	~Graphics();

	void addDisposable(Disposable *);
	void remDisposable(Disposable *);

	friend struct SharedStatePrivate;
	friend class Disposable;

	GraphicsPrivate *p;
};

#define GFX_LOCK shState->graphics().lock()
#define GFX_UNLOCK shState->graphics().unlock()


