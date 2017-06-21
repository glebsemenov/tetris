#pragma once

#include "FigureState.h"
#include "FigureTLeftState.h"
#include "TestApp.h"

class FigureTDownState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureTDownState( int x = 1, int y = 1 );
	~FigureTDownState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
