================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : Ex23a Project Overview
===============================================================================

The application wizard has created this Ex23a application for 
you.  This application not only demonstrates the basics of using the Microsoft 
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your Ex23a application.

Ex23a.vcproj
    This is the main project file for VC++ projects generated using an application wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    application wizard.

Ex23a.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CEx23aApp application class.

Ex23a.cpp
    This is the main application source file that contains the application
    class CEx23aApp.

Ex23a.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\Ex23a.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file Ex23a.rc.

res\Ex23a.rc2
    This file contains resources that are not edited by Microsoft 
    Visual C++. You should place all resources not editable by
    the resource editor in this file.
Ex23a.reg
    This is an example .reg file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .reg
    file to go along with your application.
Ex23a.idl
    This file contains the Interface Description Language source code for the
    type library of your application.

/////////////////////////////////////////////////////////////////////////////

The application wizard creates one dialog class and automation proxy class:
Ex23aDlg.h, Ex23aDlg.cpp - the dialog
    These files contain your CEx23aDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's template is
    in Ex23a.rc, which can be edited in Microsoft Visual C++.
DlgProxy.h, DlgProxy.cpp - the automation object
    These files contain your CEx23aDlgAutoProxy class.  This class
    is called the Automation proxy class for your dialog, because it
    takes care of exposing the Automation methods and properties that
    Automation controllers can use to access your dialog.  These methods
    and properties are not exposed from the dialog class directly, because
    in the case of a modal dialog-based MFC application it is cleaner and
    easier to keep the Automation object separate from the user interface.
/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Ex23a.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

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
