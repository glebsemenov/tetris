// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include "MapController.h"

TestApp * TestApp::app;

TestApp::TestApp() : Parent( 78, 43 )
{
	figure = new Figure( new FigureIVerticalState( 5, 3 ) );
	nextFigure = GenerateNextFigure();
	mapController = new MapController();
	srand( time( 0 ) );
}

void TestApp::KeyPressed( int btnCode )
{
	if ( btnCode == 115 ) // s
	{
		figure->Move( DOWN );
	}
	else if ( btnCode == 32 ) // space
	{
		figure->Clear();
		figure->SetState();
		figure->Render();
	}
	else if ( btnCode == 97 ) // a
	{
		figure->Move( LEFT );
	}
	else if ( btnCode == 100 ) // d
	{
		figure->Move( RIGHT );
	}
}

void TestApp::UpdateF( float deltaTime )
{
	static float hoarder = 0;

	hoarder += deltaTime;

	if( hoarder >= .2f )
	{
		if( ! figure->Move( DOWN ) )
		{
			if( ! mapController->CheckForGameOver() )
				mapController->CheckRows();

			delete figure;
			figure = nextFigure;
			figure->Clear();
			figure->MoveTo( 5, 3 );
			nextFigure = GenerateNextFigure();
			nextFigure->Render();
		}
		hoarder = 0;
		nextFigure->Render();
	}
}

TestApp * TestApp::GetAppInstance()
{
	return app;
}

Figure * TestApp::GenerateNextFigure()
{
	int figure = rand() % 13;
	switch( figure )
	{
		default:
		return new Figure( new FigureIDefaultState( 52, 20 ) );

		case 0:
		return new Figure( new FigureIDefaultState( 52, 20 ) );

		case 1:
		return new Figure( new FigureIVerticalState( 52, 20 ) );

		case 2:
		return new Figure( new FigureLDefaultState( 52, 20 ) );

		case 3:
		return new Figure( new FigureLDownState( 52, 20 ) );

		case 4:
		return new Figure( new FigureLLeftState( 52, 20 ) );

		case 5:
		return new Figure( new FigureLRightState( 52, 20 ) );

		case 6:
		return new Figure( new FigureODefaultState( 52, 20 ) );

		case 7:
		return new Figure( new FigureTDefaultState( 52, 20 ) );

		case 8:
		return new Figure( new FigureTDownState( 52, 20 ) );

		case 9:
		return new Figure( new FigureTLeftState( 52, 20 ) );

		case 10:
		return new Figure( new FigureTRightState( 52, 20 ) );

		case 11:
		return new Figure( new FigureZDefaultState( 52, 20 ) );

		case 12:
		return new Figure( new FigureZVerticalState( 52, 20 ) );
	}
}