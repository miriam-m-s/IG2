#pragma once
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreTrays.h>
#include <vector>
#include <iostream>
#include<OgreTimer.h>
#include<OgreAnimation.h>
#include<OgreKeyFrame.h>


enum MessageType {NADA, CAMBIATEXTURE, DETIENE};

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

	Ogre::Entity* plano;
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	bool cambiaText;
	unsigned long initTime;
	Ogre::Timer* myTymer;

public :

	Plano(Ogre::SceneNode* padre);
	void SetMaterial(std::string name);
	void frameRendered(const Ogre::FrameEvent& evt);

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

		Ogre::Entity* Cabeza;
		Ogre::Entity* Cuerpo;
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

class AspasNave :public EntidadIG {

	Ogre::SceneNode* aspaPadre;

public:

	AspasNave(Ogre::SceneNode *padre,  int n);
	void frameRendered(const Ogre::FrameEvent& evt);
	~AspasNave() {};


};

class Avion : public EntidadIG {

	Ogre::SceneNode* movimiento;
	AspasNave* Aspa1;
	AspasNave* Aspa2;
	bool estaMoviendo;

public:

	Avion(Ogre::SceneNode* padre, Ogre::SceneNode* nodoMovimiento, int n);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void frameRendered(const Ogre::FrameEvent& evt) override;
	~Avion() {};

private:

	Ogre::SceneNode* esferaCentral = nullptr;

};

class Aspa :public EntidadIG {

public:

	Aspa(Ogre::SceneNode* Aspa, int i);
	~Aspa() {};

};

class BrazoDron :public EntidadIG {

	AspasNave* aspa;

public:

	BrazoDron(Ogre::SceneNode* padre);
	void frameRendered(const Ogre::FrameEvent& evt);
	~BrazoDron() {};

};

class Dron :public EntidadIG {

	std::vector<BrazoDron*> brazos;
	Ogre::SceneNode* movimiento;
	Ogre::Timer* myTymer;
	unsigned long initTime;
	Ogre::Entity* Cabeza;
	bool actualiza = false;
	int sentido = 1;

public:

	Dron(Ogre::SceneNode* padre, int i, bool avispa, Ogre::SceneNode* move);
	void frameRendered(const Ogre::FrameEvent& evt);
	~Dron() {
		delete myTymer;
	};
	void changeColor(){
		Cabeza->setMaterialName("Practica1/Amarillo");
	}
	
};

class Sinbad :public EntidadIG {

private:
	Ogre::SceneNode* mSinbadNode = nullptr;
	Ogre::SceneNode* mSinbadNodemov = nullptr;
	Ogre::AnimationState* anim_Sinbadtop = nullptr;
	Ogre::AnimationState* anim_Sinbaddown = nullptr;
	Ogre::AnimationState* anim_Sinbaddance = nullptr;
	Ogre::Timer* myTymer;
	unsigned long initTime;
	int sentido = 1;
	Ogre::Entity* ent;
	bool corriendo;
	bool izq;
	int scene;

public:

	Sinbad(Ogre::SceneNode* padre, bool mano, int scene_);
	void frameRendered(const Ogre::FrameEvent& evt);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void arma();
	void arma(bool izq);
	void cambiaEspada();
	~Sinbad() {};
	


};

class Bomba :public EntidadIG {
	private:
		Ogre::AnimationState* animationState;
		bool parada;
		virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
public:
	Bomba(Ogre::SceneNode* padre);
	void frameRendered(const Ogre::FrameEvent& evt);
	~Bomba();
};






