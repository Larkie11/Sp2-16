#ifndef MENUSHOP_H
#define MENUSHOP_H
#include "MyMath.h"
#include <string>
using std::string;

class MenuShop
{
public:
	int item;
	string shopInput;
	string Input;
	float PressTime = 0;
	enum MENU
	{
		MENU1 = 0,
		STARTGAME,
		OPTIONS,
		QUIT,
		MAX,
	};
	enum OPTION
	{
		O_SETTING,
		O_QUIT,
		O_MAX,
	};
	enum SHOP_OPTION
	{
		S_YES,
		S_NO,
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
	SHOP_OPTION s_option;
	SHOP_BUY s_buy;
	MenuShop(){}
	~MenuShop(){}
};
#endif