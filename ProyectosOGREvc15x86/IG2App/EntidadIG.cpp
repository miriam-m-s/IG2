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
	 Cabeza = padre->getCreator()->createEntity("sphere.mesh");
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
	 Cuerpo = padre->getCreator()->createEntity("sphere.mesh");
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

bool Munyeco::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_UP)
	{
		cuello->translate(Ogre::Math::Sin(cuello->getOrientation().getYaw())*2, 0, Ogre::Math::Cos(cuello->getOrientation().getYaw()) * 2);
	}
	else if (evt.keysym.sym == SDLK_DOWN)
	{
		cuello->translate(-Ogre::Math::Sin(cuello->getOrientation().getYaw()) * 2, 0,- Ogre::Math::Cos(cuello->getOrientation().getYaw()) * 2);
	}
	else if (evt.keysym.sym == SDLK_LEFT)
	{
		cuello->yaw(Ogre::Degree(2));
	}
	else if (evt.keysym.sym == SDLK_RIGHT)
	{
		cuello->yaw(Ogre::Degree(-2));
	}


	return true;
}

void Munyeco::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	//tortura = true;
	Cabeza->setMaterialName("Practica1/CabezaRoja");
	Cuerpo->setMaterialName("Practica1/CuerpoRojo");
}

void Munyeco::frameRendered(const Ogre::FrameEvent& evt)
{
	/*if (tortura) {
		Ogre::Real time = evt.timeSinceLastEvent;
		cabeza->yaw(Ogre::Radian(time));
		cuerpo->yaw(-Ogre::Radian(time));
	}*/
	

}

Avion::Avion(Ogre::SceneNode* padre, int n):EntidadIG(padre)
{

	esferaCentral = padre->createChildSceneNode();
	Ogre::Entity * esfera = padre->getCreator()->createEntity("sphere.mesh");
	esfera->setMaterialName("Practica1/esferaAvion");
	esferaCentral->attachObject(esfera);
	esferaCentral->setScale(1.5,1.5,1.5);

	Ogre::SceneNode* NinjaNode = padre->createChildSceneNode();
	Ogre::Entity* ninja = padre->getCreator()->createEntity("ninja.mesh");
	ninja->setMaterialName("Practica1/ninja");
	NinjaNode->attachObject(ninja);

	Ogre::SceneNode* Ala1 = padre->createChildSceneNode();
	Ogre::Entity* ala1 = padre->getCreator()->createEntity("cube.mesh");
	ala1->setMaterialName("Practica1/alasAvion");
	Ala1->attachObject(ala1);
	Ala1->setScale(3, 0.1, 2);
	Ala1->setPosition(-150, 0, 0);

	Ogre::SceneNode* Ala2 = padre->createChildSceneNode();
	Ogre::Entity* ala2 = padre->getCreator()->createEntity("cube.mesh");
	ala2->setMaterialName("Practica1/alasAvion");
	Ala2->attachObject(ala2);
	Ala2->setScale(3, 0.1, 2);
	Ala2->setPosition(150, 0, 0);

	Ogre::SceneNode* Morro = padre->createChildSceneNode();
	Ogre::Entity *morro = padre->getCreator()->createEntity("Barrel.mesh");
	morro->setMaterialName("Practica1/morroAvion");
	Morro->attachObject(morro);
	Morro->setScale(20, 25, 20);
	Morro->pitch(Ogre::Degree(90));
	Morro->setPosition(0,0,-90);

	Ogre::SceneNode *alaAspa1 = Ala1->createChildSceneNode();
	AspasNave *Aspa1 = new AspasNave(alaAspa1, 5);
	alaAspa1->yaw(Ogre::Degree(90));
	alaAspa1->setInheritScale(false);
	alaAspa1->setPosition(-30,0,-50);
	alaAspa1->setScale(0.2, 0.2, 0.2);

	Ogre::SceneNode* alaAspa2 = Ala2->createChildSceneNode();
	AspasNave *Aspa2 = new AspasNave(alaAspa2, 5);
	alaAspa2->setInheritScale(false);
	alaAspa2->yaw(Ogre::Degree(90));
	alaAspa2->setPosition(30,0,-50);
	alaAspa2->setScale(0.2,0.2,0.2);

}

