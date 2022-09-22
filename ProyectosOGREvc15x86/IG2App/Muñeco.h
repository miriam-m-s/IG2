#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

class Muñeco
{
public:
	Muñeco(Ogre::SceneNode *padre);
	~Muñeco() {};

private:

	Ogre::SceneNode* cuello;
	Ogre::SceneNode* cabeza;
	Ogre::SceneNode* cuerpo;


};

