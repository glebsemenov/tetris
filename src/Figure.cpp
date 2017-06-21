#include "Figure.h"

Figure::Figure()
{
}

Figure::Figure( FigureState * figureState )
{
	this->figureState = figureState;
}

Figure::~Figure()
{
}

void Figure::SetState()
{
	FigureState * newFigureState = this->figureState->GetNextState();

	if( newFigureState == NULL )
		return;

	delete this->figureState;

	this->figureState = newFigureState;
}

void Figure::Render()
{
	this->figureState->Render();
}

bool Figure::Move( Direction direction )
{
	return this->figureState->Move( direction );
}

void Figure::Clear()
{
	this->figureState->Clear();
}

void Figure::MoveTo( int x, int y )
{
	this->figureState->MoveTo( x, y );
}