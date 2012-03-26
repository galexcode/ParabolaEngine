#ifndef PARABOLA_LOGGER_H
#define PARABOLA_LOGGER_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

namespace LoggerSettings{
	/// Verbose modes of the logger
	/// A log is always output with a verbose mode
	/// It is shown in that verbose mode, and all the lower ones.
	enum Modes{
		NONE = 0, /// Nothing is output
		DETAIL, 
		NORMAL, /// 
		CRITICAL,
		FATAL, /// Only fatal errors are output
	};
};

/**
	\ingroup Core
	\class Logger
	\brief Ability to log information into multiple destinations
*/
class PARABOLA_API Logger{
public:

	/// Simply outputs the string into the stdout
	static void fastLog(const String &output);

private:
	bool myEnabled;
	LoggerSettings::Modes myVerboseMode;
};

#ifdef PARABOLA_BUILD_DEBUG
#define DEBUG_MESSAGE(x) Logger::fastLog(x);
#elif defined PARABOLA_BUILD_RELEASE
#define DEBUG_MESSAGE(x) 
#endif

PARABOLA_NAMESPACE_END
#endif