#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR ipszCmdLine, int nCmdShow)
{
	HWND hwnd;		// 윈도우 핸들
	MSG msg;		// 메시지 구조체
	WNDCLASSEX WndClass; // 윈도우 클래스 구조체
	
	// 윈도우 클래스 구조체 WndClass에 값을 채워 윈도우 클래스를 등록한다.
	WndClass.cbSize = sizeof(WNDCLASSEX);						// 구조체 크기
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;		// 클래스 스타일
	WndClass.lpfnWndProc = WndProc;								// 윈도우 프로시저
	WndClass.cbClsExtra = 0;									// 윈도우 클래스 데이터 영역
	WndClass.cbWndExtra = 0;									// 윈도우의 데이터 영역
	WndClass.hInstance = hInstance;								// 인스턴스 핸들
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// 아이콘 핸들
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);				// 커서 핸들
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경 브러시 핸들
	WndClass.lpszMenuName = NULL;								// 메뉴 이름
	WndClass.lpszClassName = "EasyText";						// 윈도우 클래스 이름
	WndClass.hIconSm = 0;										// 기본적인 작은 아이콘
	
	// 윈도우 클래스를 등록한다.
	RegisterClassEx(&WndClass);
	
	// 프레임 윈도우를 생성한다.
	hwnd = CreateWindow(
		"EasyText",
		"Practice1a",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	 // 프레임 윈도우를 화면에 표시한다.
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	// 메시지 큐로부터 메시지를 받아와 메시지를 해당 윈도우 프로시저로 보낸다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return msg.wParam;	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rect;
	PAINTSTRUCT ps;
	LPCSTR szMsg1 = "I love Window Programming!";
	LPCSTR szMsg2 = "키보드가 눌러졌습니다";
	LPCSTR szMsg3 = "키보드가 떼어졌습니다";
	
	// 커널에서 들어온 메시지를 switch 문을 이용해 처리
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 10, 10, szMsg1, strlen(szMsg1));
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg2, strlen(szMsg2), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_KEYUP:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg3, strlen(szMsg3), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_LBUTTONDBLCLK:
		MessageBox(hwnd, "마우스 더블 클릭!", "마우스 메시지", MB_OK | MB_ICONASTERISK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
