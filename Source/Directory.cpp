#include <ParabolaCore/Directory.h>

#ifdef PARABOLA_WINDOWS
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#endif
PARABOLA_NAMESPACE_BEGIN

/// Get the extension of the file
/// The '.' is not included; ex: "png", "jpg", "html"
/// Empty string is returned if there is no extension present
String Path::getExtension()
{
	return m_path.substr(m_path.find_last_of('.')+1, m_path.size()-1);
};

/// Test if the path is relative or absolute
bool Path::isRelativePath()
{
#ifdef PARABOLA_WINDOWS
	// on windows, special handling
	if(PathIsRelativeA(m_path.c_str())){
		return true;
	}
#else
	// for every other non windows system, the slash defines an absolute path
	if(!m_path.empty() && m_path[0] == '/')
	{
		return true;
	}
#endif
	return false;
};

PARABOLA_NAMESPACE_END