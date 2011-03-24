#include "StdAfx.h"
#include "ca2/radix/cafxdllx.h"


static AFX_EXTENSION_MODULE VmscdadecDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
      ::OutputDebugStringA("audio_decode_windows_media.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(VmscdadecDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an ca2 API Regular DLL (such as an ActiveX control)
		//  instead of an ca2 API application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(VmscdadecDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		::OutputDebugStringA("audio_decode_windows_media.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(VmscdadecDLL);
	}
	return 1;   // ok
}
