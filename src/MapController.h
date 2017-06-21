#pragma once

class TestApp;
class MapController
{
private:
	void CleanUp();
	void ShiftBufferDown( int );
	void EraseLine( int );

public:
	MapController();
	~MapController();

	bool CheckForGameOver();
	void CheckRows();
};