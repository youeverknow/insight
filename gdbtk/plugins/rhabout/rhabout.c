/* Sample command procedure library for a plug-in. */

/* You have to include the Tcl headers, of course. */
#include <tcl.h>

/* Define the functions that implement your commands as required by Tcl */
#if defined(__WIN32__) || defined(_WIN64)
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT /* nothing */
#endif

int extra_text (ClientData clientData,
                Tcl_Interp *interp,
                int objc, Tcl_Obj *CONST objv[]);

/* Here you actually do whatever you want, like calling your target 
   libraries etc.  Here we just return a string. */

int
extra_text (ClientData clientData,
                Tcl_Interp *interp,
                int objc, Tcl_Obj *CONST objv[])
{
  Tcl_SetObjResult (interp,
		    Tcl_NewStringObj ("\nThis is a sample plug-in\n", -1));
  return TCL_OK;
}

/* Initialization function required in Tcl libraries. */

int EXPORT
Rhabout_Init (Tcl_Interp *interp)
{
  /* Register your command as a Tcl command with this interpreter. */
  Tcl_CreateObjCommand (interp, "rhabout_extra_text", extra_text,
                        (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);

  /* Register this package */
  Tcl_PkgProvide (interp, "RHABOUT", "1.0");
  return TCL_OK;
}

/* This is REQUIRED for native windows implementations. */
#ifdef TCL_PLATFORM_WIN
#include <windows.h>
#include <tclInt.h>

struct _reent *_impure_ptr;
extern struct _reent *_imp__reent_data;

BOOL APIENTRY
DllMain (HINSTANCE hInstance, DWORD reason, LPVOID reserved)
{
  _impure_ptr = _imp__reent_data;
  return TRUE;
}
#endif
