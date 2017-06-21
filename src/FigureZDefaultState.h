#pragma once

#include "FigureState.h"
#include "FigureZVerticalState.h"
#include "TestApp.h"

class FigureZDefaultState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureZDefaultState( int x = 1, int y = 1 );
	~FigureZDefaultState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
