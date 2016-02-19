#ifndef SHARED_DATA_H
#define SHARED_DATA_H

class SharedData
{
public:
	enum GAMESTATE
	{
		MENU,
		GAME,
		SHOP,
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
	int bullet;
private:
	SharedData()
	{
		gameState = MENU;
		bullet = 30;
	}
	~SharedData()
	{

	}
};
#endif // !SHARED_DATA_H