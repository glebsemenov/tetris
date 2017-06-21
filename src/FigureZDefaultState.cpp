#include "FigureZDefaultState.h"

FigureZDefaultState::FigureZDefaultState( int x, int y ): Base( x, y )
{
	int collisionY = y + 1;

	for( int i = 0; i < 9; ++i)
	{
		if( i == 3 )
			++collisionY;

		collisionPoints.push_back( new Point( x + i, collisionY ) );
	}
}

FigureZDefaultState::~FigureZDefaultState()
{
}

FigureState * FigureZDefaultState::GetNextState()
{
	TestApp * instance = TestApp::GetAppInstance();

	if( instance->GetChar( x, y + 1 ) != L' ' )
		return NULL;

	return new FigureZVerticalState( x, y );
}

void FigureZDefaultState::Render()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	for( int i = 0, inc = 0; i < 9; i += 3 )
	{
		if( i == 6 && inc == 0 )
		{
			i -= 3;
			++inc;
		}

		instance->SetChar( x + i, y + inc, L'[' );
		instance->SetChar( x + 1 + i, y + inc, L'x' );
		instance->SetChar( x + 2 + i, y + inc, L']' );
	}
}

void FigureZDefaultState::CollisionUpdate()
{
	collisionPoints.clear();

	int collisionY = y + 1;

	for( int i = 0; i < 9; ++i)
	{
		if( i == 3 )
			++collisionY;

		collisionPoints.push_back( new Point( x + i, collisionY ) );
	}
}

bool FigureZDefaultState::Move( Direction direction )
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

void FigureZDefaultState::Clear()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	for( int i = 0, inc = 0; i < 9; i += 3 )
	{
		if( i == 6 && inc == 0 )
		{
			i -= 3;
			++inc;
		}

		instance->SetChar( x + i, y + inc, L' ' );
		instance->SetChar( x + 1 + i, y + inc, L' ' );
		instance->SetChar( x + 2 + i, y + inc, L' ' );
	}
}

void FigureZDefaultState::MoveTo( int x, int y )
{
	this->x = x;
	this->y = y;

	CollisionUpdate();
}