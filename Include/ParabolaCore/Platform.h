#ifndef PARABOLAPLATFORM_H
#define PARABOLAPLATFORM_H

	// Engine Version
	#define PARABOLA_VERSION_MAJOR 0
	#define PARABOLA_VERSION_MINOR 7
	#define PARABOLA_VERSION_PATCH 3
	#define PARABOLA_VERSION_STAMP "ParabolaEngine v0.7.3"

	/**
		\namespace pE
		\brief Contains everything from Parabola Engine SDK
	*/
	#define PARABOLA_NAMESPACE_BEGIN namespace pE{
	#define PARABOLA_NAMESPACE_END }

	// Platform & Compiler
	#ifdef _WIN32
        #ifdef _MSC_VER
            #pragma warning(disable : 4251) // annoying dll warning
            #pragma warning(disable : 4275) // annoying dll warning
			#pragma warning(disable : 4355) // warning this in base member initialiser list

            #define PARABOLA_COMPILER "msvc"
            #define PARABOLA_COMPILER_MSVC
            #define _CRT_SECURE_NO_DEPRECATE

        #else //GCC
            #define PARABOLA_COMPILER "gcc"
            #define PARABOLA_COMPILER_GCC
        #endif
		#define PARABOLA_WINDOWS
		#define PARABOLA_OS "win"

		#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
		#endif


    #elif defined __APPLE_CC__
        #define PARABOLA_UNIX
        #define PARABOLA_MAC
        #define PARABOLA_OS "mac"
        #define PARABOLA_COMPILER "gcc"
        #define PARABOLA_COMPILER_GCC

    #else
        #define PARABOLA_UNIX
        #define PARABOLA_LINUX
        #define PARABOLA_OS "linux"
        #define PARABOLA_COMPILER "gcc"
        #define PARABOLA_COMPILER_GCC

	#endif

	#if defined __x86_64__ || defined _M_X64 || defined __powerpc64__ || defined __alpha__ || defined __ia64__ || defined __s390__ || defined __s390x__
        #define PARABOLA_ARCH_64
    #else
        #define PARABOLA_ARCH_32
    #endif


	/*
		\def PARABOLA_API
		\brief This is a define for DLL Imports/Exports

		Every class is declared as class PARABOLA_API Name.

	*/

	// Shared Libraries
	#if defined PARABOLA_DYNAMIC
		#define PARABOLA_API __declspec(dllexport)
	#else
		#define PARABOLA_API
		#define SFML_STATIC
	#endif

	// Build Mode
	#ifdef _DEBUG
		#define PARABOLA_BUILD_DEBUG
	#else
		#define PARABOLA_BUILD_RELEASE
	#endif

PARABOLA_NAMESPACE_BEGIN
	typedef signed   char Int8;
	typedef unsigned char Uint8;
	typedef signed   short Int16;
	typedef unsigned short Uint16;
	typedef signed   int Int32;
	typedef unsigned int Uint32;

	#if defined(_MSC_VER)
		typedef signed   __int64 Int64;
		typedef unsigned __int64 Uint64;
	#else
		typedef signed   long long Int64;
		typedef unsigned long long Uint64;
	#endif
	
PARABOLA_NAMESPACE_END

#define NULL 0

#endif
