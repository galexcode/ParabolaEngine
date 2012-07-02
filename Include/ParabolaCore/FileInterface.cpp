#include "ParabolaCore/FileInterface.h"
#include "ParabolaCore/Application.h"
#include "ParabolaCore/ScopedFile.h"

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

PARABOLA_NAMESPACE_END