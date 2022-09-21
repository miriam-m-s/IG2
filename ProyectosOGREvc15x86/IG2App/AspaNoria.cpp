#include "AspaNoria.h"
#include <OgreEntity.h>

AspaNoria::AspaNoria( Ogre::SceneNode*  NoriaNode)
{

	AspaNoriaNode = NoriaNode->createChildSceneNode();

	Ogre::Entity* cubo = NoriaNode->getCreator()->createEntity("cube.mesh");
	cuboNode = AspaNoriaNode->createChildSceneNode();
	cuboNode->attachObject(cubo);
	cuboNode->setScale(0.7, 0.7, 0.7);
	cuboNode->setPosition(0,0,-325);

	Ogre::Entity* tablero1 = NoriaNode->getCreator()->createEntity("cube.mesh");
	tableNode1 = AspaNoriaNode->createChildSceneNode();
	tableNode1->attachObject(tablero1);
	tableNode1->setScale(0.05, 0.5, 7);
	tableNode1->setPosition(cuboNode->getScale().x*50, 0, 0);

	Ogre::Entity* tablero2 = NoriaNode->getCreator()->createEntity("cube.mesh");
	tableNode2 = AspaNoriaNode->createChildSceneNode();
	tableNode2->attachObject(tablero2);
	tableNode2->setScale(0.05, 0.5, 7);
	tableNode2->setPosition(-cuboNode->getScale().x * 50, 0, 0);

}

AspaNoria::~AspaNoria()
{
}
