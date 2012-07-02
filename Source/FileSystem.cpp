#include "ParabolaCore/FileSystem.h"
#include "ParabolaCore/Application.h"

#ifdef PARABOLA_WINDOWS
#include <windows.h>
#include <CommDlg.h>
#undef SetCurrentDirectory
#endif

PARABOLA_NAMESPACE_BEGIN
	String FileSystem::myCurrentDirectory;


/// Load a dialog
String FileSystem::loadFileDialog(){
#ifdef PARABOLA_WINDOWS
		wchar_t Filestring[256];
		String returnstring;

		OPENFILENAME opf;
		opf.hwndOwner = NULL;
		opf.lpstrFilter = L"";
		opf.lpstrCustomFilter = 0;
		opf.nMaxCustFilter = 0L;
		opf.nFilterIndex = 1L;
		opf.lpstrFile = (LPWSTR)&Filestring;
		opf.lpstrFile[0] = '\0';
		opf.nMaxFile = 256;
		opf.lpstrFileTitle = 0;
		opf.nMaxFileTitle=50;
		opf.lpstrInitialDir = L"C:\\";
		opf.lpstrTitle = L"Rocks Papers";
		opf.nFileOffset = 0;
		opf.nFileExtension = 0;
		opf.lpstrDefExt = L"*.*";
		opf.lpfnHook = NULL;
		opf.lCustData = 0;
		opf.Flags = (OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR) & ~OFN_ALLOWMULTISELECT ;
		opf.lStructSize = sizeof(OPENFILENAME);

		if(GetOpenFileName(&opf))
		{
			returnstring.fromWide(static_cast<std::wstring>(opf.lpstrFile));
		}

		return returnstring;
#else
	return "";
#endif
};

