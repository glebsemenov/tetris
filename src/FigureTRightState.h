#pragma once

#include "FigureState.h"
#include "FigureTDownState.h"
#include "TestApp.h"

class FigureTRightState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureTRightState( int x = 1, int y = 1 );
	~FigureTRightState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
