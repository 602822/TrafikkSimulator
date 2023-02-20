// Assignment1v4.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Assignment1v4.h"
#include <vector>



#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int pw;
int pn;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    MyDlg(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASSIGNMENT1V4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSIGNMENT1V4));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSIGNMENT1V4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASSIGNMENT1V4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	static int state = 3;
	static int stateTL2 = 1;

	static BOOL lagBiler = false;
	static BOOL lagBiler2 = false;

	


	class Car {
	public:
		int left ;
		int top ;
		int right;
		int bottom;

		Car(int l, int t, int r, int b) {
			left = l;
			top = t;
			right = r;
			bottom = b;
		}

		


	};


	static	std::vector<Car*> cars;
	static	std::vector<Car*> cars2;



	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	//Bilene horisontalt begynner å spawne når du klikker på vestre musetast
	case WM_LBUTTONDOWN:
	{

		lagBiler = true;

	}
	break;

	//Bilene vertikalt begynner å spawne når du klikker på høgre musetast
	case WM_RBUTTONDOWN:
	{
		lagBiler2 = true;
	}
	break;


	//Stiller Sannsynlgheten for at bilene spawner med piltastene
	case WM_KEYDOWN:
	{

		switch (wParam) {

		case VK_LEFT:
		{
			if (pw < 100) {
				pw += 10;
			}
		}
		break;

		case VK_RIGHT:
		{
			if (pw > 0) {
				pw -= 10;
			}
		}
		break;

		case VK_UP:
		{
			if (pn < 100) {
				pn += 10;
			}
		}
		break;

		case VK_DOWN:
		{
			if (pn > 0) {
				pn -= 10;
			}
		}
		break;

	}
	break;
	

	case WM_CREATE:
	{
		//timer for trafikklys
		SetTimer(hWnd, 0, 3000, 0);

		//legge til biler i ein vektor kvart andre sekund
		SetTimer(hWnd, 1, 2000, 0);

		//timer for å øke posisjonen til biler horisontalt
		SetTimer(hWnd, 2, 100, 0);

		//timer for å øke posisjonen biler vertikalt
		SetTimer(hWnd, 3, 100, 0);

	
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDlg);

	}
	break;


	case WM_TIMER:
	{

		switch (wParam) {
		case 0:
		{
			//Oppdaterer fargen på trafikklysene
			state += 1;
			stateTL2 += 1;

			if (state == 5) {
				state = 1;
			}

			if (stateTL2 == 5) {
				stateTL2 = 1;
			}


		}
		break;



		case 1:
		{

			// Pusher bil objecter i vektorene, med ein viss sansynlighet
			if (rand() % 100 <= pw) {
				cars.push_back(new Car(150, 300, 210, 320));
			}

			if (rand() % 100 <= pn) {
				cars2.push_back(new Car(595, 495, 615, 555));
			}

		}
		break;



		// Øker posisjonene til bilene som går horisontalt

		case 2:
		{
		  // kjører bilene
			for (Car* c : cars) {
				if (lagBiler) {
					c->left += 5;
					c->right += 5;
				}

				//Stoppe bilene på rett plass og rett lys
				if (c->right >= 520 && c -> right <= 560) {
					if (state == 1 || state == 2) {
						c->left -= 5;
						c->right -= 5;
					}
				}
				// Stoppe bilene bak når bilen forran stopper
				for (size_t i = 0; i < cars.size() - 1; i++) {
					if (cars[i + 1]->right >= cars[i]->left) {
						cars[i + 1]->left -= 5;
						cars[i + 1]->right -= 5;
					}
				}




			}

		}
		break;


		case 3:
		{
			//Kjøre bilene
			for (Car* c2 : cars2) {
				if (lagBiler2) {
					c2->top -= 5;
					c2->bottom -= 5;

					//Stoppe bilene på rett plass og rett lys
					if ( c2 ->top <=380 && c2 -> top >= 350) {
						if (stateTL2 == 1 || stateTL2 == 2) {
							c2->top += 5;
							c2->bottom += 5;
						}
					}

					
					//Stopper bilene når bilene bak stopper
					
					for (size_t i = 0; i < cars2.size() -1; i++) {
						if (cars2[i + 1]->top <= cars2[i]->bottom) {
							cars2[i + 1]->top += 5;
							cars2[i + 1]->bottom += 5;
						}
					}
					
					

				}
			}


		}
		break;


		}
		InvalidateRect(hWnd, 0, true);
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...



		Rectangle(hdc, 500, 250, 600, 100); //trafikklys 1 ramme
		Rectangle(hdc, 400, 300, 550, 400); //trafikklys 2 ramme



		HBRUSH greyBrush = CreateSolidBrush(RGB(105, 105, 105));
		HGDIOBJ horg = SelectObject(hdc, greyBrush);


		Rectangle(hdc, 150, 350, 1050, 250);  //vei horisonal
		Rectangle(hdc, 550, 0, 650, 600);    // vei vertikal


		//Sannsynlghet tekst på skjermen
		TCHAR buffer[100];
		_stprintf_s(buffer, _T("Probability cars west : %d %%"), pw);
		TextOut(hdc, 0, 0, buffer, _tcslen(buffer));



		TCHAR buffer2[100];
		_stprintf_s(buffer2, _T("Probability cars north : %d %%"), pn);
		TextOut(hdc, 0, 20, buffer2, _tcslen(buffer2));



		HBRUSH pinkBrush = CreateSolidBrush(RGB(255, 192, 203));
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));


		// Lager firkanter for Alle bil objektene i vektoren
		if (lagBiler) {
			for (Car* c : cars) {
				SelectObject(hdc, pinkBrush);
				Rectangle(hdc, c->left, c->top , c->right , c->bottom );

			}
		}

		if (lagBiler2) {
			for (Car* c2 : cars2) {
				SelectObject(hdc, blueBrush);
				Rectangle(hdc, c2->left, c2->top, c2->right, c2->bottom);
			}
		}

	




		//trafikklys 2
		switch (stateTL2) {
		case 1:
		{
			// HBRUSH hwhiteBrush = CreateSolidBrush(RGB());
			 //venstre top høgre bunn



			HBRUSH hredbrush = CreateSolidBrush(RGB(255, 0, 0));
			HGDIOBJ horg = SelectObject(hdc, hredbrush);
			Ellipse(hdc, 500, 350, 550, 400);



			HBRUSH hgreybrush = CreateSolidBrush(RGB(105, 105, 105));
			SelectObject(hdc, hgreybrush);
			Ellipse(hdc, 450, 350, 500, 400);
			Ellipse(hdc, 400, 350, 450, 400);

			//opprydding
			SelectObject(hdc, horg);
			DeleteObject(hredbrush);
			DeleteObject(hgreybrush);}
		break;

		case 2:
		{

			HBRUSH hredbrush = CreateSolidBrush(RGB(255, 0, 0));
			HGDIOBJ horg = SelectObject(hdc, hredbrush);
			Ellipse(hdc, 500, 350, 550, 400);




			HBRUSH hyellowbrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hyellowbrush);
			Ellipse(hdc, 450, 350, 500, 400);




			HBRUSH hgreybrush = CreateSolidBrush(RGB(105, 105, 105));
			SelectObject(hdc, hgreybrush);
			Ellipse(hdc, 400, 350, 450, 400);

			//opprydding
			SelectObject(hdc, horg);
			DeleteObject(hredbrush);
			DeleteObject(hyellowbrush);
			DeleteObject(hgreybrush);
		}
		break;

		case 3:
		{



			HBRUSH hgreybrush = CreateSolidBrush(RGB(105, 105, 105));
			HGDIOBJ horg = SelectObject(hdc, hgreybrush);
			Ellipse(hdc, 500, 350, 550, 400);
			Ellipse(hdc, 450, 350, 500, 400);


			HBRUSH hgreenBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hgreenBrush);
			Ellipse(hdc, 400, 350, 450, 400);

			//opprydding
			SelectObject(hdc, horg);
			DeleteObject(hgreybrush);
			DeleteObject(hgreenBrush);}
		break;
		case 4:
		{

			HBRUSH hgreybrush = CreateSolidBrush(RGB(105, 105, 105));
			HGDIOBJ horg = SelectObject(hdc, hgreybrush);


			Ellipse(hdc, 400, 350, 450, 400);
			Ellipse(hdc, 500, 350, 550, 400);

			HBRUSH hyellowbrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hyellowbrush);
			Ellipse(hdc, 450, 350, 500, 400);
			SelectObject(hdc, horg);
			DeleteObject(hyellowbrush);
			DeleteObject(hgreybrush);
		}
		}

		//trafikklys 1
		switch (state) {
		case 1:
		{
			// HBRUSH hwhiteBrush = CreateSolidBrush(RGB());
			 //venstre top høgre bunn



			HBRUSH hredbrush = CreateSolidBrush(RGB(255, 0, 0));
			HGDIOBJ horg = SelectObject(hdc, hredbrush);
			Ellipse(hdc, 550, 150, 500, 100);

			HBRUSH hgreybrush = CreateSolidBrush(RGB(105, 105, 105));
			SelectObject(hdc, hgreybrush);
			Ellipse(hdc, 550, 200, 500, 150);
			Ellipse(hdc, 550, 250, 500, 200);

			//opprydding
			SelectObject(hdc, horg);
			DeleteObject(hredbrush);
			DeleteObject(hgreybrush);}
		break;

		case 2:
		{




			HBRUSH hredbrush = CreateSolidBrush(RGB(255, 0, 0));
			HGDIOBJ horg = SelectObject(hdc, hredbrush);
			Ellipse(hdc, 550, 150, 500, 100);


			HBRUSH hyellowbrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hyellowbrush);
			Ellipse(hdc, 550, 200, 500, 150);


			HBRUSH hgreybrush = CreateSolidBrush(RGB(105, 105, 105));
			SelectObject(hdc, hgreybrush);
			Ellipse(hdc, 550, 250, 500, 200);

			//opprydding
			SelectObject(hdc, horg);
			DeleteObject(hredbrush);
			DeleteObject(hyellowbrush);
			DeleteObject(hgreybrush);
		}
		break;


		case 3:
		{



			HBRUSH hgreybrush = CreateSolidBrush(RGB(105, 105, 105));
			HGDIOBJ horg = SelectObject(hdc, hgreybrush);
			Ellipse(hdc, 550, 150, 500, 100);
			Ellipse(hdc, 550, 200, 500, 150);


			HBRUSH hgreenBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hgreenBrush);
			Ellipse(hdc, 550, 250, 500, 200);

			//opprydding
			SelectObject(hdc, horg);
			DeleteObject(hgreybrush);
			DeleteObject(hgreenBrush);}
		break;
		case 4:
		{



			HBRUSH hgreybrush = CreateSolidBrush(RGB(105, 105, 105));
			HGDIOBJ horg = SelectObject(hdc, hgreybrush);

			Ellipse(hdc, 550, 150, 500, 100);
			Ellipse(hdc, 550, 250, 500, 200);

			HBRUSH hyellowbrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hyellowbrush);
			Ellipse(hdc, 550, 200, 500, 150);

			SelectObject(hdc, horg);
			DeleteObject(hyellowbrush);
			DeleteObject(hgreybrush);
		}
		}

		

		

		SelectObject(hdc, horg);
		DeleteObject(pinkBrush);
		DeleteObject(blueBrush);



		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:

		//slette bil objektene
		for (auto c : cars) {
			delete c;
		}
		cars.clear();

		for (auto c2 : cars2) {
			delete c2;
		}
		cars2.clear();

		PostQuitMessage(0);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
	}
	}


	

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK MyDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:

	{
		HWND pwControl = GetDlgItem(hDlg, IDC_EDIT1);
		HWND pnControl = GetDlgItem(hDlg, IDC_EDIT2);

		SetWindowText(pwControl, L"Legg inn eit heiltal 1-100");
		SetWindowText(pnControl, L"Legg inn eit heiltal 1-100");

		return (INT_PTR)TRUE;

	}
	break;

	case WM_COMMAND:


		if (LOWORD(wParam) == IDOK) {

			BOOL isNumber = false;
			pw = GetDlgItemInt(hDlg, IDC_EDIT1, &isNumber, false);
			pn = GetDlgItemInt(hDlg, IDC_EDIT2, &isNumber, false);







			EndDialog(hDlg, LOWORD(wParam));

		}


		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
