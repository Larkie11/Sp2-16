/************************************************************/
/*!
\file	rawMaterial.cpp
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A Class for the raw material to use in the game
*/
/************************************************************/

#include "rawMaterial.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

/************************************************************/
/*!

\brief
rawMaterial() is a constructor for rawMaterial class, where I
set the default values needed for the methods.

*/
/************************************************************/

rawMaterial::rawMaterial() :hp(3), isAlive(true)
{
	shape = MeshBuilder::GenerateOBJ("material", "OBJ//rawMaterial.obj");
	shape->textureID = LoadTGA("Image//RawMaterial.tga");
};

/************************************************************/
/*!

\brief
~rawMaterial() is a destructor for rawMaterial class.

*/
/************************************************************/

rawMaterial::~rawMaterial()
{};
