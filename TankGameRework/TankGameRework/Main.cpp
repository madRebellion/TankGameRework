#include <windows.h>
#include <gl/GL.h>		// OpenGl graphics
#include <gl/GLU.h>		// OpenGL perspective projection
#include <iostream>
#include <string.h>
using namespace std;
#include <stdlib.h>
#include <tchar.h>

#include "GameController.h"
#include "Update.h"
#include "Draw.h"
#include "Transform.h"
#include "Tank.h"
#include "PowerUp.h"

// Global variables

//Tank *player = new Tank;
Update update;
Draw draw;

int windowHeight = 600;
int windowWidth = 800;
int windowTopLeftX = 100;
int windowTopLeftY = 100;

// Main window class name
//static TCHAR szWindowClass[] = _T("DesktopApp");
// Application title bar
//static TCHAR szTitle[] = _T("Tank Game Rework");

// Stored variables
HWND gameWindow;
HINSTANCE hInst;
MSG message;

// Add the OpenGl and GLU libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

// Function prototype - forward declaration
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	GameController *gameController = new GameController;
	gameController->powerUp->RandomNumber();

#pragma region Window/OpenGL initialization

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("DesktopApp");
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		FatalAppExit(NULL, TEXT("Call to RegisterClassEx failed."));
		return 1;
	}

	//RegisterClassEx(&wcex);

	// Set the dimensions of the window
	RECT rect;
	SetRect(&rect, windowTopLeftX, windowTopLeftY, windowTopLeftX + windowWidth, windowTopLeftY + windowHeight);
	// Calculates required size of the window rectangle (the client area - the part we use to control the content within the application)
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// Store this instance to the global variable
	hInst = hInstance;

	// Handle window
	gameWindow = CreateWindow(TEXT("DesktopApp"), TEXT("Tank Game Rework"), WS_OVERLAPPEDWINDOW, windowTopLeftX, windowTopLeftY, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

	if (gameWindow == NULL)
	{
		FatalAppExit(NULL, TEXT("Failed to create window."));
		return 1;
	}

	// Show the window we just created, iCmdShow is a WinMain parameter
	ShowWindow(gameWindow, iCmdShow);
	// Update allows for us to move the window and use the close, max & min buttons on the title bar
	UpdateWindow(gameWindow);

	// Main windows message loop
	/*MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/

	HDC hDeviceContext = GetWindowDC(gameWindow);

	// Describes the pixel format we want to use
	// Set all values to 0 as this class contains a lot of useless fields that we don't care about
	PIXELFORMATDESCRIPTOR pixelDesc{ 0 };

	// Set the pixel foramt fields that we want
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;		// Version of this data structure and is always 1

	// Set this PFD to support OpenGL, double buffering and to draw to the window and not memory bitmap
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	// Use the Red, Green, Blue and Alpha channels
	// With 8 bits for each RGB - 24 bit colour
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 24;

	// Z-axis bit buffer
	pixelDesc.cDepthBits = 32;

	pixelDesc.iLayerType = PFD_MAIN_PLANE;

	// Collect the pixel format as defined by the parameters above
	int pixelFormat = ChoosePixelFormat(hDeviceContext, &pixelDesc);

	// If this format does not exist then we can't draw on the window
	if (pixelFormat == 0)
	{
		FatalAppExit(NULL, _T("No pixel format suitable. ChoosePixelFormat() failed."));
	}

	// If it does exist then set this as our pixel format
	int setPixelFormat = SetPixelFormat(hDeviceContext, pixelFormat, &pixelDesc);

	if (setPixelFormat == NULL)
	{
		FatalAppExit(NULL, _T("Could not set pixel format. SetPixelFormat() failed."));
	}

	// Create a render device context for OpenGL that is compatible with the window thus far
	HGLRC renderContext = wglCreateContext(hDeviceContext);
	// Combine the OpenGL render context and the window device context together
	wglMakeCurrent(hDeviceContext, renderContext);

	// OpenGL content creation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)windowWidth / windowHeight, 1, 1000);
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(0, 0.5, 0, 1.0);

#pragma endregion

#pragma region Main Program Loop

	while (update.playing)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update Game
		update.UpdateGame(gameController);
		gameController->ScreenWrap();
		// Draw Game
		draw.DrawGame(gameController);

		SwapBuffers(hDeviceContext);
	}

#pragma endregion

	// When the client is terminated and the application is closed
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(renderContext);
	ReleaseDC(gameWindow, hDeviceContext);

	return (int)message.wParam;
}

// Used to handle messages
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	/*PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Greetings!");*/

	//WM_PAINT is used by windows to notify this application that its display needs updating. For example,
	//if another window is in front of this one and then moved away
	switch (msg)
	{
		//case WM_PAINT:
		//	// hdc handles a device context, which is used to draw in the window area
		//	hdc = BeginPaint(hWnd, &ps);
		//	TextOut(hdc, 5, 5, greeting, _tcslen(greeting));

		//	EndPaint(hWnd, &ps);
		//	break;
	case WM_QUIT:
		update.playing = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return 0;
}
