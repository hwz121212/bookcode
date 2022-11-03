================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : Ex16b Project Overview
===============================================================================

The application wizard has created this Ex16b application for 
you.  This application not only demonstrates the basics of using the Microsoft 
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your Ex16b application.

Ex16b.vcproj
    This is the main project file for VC++ projects generated using an application wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    application wizard.

Ex16b.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CEx16bApp application class.

Ex16b.cpp
    This is the main application source file that contains the application
    class CEx16bApp.

Ex16b.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\Ex16b.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file Ex16b.rc.

res\Ex16b.rc2
    This file contains resources that are not edited by Microsoft 
    Visual C++. You should place all resources not editable by
    the resource editor in this file.
Ex16b.reg
    This is an example .reg file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .reg
    file to go along with your application or just delete it and rely
    on the default RegisterShellFileTypes registration.
/////////////////////////////////////////////////////////////////////////////

For the main frame window:
    The project includes a standard MFC interface.
MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CMDIFrameWnd and controls all MDI frame features.
res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in Ex16b.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

For the child frame window:

ChildFrm.h, ChildFrm.cpp
    These files define and implement the CChildFrame class, which
    supports the child windows in an MDI application.

/////////////////////////////////////////////////////////////////////////////

The application wizard creates one document type and one view:

Ex16bDoc.h, Ex16bDoc.cpp - the document
    These files contain your CEx16bDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CEx16bDoc::Serialize).
    The Document will have the following strings:
        File extension:      16b
        File type ID:        Ex16b.Document
        Main frame caption:  Ex16b
        Doc type name:       Ex16b
        Filter name:         Ex16b Files (*.16b)
        File new short name: Ex16b
        File type long name: Ex16b.Document
Ex16bView.h, Ex16bView.cpp - the view of the document
    These files contain your CEx16bView class.
    CEx16bView objects are used to view CEx16bDoc objects.
res\Ex16bDoc.ico
    This is an icon file, which is used as the icon for MDI child windows
    for the CEx16bDoc class.  This icon is included by the main
    resource file Ex16b.rc.
/////////////////////////////////////////////////////////////////////////////

Other Features:

ActiveX Controls
    The application includes support to use ActiveX controls.
/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Ex16b.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

Ex16b.manifest
	Application manifest files are used by Windows XP to describe an applications 
	dependency on specific versions of Side-by-Side assemblies. The loader uses this 
	information to load the appropriate assembly from the assembly cache or private 
	from the application. The Application manifest  maybe included for redistribution 
	as an external .manifest file that is installed in the same folder as the application 
	executable or it may be included in the executable in the form of a resource. 
/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is in a 
language other than the operating system's current language, you will need 
to copy the corresponding localized resources MFC70XXX.DLL from the Microsoft
Visual C++ CD-ROM under the Win\System directory to your computer's system or 
system32 directory, and rename it to be MFCLOC.DLL.  ("XXX" stands for the 
language abbreviation.  For example, MFC70DEU.DLL contains resources 
translated to German.)  If you don't do this, some of the UI elements of 
your application will remain in the language of the operating system.

/////////////////////////////////////////////////////////////////////////////
