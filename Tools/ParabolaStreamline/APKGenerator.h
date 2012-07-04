#ifndef APKGenerator_h__
#define APKGenerator_h__

#include <ParabolaCore/StringList.h>
#include <ParabolaCore/ScopedFile.h>

#include <ParabolaCore/FileStream.h>
#include <ParabolaCore/TextStream.h>
#include <ParabolaCore/FileSystem.h>
#include <ParabolaCore/FileInterface.h>
using namespace pE;

#include <map>
using namespace std;

map<String, String> TokenContent;
bool usingAirPush = true;

String m_ProgramDir;

void applyTokens(String &line){

	bool inToken = false;
	int pos = -1;
	String cache;
	for(unsigned int i = 0; i < line.length(); i++){		
		if(line[i] == '%'){

			if(inToken){
				//token finish, swap
				
				//cout<<"Token: "<<cache<<endl;

				if(TokenContent.find(cache) != TokenContent.end()){
					//cout<<"Replacing token: "<<cache<<" with "<<TokenContent[cache]<<endl;
					line.replace(line.begin() + pos, line.begin() + i + 1, TokenContent[cache].begin(), TokenContent[cache].end());
					i =  (unsigned int)( pos + TokenContent[cache].length());
				}

				cache.clear();
				inToken = false;
			}
			else{
				pos = i;
				inToken = true;
			}

			//inToken = !inToken;
		}
		else if(inToken){
			//record the token
			cache += line[i];
		}

	}
}

void convertTokens(String path){
	{
		
		FileInterface::copy(path, "tmpfile");

		ScopedFile txtFile("tmpfile", IODevice::TextRead);

		//now copy back with tokens applied
		TextStream txtStream(&txtFile);

		if(txtFile.isReady()){
			// now read , parse and save into the target file
			ScopedFile out(path, IODevice::TextWrite);
			TextStream outStream(&out);
			if(out.isReady()){
				//save here
			
				//do the parsing

				while(!txtStream.atEnd()){
					String line = txtStream.getLine();
					applyTokens(line);
					outStream << line + "\n";
				}


			}

		}

	} // force the stream out of scope

	::remove("tmpfile");
}

String dumpToString(String path){
	String result;
	ScopedFile inFile(path, IODevice::TextRead);
	TextStream in(&inFile);

	if(inFile.isReady()){
		while(!in.atEnd()){
			result += in.getLine() + "\n";
		}
	}
	
	return result;
}

void prepareApkTokens(){

	TokenContent["PROJECT_PROPERTIES_ANDROID_API"] = String("android-10");
	TokenContent["ANDROID_MANIFEST_AIRPUSH_HOLDER"] = dumpToString(m_ProgramDir + "resources/APKModel/fragments/airpushmanifest.txt");
	TokenContent["PACKAGE_VERSION"] = "1.0"; //hardcoded now
	TokenContent["ANDROID_MANIFEST_ICON_DEFINITION"] = "android:icon=\"@drawable/icon_launcher\""; //hardcoded now
	TokenContent["ANDROID_MANIFEST_ACTIVITY_ORIENTATION"] = "landscape"; //hardcoded now
	TokenContent["ANDROID_MANIFEST_MINSDK"] = "4"; //hardcoded now
	TokenContent["ACTIVITY_CLASS"] = "ParabolaEngineActivity";
	TokenContent["PROJECT_NAME"] = "ParabolaEngineProject";
	TokenContent["ACTIVITY_LABEL"] = "Parabola Engine";
	TokenContent["APPLICATION_LABEL"] = "Parabola Engine";
	TokenContent["AIRPUSH_APPID"] = "52201"; 
	TokenContent["AIRPUSH_APIKEY"] = "337301308105398636";
	TokenContent["AIRPUSH_TESTMODE"] = "true";
	TokenContent["AIRPUSH_PUSHADS"] = "true";
	TokenContent["AIRPUSH_ICONADS"] = "true";

	// To make java code
	TokenContent["ACTIVITY_FEATURE_SENDSMS"] = dumpToString(m_ProgramDir + "resources/APKModel/fragments/sendsms.txt");

	TokenContent["AIRPUSH_IMPORT"] = "import com.airpush.android.Airpush;";


}

