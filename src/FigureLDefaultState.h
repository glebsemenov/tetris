#pragma once

#include "FigureState.h"
#include "FigureLRightState.h"
#include "TestApp.h"

class FigureLDefaultState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureLDefaultState( int x = 1, int y = 1 );
	~FigureLDefaultState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