/// Testing \todo make
String FileSystem::saveFileDialog(){
#ifdef PARABOLA_WINDOWS
	OPENFILENAME ofn;
	String result;

	wchar_t saveFileName[MAX_PATH] = L"";

	ZeroMemory( &ofn, sizeof( ofn ) );

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Script file (*.as)\0*.as\0";
	ofn.lpstrFile = saveFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = L"as";
	ofn.Flags  = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	ofn.lpstrTitle = L"Save File";
	

	if(GetSaveFileName(&ofn)){
		result.fromWide(static_cast<std::wstring>(ofn.lpstrFile));
	}

	return result;
	//	wcscpy(file,saveFileName);
#else
	return "";
#endif
};

	StringList FileSystem::scanDirectory(const String &Directory, const String &Extension, bool Recursive){
		//std::vector<String> Files;

		StringList Files;
		{
		#ifdef PARABOLA_WINDOWS ////////////////////////////////////////////////////WINDOWS CONFIG
			String Query = Directory + String("\\*.") + Extension;
			WIN32_FIND_DATAA FileData;
			HANDLE hFindHandle = INVALID_HANDLE_VALUE;
			hFindHandle = FindFirstFileA(Query.c_str(), &FileData);

			if(hFindHandle == INVALID_HANDLE_VALUE)
				return Files;

			String FileName(FileData.cFileName);

			if(FileName[0] != '.')
			{
				if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if(Recursive)
					{
						StringList t(scanDirectory(Directory + String("/") +
							String(FileData.cFileName), Extension, Recursive));

						Files.insert(Files.end(), t.begin(), t.end());
					};
				}
				else
				{
					String FileName(FileData.cFileName);
					Files.push_back(Directory + String("/") + FileName);
				};
			};

			while(FindNextFileA(hFindHandle, &FileData))
			{
				FileName = FileData.cFileName;

				if(FileName[0] != '.')
				{
					if(Recursive)
					{
						StringList t(scanDirectory(Directory + String("/") +
							String(FileData.cFileName), Extension, Recursive));

						Files.insert(Files.end(), t.begin(), t.end());
					}

					Files.insert(Files.end(), Directory + String("/") + FileName);

				}
				else
				{
					//Files.insert(Files.end(), Directory + String("/") + FileName);
				};
			};

			FindClose(hFindHandle);
		#elif defined(PARABOLA_PLATFORM_LINUX) || defined(PARABOLA_PLATFORM_MAC)///////////////////////MAC|LINUX
			DIR *Root = opendir (Directory);

			if(Root == nullptr)
			{
				return Files;
			}

			dirent *Entry = readdir(Root);

			while(Entry != nullptr)
			{
				String FileName(Entry->d_name);

				if(FileName[0] != '.')
				{
					if(Entry->d_type == DT_DIR)
					{
						if(Recursive)
						{
							std::vector<String> t(scanDirectory(Directory + String("/") +
								String(FileData.cFileName), Extension, Recursive));

							Files.insert(Files.end(), t.begin(), t.end());
						};
					}
					else if(Entry->d_type == DT_REG)
					{
						Files.push_back(Directory + String("/") + FileName);
					};
				};

				Entry = readdir(Root);
			}

			closedir(Root);
	#elif defined PARABOLA_ANDROID
		Files = Application::myInstance->getAssetList(Directory);
#else 
#error Platform filesystem unsupported

	#endif
		}

		return Files;
	}

	
	bool FileSystem::isDirectory(String Directory){
		#ifdef PARABOLA_WINDOWS ////////////////////////////////////////////////////WINDOWS CONFIG
			String Query = Directory;
			WIN32_FIND_DATAA FileData;
			HANDLE hFindHandle = INVALID_HANDLE_VALUE;
			hFindHandle = FindFirstFileA(Query.c_str(), &FileData);

			if(hFindHandle == INVALID_HANDLE_VALUE)
				return false;

			String FileName(FileData.cFileName);
			if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				return true;
			else
				return false;

		#else

		#endif
	};


	bool FileSystem::isFile(String fileName){
		#ifdef PARABOLA_WINDOWS ////////////////////////////////////////////////////WINDOWS CONFIG
			String Query = fileName;
			WIN32_FIND_DATAA FileData;
			HANDLE hFindHandle = INVALID_HANDLE_VALUE;
			hFindHandle = FindFirstFileA(Query.c_str(), &FileData);

			if(hFindHandle == INVALID_HANDLE_VALUE)
				return false;

			String FileName(FileData.cFileName);
			if(FileData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
				return true;
			else
				return false;

		#else

		#endif
	}


	StringList FileSystem::directoryList(String Where, bool KeepRelativePath){
		StringList Files;
		{
		#ifdef PARABOLA_WINDOWS ////////////////////////////////////////////////////WINDOWS CONFIG
			String Query = Where + String("\\*");
			WIN32_FIND_DATAA FileData;
			HANDLE hFindHandle = INVALID_HANDLE_VALUE;
			hFindHandle = FindFirstFileA(Query.c_str(), &FileData);

			if(hFindHandle == INVALID_HANDLE_VALUE)
				return Files;

			String FileName(FileData.cFileName);

			if(FileName[0] != '.' && FileName != "..")
			{
				if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					String FileName(FileData.cFileName);
					if(KeepRelativePath)
						Files.push_back(Where + String("/") + FileName);
					else
						Files.push_back(FileData.cFileName);

				}
				
			};

			while(FindNextFileA(hFindHandle, &FileData))
			{
				FileName = FileData.cFileName;

				if(FileName[0] != '.' && FileName != "..")
				{
					if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						String FileName(FileData.cFileName);
						if(KeepRelativePath)
							Files.push_back(Where + String("/") + FileName);
						else
							Files.push_back(FileData.cFileName);
					}
					
				};
			};

			FindClose(hFindHandle);
		#elif defined(PARABOLA_PLATFORM_LINUX) || defined(PARABOLA_PLATFORM_MAC)///////////////////////MAC|LINUX
			DIR *Root = opendir (Directory);

			if(Root == nullptr)
			{
				return Files;
			}

			dirent *Entry = readdir(Root);

			while(Entry != nullptr)
			{
				String FileName(Entry->d_name);

				if(FileName[0] != '.')
				{
					if(Entry->d_type == DT_DIR)
					{
						if(Recursive)
						{
							std::vector<String> t(scanDirectory(Directory + String("/") +
								String(FileData.cFileName), Extension, Recursive));

							Files.insert(Files.end(), t.begin(), t.end());
						};
					}
					else if(Entry->d_type == DT_REG)
					{
						Files.push_back(Directory + String("/") + FileName);
					};
				};

				Entry = readdir(Root);
			}

			closedir(Root); 
#elif defined PARABOLA_ANDROID
			 
#else

		#error 

	#endif
		}

		return Files;
	};


	bool FileSystem::makeDirectory(String Name){

#ifdef PARABOLA_WINDOWS
		if(!CreateDirectory((LPCWSTR)Name.toWide().c_str(), LPSECURITY_ATTRIBUTES()))
			return false;
#endif
		return true;
	}

	String FileSystem::currentDirectory(){
		return myCurrentDirectory;
	}


PARABOLA_NAMESPACE_END
