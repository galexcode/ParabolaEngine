#include <ParabolaCore/Clipboard.h>

#include <stdio.h>
#include <windows.h>

PARABOLA_NAMESPACE_BEGIN

/// Returns the current contents of the clipboard
String Clipboard::getClipboardText(){
	HANDLE clip;
	if (OpenClipboard(NULL)) 
		clip = GetClipboardData(CF_TEXT);
	printf("%s\n",clip);
	return "";
}

PARABOLA_NAMESPACE_END