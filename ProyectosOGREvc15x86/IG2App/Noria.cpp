#include "Noria.h"
#include "AspaNoria.h"
#include <OgreEntity.h>
Noria::Noria(int n, Ogre::SceneNode* node)
{
	float angle = 90.0f;
	float radius = 200.0f;
	aspasNode= node->createChildSceneNode("Aspas");
	for (int i = 0; i < n; i++) {

		Ogre::SceneNode* Aspa = aspasNode->createChildSceneNode("Aspa" + std::to_string(i + 1));
		AspaNoria* aspaNoria = new AspaNoria(Aspa);
		/*Aspa->setPosition(0, Ogre::Math::Sin(Ogre::Math::DegreesToRadians(angle))*radius , 
			-Ogre::Math::Cos(Ogre::Math::DegreesToRadians(angle)) * radius);*/
	
		Aspa->pitch(Ogre::Degree(angle));

		angle += 360.0f / n;

	}
	Ogre::SceneNode* cilidroNode= node->createChildSceneNode("Cilindro");	

	Ogre::Entity* cilindro = node->getCreator()->createEntity("column.mesh");
	
	cilidroNode->attachObject(cilindro);
	cilidroNode->setScale(3,-0.2, 3);
	cilidroNode->roll(Ogre::Degree(90));
	
	
}

void Noria::giraNoria()
{
	aspasNode->pitch(Ogre::Degree(1));
}

void Noria::frameRendered()
{
	giraNoria();
}
