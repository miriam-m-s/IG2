#include "EntidadIG.h"
#include "IG2App.h"
#include <random>

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
	plano = node->getCreator()->createEntity("cube.mesh");
	plano->setMaterialName("Practica1/plano");
	node->attachObject(plano);
	cambiaText = false;
	myTymer = new Ogre::Timer();
}

void Plano::SetMaterial(std::string name) {
	plano->setMaterialName(name);
}

void Plano::receiveEvent(MessageType msgType, EntidadIG* entidad) {

	switch (msgType)
	{
	case NADA:
		break;
	case CAMBIATEXTURE:
		cambiaText = true;
		initTime = myTymer->getMilliseconds();
		break;
	case DETIENE:
		break;
	default:
		break;
	}

}

void Plano::frameRendered(const Ogre::FrameEvent& evt) {

	if (cambiaText) {
		if (myTymer->getMilliseconds() >= initTime+5000) {
			plano->setMaterialName("Practica1/piedras");
			cambiaText = false;
		}
	}

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

Avion::Avion(Ogre::SceneNode* padre, Ogre::SceneNode* nodoMovimiento, int n):EntidadIG(padre), movimiento(nodoMovimiento), estaMoviendo(false)
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

	Ogre::SceneNode *alaAspa1 = padre->createChildSceneNode();
	Aspa1 = new AspasNave(alaAspa1, 5);
	alaAspa1->yaw(Ogre::Degree(90));
	alaAspa1->setPosition(-200,0,-100);
	alaAspa1->setScale(0.2, 0.2, 0.2);

	Ogre::SceneNode* alaAspa2 = padre->createChildSceneNode();
	Aspa2 = new AspasNave(alaAspa2, 5);
	alaAspa2->yaw(Ogre::Degree(90));
	alaAspa2->setPosition(200,0,-100);
	alaAspa2->setScale(0.2,0.2,0.2);

}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_h)
	{
		movimiento->pitch(Ogre::Degree(-4));
		estaMoviendo = true;
	}
	else if (evt.keysym.sym == SDLK_j)
	{
		movimiento->yaw(Ogre::Degree(-2));
	}

	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	if (estaMoviendo) {
		Aspa1->frameRendered(evt);
		Aspa2->frameRendered(evt);
	}

	estaMoviendo = false;
}

AspasNave::AspasNave(Ogre::SceneNode* padre, int n):EntidadIG(padre) {

	float angle = 90.0f;

	Ogre::SceneNode *cilindroNode = padre->createChildSceneNode();
	Ogre::Entity* cilindro = padre->getCreator()->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/morroAspa");
	cilindroNode->attachObject(cilindro);
	cilindroNode->setScale(7, 7,7);
	cilindroNode->roll(Ogre::Degree(90));

	aspaPadre = padre->createChildSceneNode();

	for (int i = 0; i < n; i++) {

		Ogre::SceneNode* aspaNode = aspaPadre->createChildSceneNode();

		Aspa * aspaAvion = new Aspa(aspaNode, i);
		aspaNode->pitch(Ogre::Degree(angle));
		angle += 360.0f / n;
	}
	

 }

