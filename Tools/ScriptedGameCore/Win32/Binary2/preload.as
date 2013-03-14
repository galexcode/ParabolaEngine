// Pre-load assets of the game - browser only
void preload(BrowserPreloader@ preloader)
{
	// Ensure downloads
	//ContentLoader.addDirectory("levels", false);
	//ContentLoader.addFile("package1.pak");
	
	preloader.download("Scripts/Main.as", "Scripts/Main.as");

	// Assign a custom preload state
	//ContentLoader.setCustomPreloadState("custom_preload.as");
	
	// Optionally skip preload and have no assets
	//ContentLoader.enablePreload(false);
}

void test()
{
	//testP();
}

string getMainScript()
{
	return "Scripts/Main.as";
}

string getName()
{
	return "Arkanoid";
}

string getVersion()
{
	return "0.0.1";
}


