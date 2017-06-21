#include "FigureODefaultState.h"

FigureODefaultState::FigureODefaultState( int x, int y ): Base( x, y )
{
	int collisionY = y + 2;

	for( int i = 0; i < 6; ++i)
		collisionPoints.push_back( new Point( x + i, collisionY ) );
}

FigureODefaultState::~FigureODefaultState()
{
}

FigureState * FigureODefaultState::GetNextState()
{
	return NULL;
}

void FigureODefaultState::Render()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	for( int i = 0; i < 2; ++i )
	{
		instance->SetChar( x, y + i, L'[' );
		instance->SetChar( x + 1, y + i, L'x' );
		instance->SetChar( x + 2, y + i, L']' );

		instance->SetChar( x + 3, y + i, L'[' );
		instance->SetChar( x + 4, y + i, L'x' );
		instance->SetChar( x + 5, y + i, L']' );
	}
}

void FigureODefaultState::CollisionUpdate()
{
	collisionPoints.clear();

	int collisionY = y + 2;

	for( int i = 0; i < 6; ++i)
		collisionPoints.push_back( new Point( x + i, collisionY ) );
}

bool FigureODefaultState::Move( Direction direction )
{
	TestApp * instance = TestApp::GetAppInstance();

	switch( direction )
	{
		case DOWN:
			if( collisionPoints[3]->y >= instance->GetDwBufferSize().Y )
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

void FigureODefaultState::Clear()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	for( int i = 0; i < 2; ++i )
	{
		instance->SetChar( x, y + i, L' ' );
		instance->SetChar( x + 1, y + i, L' ' );
		instance->SetChar( x + 2, y + i, L' ' );

		instance->SetChar( x + 3, y + i, L' ' );
		instance->SetChar( x + 4, y + i, L' ' );
		instance->SetChar( x + 5, y + i, L' ' );
	}
}

void FigureODefaultState::MoveTo( int x, int y )
{
	this->x = x;
	this->y = y;

	CollisionUpdate();
}