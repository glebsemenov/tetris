#include "FigureIVerticalState.h"

FigureIVerticalState::FigureIVerticalState( int x, int y ): Base( x, y )
{
	int collisionY = y + 4;

	for( int i = 0; i < 3; ++i)
		collisionPoints.push_back( new Point( x + i, collisionY ) );
}

FigureIVerticalState::~FigureIVerticalState()
{
}

FigureState * FigureIVerticalState::GetNextState()
{
	TestApp * instance = TestApp::GetAppInstance();

	for( int i = 1; i <= 9; ++i )
		for( int j = 1; j <= 3; ++j )
			if( instance->GetChar( x + i, y + j ) != L' ' )
				return NULL;

	if( x + 9 > instance->GetGameFieldWidth() - 1 )
		x -= 9;

	return new FigureIDefaultState( x, y );
}

void FigureIVerticalState::Render()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	for( int i = 0; i < 4; ++i )
	{
		instance->SetChar( x, y + i, L'[' );
		instance->SetChar( x + 1, y + i, L'x' );
		instance->SetChar( x + 2, y + i, L']' );
	}
}

void FigureIVerticalState::CollisionUpdate()
{
	collisionPoints.clear();

	int collisionY = y + 4;

	for( int i = 0; i < 3; ++i)
		collisionPoints.push_back( new Point( x + i, collisionY ) );
}

bool FigureIVerticalState::Move( Direction direction )
{
	TestApp * instance = TestApp::GetAppInstance();

	switch( direction )
	{
		case DOWN:
			if( collisionPoints[0]->y >= instance->GetDwBufferSize().Y )
				return false;

			for( vector<Point*>::iterator it = collisionPoints.begin(); it != collisionPoints.end(); ++it )
				if( ( instance->GetChar( (*it)->x, (*it)->y ) ) != ' ' )
					return false;

			Clear();
			++y;
			Render();
			CollisionUpdate();

			return true;

		case LEFT:
			if( x - 3 <= (int)instance->GetDwBufferCoord().X )
				return false;

			Clear();
			x -= 3;
			Render();
			CollisionUpdate();

			return true;

		case RIGHT:
			if( x + (int)collisionPoints.size() + 3 >= (int)instance->GetGameFieldWidth() )
				return false;

			Clear();
			x += 3;
			Render();
			CollisionUpdate();

			return true;
	}

	return false;
}

void FigureIVerticalState::Clear()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	for( int i = 0; i < 4; ++i )
	{
		instance->SetChar( x, y + i, L' ' );
		instance->SetChar( x + 1, y + i, L' ' );
		instance->SetChar( x + 2, y + i, L' ' );
	}
}

void FigureIVerticalState::MoveTo( int x, int y )
{
	this->x = x;
	this->y = y;

	CollisionUpdate();
}