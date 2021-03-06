// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include <algorithm>
#include <time.h>
#include <conio.h>
#include <assert.h>
#include <strsafe.h>

#define MY_PERFORMENCE_COUNTER

#include "PerformanceCounter.h"

BaseApp::BaseApp(int xSize, int ySize) : X_SIZE(xSize), Y_SIZE(ySize)
{
	COORD windowBufSize = {80, 45};

	mConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	mConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	if(!SetConsoleScreenBufferSize(mConsole,  windowBufSize))
	{
		cout << "SetConsoleScreenBufferSize failed with error " << GetLastError() << endl;
	}
	
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect( hDesktop, &desktop );
	const COORD wndSize = { 653, 600 };

	HWND console = GetConsoleWindow();
	MoveWindow(
		console,
		( desktop.right / 2 ) - ( wndSize.X / 2 ),
		( desktop.bottom / 2 ) - ( wndSize.Y / 2 ),
		wndSize.X,
		wndSize.Y,
		true
	);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(mConsole, &cursorInfo);


	mChiBuffer = (CHAR_INFO*)malloc((X_SIZE+1)*(Y_SIZE+1)*sizeof(CHAR_INFO));

	mDwBufferSize.X = X_SIZE + 1;
	mDwBufferSize.Y = Y_SIZE + 1;		// размер буфера данных

	gameFieldWidth = 39;

	mDwBufferCoord.X = 1;
	mDwBufferCoord.Y = 1;				// координаты ячейки

	mLpWriteRegion.Left = 1;
	mLpWriteRegion.Top = 1;
	mLpWriteRegion.Right = X_SIZE + 1;
	mLpWriteRegion.Bottom = Y_SIZE + 1;	// прямоугольник для чтения

	for ( int x = 0; x < X_SIZE + 1; x++)
		for ( int y = 0; y < Y_SIZE + 1; y++ )
		{
			if( x == 1 || x == X_SIZE || x == gameFieldWidth - 1 )
				SetChar( x, y, L'|' );
			else if( y == 1 || y == Y_SIZE )
				SetChar( x, y, L'—' );
			else
				SetChar( x, y, L' ' );
		}
}

BaseApp::~BaseApp()
{
	free(mChiBuffer);
}

void BaseApp::SetChar(int x, int y, wchar_t c)
{
	mChiBuffer[x + (X_SIZE+1)*y].Char.UnicodeChar = c;
	mChiBuffer[x + (X_SIZE+1)*y].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
}

wchar_t BaseApp::GetChar(int x, int y)
{
	return mChiBuffer[x + (X_SIZE+1)*y].Char.AsciiChar;
}

void BaseApp::Render()
{
	if (!WriteConsoleOutput(mConsole, mChiBuffer, mDwBufferSize, mDwBufferCoord, &mLpWriteRegion)) 
	{
		printf("WriteConsoleOutput failed - (%d)\n", GetLastError()); 
	}
}

void BaseApp::Run()
{
	CStopwatch timer;
	int sum = 0;
	int counter = 0;

	int deltaTime = 0;
	while (1)
	{
		timer.Start();
		if (_kbhit())
		{
			KeyPressed (_getch());
			if (!FlushConsoleInputBuffer(mConsoleIn))
				cout<<"FlushConsoleInputBuffer failed with error "<<GetLastError();
		}

		UpdateF((float)deltaTime / 1000.0f);
		Render();
		Sleep(1);

		while (1)
		{
			deltaTime = timer.Now();
			if (deltaTime > 20)
				break;
		}

		sum += deltaTime;
		counter++;
		if (sum >= 1000)
		{
			TCHAR  szbuff[255];
			StringCchPrintf(szbuff, 255, TEXT("FPS: %d"), counter);
			SetConsoleTitle(szbuff);

			counter = 0;
			sum = 0;
		}
	}
}

COORD BaseApp::GetDwBufferSize()
{
	return mDwBufferSize;
}

COORD BaseApp::GetDwBufferCoord()
{
	return mDwBufferCoord;
}

int BaseApp::GetGameFieldWidth()
{
	return gameFieldWidth;
}

int BaseApp::GetGameFieldHeight()
{
	return Y_SIZE + 1;
}