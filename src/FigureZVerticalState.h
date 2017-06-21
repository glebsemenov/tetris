#pragma once

#include "FigureState.h"
#include "FigureZDefaultState.h"
#include "TestApp.h"

class FigureZVerticalState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureZVerticalState( int x = 1, int y = 1 );
	~FigureZVerticalState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
