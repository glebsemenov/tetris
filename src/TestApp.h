// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "Figure.h"
#include "FigureIDefaultState.h"
#include "FigureTDefaultState.h"
#include "FigureLDefaultState.h"
#include "FigureZDefaultState.h"
#include "FigureODefaultState.h"
#include "DirectionEnum.h"
#include <ctime>

class MapController;

class TestApp : public BaseApp
{
private:
	typedef BaseApp Parent;

	Figure * figure;
	Figure * nextFigure;
	MapController * mapController;
	
public:	
	static TestApp * app;

	TestApp();
	static TestApp * GetAppInstance();
	virtual void KeyPressed( int btnCode );
	virtual void UpdateF( float deltaTime );
	Figure * GenerateNextFigure();
};
