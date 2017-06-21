#pragma once

#include "BaseApp.h"
#include "Point.h"
#include "DirectionEnum.h"

class FigureState: public BaseApp
{
protected:
	int x, y;
	vector< Point* > collisionPoints;

public:
	FigureState( int x = 1, int y = 1 );
	~FigureState();

	virtual FigureState * GetNextState() = 0;
	virtual void Render() = 0;
	virtual void CollisionUpdate() = 0;
	virtual bool Move( Direction ) = 0;
	virtual void Clear() = 0;
	virtual void MoveTo( int, int ) = 0;
};
