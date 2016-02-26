#ifndef SHARED_DATA_H
#define SHARED_DATA_H
#include "irrklang.h"
#include <string>
#include <iostream>
using std::string;
using std::cout;

class SharedData
{
//Variables in here can be used by any other classes as long as you include "SharedData.h"
//How to use: SharedData::GetInstance()->(call whatever that is in the shared data class you want, example: bullet.quantity)
//Don't know can ask me (Wei Min)
public:
	struct INVENTORY
	{
		int quantity;
	};
	enum GAMESTATE
	{
		MENU,
		GAME,
		SCENE2,
		SCENE3,
		SHOP,
		CUTSCENE,
		WIN,
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
	string gameScene;
	static SharedData* GetInstance()
	{
		static SharedData data;
		return &data;
	}
	bool stateCheck = false;
	string music;
	//Items player has share across all scenes
	INVENTORY bullet;
	INVENTORY gold;
	INVENTORY bomb;
	INVENTORY egg;
	INVENTORY mineral;
	float width;
	float height;

	string SoundName[];
private:
	SharedData()
	{
		//Instantiate
		gameState = MENU;
		bullet.quantity = 30;
		egg.quantity = 0;
		bomb.quantity = 0;
		gold.quantity = 100;
		mineral.quantity = 0;
	}
	~SharedData()
	{

	}
};
#endif // !SHARED_DATA_H