#include "EntidadIG.h"
#include "IG2App.h"

std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(Ogre::SceneNode* nodo) {
	mNode = nodo;
	mSM = mNode->getCreator();
}

void EntidadIG::sendEvent(MessageType msgType, EntidadIG* entidad)
{
	for (EntidadIG* e : appListeners)
		e->receiveEvent(msgType, this);
}

Plano::Plano(Ogre::SceneNode* node) :EntidadIG(node)
{

	Ogre::Entity* plano = node->getCreator()->createEntity("cube.mesh");
	plano->setMaterialName("Practica1/plano");
	node->attachObject(plano);
	node->setScale(30, 0.25, 30);
}

AspaNoria::AspaNoria(Ogre::SceneNode* NoriaNode, float angle,int i) :EntidadIG(NoriaNode)
{
	
	AspaNoriaNode = NoriaNode->createChildSceneNode("Aspita" + std::to_string(i + 1));

	Ogre::Entity* cubo = NoriaNode->getCreator()->createEntity("cube.mesh");
	cuboNode = AspaNoriaNode->createChildSceneNode("cubo" + std::to_string(i + 1));
	cubo->setMaterialName("Practica1/cangilon");
	cuboNode->attachObject(cubo);
	cuboNode->setScale(0.7, 0.7, 0.7);
	cuboNode->setPosition(0, 0, -225);
	cuboNode->pitch(Ogre::Degree(-angle));

	Ogre::Entity* tablero1 = NoriaNode->getCreator()->createEntity("cube.mesh");
	tableNode1 = AspaNoriaNode->createChildSceneNode();
	tablero1->setMaterialName("Practica1/tablon");
	tableNode1->attachObject(tablero1);
	tableNode1->setScale(0.05, 0.3, 5);
	tableNode1->setPosition(cuboNode->getScale().x * 50, 0, 0);

	Ogre::Entity* tablero2 = NoriaNode->getCreator()->createEntity("cube.mesh");
	tableNode2 = AspaNoriaNode->createChildSceneNode();
	tablero2->setMaterialName("Practica1/tablon");
	tableNode2->attachObject(tablero2);
	tableNode2->setScale(0.05, 0.3, 5);
	tableNode2->setPosition(-cuboNode->getScale().x * 50, 0, 0);

	AspaNoriaNode->translate(0, 0, -250);
}

AspaNoria::~AspaNoria()
{
}

void AspaNoria::frameRendered(const Ogre::FrameEvent& evt)
{
	//
}

Noria::Noria(int n, Ogre::SceneNode* node) :EntidadIG(node), estagirando(true),n(n)
{
	float angle = 90.0f;
	
	cilindroNode = node->createChildSceneNode("Cilindro");
	cilindroNode->setInheritScale(false);
	Ogre::Entity* cilindro = node->getCreator()->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/rodillo");

	cilindroNode->attachObject(cilindro);
	cilindroNode->setScale(40, 25, 40);
	cilindroNode->roll(Ogre::Degree(90));

	aspasNode = cilindroNode->createChildSceneNode("Aspas");
	aspasNode->setInheritScale(false);
	aspasNode->roll(Ogre::Degree(-90));

	for (int i = 0; i < n; i++) {
		Ogre::SceneNode* Aspa = aspasNode->createChildSceneNode("Aspa" + std::to_string(i + 1));
		
		AspaNoria* aspaNoria = new AspaNoria(Aspa,angle,i);
		Aspa->pitch(Ogre::Degree(angle));
		angle += 360.0f / n;
	}
}


void Noria::giraNoria()
{
	if (!estagirando) aspasNode->pitch(Ogre::Degree(1.0));
}

void Noria::frameRendered(const Ogre::FrameEvent& evt)
{

	if (estagirando) {
		Ogre::Real time = evt.timeSinceLastEvent;
	
		aspasNode->pitch(Ogre::Radian(time));

		for (int i = 0; i < n; i++) {
			auto node = aspasNode->getChild("Aspa" + std::to_string(i + 1))->getChild("Aspita" + std::to_string(i + 1))->getChild("cubo" + std::to_string(i + 1));
			node->pitch(Ogre::Radian( -time));
		}
	}
}

void Noria::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	estagirando = false;
}

Munyeco::Munyeco(Ogre::SceneNode* padre) :  EntidadIG(padre), tortura(false) 
{
	cuello = padre->createChildSceneNode();
	cuello->setInheritScale(false);

	cabeza = cuello->createChildSceneNode();
	Ogre::Entity* Cabeza = padre->getCreator()->createEntity("sphere.mesh");
	cabeza->attachObject(Cabeza);
	Cabeza->setMaterialName("Practica1/cabeza");
	cabeza->setPosition(0, 100 * cabeza->getScale().y, 0);

	//Ogre::SceneNode* nariz = cabeza->createChildSceneNode();
	//Ogre::Entity* Nariz = padre->getCreator()->createEntity("sphere.mesh");
	//Nariz->setMaterialName("Practica1/nariz");
	//nariz->attachObject(Nariz);
	//nariz->setScale(0.1, 0.1, 0.1);
	//nariz->setPosition(0, 0, 100 * cabeza->getScale().z);

	cuerpo = cuello->createChildSceneNode();
	Ogre::Entity* Cuerpo = padre->getCreator()->createEntity("sphere.mesh");
	Cuerpo->setMaterialName("Practica1/cuerpo");
	cuerpo->attachObject(Cuerpo);
	cuerpo->setScale(2, 2, 2);
	cuerpo->setPosition(0, -100 * cuerpo->getScale().y, 0);

	Ogre::SceneNode* ombligo = cuerpo->createChildSceneNode();
	Ogre::Entity* Ombligo = padre->getCreator()->createEntity("sphere.mesh");
	Ombligo->setMaterialName("Practica1/ombligo");
	ombligo->attachObject(Ombligo);
	ombligo->setScale(0.1, 0.1, 0.1);
	ombligo->setPosition(0, 0, 100 * cuerpo->getScale().z / 2);

	cuello->setScale(0.5, 0.5, 0.5);
}

void Munyeco::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	tortura = true;
}

void Munyeco::frameRendered(const Ogre::FrameEvent& evt)
{
	if (tortura) {
		Ogre::Real time = evt.timeSinceLastEvent;
		cabeza->yaw(Ogre::Radian(time));
		cuerpo->yaw(-Ogre::Radian(time));
	}
}

bool Munyeco::KeyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_UP)
	{
		cuello->translate(0, 0, 100);
	}

	return true;
}


