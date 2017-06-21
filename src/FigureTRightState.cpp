#include "FigureTRightState.h"

FigureTRightState::FigureTRightState( int x, int y ): Base( x, y )
{
	int collisionY = y + 2;

	for( int i = 0; i < 6; ++i)
	{
		if( i == 3 )
			++collisionY;

		collisionPoints.push_back( new Point( x + i, collisionY ) );
	}
}

FigureTRightState::~FigureTRightState()
{
}

FigureState * FigureTRightState::GetNextState()
{
	TestApp * instance = TestApp::GetAppInstance();

	if( ( instance->GetChar( x + 6, y + 1 ) != L' ' || instance->GetChar( x, y + 2 ) != L' ' ) && x + 6 < instance->GetGameFieldWidth() - 1 )
		return NULL;

	if( x + 6 >= instance->GetGameFieldWidth() - 1 )
		x -= 3;

	return new FigureTDownState( x, y );
}

void FigureTRightState::Render()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	instance->SetChar( x + 3, y, L'[' );
	instance->SetChar( x + 4, y, L'x' );
	instance->SetChar( x + 5, y, L']' );

	instance->SetChar( x, y + 1, L'[' );
	instance->SetChar( x + 1, y + 1, L'x' );
	instance->SetChar( x + 2, y + 1, L']' );

	instance->SetChar( x + 3, y + 1, L'[' );
	instance->SetChar( x + 4, y + 1, L'x' );
	instance->SetChar( x + 5, y + 1, L']' );

	instance->SetChar( x + 3, y + 2, L'[' );
	instance->SetChar( x + 4, y + 2, L'x' );
	instance->SetChar( x + 5, y + 2, L']' );
}

void FigureTRightState::CollisionUpdate()
{
	collisionPoints.clear();

	int collisionY = y + 2;

	for( int i = 0; i < 6; ++i)
	{
		if( i == 3 )
			++collisionY;

		collisionPoints.push_back( new Point( x + i, collisionY ) );
	}
}

bool FigureTRightState::Move( Direction direction )
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

void FigureTRightState::Clear()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	instance->SetChar( x + 3, y, L' ' );
	instance->SetChar( x + 4, y, L' ' );
	instance->SetChar( x + 5, y, L' ' );

	instance->SetChar( x, y + 1, L' ' );
	instance->SetChar( x + 1, y + 1, L' ' );
	instance->SetChar( x + 2, y + 1, L' ' );

	instance->SetChar( x + 3, y + 1, L' ' );
	instance->SetChar( x + 4, y + 1, L' ' );
	instance->SetChar( x + 5, y + 1, L' ' );

	instance->SetChar( x + 3, y + 2, L' ' );
	instance->SetChar( x + 4, y + 2, L' ' );
	instance->SetChar( x + 5, y + 2, L' ' );
}

void FigureTRightState::MoveTo( int x, int y )
{
	this->x = x;
	this->y = y;

	CollisionUpdate();
}