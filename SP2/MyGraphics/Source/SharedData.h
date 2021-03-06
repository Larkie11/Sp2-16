/******************************************************************************/
/*!
\file	SharedData.h
\author Mok Wei Min
\par	email: 155208U\@mymail.nyp.edu.sg
\brief
Variables that are accessible for other classes
*/
/******************************************************************************/
#ifndef SHARED_DATA_H
#define SHARED_DATA_H
#include "irrklang.h"
#include <string>
using std::string;


/******************************************************************************/
/*!
Class SharedData:
\brief	Stores the struct/booleans/game states that we want to access from other classes
*/
/******************************************************************************/
class SharedData
{
//Variables in here can be used by any other classes as long as you include "SharedData.h"
//How to use: SharedData::GetInstance()->(call whatever that is in the shared data class you want, example: bullet.quantity)
public:
	struct INVENTORY
	{
		int quantity;
	};
	enum GAMESTATE
	{
		MENU,
		G_CUTSCENE,
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
	//Items player has share across all scenes
	INVENTORY bullet;
	INVENTORY gold;
	INVENTORY bomb;
	INVENTORY egg;
	INVENTORY mineral;
	float width;
	float height;
	int enemycounter;
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
		enemycounter = 0;
	}
	~SharedData()
	{

	}
};
#endif // !SHARED_DATA_H