bool generateAPK(String path, String packageName, int targetAndroidPlatform){
	
	if(!FileSystem::isDirectory(path)){
		if(!FileSystem::makeDirectory(path)){
			cout<<"Failed to create the directory for the APK"<<endl;
			return false;
		}
	}
	// there is an APK directory by now

	// Fill more tokens
	TokenContent["PACKAGE_NAME"] = packageName;
	
	// Ensure the directory structure
	FileSystem::makeDirectory(path + "/assets");
	FileSystem::makeDirectory(path + "/libs");
	FileSystem::makeDirectory(path + "/libs/armeabi");
	FileSystem::makeDirectory(path + "/res");
	FileSystem::makeDirectory(path + "/res/drawable");
	FileSystem::makeDirectory(path + "/res/drawable-hdpi");
	FileSystem::makeDirectory(path + "/res/drawable-mdpi");
	FileSystem::makeDirectory(path + "/res/drawable-xhdpi");
	FileSystem::makeDirectory(path + "/res/drawable-ldpi");
	FileSystem::makeDirectory(path + "/res/layout");
	FileSystem::makeDirectory(path + "/res/values");
	
	

	// Copy the icon
	FileInterface::copy(m_ProgramDir + "resources/APKModel/res/drawable-hdpi/icon_launcher.png",path + "/res/drawable-hdpi/icon_launcher.png");
	FileInterface::copy(m_ProgramDir + "resources/APKModel/res/drawable-xhdpi/icon_launcher.png",path + "/res/drawable-xhdpi/icon_launcher.png");
	FileInterface::copy(m_ProgramDir + "resources/APKModel/res/drawable-ldpi/icon_launcher.png",path + "/res/drawable-ldpi/icon_launcher.png");
	FileInterface::copy(m_ProgramDir + "resources/APKModel/res/drawable-mdpi/icon_launcher.png",path + "/res/drawable-mdpi/icon_launcher.png");
	// Finished copy the icon

	
	// The localized strings
	FileInterface::copy(m_ProgramDir +"resources/APKModel/res/values/strings.xml", path + "/res/values/strings.xml");
	convertTokens(path + "/res/values/strings.xml");


	// Preparing the Java Source
	FileSystem::makeDirectory(path + "/src");

	StringList packageDecompose;
	packageName.split('.', 0, packageDecompose);
	String packageSrcDir = path + "/src/";
	for(unsigned int j = 0; j < packageDecompose.size(); j++){
		FileSystem::makeDirectory(packageSrcDir + packageDecompose[j]);
		packageSrcDir += packageDecompose[j] + "/";
	}

	// Airpush
	if(usingAirPush){

		// Define some tokens
		

		FileInterface::copy(m_ProgramDir +"resources/APKModel/src/BootReceiver.java", packageSrcDir + "BootReceiver.java");
		convertTokens(packageSrcDir + "BootReceiver.java");

		///copy the lib too.
		FileInterface::copy(m_ProgramDir +"resources/APKModel/libs/AirpushSDK.jar", path + "/libs/AirpushSDK.jar");

	}
	FileInterface::copy(m_ProgramDir +"resources/APKModel/src/Activity.java", packageSrcDir + TokenContent["ACTIVITY_CLASS"] + ".java");
	convertTokens(packageSrcDir + TokenContent["ACTIVITY_CLASS"] + ".java");

	cout<<"[Streamline] Android Activity name: "<<TokenContent["ACTIVITY_CLASS"]<<endl;

	// End of preparing the Java Source

	FileInterface::copy(m_ProgramDir +"resources/APKModel/project.properties", path + "/project.properties");
	FileInterface::copy(m_ProgramDir +"resources/APKModel/local.properties", path + "/local.properties");
	FileInterface::copy(m_ProgramDir +"resources/APKModel/AndroidManifest.xml", path + "/AndroidManifest.xml");
	FileInterface::copy(m_ProgramDir +"resources/APKModel/build.xml", path + "/build.xml");

	convertTokens(path + "/project.properties");
	convertTokens(path + "/AndroidManifest.xml");
	convertTokens(path + "/AndroidManifest.xml"); // second pass because a fragment may be used.
	convertTokens(path + "/build.xml");
	

	return true;
}


#endif // APKGenerator_h__
