#undef UNICODE
#undef _UNICODE
#include <windows.h>
#include <cstdio>
HWND textfield,btnPlus,btnMinus,btnMul,btnDiv,input1,input2;
char input1Saved[100];
char input2Saved[100];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE: {
			input1 = CreateWindow("EDIT",
				"",
				WS_BORDER | WS_CHILD | WS_VISIBLE,
				20,45,200,20,
				hwnd,NULL,NULL,NULL);

			input2 = CreateWindow("EDIT",
							"",
							WS_BORDER | WS_CHILD | WS_VISIBLE,
							20,70,200,20,
							hwnd,NULL,NULL,NULL);

			textfield =  CreateWindow("STATIC",
							"Please input two numbers",
							WS_VISIBLE | WS_CHILD ,
							20,20,200,20,
							hwnd,NULL,NULL,NULL);

			btnPlus = CreateWindow("BUTTON",
						"+",
						WS_VISIBLE | WS_CHILD | WS_BORDER,
						20,95,40,40,
						hwnd,(HMENU) 1,NULL,NULL);

			btnMinus = CreateWindow("BUTTON",
						"-",
						WS_VISIBLE | WS_CHILD | WS_BORDER,
						75,95,40,40,
						hwnd,(HMENU) 2,NULL,NULL);

			btnMul = CreateWindow("BUTTON",
						"*",
						WS_VISIBLE | WS_CHILD | WS_BORDER,
						130,95,40,40,
						hwnd,(HMENU) 3,NULL,NULL);

			btnDiv = CreateWindow("BUTTON",
						"/",
						WS_VISIBLE | WS_CHILD | WS_BORDER,
						185,95,40,40,
						hwnd,(HMENU) 4,NULL,NULL);
			break;
		}

		case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case 1:
                {
                int gwt1 = 0,gwt2 = 0;
                gwt1 = GetWindowText(input1,&input1Saved[0],100);
                gwt2 = GetWindowText(input2,&input2Saved[0],100);
                double num1 = atof(input1Saved);
                double num2 = atof(input2Saved);
                double result = num1 + num2;

                char resultStr[100];
                snprintf(resultStr, sizeof(resultStr), "%f", result);

                ::MessageBox(hwnd,resultStr,"Result",MB_OK);
                break;
                }

                case 2:
                {
                int gwt1 = 0,gwt2 = 0;
                gwt1 = GetWindowText(input1,&input1Saved[0],100);
                gwt2 = GetWindowText(input2,&input2Saved[0],100);
                double num1 = atof(input1Saved);
                double num2 = atof(input2Saved);
                double result = num1 - num2;

                char resultStr[100];
                snprintf(resultStr, sizeof(resultStr), "%f", result);

                ::MessageBox(hwnd,resultStr,"Result",MB_OK);
                break;
                }

                case 3:
                {
                int gwt1 = 0,gwt2 = 0;
                gwt1 = GetWindowText(input1,&input1Saved[0],100);
                gwt2 = GetWindowText(input2,&input2Saved[0],100);
                double num1 = atof(input1Saved);
                double num2 = atof(input2Saved);
                double result = num1*num2;

                char resultStr[100];
                snprintf(resultStr, sizeof(resultStr), "%f", result);

                ::MessageBox(hwnd,resultStr,"Result",MB_OK);
                break;
                }

                case 4:
                {
                int gwt1 = 0,gwt2 = 0;
                gwt1 = GetWindowText(input1,&input1Saved[0],100);
                gwt2 = GetWindowText(input2,&input2Saved[0],100);
                double num1 = atof(input1Saved);
                double num2 = atof(input2Saved);
                double result = num1/num2;

                char resultStr[100];
                snprintf(resultStr, sizeof(resultStr), "%f", result);

                ::MessageBox(hwnd,resultStr,"Result",MB_OK);
                break;
                }

            }

            break;


		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Calculator",WS_VISIBLE|WS_OVERLAPPED|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
