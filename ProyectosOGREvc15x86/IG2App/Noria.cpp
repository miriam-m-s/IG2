#include "Noria.h"
#include "AspaNoria.h"

Noria::Noria(int n, Ogre::SceneNode* node)
{
	double angle = 90;
	double radius = 200;

	for (int i = 0; i < n; i++) {

		Ogre::SceneNode* Aspa = node->createChildSceneNode("Aspa" + std::to_string(i + 1));
		AspaNoria* aspaNoria = new AspaNoria(Aspa);


		/*Aspa->setPosition(0, Ogre::Math::Sin(Ogre::Math::DegreesToRadians(angle))*radius , 
			-Ogre::Math::Cos(Ogre::Math::DegreesToRadians(angle)) * radius);*/
	
		Aspa->pitch(Ogre::Degree(angle));

		angle += 360 / n;

	}
}
