#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

class Munyeco
{
public:
	Munyeco(Ogre::SceneNode *padre);
	~Munyeco() {};
	Ogre::SceneNode* getCuello();

private:

	Ogre::SceneNode* cuello;
	Ogre::SceneNode* cabeza;
	Ogre::SceneNode* cuerpo;


};

