#include "FigureTDownState.h"

FigureTDownState::FigureTDownState( int x, int y ): Base( x, y )
{
	int collisionY = y + 2;

	for( int i = 0; i < 9; ++i)
		collisionPoints.push_back( new Point( x + i, collisionY ) );
}

FigureTDownState::~FigureTDownState()
{
}

FigureState * FigureTDownState::GetNextState()
{
	TestApp * instance = TestApp::GetAppInstance();

	if( instance->GetChar( x, y + 2 ) != L' ' )
		return NULL;

	return new FigureTLeftState( x, y );
}

void FigureTDownState::Render()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	instance->SetChar( x + 3, y, L'[' );
	instance->SetChar( x + 4, y, L'x' );
	instance->SetChar( x + 5, y, L']' );

	for( int i = 0; i < 9; i += 3 )
	{
		instance->SetChar( x + i, y + 1, L'[' );
		instance->SetChar( x + 1 + i, y + 1, L'x' );
		instance->SetChar( x + 2 + i, y + 1, L']' );
	}
}

void FigureTDownState::CollisionUpdate()
{
	collisionPoints.clear();

	int collisionY = y + 2;

	for( int i = 0; i < 9; ++i)
		collisionPoints.push_back( new Point( x + i, collisionY ) );
}

bool FigureTDownState::Move( Direction direction )
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

void FigureTDownState::Clear()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	instance->SetChar( x + 3, y, L' ' );
	instance->SetChar( x + 4, y, L' ' );
	instance->SetChar( x + 5, y, L' ' );

	for( int i = 0; i < 9; i += 3 )
	{
		instance->SetChar( x + i, y + 1, L' ' );
		instance->SetChar( x + 1 + i, y + 1, L' ' );
		instance->SetChar( x + 2 + i, y + 1, L' ' );
	}
}

void FigureTDownState::MoveTo( int x, int y )
{
	this->x = x;
	this->y = y;

	CollisionUpdate();
}