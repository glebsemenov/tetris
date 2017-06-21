#pragma once

#include "FigureState.h"
#include "FigureIDefaultState.h"
#include "TestApp.h"

class FigureIVerticalState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureIVerticalState( int x = 1, int y = 1 );
	~FigureIVerticalState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
