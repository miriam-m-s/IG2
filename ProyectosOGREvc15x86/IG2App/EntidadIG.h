#pragma once
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreTrays.h>
#include <vector>
#include <iostream>

enum MessageType {NADA};

class EntidadIG :public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* node);

	
	virtual ~EntidadIG() {	};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {};
	virtual void receiveEvent(MessageType msgType,  EntidadIG* entidad) {};
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {return true; };
	virtual void sendEvent(MessageType msgType,  EntidadIG* entidad);

	//Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad) { appListeners.push_back(entidad); };

protected:

	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	
	
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
	
	private:

		bool tortura;
		virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
		void frameRendered(const Ogre::FrameEvent& evt);
		bool keyPressed(const OgreBites::KeyboardEvent& evt);
		Ogre::SceneNode* cuello;
		Ogre::SceneNode* cabeza;
		Ogre::SceneNode* cuerpo;
};

class Noria :public  EntidadIG
{

	public:

		Noria(int n, Ogre::SceneNode* node);
		~Noria() {  };
		void giraNoria();
		void frameRendered(const Ogre::FrameEvent& evt);

	private:

		virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
		Ogre::SceneNode* aspasNode = nullptr;
		Ogre::SceneNode* cilindroNode = nullptr;
		bool estagirando;
		int n;
};

class AspaNoria : public  EntidadIG
{

	public:

		AspaNoria(Ogre::SceneNode* NoriaNode, float angle,int i);
		~AspaNoria();


		void frameRendered(const Ogre::FrameEvent& evt) override;


	private:

		Ogre::SceneNode* AspaNoriaNode = nullptr;
		Ogre::SceneNode* tableNode1 = nullptr;
		Ogre::SceneNode* tableNode2 = nullptr;
		Ogre::SceneNode* cuboNode = nullptr;

};



