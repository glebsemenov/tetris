#pragma once

#include "FigureState.h"
#include "TestApp.h"

class FigureODefaultState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureODefaultState( int x = 1, int y = 1 );
	~FigureODefaultState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
