#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <WinUser.h>
#include "resource.h"
using namespace std;

HWND hEdit1;
HWND hEdit2;
//
CONST UINT TEXT_SIZE = 256;
CHAR sz_buffer[TEXT_SIZE] = {};

CONST CHAR* cb_content[] =
{
	"This", "is", "my", "first", "combo", "box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc,0);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 1, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		
		for (int i = 0; i < sizeof(cb_content) / sizeof(cb_content[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)cb_content[i]);
		}
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CHAR sz_buffer[256] = {};
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_msg[256] = {};
			strcpy(sz_msg, "Вы выбрали пункт: ");
			strcat(sz_msg, sz_buffer);
			MessageBox(hwnd, sz_msg, "info", MB_ICONINFORMATION | MB_OK);
		}
		break;
		
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}