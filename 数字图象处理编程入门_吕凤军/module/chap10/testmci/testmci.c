#include <windows.h>
#include <vfw.h>
void SetClientRect(HWND hwnd, HWND hwndMCI)
{
    RECT rect;
    GetWindowRect(hwndMCI, &rect);
    AdjustWindowRectEx(&rect, GetWindowLong(hwnd, GWL_STYLE),
                       FALSE, GetWindowLong(hwnd, GWL_EXSTYLE));
    MoveWindow(hwnd, rect.left, rect.top, rect.right - rect.left,
               rect.bottom - rect.top, TRUE);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg,
                         WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case MCIWNDM_NOTIFYPOS:
        case MCIWNDM_NOTIFYSIZE:
            SetClientRect(hwnd, (HWND)wParam);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                                     LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    HWND hwnd;
    WNDCLASS wndClass;
    if (hPrevInstance == NULL)
    {
        memset(&wndClass, 0, sizeof(wndClass));
        wndClass.style = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc = WndProc;
        wndClass.hInstance = hInstance;
        wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wndClass.lpszClassName = "HELLO";
        if (!RegisterClass(&wndClass)) return FALSE;
    }
    hwnd = CreateWindow("HELLO", "HELLO",
                        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
                        NULL, NULL, hInstance, NULL);
    SetClientRect(hwnd, MCIWndCreate(hwnd, hInstance, WS_VISIBLE |
                                    WS_CHILD | MCIWNDF_SHOWALL |
                                    MCIWNDF_NOTIFYSIZE |
                                    MCIWNDF_NOTIFYPOS, "c:\\test.avi"));
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0))
        DispatchMessage(&msg);
    return msg.wParam;
}
