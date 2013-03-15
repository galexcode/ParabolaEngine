#ifndef APKAssets_h__
#define APKAssets_h__

#include <ParabolaCore/FileSystem.h>
#include <ParabolaCore/FileInterface.h>
using namespace pE;

#include "Command.h"

class CommandDeployAssets : public Command
{
	void run(int argc, char** argv, ProgramContext& context)
	{
		cout<<"Deploying assets"<<endl;
	}
};

void deployHandleDirectory(String directory, String dest){

	FileSystem::makeDirectory(dest); 

	StringList flist = FileSystem::scanDirectory(directory, "*", false);
	for(unsigned int i = 0; i < flist.size(); i++){
		String relativepath = flist[i];
		if(flist[i].find_last_of('/') != flist[i].npos)
			flist[i].erase(flist[i].begin(), flist[i].begin() + flist[i].find_last_of('/')+1);

		cout<<"[Streamline] Installing file: "<<flist[i]<<endl;


		if(!FileSystem::isDirectory(relativepath)){

			if(!	FileInterface::copy(directory + "/" + flist[i], dest + "/" + flist[i] + ".png") ) cout<<"Failed to install file."<<endl;
		}
	}
	

	/// Check nested directories within this one
	StringList list = FileSystem::directoryList(directory, false);
	for(unsigned int i = 0; i < list.size(); i++){
		cout<<"[Streamline] Deploying directory: "<<directory + "/" + list[i]<<endl;
		deployHandleDirectory(directory + "/" + list[i], dest + "/" + list[i]);
	}


}

void deployAPKAssets(String source, String destinationAPK){
	cout<<"[Streamline] Assembling assets to target APK."<<endl;
	cout<<"[Streamline] Deploying directory: "<<source<<endl;
	deployHandleDirectory(source, destinationAPK + "/assets");
	cout<<"[Streamline] Finished assembling assets to target APK"<<endl;
}

#endif // APKAssets_h__
