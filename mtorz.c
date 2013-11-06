// Mt.orz0

#include <windows.h>
#define ID_SOFTNAME "Mt.orz0"

/* OSASKƒpƒŒƒbƒg */
static int osar[8] = { 0, 128,   0, 128,   0, 128,   0, 128 };
static int osag[8] = { 0,   0, 128, 128,   0,   0, 128, 128 };
static int osab[8] = { 0,   0,   0,   0, 128, 128, 128, 128 };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassNme[] = ID_SOFTNAME;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	HBRUSH hBrush;
	WNDCLASS myProg;

	if (!hPreInst) {
		myProg.style			=CS_HREDRAW | CS_VREDRAW;
		myProg.lpfnWndProc		=WndProc;
		myProg.cbClsExtra		=0;
		myProg.cbWndExtra		=0;
		myProg.hInstance		=hInstance;
		myProg.hIcon			=LoadIcon(hInstance, MAKEINTRESOURCE(100));
		myProg.hCursor			=LoadCursor(NULL, IDC_ARROW);
		myProg.hbrBackground	=GetSysColorBrush(4);
		myProg.lpszMenuName		=NULL;
		myProg.lpszClassName	=ID_SOFTNAME;
		if (!RegisterClass(&myProg))
			return FALSE;
	}
	hWnd = CreateWindow(szClassNme, ID_SOFTNAME,
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	CW_USEDEFAULT, CW_USEDEFAULT, 162, 100, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int col = 0;
	switch (msg) {
		case WM_CREATE:
			SetTimer(hWnd, 1, 0, NULL);
			break;

		case WM_TIMER:
			KillTimer(hWnd, 1);
			InvalidateRect(hWnd, NULL, FALSE);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_PAINT:
			int cnty = 0;
			char *str = " orz";
			PAINTSTRUCT paint;
			HDC hdc = BeginPaint(hWnd, &paint);
			HFONT hFont;
			hFont = CreateFont(	0, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE,
								SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "Fixed Sys");
			do {
				int cntx = 6 - cnty * 2;
				do {
					SelectObject(hdc, hFont);
					SetTextColor(hdc, RGB(osar[col], osag[col], osab[col]));
					SetBkMode(hdc, TRANSPARENT);
					TextOut(hdc, cntx * 8 + 10, cnty * 16 + 5, (LPCSTR)str, 4);
					cntx += 4;
				} while (!(cntx % 10 == cnty * 2 && cntx / 10 == 1));	// -(-3)‚ª(+3)‚É‚È‚éŠ´‚¶
				cnty++;
			} while (cnty < 4);
			EndPaint(hWnd, &paint);

			col++;
			if (col > 7)
				col = 0;
			SetTimer(hWnd, 1, 500, NULL);
			break;

		default:
			return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}
