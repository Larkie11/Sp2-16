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
	enum MENUPAGE
	{
		STARTGAME,
		SETTING,
		CREDIT,
		M_QUIT
	};
	GAMESTATE gameState;

	static SharedData* GetInstance()
	{
		static SharedData data;
		return &data;
	}
	bool stateCheck = false;
	int bullet;
	int gold;
	int bomb;
	int egg;
private:
	SharedData()
	{
		gameState = MENU;
		bullet = 30;
		gold = 100;
		bomb = 0;
		egg = 0;
	}
	~SharedData()
	{

	}
};
#endif // !SHARED_DATA_H