AspasNave::AspasNave(Ogre::SceneNode* padre, int n):EntidadIG(padre) {

	float angle = 90.0f;

	Ogre::SceneNode *cilindroNode = padre->createChildSceneNode();
//	cilindroNode->setInheritScale(false);
	Ogre::Entity* cilindro = padre->getCreator()->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/morroAspa");

	cilindroNode->attachObject(cilindro);
	
	cilindroNode->setScale(7, 7,7);
	cilindroNode->roll(Ogre::Degree(90));
	Ogre::SceneNode* aspapadre= padre->createChildSceneNode();
	/*aspapadre->setInheritScale(false);*/
	aspapadre->pitch(Ogre::Degree(90));
	for (int i = 0; i < n; i++) {

		Ogre::SceneNode* aspaNode = aspapadre->createChildSceneNode();

		Aspa * aspaAvion = new Aspa(aspaNode, i);
		aspaNode->pitch(Ogre::Degree(angle));
		angle += 360.0f / n;
	}
	

}

Aspa::Aspa(Ogre::SceneNode *Aspa, int i):EntidadIG(Aspa) {

	Ogre::SceneNode *tableNode = Aspa->createChildSceneNode();
	Ogre::Entity* tablero = Aspa->getCreator()->createEntity("cube.mesh");
	tablero->setMaterialName("Practica1/tablon");
	tableNode->attachObject(tablero);
	tableNode->setScale(0.05,0.5, 4);
	tableNode->setPosition(0, 0, 0);

	Ogre::SceneNode *Cilindro = Aspa->createChildSceneNode();
	Ogre::Entity* cilindro = Aspa->getCreator()->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/ombligo");
	Cilindro->attachObject(cilindro);
	Cilindro->setScale(3, 10,3);
	Cilindro->setInheritOrientation(false);
	Cilindro->setPosition(5, 0, -280);
	tableNode->translate(0, 0, -130);

}

Dron::Dron(Ogre::SceneNode* padre, int n):EntidadIG(padre)
{
	Ogre::SceneNode* esferaCentral = padre->createChildSceneNode();
	Ogre::Entity* esfera = padre->getCreator()->createEntity("sphere.mesh");
	esfera->setMaterialName("Practica1/esferaAvion");
	esferaCentral->attachObject(esfera);

	Ogre::SceneNode* aspapadre = padre->createChildSceneNode();
	
	float angle = 90.0f;
	for (int i = 0; i < n; i++) {

		Ogre::SceneNode* brazo = aspapadre->createChildSceneNode();

		BrazoDron* brazito = new BrazoDron(brazo);
		brazo->pitch(Ogre::Degree(angle));
	
		angle += 360.0f / n;
	}
	//BrazoDron* brazo = new BrazoDron(padre);
}

BrazoDron::BrazoDron(Ogre::SceneNode* padre):EntidadIG(padre)
{
	Ogre::SceneNode* cilindreNode = padre->createChildSceneNode();
	Ogre::Entity* cilin = padre->getCreator()->createEntity("Barrel.mesh");
	cilin->setMaterialName("Practica1/brazo");
	cilindreNode->attachObject(cilin);
	cilindreNode->setScale(5, 40, 5);
	cilindreNode->yaw(Ogre::Degree(90));
	cilindreNode->translate(0, -100, 0);

	Ogre::SceneNode* esferaCentral = padre->createChildSceneNode();
	Ogre::Entity* esfera = padre->getCreator()->createEntity("sphere.mesh");
	esferaCentral->setInheritScale(false);
	esfera->setMaterialName("Practica1/naranja");
	esferaCentral->attachObject(esfera);
	esferaCentral->setScale(0.5, 0.5, 0.5);
	esferaCentral->setPosition(0, -200, 0);
	Ogre::SceneNode* AspaNode = esferaCentral->createChildSceneNode();
	//AspaNode->setInheritScale(false);
	//AspaNode->setInheritOrientation(false);
	AspasNave* aspa = new AspasNave(AspaNode, 3);
	AspaNode->translate(100, 0, 0);
	AspaNode->setScale(0.4, 0.4, 0.4);
}
