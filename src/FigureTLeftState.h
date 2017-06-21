#pragma once

#include "FigureState.h"
#include "FigureTDefaultState.h"
#include "TestApp.h"

class FigureTLeftState : public FigureState
{
private:
	typedef FigureState Base;

public:
	FigureTLeftState( int x = 1, int y = 1 );
	~FigureTLeftState();

	virtual FigureState * GetNextState();
	virtual void Render();
	virtual void CollisionUpdate();
	virtual bool Move( Direction );
	virtual void Clear();
	virtual void MoveTo( int, int );
};
