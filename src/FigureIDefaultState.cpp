#include "FigureIDefaultState.h"

FigureIDefaultState::FigureIDefaultState( int x, int y ): Base( x, y )
{
	int collisionY = y + 1;

	for( int i = 0; i < 12; ++i)
		collisionPoints.push_back( new Point( x + i, collisionY ) );
}

FigureIDefaultState::~FigureIDefaultState()
{
}

FigureState * FigureIDefaultState::GetNextState()
{
	TestApp * instance = TestApp::GetAppInstance();

	for( int i = 1; i <= 3; ++i )
		if( instance->GetChar( x, y + i ) != L' ' )
			return NULL;

	return new FigureIVerticalState( x, y );
}

void FigureIDefaultState::Render()
{
	TestApp * instance = TestApp::GetAppInstance();
	instance->SetChar( x, y, L'[' );
	instance->SetChar( x + 1, y, L'x' );
	instance->SetChar( x + 2, y, L']' );

	instance->SetChar( x + 3, y, L'[' );
	instance->SetChar( x + 4, y, L'x' );
	instance->SetChar( x + 5, y, L']' );

	instance->SetChar( x + 6, y, L'[' );
	instance->SetChar( x + 7, y, L'x' );
	instance->SetChar( x + 8, y, L']' );

	instance->SetChar( x + 9, y, L'[' );
	instance->SetChar( x + 10, y, L'x' );
	instance->SetChar( x + 11, y, L']' );
}

void FigureIDefaultState::CollisionUpdate()
{
	collisionPoints.clear();

	int collisionY = y + 1;

	for( int i = 0; i < 12; ++i)
		collisionPoints.push_back( new Point( x + i, collisionY ) );
}

bool FigureIDefaultState::Move( Direction direction )
{
	TestApp * instance = TestApp::GetAppInstance();

	switch( direction )
	{
		case DOWN:
			if( collisionPoints[0]->y >= instance->GetDwBufferSize().Y )
				return false;

			for( vector<Point*>::iterator it = collisionPoints.begin(); it != collisionPoints.end(); ++it )
				if( ( instance->GetChar( (*it)->x, (*it)->y ) ) != L' ' )
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

void FigureIDefaultState::Clear()
{
	TestApp * instance = TestApp::GetAppInstance();

	for( int i = 0; i < 12; ++i)
		instance->SetChar( x + i, y, L' ' );
}

void FigureIDefaultState::MoveTo( int x, int y )
{
	this->x = x;
	this->y = y;

	CollisionUpdate();
}