void AspasNave::frameRendered(const Ogre::FrameEvent& evt)
{
	Ogre::Real time = evt.timeSinceLastEvent;
	aspaPadre->pitch(Ogre::Radian(time*2000));
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

Dron::Dron(Ogre::SceneNode* padre, int n, bool avispa,Ogre::SceneNode* move):EntidadIG(padre), movimiento(move)
{
	myTymer = new Ogre::Timer();
	initTime = myTymer->getMilliseconds();
	Ogre::SceneNode* esferaCentral = padre->createChildSceneNode();
	Cabeza = padre->getCreator()->createEntity("sphere.mesh");

	if(!avispa)Cabeza->setMaterialName("Practica1/esferaAvion");
	else Cabeza->setMaterialName("Practica1/cabeza");

	esferaCentral->attachObject(Cabeza);

	Ogre::SceneNode *aspaPadre = padre->createChildSceneNode();
	
	float angle = 90.0f;
	for (int i = 0; i < n; i++) {

		Ogre::SceneNode* brazo = aspaPadre->createChildSceneNode();

		BrazoDron* brazito = new BrazoDron(brazo);
		brazo->pitch(Ogre::Degree(angle));
		if (i == 0) brazo->setScale(1.5,1.5,1.5);
		brazos.push_back(brazito);
	
		angle += 360.0f / n;
	}
}

void Dron::frameRendered(const Ogre::FrameEvent& evt)
{
	
	for (int i = 0; i < brazos.size(); i++) {
		brazos[i]->frameRendered(evt);
	}

	unsigned long s = myTymer->getMilliseconds();
	if ( s>= initTime + 2000&&s<initTime+4000) {
		
		movimiento->yaw(Ogre::Degree(sentido*1));
		actualiza = true;
	}
	else
	{
		if (actualiza) {
			initTime = s;
			actualiza = false;
			std::random_device rd;
			std::default_random_engine eng(rd());
			std::uniform_int_distribution<int> distr(-1, 1);
			 sentido = distr(eng);
			if (sentido == 0) {
				sentido = -1;
			}
		}
		movimiento->pitch(Ogre::Degree(-0.5f));
	}
	

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
	esfera->setMaterialName("Practica1/naranja");
	esferaCentral->attachObject(esfera);
	esferaCentral->setScale(0.5, 0.5, 0.5);
	esferaCentral->setPosition(0, -200, 0);

	Ogre::SceneNode* AspaNode = esferaCentral->createChildSceneNode();
	aspa = new AspasNave(AspaNode, 3);
	AspaNode->translate(100, 0, 0);
	AspaNode->setScale(0.4, 0.4, 0.4);
}

void BrazoDron::frameRendered(const Ogre::FrameEvent& evt) 
{
	aspa->frameRendered(evt);
}

Sinbad::Sinbad(Ogre::SceneNode* padre, bool mano, int scene_) :EntidadIG(padre)
{
	myTymer = new Ogre::Timer();
	ent = mSM->createEntity("Sinbad.mesh");
	mSinbadNodemov = padre->createChildSceneNode();
	mSinbadNode = mSinbadNodemov->createChildSceneNode();
	mSinbadNode->attachObject(ent);

	scene = scene_;

	if (scene == 3) {
		mSinbadNode->setPosition(0, 120, 0);
		mSinbadNode->yaw(Ogre::Degree(180));
		mSinbadNode->setScale(5, 5, 5);
	}

	else if (scene == 4) {
		mSinbadNode->setScale(20, 20, 20);
		mSinbadNode->setPosition(1000, mSinbadNode->getScale().y / 2 * 12, 1000);
		mSinbadNode->yaw(Ogre::Degree(90));
	}

	animaciones();
	



    Ogre::AnimationStateSet* aux = ent->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end())
	{
		auto s = it->first; ++it;
		std::cout << s << std::endl;
	}

	initTime = myTymer->getMilliseconds();
	corriendo = true;
	izq = mano;
	cambiaEspada();

	int duration = 16;
	Ogre::Animation* animation = mSM->createAnimation("animSS", duration);

	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mSinbadNodemov);

	Ogre::Real durPaso = duration / 4.0;
	Ogre::Vector3 sinbadInitPose = mSinbadNodemov->getPosition();
	Ogre::Vector3 src(0, 0, 1);

	//1 keyframe rotar a simbad
	Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setScale(mSinbadNodemov->getScale());
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, -1)));

	//2 keyframe mover a sinbad 
	kf = track->createNodeKeyFrame(durPaso * 1);
	kf->setScale(mSinbadNodemov->getScale());
	kf->setTranslate(Ogre::Vector3(0, 0, 200));

	//3 keyframe girar a sinbad
	kf = track->createNodeKeyFrame(durPaso * 2);
	kf->setScale(mSinbadNodemov->getScale());
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 1)));

	//4 keyframe mover a sinbad 
	kf = track->createNodeKeyFrame(durPaso * 3);
	kf->setScale(mSinbadNodemov->getScale());
	kf->setTranslate(Ogre::Vector3(0, 0, 200));

	//5 keyframe rotar a simbad
	kf = track->createNodeKeyFrame(durPaso * 4);
	kf->setScale(mSinbadNodemov->getScale());
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, -1)));

	anim_Sinbadmove = mSM->createAnimationState("animSS");
	anim_Sinbadmove->setLoop(true);
	anim_Sinbadmove->setEnabled(true);
}

