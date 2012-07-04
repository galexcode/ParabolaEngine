#include "ParabolaCore/FileInterface.h"
#include "ParabolaCore/Application.h"
#include "ParabolaCore/ScopedFile.h"

#include <iostream>
using namespace std;

#ifdef PARABOLA_ANDROID
#include "ParabolaCore/AndroidInterface.h"
#endif

PARABOLA_NAMESPACE_BEGIN
/// The root for file access, empty by default, so the executable directory is used
String FileInterface::m_root = "";


/// Get an open handle to an asset in the underlying filesystem
/// Returns NULL if the file was innacessible or not found
/// By default ReadOnly is passed as the open mode but please notice that in some cases only that flag is allowed
/// For example, when loading an asset packaged in an Android APK
/// Please ensure you delete the handle when you are done
bool FileInterface::getAssetFile(ScopedFile* file, const String &path, bool binaryMode){
	if(!file)return false;

#ifdef PARABOLA_ANDROID
	return AndroidInterface::getAssetFile(file, path, binaryMode);
#elif defined PARABOLA_DESKTOP
	FILE* ff = fopen(path.c_str(), "rb");
	file->open(ff, 0, -1);
	return true;
#endif
}

/// Copies the contents of sourceFile to destinationFile
/// \return true or false whether the operation was successfully made
bool FileInterface::copy(const String &sourceFile, const String &destinationFile){
	//cout<<"Copying: " <<sourceFile<<"\nTo: "<<destinationFile<<endl;

	ScopedFile in(sourceFile, IODevice::BinaryRead);
	ScopedFile out(destinationFile, IODevice::BinaryWrite);
	if(!in.isReady() || !out.isReady() )return false;
	 
	const unsigned int buffer_size = sizeof(char)*1024*5;
	char buffer[buffer_size];
	Int64 bytes_read;
	Int64 totalWritten = 0;
	do{
		bytes_read = in.read(&buffer[0], buffer_size);
		out.write(&buffer[0], bytes_read);
		totalWritten += bytes_read;
	}while(bytes_read > 0);

	//cout<<"Written copy of file: "<< destinationFile<<endl<<totalWritten<< "bytes."<<endl;

	return true;
};

PARABOLA_NAMESPACE_END