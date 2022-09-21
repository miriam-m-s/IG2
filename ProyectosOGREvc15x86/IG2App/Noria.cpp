#include "Noria.h"
#include "AspaNoria.h"
#include <OgreEntity.h>
Noria::Noria(int n, Ogre::SceneNode* node)
{
	float angle = 90.0f;

	Ogre::SceneNode* cilindroNode = node->createChildSceneNode("Cilindro");
	cilindroNode->setInheritScale(false);
	Ogre::Entity* cilindro = node->getCreator()->createEntity("Barrel.mesh");

	cilindroNode->attachObject(cilindro);
	cilindroNode->setScale(40, 25, 40);
	cilindroNode->roll(Ogre::Degree(90));

	aspasNode= node->createChildSceneNode("Aspas");
	aspasNode->setInheritScale(false);

	for (int i = 0; i < n; i++) {

		Ogre::SceneNode* Aspa = aspasNode->createChildSceneNode("Aspa" + std::to_string(i + 1));
		AspaNoria* aspaNoria = new AspaNoria(Aspa);
		/*Aspa->setPosition(0, Ogre::Math::Sin(Ogre::Math::DegreesToRadians(angle))*radius , 
			-Ogre::Math::Cos(Ogre::Math::DegreesToRadians(angle)) * radius);*/
	
		Aspa->pitch(Ogre::Degree(angle));

		angle += 360.0f / n;

	}	
}

void Noria::giraNoria()
{
	aspasNode->pitch(Ogre::Degree(1));
}

void Noria::frameRendered()
{
	giraNoria();
}
