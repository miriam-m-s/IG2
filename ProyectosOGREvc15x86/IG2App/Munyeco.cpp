#include "Munyeco.h"
#include <OgreEntity.h>

Munyeco::Munyeco(Ogre::SceneNode* padre)
{
	cuello = padre->createChildSceneNode();
	cuello->setInheritScale(false);

	cabeza = cuello->createChildSceneNode();
	Ogre::Entity* Cabeza = padre->getCreator()->createEntity("sphere.mesh");
	cabeza->attachObject(Cabeza);
	cabeza->setPosition(0, 100*cabeza->getScale().y,0);

	Ogre::SceneNode *nariz = cabeza->createChildSceneNode();
	Ogre::Entity* Nariz = padre->getCreator()->createEntity("sphere.mesh");
	nariz->attachObject(Nariz);
	nariz->setScale(0.1, 0.1, 0.1);
	nariz->setPosition(0, 0, 100 * cabeza->getScale().z);

	cuerpo = cuello->createChildSceneNode();
	Ogre::Entity* Cuerpo = padre->getCreator()->createEntity("sphere.mesh");
	cuerpo->attachObject(Cuerpo);
	cuerpo->setScale(2,2,2);
	cuerpo->setPosition(0, -100*cuerpo->getScale().y, 0);

	Ogre::SceneNode* ombligo = cuerpo->createChildSceneNode();
	Ogre::Entity* Ombligo = padre->getCreator()->createEntity("sphere.mesh");
	ombligo->attachObject(Ombligo);
	ombligo->setScale(0.1, 0.1, 0.1);
	ombligo->setPosition(0, 0, 100 * cuerpo->getScale().z / 2);

	cuello->setScale(0.5,0.5,0.5);


}

Ogre::SceneNode* Munyeco::getCuello()
{
	return cuello;
}
