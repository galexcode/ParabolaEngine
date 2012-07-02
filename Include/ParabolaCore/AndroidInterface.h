#ifndef PARABOLA_ANDROIDINTERFACE_H
#define PARABOLA_ANDROIDINTERFACE_H

#include "Platform.h"
#include "ScopedFile.h"
#include "StringList.h"

#ifdef PARABOLA_ANDROID
#include <jni.h>
#include <android/log.h>
#endif

PARABOLA_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
///\ingroup Core
///\class AndroidInterface
///\brief Static class to interact with the android platform
/// Please notice that this class is not meant to be used directly by the user. 
/// It is even omitted to the user completely for true cross platform usability.
/// For optimization it is not compiled in other platforms, as it wont be used.
////////////////////////////////////////////////////////////////////////////////
class PARABOLA_API AndroidInterface{
public:
	/// Fetch an asset file in the android file system
	/// Returns true or false wether it could find the file and access it
	/// The ScopedFile must be a pointer to a valid instance, and it will be overriden by the asset found
	/// path is the location of the asset, relative paths will be in the APK assets
	/// Absolute paths to external storage or data path are allowed and will work as well.
	/// The asset suffix will be applied to the path automatically if needed. Change it using setAssetSuffix()
	/// An absolute directory is recognized by the first character being a slash (  /  )
	/// binaryMode is meant to specify if you want to read in binary or text mode ( "rb" and "r" modes )
	static bool getAssetFile(ScopedFile* file, const String &path, bool binaryMode = true);

	/// Get a listing of files/directories within the APK assets, empty path will mean the root directory of assets
	static StringList getAssetList(const String &path);

	/// Sends a text message through the android device, please note the permissions must be requested in the manifest and the legacy java source must be in place.
	static bool sendTextMessage(const String &destinationNumber, const String &content);

	/// Get the current asset suffix
	static String getAssetSuffix();

	/// Set the asset suffix to be automatically applied to paths
	static void setAssetSuffix(const String &suffix);

	/// Get the android package name
	static String getPackageName();

	/// Set the android package name
	static void setPackageName(const String &name);

	/// Get the android activity name
	static String getActivityName();

	/// Request a frame render
	static void requestFrameRender();

	/// Set the android activity name
	static void setActivityName(const String& name);

	/// Set the JNI environment the application is using
	static void setJavaNativeInterfaceEnvironment(JavaVM *environment);

private:
	/// Suffix to automatically append to file names
	/// For now, it is .png because all assets are suffixed with an additional .png to avoid apk compression.
	static String m_AssetSuffix;

	/// The android package name, usually its in the form of com.x.y.z
	static String m_packageName;

	/// The name of the activity, as JNI understands it. Usually something like com/x/y/z/classname
	static String m_JNIActivityName;

	/// JNI virtual machine to get the environment
	static JavaVM* m_javaVM;
};

PARABOLA_NAMESPACE_END
#endif