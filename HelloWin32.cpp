#include <windows.h>    // Windows API
#include <windowsx.h>   // Windows macro API
#include <commctrl.h>   // Common Controls
#include <cassert>      // for assert macro
#include "resource.h"

inline LPWSTR LoadStringDx(INT nID)
{
    static UINT s_index = 0;
    const UINT cchBuffMax = 1024;
    static WCHAR s_sz[4][cchBuffMax];

    WCHAR *pszBuff = s_sz[s_index];
    s_index = (s_index + 1) % _countof(s_sz);
    pszBuff[0] = 0;
    if (!::LoadStringW(NULL, nID, pszBuff, cchBuffMax))
        assert(0);
    return pszBuff;
}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    return TRUE;
}

void OnPsh1(HWND hwnd)
{
    MessageBoxW(hwnd, LoadStringDx(IDS_PSH1PRESSED), L"Info", MB_ICONINFORMATION);
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
    case IDCANCEL:
        EndDialog(hwnd, id);
        break;
    case psh1:
        OnPsh1(hwnd);
        break;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    INT_PTR ret;

    InitCommonControls();

    ret = DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_MAIN), NULL, DialogProc);
    switch (ret)
    {
    case IDOK:
        MessageBoxW(NULL, LoadStringDx(IDS_OKPRESSED), L"Info", MB_ICONINFORMATION);
        break;
    case IDCANCEL:
        MessageBoxW(NULL, LoadStringDx(IDS_CANCELPRESSED), L"Info", MB_ICONINFORMATION);
        break;
    }
    return 0;
}
