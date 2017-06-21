#pragma once

#include "FigureState.h"
#include "FigureLDownState.h"
#include "TestApp.h"

class FigureLRightState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureLRightState( int x = 1, int y = 1 );
	~FigureLRightState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
