#pragma once

#include "FigureState.h"
#include "FigureIVerticalState.h"
#include "TestApp.h"

class FigureIDefaultState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureIDefaultState( int x = 1, int y = 1 );
	~FigureIDefaultState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
