#include "FigureTDefaultState.h"

FigureTDefaultState::FigureTDefaultState( int x, int y ): Base( x, y )
{
	int collisionY = y + 1;

	for( int i = 0; i < 9; ++i)
	{
		// т.к. фигура в виде буквы "Т", то коллизия должна быть на крайних блоках:
		// ( (0, 1), (1, 1) и (2, 1) )
		// ( (3, 2), (4, 2) и (5, 2) )
		// ( (6, 1), (7, 1) и (8, 1) )
		if( i == 3 )
			++collisionY;

		if( i == 6 )
			--collisionY;

		collisionPoints.push_back( new Point( x + i, collisionY ) );
	}
}

FigureTDefaultState::~FigureTDefaultState()
{
}

FigureState * FigureTDefaultState::GetNextState()
{
	TestApp * instance = TestApp::GetAppInstance();

	if( instance->GetChar( x, y + 1 ) != L' ' || instance->GetChar( x + 3, y + 2 ) != L' ' )
		return NULL;

	return new FigureTRightState( x, y );
}

void FigureTDefaultState::Render()
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

	instance->SetChar( x + 3, y + 1, L'[' );
	instance->SetChar( x + 4, y + 1, L'x' );
	instance->SetChar( x + 5, y + 1, L']' );
}

void FigureTDefaultState::CollisionUpdate()
{
	collisionPoints.clear();

	int collisionY = y + 1;

	for( int i = 0; i < 9; ++i)
	{
		if( i == 3 )
			++collisionY;

		if( i == 6 )
			--collisionY;

		collisionPoints.push_back( new Point( x + i, collisionY ) );
	}
}

bool FigureTDefaultState::Move( Direction direction )
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

void FigureTDefaultState::Clear()
{
	TestApp * instance = TestApp::GetAppInstance();
	
	instance->SetChar( x, y, L' ' );
	instance->SetChar( x + 1, y, L' ' );
	instance->SetChar( x + 2, y, L' ' );

	instance->SetChar( x + 3, y, L' ' );
	instance->SetChar( x + 4, y, L' ' );
	instance->SetChar( x + 5, y, L' ' );

	instance->SetChar( x + 6, y, L' ' );
	instance->SetChar( x + 7, y, L' ' );
	instance->SetChar( x + 8, y, L' ' );

	instance->SetChar( x + 3, y + 1, L' ' );
	instance->SetChar( x + 4, y + 1, L' ' );
	instance->SetChar( x + 5, y + 1, L' ' );
}

void FigureTDefaultState::MoveTo( int x, int y )
{
	this->x = x;
	this->y = y;

	CollisionUpdate();
}