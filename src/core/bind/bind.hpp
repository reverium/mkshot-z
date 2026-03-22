/*
** mkshot-z - Experimental OneShot (2016) engine reimplementation for modders.
**
** Copyright (C) 2026 Reverium <https://github.com/reverium>
** Copyright (C) 2024 hat_kid <https://github.com/thehatkid> (ModShot-mkxp-z)
** Copyright (C) 2013-2023 Amaryllis Kulla and mkxp-z contributors
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
*/

#pragma once

#include "core/bind/bind-util.hpp"

struct ScriptBinding
{
	/* Starts the part where the binding takes over,
	 * loading the compressed scripts and executing them.
	 * This function returns as soon as the scripts finish
	 * execution or an error is encountered */
	void (*execute) (void);

	/* Instructs the binding
	 * to immediately terminate script execution. This
	 * function will perform a longjmp instead of returning,
	 * so be careful about any variables with local storage */
	void (*terminate) (void);

	/* Instructs the binding to issue a game reset.
	 * Same conditions as for terminate apply */
	void (*reset) (void);
};

/* VTable defined in the binding source */
extern ScriptBinding *scriptBinding;


static void mriBindingExecute();
static void mriBindingTerminate();
static void mriBindingReset();

ScriptBinding scriptBindingImpl = {mriBindingExecute, mriBindingTerminate,
                                   mriBindingReset};

ScriptBinding *scriptBinding = &scriptBindingImpl;

void tableBindingInit();
void etcBindingInit();
void fontBindingInit();
void bitmapBindingInit();
void spriteBindingInit();
void viewportBindingInit();
void planeBindingInit();
void windowBindingInit();
void tilemapBindingInit();
void windowVXBindingInit();
void tilemapVXBindingInit();

void inputBindingInit();
void audioBindingInit();
void graphicsBindingInit();

void fileIntBindingInit();

void httpBindingInit();

// OneShot bindings
void oneshotBindingInit();
void journalBindingInit();
void nikoBindingInit();
void wallpaperBindingInit();

void steamBindingInit();

#ifdef MKSHOT_STEAM
void CUSLBindingInit();
#endif

RB_METHOD(mkshotDelta);
RB_METHOD(mriPrint);
RB_METHOD(mriP);
RB_METHOD(mkshotDataDirectory);
RB_METHOD(mkshotSetTitle);
RB_METHOD(mkshotGetTitle);
RB_METHOD(mkshotDesensitize);
RB_METHOD(mkshotPuts);

RB_METHOD(mkshotPlatform);
RB_METHOD(mkshotIsMacHost);
RB_METHOD(mkshotIsWindowsHost);
RB_METHOD(mkshotIsLinuxHost);
RB_METHOD(mkshotIsUsingRosetta);
RB_METHOD(mkshotIsUsingWine);
RB_METHOD(mkshotIsReallyMacHost);
RB_METHOD(mkshotIsReallyLinuxHost);
RB_METHOD(mkshotIsReallyWindowsHost);

RB_METHOD(mkshotUserLanguage);
RB_METHOD(mkshotUserName);
RB_METHOD(mkshotUserFullName);

RB_METHOD(mkshotGameTitle);
RB_METHOD(mkshotPowerState);
RB_METHOD(mkshotSettingsMenu);
RB_METHOD(mkshotCpuCount);
RB_METHOD(mkshotSystemMemory);
RB_METHOD(mkshotReloadPathCache);
RB_METHOD(mkshotAddPath);
RB_METHOD(mkshotRemovePath);
RB_METHOD(mkshotFileExists);
RB_METHOD(mkshotLaunch);

RB_METHOD(mkshotGetJSONSetting);
RB_METHOD(mkshotSetJSONSetting);
RB_METHOD(mkshotGetAllJSONSettings);

RB_METHOD(mkshotSetDefaultFontFamily);

RB_METHOD(mriRgssMain);
RB_METHOD(mriRgssStop);
RB_METHOD(_kernelCaller);
