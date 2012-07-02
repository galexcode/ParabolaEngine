#include <ParabolaCore/RocketFileInterface.h>
#include <ParabolaCore/ScopedFile.h>
#include <ParabolaCore/FileInterface.h>
#include <ParabolaCore/Logger.h>
#include <ParabolaCore/Application.h>

PARABOLA_NAMESPACE_BEGIN

RocketFileInterface::RocketFileInterface(const Rocket::Core::String& root){

}

RocketFileInterface::~RocketFileInterface(){

}

/// Opens a file.		
Rocket::Core::FileHandle RocketFileInterface::Open(const Rocket::Core::String& path){
	String finalPath = path.CString();
	ScopedFile* fileStream = NULL;

#ifdef PARABOLA_ANDROID
	// is it an asset?
	if(!finalPath.startsWith(Application::myInstance->myDataDirectory) || !finalPath.startsWith(Application::myInstance->myExternalStorageDirectory) ){
		//its an asset , special handling
		TESTLOG("Trying to load an asset for libRocket: read-only from APK\n")
		fileStream = new ScopedFile();
		if(pE::FileInterface::getAssetFile(fileStream, finalPath, true) ){		
			return (Rocket::Core::FileHandle)fileStream;
		}
		else return NULL;
	}
	else{
		// just load normally
		fileStream = new ScopedFile(finalPath, IODevice::TextRead);
		if(fileStream->canRead()){
			return (Rocket::Core::FileHandle)fileStream;
		}
		else return NULL;
	}
	

#elif defined PARABOLA_DESKTOP
	// normal file behaviour
	fileStream = new ScopedFile(finalPath, IODevice::BinaryRead);
	if(fileStream->canRead()){
		 return (Rocket::Core::FileHandle)fileStream;
	}
	else return (Rocket::Core::FileHandle)NULL;

#endif

	return NULL;
}

/// Closes a previously opened file.
void RocketFileInterface::Close(Rocket::Core::FileHandle file){
	delete (ScopedFile*)file;
}

/// Reads data from a previously opened file.		
size_t RocketFileInterface::Read(void* buffer, size_t size, Rocket::Core::FileHandle file){
	ScopedFile* stream = (ScopedFile*)file;
	size_t result = (size_t)stream->read((char*)buffer, size);
	/*String logs = "Trying to read: " + String::number(size)+ " but read: " + String::number(result);
	TESTLOG(logs.c_str())
	String readDone((char*)buffer, result);
	readDone += '\0';
	TESTLOG(readDone.c_str())*/
	return result;
}

/// Seeks to a point in a previously opened file.
bool RocketFileInterface::Seek(Rocket::Core::FileHandle file, long offset, int origin){
	/*String types[] = { "SEEK_SET", "SEEK_CURR", "SEEK_END" };
	String logs = "Seeking to: " + String::number(offset) + " type: " + types[origin];
	TESTLOG(logs.c_str())*/
	return ((ScopedFile*)file)->seek(offset, origin);

} 

/// Returns the current position of the file pointer.		
size_t RocketFileInterface::Tell(Rocket::Core::FileHandle file){
	size_t result = (size_t)((ScopedFile*)file)->tell();	
	/*String logs = "Tell said: " + String::number(result);
	TESTLOG(logs.c_str())*/
	return result;
}

PARABOLA_NAMESPACE_END