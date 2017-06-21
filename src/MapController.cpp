#include "MapController.h"
#include "TestApp.h"

MapController::MapController()
{
}

MapController::~MapController()
{
}

bool MapController::CheckForGameOver()
{
	TestApp * instance = TestApp::GetAppInstance();

	for( int i = 2; i < instance->GetGameFieldWidth() - 1; ++i )
		if( instance->GetChar( i, 5 ) != L' ' )
		{
			CleanUp();
			return true;
		}

	return false;
}

void MapController::CleanUp()
{
	TestApp * instance = TestApp::GetAppInstance();

	for ( int x = 2; x < instance->GetGameFieldWidth() - 1; ++x )
		for ( int y = 2; y < instance->GetGameFieldHeight() - 1; ++y )
			instance->SetChar( x, y, L' ' );
}

void MapController::CheckRows()
{
	TestApp * instance = TestApp::GetAppInstance();

	for( int y = instance->GetGameFieldHeight() - 2; y > 2; --y )
	{
		for( int x = 2, width = instance->GetGameFieldWidth() - 1; x < width; ++x )
		{
			if( instance->GetChar( x, y ) == L' ' )
				break;

			if( x == width - 1 )
			{
				EraseLine( y );

				ShiftBufferDown( y );

				++y;
			}
		}
	}
}

void MapController::ShiftBufferDown( int line )
{
	TestApp * instance = TestApp::GetAppInstance();

	for( int y = line; y > 2; --y )
		for( int x = 2, width = instance->GetGameFieldWidth() - 1; x < width; ++x )
			instance->SetChar( x, y, instance->GetChar( x, y - 1 ) );
}

void MapController::EraseLine( int line )
{
	TestApp * instance = TestApp::GetAppInstance();

	for( int x = 2, width = instance->GetGameFieldWidth() - 1; x < width; ++x )
		instance->SetChar( x, line, L' ' );
}