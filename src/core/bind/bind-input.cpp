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

#include <SDL3/SDL_joystick.h>
#include <string>


#include "core/event-thread.hpp"

#include "core/bind/bind-util.hpp"
#include "util/exception.hpp"
#include "core/input/input.hpp"
#include "core/shared-state.hpp"
#include "util/util.hpp"

RB_METHOD(inputDelta) {
    RB_UNUSED_PARAM;

    return rb_float_new(shState->input().getDelta());
}

RB_METHOD(inputUpdate) {
    RB_UNUSED_PARAM;

    shState->input().update();

    return Qnil;
}

static int getButtonArg(VALUE *argv) {
    int num;

    if (FIXNUM_P(*argv)) {
        num = FIX2INT(*argv);
    } else if (SYMBOL_P(*argv) && rgssVer >= 3) {
        VALUE symHash = getRbData()->buttoncodeHash;
        num = FIX2INT(rb_hash_lookup2(symHash, *argv, INT2FIX(Input::None)));
    } else {
        // FIXME: RMXP allows only few more types that
        // don't make sense (symbols in pre 3, floats)
        num = 0;
    }

    return num;
}

static int getScancodeArg(VALUE *argv) {
    const char *scancode = rb_id2name(SYM2ID(*argv));
    int code{};
    try {
        code = strToScancode[scancode];
    } catch (...) {
        rb_raise(rb_eRuntimeError, "%s is not a valid name of an SDL scancode.", scancode);
    }

    return code;
}

static int getJoystickButtonArg(VALUE *argv) {
    const char *button = rb_id2name(SYM2ID(*argv));
    int btn{};
    try {
        btn = strToGCButton[button];
    } catch (...) {
        rb_raise(rb_eRuntimeError, "%s is not a valid name of an SDL Joystick button.", button);
    }

    return btn;
}

RB_METHOD(inputPress) {
    RB_UNUSED_PARAM;

    rb_check_argc(argc, 1);

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    int num = getButtonArg(&button);

    return rb_bool_new(shState->input().isPressed(num));
}

RB_METHOD(inputTrigger) {
    RB_UNUSED_PARAM;

    rb_check_argc(argc, 1);

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    int num = getButtonArg(&button);

    return rb_bool_new(shState->input().isTriggered(num));
}

RB_METHOD(inputRepeat) {
    RB_UNUSED_PARAM;

    rb_check_argc(argc, 1);

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    int num = getButtonArg(&button);

    return rb_bool_new(shState->input().isRepeated(num));
}

RB_METHOD(inputRelease) {
    RB_UNUSED_PARAM;

    rb_check_argc(argc, 1);

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    int num = getButtonArg(&button);

    return rb_bool_new(shState->input().isReleased(num));
}

RB_METHOD(inputCount) {
    RB_UNUSED_PARAM;

    rb_check_argc(argc, 1);

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    int num = getButtonArg(&button);

    return UINT2NUM(shState->input().count(num));
}

RB_METHOD(inputRepeatTime) {
    RB_UNUSED_PARAM;

    rb_check_argc(argc, 1);

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    int num = getButtonArg(&button);

    return rb_float_new(shState->input().repeatTime(num));
}

RB_METHOD(inputPressEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getScancodeArg(&button);
        return rb_bool_new(shState->input().isPressedEx(num, 0));
    }

    return rb_bool_new(shState->input().isPressedEx(NUM2INT(button), 1));
}

RB_METHOD(inputTriggerEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getScancodeArg(&button);
        return rb_bool_new(shState->input().isTriggeredEx(num, 0));
    }

    return rb_bool_new(shState->input().isTriggeredEx(NUM2INT(button), 1));
}

RB_METHOD(inputRepeatEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getScancodeArg(&button);
        return rb_bool_new(shState->input().isRepeatedEx(num, 0));
    }

    return rb_bool_new(shState->input().isRepeatedEx(NUM2INT(button), 1));
}

RB_METHOD(inputReleaseEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getScancodeArg(&button);
        return rb_bool_new(shState->input().isReleasedEx(num, 0));
    }

    return rb_bool_new(shState->input().isReleasedEx(NUM2INT(button), 1));
}

RB_METHOD(inputCountEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getScancodeArg(&button);
        return UINT2NUM(shState->input().repeatcount(num, 0));
    }

    return UINT2NUM(shState->input().repeatcount(NUM2INT(button), 1));
}

