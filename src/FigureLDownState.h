#pragma once

#include "FigureState.h"
#include "FigureLLeftState.h"
#include "TestApp.h"

class FigureLDownState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureLDownState( int x = 1, int y = 1 );
	~FigureLDownState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
