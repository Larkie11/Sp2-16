#ifndef SHARED_DATA_H
#define SHARED_DATA_H

class SharedData
{
public:
	enum GAMESTATE
	{
		MENU,
		GAME,
		QUIT,
		MAX,
	};
	GAMESTATE gameState;
	static SharedData* GetInstance()
	{
		static SharedData data;
		return &data;
	}
	bool stateCheck = false;
private:
	SharedData()
	{
		gameState = MENU;
	}
	~SharedData()
	{

	}
};
#endif // !SHARED_DATA_H