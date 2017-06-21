#include "FigureState.h"

FigureState::FigureState( int x, int y )
{
	this->x = x;
	this->y = y;
}

FigureState::~FigureState()
{
	collisionPoints.clear();
}