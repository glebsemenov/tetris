#pragma once

#include "FigureState.h"

class Figure
{
protected:
	FigureState * figureState;
	int x, y;

public:
	Figure();
	Figure( FigureState * );
	~Figure();

	void SetState();
	void Render();
	bool Move( Direction );
	void Clear();
	void MoveTo( int, int );
};
