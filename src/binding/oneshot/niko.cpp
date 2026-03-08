#include "binding/util.hpp"
#include "core/shared-state.hpp"
#include "core/sys/sys.hpp"
#include "core/oneshot/oneshot.hpp"
#include "core/oneshot/journal.hpp"

RB_METHOD(nikoPrepare)
{
	RB_UNUSED_PARAM;

#if MKSHOT_PLATFORM != MKSHOT_PLATFORM_WINDOWS
	// Needed on non-Windows to prepare (start) Journal program
	shState->oneshot().journal->nikoPrepare();
#endif

	return Qnil;
}

RB_METHOD(nikoStart)
{
	RB_UNUSED_PARAM;

	shState->oneshot().journal->nikoStart();

	return Qnil;
}

void nikoBindingInit()
{
	VALUE module = rb_define_module("Niko");

	_rb_define_module_function(module, "get_ready", nikoPrepare);
	_rb_define_module_function(module, "do_your_thing", nikoStart);
}
