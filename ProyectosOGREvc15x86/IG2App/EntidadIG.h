#pragma once
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreTrays.h>
#include <vector>
#include <iostream>

class EntidadIG :public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* node);

	
	virtual ~EntidadIG() {

	};
	virtual void frameRendered(const Ogre::FrameEvent& evt) {
	}

	//Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad) { };

protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt)
	{
		return false;
	};
};

class Plano :public EntidadIG {
public :
	Plano(Ogre::SceneNode* padre);
	
};

class Munyeco :public  EntidadIG
{
	public:

		Munyeco(Ogre::SceneNode* padre);
		~Munyeco() {};
		Ogre::SceneNode* getCuello();

	private:

		Ogre::SceneNode* cuello;
		Ogre::SceneNode* cabeza;
		Ogre::SceneNode* cuerpo;
};
class Noria :public  EntidadIG
{

	public:

		Noria(int n, Ogre::SceneNode* node);
		~Noria() {  };
		void giraNoria(Ogre::Real time);
		void frameRendered(const Ogre::FrameEvent& evt);
		Ogre::SceneNode* getNoria();

	private:
		Ogre::SceneNode* aspasNode = nullptr;
		Ogre::SceneNode* cilindroNode = nullptr;
		bool estagirando;
};

class AspaNoria : public  EntidadIG
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



