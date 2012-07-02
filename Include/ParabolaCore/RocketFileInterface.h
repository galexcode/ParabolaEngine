#ifndef PARABOLA_ROCKETFILEINTERFACE_H
#define PARABOLA_ROCKETFILEINTERFACE_H

#include "Platform.h"
#include "Strings.h"
#include <Rocket/Core/String.h>
#include <Rocket/Core/FileInterface.h>

PARABOLA_NAMESPACE_BEGIN

/**
	\class RocketFileInterface
	\brief The Custom Rocket File Interface - Disabled
*/
class RocketFileInterface : public Rocket::Core::FileInterface{
	public:
		RocketFileInterface(const Rocket::Core::String& root);
		virtual ~RocketFileInterface();

		/// Opens a file.		
		virtual Rocket::Core::FileHandle Open(const Rocket::Core::String& path);

		/// Closes a previously opened file.
		virtual void Close(Rocket::Core::FileHandle file);

		/// Reads data from a previously opened file.		
		virtual size_t Read(void* buffer, size_t size, Rocket::Core::FileHandle file);

		/// Seeks to a point in a previously opened file.		
		virtual bool Seek(Rocket::Core::FileHandle file, long offset, int origin);

		/// Returns the current position of the file pointer.		
		virtual size_t Tell(Rocket::Core::FileHandle file);

	private:
		Rocket::Core::String root;
};

PARABOLA_NAMESPACE_END
#endif