void Sinbad::animaciones()
{
	anim_Sinbadtop = ent->getAnimationState("RunTop");
	anim_Sinbadtop->setLoop(true);
	anim_Sinbadtop->setEnabled(true);

	anim_Sinbaddown = ent->getAnimationState("RunBase");
	anim_Sinbaddown->setLoop(true);
	anim_Sinbaddown->setEnabled(true);

	anim_Sinbaddance = ent->getAnimationState("Dance");
	anim_Sinbaddance->setLoop(true);
	anim_Sinbaddance->setEnabled(false);
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if (scene == 3) {
		if (corriendo) {
			anim_Sinbadtop->addTime(evt.timeSinceLastFrame);
			anim_Sinbaddown->addTime(evt.timeSinceLastFrame);
			mSinbadNodemov->pitch(Ogre::Degree(-100 * evt.timeSinceLastFrame));

			unsigned long s = myTymer->getMilliseconds();
			if (s >= initTime + 2000) {

				mSinbadNodemov->yaw(Ogre::Degree(sentido * 30));
				initTime = s;

			}
			else
			{
				std::random_device rd;
				std::default_random_engine eng(rd());
				std::uniform_int_distribution<int> distr(-1, 1);
				sentido = distr(eng);
				if (sentido == 0) {
					sentido = -1;
				}
				mSinbadNodemov->pitch(Ogre::Degree(-0.2f));
			}
		}

		else {
			anim_Sinbaddance->addTime(evt.timeSinceLastFrame);
		}
	}

	else if (scene == 4) {
		/*anim_Sinbadtop->addTime(evt.timeSinceLastFrame);
		anim_Sinbaddown->addTime(evt.timeSinceLastFrame);
		anim_Sinbadmove->addTime(evt.timeSinceLastFrame);*/

	}
}

bool  Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt) {
	
	if (evt.keysym.sym == SDLK_c)
	{
		corriendo = !corriendo;

		anim_Sinbaddown->setEnabled(!anim_Sinbaddown->getEnabled());
		anim_Sinbadtop->setEnabled(!anim_Sinbadtop->getEnabled());
		anim_Sinbaddance->setEnabled(!anim_Sinbaddance->getEnabled());

	}

	return true;
}

void Sinbad::arma(bool izq) {

	Ogre::MovableObject* sword = mSM->createEntity("Sword.mesh");
	ent->detachObjectFromBone(sword);

	if (!izq) {
		ent->attachObjectToBone("Hand.R", sword);
	}

	else	ent->attachObjectToBone("Hand.L", sword);

}

void Sinbad::arma() {

	Ogre::MovableObject *swordL = mSM->createEntity("Sword.mesh");
	Ogre::MovableObject *swordR = mSM->createEntity("Sword.mesh");

	ent->attachObjectToBone("Hand.R", swordR);
	ent->attachObjectToBone("Hand.L", swordL);

}

void Sinbad::cambiaEspada() {
	arma(izq);
}

Bomba::Bomba(Ogre::SceneNode* padre) :EntidadIG(padre)
{
	Ogre::SceneNode* node = padre->createChildSceneNode();
	Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/bomba");
	node->attachObject(ent);
	node->setScale(35, 35, 35);
	node->setPosition(0, 100, 0);

	int duration = 16;
	Ogre::Animation* animation = mSM->createAnimation("AnimVV", duration);

	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(node);
	Ogre::Real durPaso = duration / 4.0;
	Ogre::Vector3 keyframePos = node->getPosition();
	Ogre::Vector3 src(0, 0, 1);

	//ORIGEN
	Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyframePos);
	kf->setScale(node->getScale());
	//ARRIBA
    kf=track->createNodeKeyFrame(durPaso*1);
	kf->setTranslate(keyframePos +Ogre::Vector3(0,200,0));
	kf->setScale(node->getScale());
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 1)));
	//ORIGEN
	kf = track->createNodeKeyFrame(durPaso * 2);
	kf->setTranslate(keyframePos);
	kf->setScale(node->getScale());
	//ABAJO
	kf = track->createNodeKeyFrame(durPaso *3);
	kf->setTranslate(keyframePos + Ogre::Vector3(0, -300, 0));
	kf->setScale(node->getScale());
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1)));
	//ORIGEN
	kf = track->createNodeKeyFrame(durPaso *4);
	kf->setTranslate(keyframePos);
	kf->setScale(node->getScale());

	animationState = mSM->createAnimationState("AnimVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
	
	parada = false;
}

void Bomba::frameRendered(const Ogre::FrameEvent& evt) {
	if(!parada) animationState->addTime(evt.timeSinceLastFrame);
}

Bomba::~Bomba()
{
}

void Bomba::receiveEvent(MessageType msgType, EntidadIG* entidad) {
	
	switch (msgType)
	{
	case NADA:
		break;
	case CAMBIATEXTURE:
		break;
	case DETIENE:
		parada = true;
		break;
	default:
		break;
	}

}
