/******************************************************************************/
/*!
\file	MenuShop.h
\author Mok Wei Min
\par
\brief
All the enums for shop/menu states
*/
/******************************************************************************/
#ifndef MENUSHOP_H
#define MENUSHOP_H
#include "MyMath.h"
#include <string>
using std::string;

/******************************************************************************/
/*!
Class MenuShop:
\brief	Shop enums/Menu enums
*/
/******************************************************************************/
class MenuShop
{
public:
	float PressTime = 0;
	enum MENU
	{
		MENU1 = 0,
		STARTGAME,
		CREDITS,
		HELP,
		QUIT,
		MAX,
	};
	enum OPTION
	{
		O_QUIT,
		O_CREDIT,
		O_HELP,
		O_MAX,
	};
	enum SHOP_OPTION
	{
		S_BUY,
		S_SELL,
		S_BACK,
		S_MAX,
	};
	enum SHOP_BUY
	{
		SB_AMMO,
		SB_BOMB,
		SB_BACK,
		SB_MAX,
	};

	enum SHOP_SELL
	{
		SS_AMMO,
		SS_ORE,
		SS_EGG,
		SS_BACK,
		SS_MAX,
	};

	MenuShop(){}
	~MenuShop(){}
};
#endif