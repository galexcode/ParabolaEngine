#ifndef PARABOLA_SIGNALS_H
#define PARABOLA_SIGNALS_H

#include <sigc++/sigc++.h>
#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN	
	using sigc::ptr_fun;

	typedef sigc::signal<void> void_signal;
	typedef sigc::signal<int> int_signal;
	typedef sigc::signal<float> float_signal;
	typedef sigc::signal<double> double_signal;
	typedef sigc::signal<unsigned long> unsigned_long_signal;
	typedef sigc::signal<bool> bool_signal;

PARABOLA_NAMESPACE_END

#endif