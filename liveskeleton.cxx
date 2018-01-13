/**	\file	liveskeleton.cxx
*	Library declarations.
*	Contains the basic routines to declare the DLL as a loadable
*	library for FiLMBOX.
*/

//--- SDK include
#include <fbsdk/fbsdk.h>

#ifdef KARCH_ENV_WIN
	#include <windows.h>
#endif

//--- Library declaration
FBLibraryDeclare( liveskeleton )
{
	FBLibraryRegister( LiveSkeleton	);
	FBLibraryRegister( LiveSkeletonLayout	);
}
FBLibraryDeclareEnd;

/************************************************
 *	Library functions.
 ************************************************/
bool FBLibrary::LibInit()	{ return true; }
bool FBLibrary::LibOpen()	{ return true; }
bool FBLibrary::LibReady()	{ return true; }
bool FBLibrary::LibClose()	{ return true; }
bool FBLibrary::LibRelease(){ return true; }

