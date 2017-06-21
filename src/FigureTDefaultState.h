#pragma once

#include "FigureState.h"
#include "FigureTRightState.h"
#include "TestApp.h"

class FigureTDefaultState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureTDefaultState( int x = 1, int y = 1 );
	~FigureTDefaultState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
