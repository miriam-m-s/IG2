#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

class AspaNoria
{

	public: 
		
	AspaNoria(Ogre::SceneNode* NoriaNode);
	~AspaNoria();
	

private:

	Ogre::SceneNode* AspaNoriaNode = nullptr;
	Ogre::SceneNode* tableNode1 = nullptr;
	Ogre::SceneNode* tableNode2 = nullptr;
	Ogre::SceneNode* cuboNode = nullptr;

};

