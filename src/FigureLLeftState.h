#pragma once

#include "FigureState.h"
#include "FigureLDefaultState.h"
#include "TestApp.h"

class FigureLLeftState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureLLeftState( int x = 1, int y = 1 );
	~FigureLLeftState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
