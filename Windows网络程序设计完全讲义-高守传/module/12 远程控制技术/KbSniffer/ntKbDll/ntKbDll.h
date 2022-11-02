

#ifdef NTKBDLL_EXPORTS
#define NTKBDLL_API __declspec(dllexport)
#else
#define NTKBDLL_API __declspec(dllimport)
#endif

//This message is recieved when key is down/up
#define WM_KEYSTROKE (WM_USER + 100)

NTKBDLL_API void InstallHook(HWND h);//This function installs the Keyboard hook.
NTKBDLL_API void RemoveHook();//This function removes the previously installed hook.
NTKBDLL_API LRESULT CALLBACK KeyboardProc(int ncode,WPARAM wparam,LPARAM lparam);//This function is called when the keyboard is operated.