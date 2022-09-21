#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

class Noria
{

public:

	Noria(int n, Ogre::SceneNode* node);
	~Noria() {  };
	void giraNoria();
	void frameRendered();

private:
	Ogre::SceneNode* aspasNode=nullptr;
};