RB_METHOD(inputRepeatTimeEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getScancodeArg(&button);
        return rb_float_new(shState->input().repeatTimeEx(num, 0));
    }

    return rb_float_new(shState->input().repeatTimeEx(NUM2INT(button), 1));
}

RB_METHOD(inputDir4) {
    RB_UNUSED_PARAM;

    return rb_fix_new(shState->input().dir4Value());
}

RB_METHOD(inputDir8) {
    RB_UNUSED_PARAM;

    return rb_fix_new(shState->input().dir8Value());
}

/* Non-standard extensions */
RB_METHOD(inputMouseX) {
    RB_UNUSED_PARAM;

    return rb_fix_new(shState->input().mouseX());
}

RB_METHOD(inputMouseY) {
    RB_UNUSED_PARAM;

    return rb_fix_new(shState->input().mouseY());
}

RB_METHOD(inputScrollV) {
    RB_UNUSED_PARAM;

    return rb_fix_new(shState->input().scrollV());
}

RB_METHOD(inputMouseInWindow) {
    RB_UNUSED_PARAM;

    return rb_bool_new(shState->input().mouseInWindow());
}

RB_METHOD(inputRawKeyStates) {
    RB_UNUSED_PARAM;

    VALUE ret = rb_ary_new();

    uint8_t *states = shState->input().rawKeyStates();

    for (unsigned int i = 0; i < shState->input().rawKeyStatesLength(); i++)
        rb_ary_push(ret, rb_bool_new(states[i]));

    return ret;
}

