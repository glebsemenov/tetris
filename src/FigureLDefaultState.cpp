#include "FigureLDefaultState.h"

FigureLDefaultState::FigureLDefaultState( int x, int y ): Base( x, y )
{
	int collisionY = y + 1;

	for( int i = 0; i < 9; ++i)
	{
		if( i == 6 )
			++collisionY;

		collisionPoints.push_back( new Point( x + i, collisionY ) );
	}
}

FigureLDefaultState::~FigureLDefaultState()
{
}

FigureState * FigureLDefaultState::GetNextState()
{
	TestApp * instance = TestApp::GetAppInstance();

	if( instance->GetChar( x + 3, y + 1 ) != L' ' ||
		instance->GetChar( x + 3, y + 2 ) != L' ' ||
		instance->GetChar( x + 6, y + 2 ) != L' ' ||
		instance->GetChar( x, y + 2 ) != L' ')
		return NULL;

	return new FigureLRightState( x, y );
}

void FigureLDefaultState::Render()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	for( int i = 0; i < 9; i += 3 )
	{
		instance->SetChar( x + i, y, L'[' );
		instance->SetChar( x + 1 + i, y, L'x' );
		instance->SetChar( x + 2 + i, y, L']' );
	}

	instance->SetChar( x + 6, y + 1, L'[' );
	instance->SetChar( x + 7, y + 1, L'x' );
	instance->SetChar( x + 8, y + 1, L']' );
}

void FigureLDefaultState::CollisionUpdate()
{
	collisionPoints.clear();

	int collisionY = y + 1;

	for( int i = 0; i < 9; ++i)
	{
		if( i == 6 )
			++collisionY;

		collisionPoints.push_back( new Point( x + i, collisionY ) );
	}
}

bool FigureLDefaultState::Move( Direction direction )
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

void FigureLDefaultState::Clear()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	for( int i = 0; i < 9; i += 3 )
	{
		instance->SetChar( x + i, y, L' ' );
		instance->SetChar( x + 1 + i, y, L' ' );
		instance->SetChar( x + 2 + i, y, L' ' );
	}

	instance->SetChar( x + 6, y + 1, L' ' );
	instance->SetChar( x + 7, y + 1, L' ' );
	instance->SetChar( x + 8, y + 1, L' ' );
}

void FigureLDefaultState::MoveTo( int x, int y )
{
	this->x = x;
	this->y = y;

	CollisionUpdate();
}