#define M_SYMBOL(x) ID2SYM(rb_intern(x))
#define POWERCASE(v, c)                                                        \
case SDL_POWERSTATE_##c:                                                 \
v = M_SYMBOL(#c);                                                          \
break;

RB_METHOD(inputJoystickConnected) {
    RB_UNUSED_PARAM;

    return rb_bool_new(shState->input().getJoystickConnected());
}

RB_METHOD(inputJoystickName) {
    RB_UNUSED_PARAM;

    if (!shState->input().getJoystickConnected())
        return rb_utf8_str_new_cstr("");

    return rb_utf8_str_new_cstr(shState->input().getJoystickName());
}

RB_METHOD(inputJoystickPowerInfo) {
    RB_UNUSED_PARAM;

    VALUE ret;

    if (!shState->input().getJoystickConnected())
        ret = M_SYMBOL("UNKNOWN");

    switch (shState->input().getJoystickPowerInfo()) {
    case SDL_POWERSTATE_ERROR:
        rb_raise(rb_eRuntimeError, "Error getting joystick power info: %s", SDL_GetError());
        break;

    POWERCASE(ret, ON_BATTERY);
    POWERCASE(ret, NO_BATTERY);
    POWERCASE(ret, CHARGING);
    POWERCASE(ret, CHARGED);

    case SDL_POWERSTATE_UNKNOWN:
    default:
        ret = M_SYMBOL("UNKNOWN");
        break;
    }

    return ret;
}

#define AXISFUNC(n, ax1, ax2) \
RB_METHOD(inputJoystickGet##n##Axis) {\
RB_UNUSED_PARAM;\
VALUE ret = rb_ary_new(); \
if (!shState->eThread().getJoystickConnected()) {\
rb_ary_push(ret, rb_float_new(0)); rb_ary_push(ret, rb_float_new(0)); \
}\
rb_ary_push(ret, rb_float_new(shState->input().getJoystickAxisValue(SDL_GAMEPAD_AXIS_##ax1) / 32767.0)); \
rb_ary_push(ret, rb_float_new(shState->input().getJoystickAxisValue(SDL_GAMEPAD_AXIS_##ax2) / 32767.0)); \
return ret; \
}

AXISFUNC(Left, LEFTX, LEFTY);
AXISFUNC(Right, RIGHTX, RIGHTY);
AXISFUNC(Trigger, LEFT_TRIGGER, RIGHT_TRIGGER);

#undef POWERCASE
#undef M_SYMBOL

RB_METHOD(inputJoystickPressEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getJoystickButtonArg(&button);
        return rb_bool_new(shState->input().controllerIsPressedEx(num));
    }

    return rb_bool_new(shState->input().controllerIsPressedEx(NUM2INT(button)));
}

RB_METHOD(inputJoystickTriggerEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getJoystickButtonArg(&button);
        return rb_bool_new(shState->input().controllerIsTriggeredEx(num));
    }

    return rb_bool_new(shState->input().controllerIsTriggeredEx(NUM2INT(button)));
}

RB_METHOD(inputJoystickRepeatEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getJoystickButtonArg(&button);
        return rb_bool_new(shState->input().controllerIsRepeatedEx(num));
    }

    return rb_bool_new(shState->input().controllerIsRepeatedEx(NUM2INT(button)));
}

RB_METHOD(inputJoystickReleaseEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getJoystickButtonArg(&button);
        return rb_bool_new(shState->input().controllerIsReleasedEx(num));
    }

    return rb_bool_new(shState->input().controllerIsReleasedEx(NUM2INT(button)));
}

RB_METHOD(inputJoystickCountEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getJoystickButtonArg(&button);
        return rb_bool_new(shState->input().controllerRepeatcount(num));
    }

    return rb_bool_new(shState->input().controllerRepeatcount(NUM2INT(button)));
}

RB_METHOD(inputJoystickRepeatTimeEx) {
    RB_UNUSED_PARAM;

    VALUE button;
    rb_scan_args(argc, argv, "1", &button);

    if (SYMBOL_P(button)) {
        int num = getJoystickButtonArg(&button);
        return rb_float_new(shState->input().controllerRepeatTimeEx(num));
    }

    return rb_float_new(shState->input().controllerRepeatTimeEx(NUM2INT(button)));
}

RB_METHOD(inputJoystickRawButtonStates) {
    RB_UNUSED_PARAM;

    VALUE ret = rb_ary_new();
    uint8_t *states = shState->input().rawButtonStates();

    for (unsigned int i = 0; i < shState->input().rawButtonStatesLength(); i++)
        rb_ary_push(ret, rb_bool_new(states[i]));

    return ret;
}

RB_METHOD(inputJoystickRawAxes) {
    RB_UNUSED_PARAM;

    VALUE ret = rb_ary_new();
    int16_t *states = shState->input().rawAxes();

    for (unsigned int i = 0; i < shState->input().rawAxesLength(); i++)
        rb_ary_push(ret, rb_float_new(states[i] / 32767.0));

    return ret;
}

RB_METHOD(inputGetMode) {
    RB_UNUSED_PARAM;

    return rb_bool_new(shState->input().getTextInputMode());
}

RB_METHOD(inputSetMode) {
    RB_UNUSED_PARAM;

    bool mode;
    rb_get_args(argc, argv, "b", &mode RB_ARG_END);

    shState->input().setTextInputMode(mode);

    return mode;
}

RB_METHOD(inputGets) {
    RB_UNUSED_PARAM;
    shState->eThread().lockText(true);
    VALUE ret = rb_utf8_str_new_cstr(shState->input().getText());
    shState->input().clearText();
    shState->eThread().lockText(false);
    return ret;
}

RB_METHOD(inputGetClipboard) {
    RB_UNUSED_PARAM;
    VALUE ret;
    try {
        ret = rb_utf8_str_new_cstr(shState->input().getClipboardText());
    } catch (const Exception &e) {
        raiseRbExc(e);
    }
    return ret;
}

RB_METHOD(inputSetClipboard) {
    RB_UNUSED_PARAM;

    VALUE str;
    rb_scan_args(argc, argv, "1", &str);

    SafeStringValue(str);

    try {
        shState->input().setClipboardText(RSTRING_PTR(str));
    } catch (const Exception &e) {
        raiseRbExc(e);
    }
    return str;
}

RB_METHOD(inputQuit)
{
    RB_UNUSED_PARAM;

    return rb_bool_new(shState->input().hasQuit());
}

struct {
    const char *str;
    Input::ButtonCode val;
} static buttonCodes[] = {
    { "UP",    Input::Up    },
    { "DOWN",  Input::Down  },
    { "LEFT",  Input::Left  },
    { "RIGHT", Input::Right },

    { "ACTION",     Input::Action     },
    { "CANCEL",     Input::Cancel     },
    { "MENU",       Input::Menu       },
    { "ITEMS",      Input::Items      },
    { "RUN",        Input::Run        },
    { "DEACTIVATE", Input::Deactivate },

    { "L", Input::L },
    { "R", Input::R },

    { "SHIFT", Input::Shift },
    { "CTRL",  Input::Ctrl  },
    { "ALT",   Input::Alt   },

    { "F5", Input::F5 },
    { "F6", Input::F6 },
    { "F7", Input::F7 },
    { "F8", Input::F8 },
    { "F9", Input::F9 },

    { "MOUSELEFT",   Input::MouseLeft   },
    { "MOUSEMIDDLE", Input::MouseMiddle },
    { "MOUSERIGHT",  Input::MouseRight  },
    { "MOUSEX1",     Input::MouseX1     },
    { "MOUSEX2",     Input::MouseX2     }
};

static elementsN(buttonCodes);

void inputBindingInit() {
    VALUE module = rb_define_module("Input");

    _rb_define_module_function(module, "delta", inputDelta);
    _rb_define_module_function(module, "update", inputUpdate);
    _rb_define_module_function(module, "press?", inputPress);
    _rb_define_module_function(module, "trigger?", inputTrigger);
    _rb_define_module_function(module, "repeat?", inputRepeat);
    _rb_define_module_function(module, "release?", inputRelease);
    _rb_define_module_function(module, "count", inputCount);
    _rb_define_module_function(module, "time?", inputRepeatTime);
    _rb_define_module_function(module, "pressex?", inputPressEx);
    _rb_define_module_function(module, "triggerex?", inputTriggerEx);
    _rb_define_module_function(module, "repeatex?", inputRepeatEx);
    _rb_define_module_function(module, "releaseex?", inputReleaseEx);
    _rb_define_module_function(module, "repeatcount", inputCountEx);
    _rb_define_module_function(module, "timeex?", inputRepeatTimeEx);
    _rb_define_module_function(module, "dir4", inputDir4);
    _rb_define_module_function(module, "dir8", inputDir8);

    _rb_define_module_function(module, "mouse_x", inputMouseX);
    _rb_define_module_function(module, "mouse_y", inputMouseY);
    _rb_define_module_function(module, "scroll_v", inputScrollV);
    _rb_define_module_function(module, "mouse_in_window", inputMouseInWindow);
    _rb_define_module_function(module, "mouse_in_window?", inputMouseInWindow);

    _rb_define_module_function(module, "raw_key_states", inputRawKeyStates);

    VALUE submod = rb_define_module_under(module, "Joystick");
    _rb_define_module_function(submod, "connected?", inputJoystickConnected);
    _rb_define_module_function(submod, "name", inputJoystickName);
    _rb_define_module_function(submod, "power_info", inputJoystickPowerInfo);
    _rb_define_module_function(submod, "axes_left", inputJoystickGetLeftAxis);
    _rb_define_module_function(submod, "axes_right", inputJoystickGetRightAxis);
    _rb_define_module_function(submod, "axes_trigger", inputJoystickGetTriggerAxis);
    _rb_define_module_function(submod, "raw_button_states", inputJoystickRawButtonStates);
    _rb_define_module_function(submod, "raw_axes", inputJoystickRawAxes);
    _rb_define_module_function(submod, "pressex?", inputJoystickPressEx);
    _rb_define_module_function(submod, "triggerex?", inputJoystickTriggerEx);
    _rb_define_module_function(submod, "repeatex?", inputJoystickRepeatEx);
    _rb_define_module_function(submod, "releaseex?", inputJoystickReleaseEx);
    _rb_define_module_function(submod, "repeatcount", inputJoystickCountEx);
    _rb_define_module_function(submod, "timeex?", inputJoystickRepeatTimeEx);

    _rb_define_module_function(module, "text_input", inputGetMode);
    _rb_define_module_function(module, "text_input=", inputSetMode);
    _rb_define_module_function(module, "gets", inputGets);

    _rb_define_module_function(module, "clipboard", inputGetClipboard);
    _rb_define_module_function(module, "clipboard=", inputSetClipboard);

    _rb_define_module_function(module, "quit?", inputQuit);

    if (rgssVer >= 3) {
        VALUE symHash = rb_hash_new();

        for (size_t i = 0; i < buttonCodesN; ++i) {
            ID sym = rb_intern(buttonCodes[i].str);
            VALUE val = INT2FIX(buttonCodes[i].val);

            /* In RGSS3 all Input::XYZ constants are equal to :XYZ symbols,
             * to be compatible with the previous convention */
            rb_const_set(module, sym, ID2SYM(sym));
            rb_hash_aset(symHash, ID2SYM(sym), val);
        }

        rb_iv_set(module, "buttoncodes", symHash);
        getRbData()->buttoncodeHash = symHash;
    } else {
        for (size_t i = 0; i < buttonCodesN; ++i) {
            ID sym = rb_intern(buttonCodes[i].str);
            VALUE val = INT2FIX(buttonCodes[i].val);

            rb_const_set(module, sym, val);
        }
    }
}
