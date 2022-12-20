#include "EntidadIG.h"
#include "IG2App.h"
#include <random>
#include <wtypes.h>

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
		if (myTymer->getMilliseconds() >= initTime + 5000) {
			plano->setMaterialName("Practica1/piedras");
			cambiaText = false;
		}
	}

}

AspaNoria::AspaNoria(Ogre::SceneNode* NoriaNode, float angle, int i) :EntidadIG(NoriaNode)
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

Noria::Noria(int n, Ogre::SceneNode* node) :EntidadIG(node), estagirando(true), n(n)
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

		AspaNoria* aspaNoria = new AspaNoria(Aspa, angle, i);
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
			node->pitch(Ogre::Radian(-time));
		}
	}
}

void Noria::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	estagirando = false;
}

Munyeco::Munyeco(Ogre::SceneNode* padre) : EntidadIG(padre), tortura(false)
{
	cuello = padre->createChildSceneNode();
	cuello->setInheritScale(false);

	cabeza = cuello->createChildSceneNode();
	Cabeza = padre->getCreator()->createEntity("sphere.mesh");
	cabeza->attachObject(Cabeza);
	Cabeza->setMaterialName("Practica1/naranja");

	cabeza->setPosition(0, 100 * cabeza->getScale().y, 0);

	Ogre::SceneNode* nariz = cabeza->createChildSceneNode();
	Ogre::Entity* Nariz = padre->getCreator()->createEntity("sphere.mesh");
	Nariz->setMaterialName("Practica1/nariz");
	nariz->attachObject(Nariz);
	nariz->setScale(0.1, 0.1, 0.1);
	nariz->setPosition(0, 0, 100 * cabeza->getScale().z);

	cuerpo = cuello->createChildSceneNode();
	Cuerpo = padre->getCreator()->createEntity("sphere.mesh");
	Cuerpo->setMaterialName("Practica1/naranja");
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


	int duration = 16;
	Ogre::Animation* animation = mSM->createAnimation("AnimMun", duration);

	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(cuello);
	Ogre::Real durPaso = duration / 4.0;
	Ogre::Vector3 initPose = cuello->getPosition();
	Ogre::Vector3 finalPose = cuello->getPosition()+Ogre::Vector3(-800,0,0);
	Ogre::Vector3 src(1, 0, 0);

	//keyframe1
	Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(initPose);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(270), Ogre::Vector3(0, 1, 0)));
	kf->setScale(cuello->getScale());

	//keyframe2
	kf = track->createNodeKeyFrame(durPaso * 1);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(270), Ogre::Vector3(0, 1, 0)));
	kf->setScale(cuello->getScale());
	kf->setTranslate(finalPose);

	//keyframe3
    kf = track->createNodeKeyFrame(durPaso * 2);
	kf->setTranslate(finalPose);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0, 1, 0)));
	kf->setScale(cuello->getScale());

	//keyframe4
	kf = track->createNodeKeyFrame(durPaso * 3);
	kf->setTranslate(initPose);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0, 1, 0)));
	kf->setScale(cuello->getScale());

	//keyframe5
    kf = track->createNodeKeyFrame(durPaso * 4);
	kf->setTranslate(initPose);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(270), Ogre::Vector3(0, 1, 0)));
	kf->setScale(cuello->getScale());
   

	Ogre::SceneNode* explosion = padre->createChildSceneNode();


	animationState = mSM->createAnimationState("AnimMun");
	animationState->setLoop(true);
	animationState->setEnabled(true);



}

bool Munyeco::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_UP)
	{
		cuello->translate(Ogre::Math::Sin(cuello->getOrientation().getYaw()) * 2, 0, Ogre::Math::Cos(cuello->getOrientation().getYaw()) * 2);
	}
	else if (evt.keysym.sym == SDLK_DOWN)
	{
		cuello->translate(-Ogre::Math::Sin(cuello->getOrientation().getYaw()) * 2, 0, -Ogre::Math::Cos(cuello->getOrientation().getYaw()) * 2);
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
	animationState->addTime(evt.timeSinceLastFrame);

}

Avion::Avion(Ogre::SceneNode* padre, Ogre::SceneNode* nodoMovimiento, int n, int scene) :EntidadIG(padre), movimiento(nodoMovimiento), estaMoviendo(false), scene_(scene)
{

	avionCompleto = padre->createChildSceneNode();

	esferaCentral = avionCompleto->createChildSceneNode();
	Ogre::Entity* esfera = padre->getCreator()->createEntity("sphere.mesh");
	esfera->setMaterialName("Practica1/esferaAvion");
	esferaCentral->attachObject(esfera);
	esferaCentral->setScale(1.5, 1.5, 1.5);

	Ogre::SceneNode* NinjaNode = avionCompleto->createChildSceneNode();
	Ogre::Entity* ninja = padre->getCreator()->createEntity("ninja.mesh");
	ninja->setMaterialName("Practica1/ninja");
	NinjaNode->attachObject(ninja);

	Ogre::SceneNode* Ala1 = avionCompleto->createChildSceneNode();
	Ogre::Entity* ala1 = padre->getCreator()->createEntity("cube.mesh");
	ala1->setMaterialName("Practica1/alasAvion");
	Ala1->attachObject(ala1);
	Ala1->setScale(3, 0.1, 2);
	Ala1->setPosition(-150, 0, 0);

	Ogre::SceneNode* Ala2 = avionCompleto->createChildSceneNode();
	Ogre::Entity* ala2 = padre->getCreator()->createEntity("cube.mesh");
	ala2->setMaterialName("Practica1/alasAvion");
	Ala2->attachObject(ala2);
	Ala2->setScale(3, 0.1, 2);
	Ala2->setPosition(150, 0, 0);

	Ogre::SceneNode* Morro = avionCompleto->createChildSceneNode();
	Ogre::Entity* morro = padre->getCreator()->createEntity("Barrel.mesh");
	morro->setMaterialName("Practica1/morroAvion");
	Morro->attachObject(morro);
	Morro->setScale(20, 25, 20);
	Morro->pitch(Ogre::Degree(90));
	Morro->setPosition(0, 0, -90);

	Ogre::SceneNode* alaAspa1 = avionCompleto->createChildSceneNode();
	Aspa1 = new AspasNave(alaAspa1, 5);
	alaAspa1->yaw(Ogre::Degree(90));
	alaAspa1->setPosition(-200, 0, -100);
	alaAspa1->setScale(0.2, 0.2, 0.2);

	Ogre::SceneNode* alaAspa2 = avionCompleto->createChildSceneNode();
	Aspa2 = new AspasNave(alaAspa2, 5);
	alaAspa2->yaw(Ogre::Degree(90));
	alaAspa2->setPosition(200, 0, -100);
	alaAspa2->setScale(0.2, 0.2, 0.2);

	if (scene_ == 4) {

		Ogre::SceneNode* cartel = avionCompleto->createChildSceneNode();
		Ogre::BillboardSet* bbSet = mSM->createBillboardSet("cartel", 1);
		bbSet->setDefaultDimensions(200, 200);
		bbSet->setMaterialName("Practica1/points");
		cartel->attachObject(bbSet);

		bbSet->createBillboard({ 0,0,200 });

		Ogre::ParticleSystem* pSys = mSM->createParticleSystem("psSmoke", "particles/Smoke");
		pSys->setEmitting(true);
		cartel->attachObject(pSys);

		pSysExp = mSM->createParticleSystem("psSysExpA", "particles/ExplosionAv");
		padre->attachObject(pSysExp);
		pSysExp->setEmitting(false);

		estaMoviendo = true;
	}
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (scene_ == 2) {
		if (evt.keysym.sym == SDLK_h)
		{
			movimiento->pitch(Ogre::Degree(-4));
			estaMoviendo = true;
		}
		else if (evt.keysym.sym == SDLK_j)
		{
			movimiento->yaw(Ogre::Degree(-2));
		}
	}

	else if (scene_ = 4) {
		if (evt.keysym.sym == SDLK_r)
		{
			pSysExp->setEmitting(true);
			avionCompleto->setVisible(false);
			this->sendEvent(MUERTE, this);
			estaMoviendo = false;
		}
	}

	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	if (scene_ == 2) {
		if (estaMoviendo) {
			Aspa1->frameRendered(evt);
			Aspa2->frameRendered(evt);
		}

		estaMoviendo = false;
	}

	else if (scene_ == 4) {
		if (estaMoviendo){
			Aspa1->frameRendered(evt);
			Aspa2->frameRendered(evt);
			movimiento->yaw(Ogre::Degree(1));
		}
	}

}

AspasNave::AspasNave(Ogre::SceneNode* padre, int n) :EntidadIG(padre) {

	float angle = 90.0f;

	Ogre::SceneNode* cilindroNode = padre->createChildSceneNode();
	Ogre::Entity* cilindro = padre->getCreator()->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/morroAspa");
	cilindroNode->attachObject(cilindro);
	cilindroNode->setScale(7, 7, 7);
	cilindroNode->roll(Ogre::Degree(90));

	aspaPadre = padre->createChildSceneNode();

	for (int i = 0; i < n; i++) {

		Ogre::SceneNode* aspaNode = aspaPadre->createChildSceneNode();

		Aspa* aspaAvion = new Aspa(aspaNode, i);
		aspaNode->pitch(Ogre::Degree(angle));
		angle += 360.0f / n;
	}


}

void AspasNave::frameRendered(const Ogre::FrameEvent& evt)
{
	Ogre::Real time = evt.timeSinceLastEvent;
	aspaPadre->pitch(Ogre::Radian(time * 1000));
}

Aspa::Aspa(Ogre::SceneNode* Aspa, int i) :EntidadIG(Aspa) {

	Ogre::SceneNode* tableNode = Aspa->createChildSceneNode();
	Ogre::Entity* tablero = Aspa->getCreator()->createEntity("cube.mesh");
	tablero->setMaterialName("Practica1/tablon");
	tableNode->attachObject(tablero);
	tableNode->setScale(0.05, 0.5, 4);
	tableNode->setPosition(0, 0, 0);

	Ogre::SceneNode* Cilindro = Aspa->createChildSceneNode();
	Ogre::Entity* cilindro = Aspa->getCreator()->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/ombligo");
	Cilindro->attachObject(cilindro);
	Cilindro->setScale(3, 10, 3);
	Cilindro->setInheritOrientation(false);
	Cilindro->setPosition(5, 0, -280);

	tableNode->translate(0, 0, -130);

}

Dron::Dron(Ogre::SceneNode* padre, int n, bool avispa, Ogre::SceneNode* move) :EntidadIG(padre), movimiento(move)
{
	myTymer = new Ogre::Timer();
	initTime = myTymer->getMilliseconds();
	Ogre::SceneNode* esferaCentral = padre->createChildSceneNode();
	Cabeza = padre->getCreator()->createEntity("sphere.mesh");

	if (!avispa)Cabeza->setMaterialName("Practica1/esferaAvion");
	else Cabeza->setMaterialName("Practica1/cabeza");

	esferaCentral->attachObject(Cabeza);

	Ogre::SceneNode* aspaPadre = padre->createChildSceneNode();

	float angle = 90.0f;
	for (int i = 0; i < n; i++) {

		Ogre::SceneNode* brazo = aspaPadre->createChildSceneNode();

		BrazoDron* brazito = new BrazoDron(brazo);
		brazo->pitch(Ogre::Degree(angle));
		if (i == 0) brazo->setScale(1.5, 1.5, 1.5);
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
	if (s >= initTime + 2000 && s < initTime + 4000) {

		movimiento->yaw(Ogre::Degree(sentido * 1));
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

BrazoDron::BrazoDron(Ogre::SceneNode* padre) :EntidadIG(padre)
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

	sinbad = mSM->createEntity("Sinbad.mesh");
	mSinbadNodemov = padre->createChildSceneNode();
	mSinbadNode = mSinbadNodemov->createChildSceneNode();
	mSinbadNode->attachObject(sinbad);

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

		int duration = 16;
		Ogre::Animation* animation = mSM->createAnimation("animSSs", duration);

		Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
		track->setAssociatedNode(mSinbadNode);

		Ogre::Real durPaso = duration / 5.0;
		Ogre::Vector3 sinbadInitPose = mSinbadNode->getPosition();
		Ogre::Vector3 sinbadDestination = { -1200/3, mSinbadNode->getScale().y / 2 * 12, -900/3 };
		Ogre::Vector3 src(0, 0, 1);

		//1 keyframe rotar a simbad
		Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(durPaso * 0);
		kf->setScale(mSinbadNode->getScale());
		kf->setRotation(Ogre::Quaternion(Ogre::Degree(-135.0), Ogre::Vector3(0, 1, 0)));
		kf->setTranslate(sinbadInitPose);

		//2 keyframe mover a simbad al medio
		kf = track->createNodeKeyFrame(durPaso * 1);
		kf->setScale(mSinbadNode->getScale());
		kf->setRotation(Ogre::Quaternion(Ogre::Degree(-135.0), Ogre::Vector3(0, 1, 0)));
		kf->setTranslate(sinbadDestination);

		//3 keyframe mover a simbad al destino
		kf = track->createNodeKeyFrame(durPaso * 2);
		kf->setScale(mSinbadNode->getScale());
		kf->setRotation(Ogre::Quaternion(Ogre::Degree(-135.0), Ogre::Vector3(0, 1, 0)));
		kf->setTranslate(sinbadDestination * Ogre::Vector3(3,1,3));

		//4 keyframe rotar a simbad
		kf = track->createNodeKeyFrame(durPaso * 3);
		kf->setScale(mSinbadNode->getScale());
		kf->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3(0, 1, 0)));
		kf->setTranslate(sinbadDestination * Ogre::Vector3(3, 1, 3));

		//4 keyframe mover  a simbad a la posicion origen
		kf = track->createNodeKeyFrame(durPaso * 4);
		kf->setScale(mSinbadNode->getScale());
		kf->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3(0, 1, 0)));
		kf->setTranslate(sinbadInitPose);

		//5 keyframe rotar a simbad
		kf = track->createNodeKeyFrame(durPaso * 5);
		kf->setScale(mSinbadNode->getScale());
		kf->setRotation(Ogre::Quaternion(Ogre::Degree(-135.0), Ogre::Vector3(0, 1, 0)));
		kf->setTranslate(sinbadInitPose);

		anim_Sinbadmove = mSM->createAnimationState("animSSs");
		anim_Sinbadmove->setLoop(true);
		anim_Sinbadmove->setEnabled(true);

	}

	animaciones();

	Ogre::AnimationStateSet* aux = sinbad->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end())
	{
		auto s = it->first; ++it;
		std::cout << s << std::endl;
	}

	initTime = myTymer->getMilliseconds();
	corriendo = true;
	vivo = true;
	izq = mano;
	cambiaEspada();

}

void Sinbad::animaciones()
{
	anim_Sinbadtop = sinbad->getAnimationState("RunTop");
	anim_Sinbadtop->setLoop(true);
	anim_Sinbadtop->setEnabled(true);

	anim_Sinbaddown = sinbad->getAnimationState("RunBase");
	anim_Sinbaddown->setLoop(true);
	anim_Sinbaddown->setEnabled(true);

	anim_Sinbaddance = sinbad->getAnimationState("Dance");
	anim_Sinbaddance->setLoop(true);
	anim_Sinbaddance->setEnabled(false);

	anim_SinbaddeadTop = sinbad->getAnimationState("IdleTop");
	anim_SinbaddeadTop->setLoop(true);
	anim_SinbaddeadTop->setEnabled(true);

	anim_SinbaddeadIdle = sinbad->getAnimationState("IdleBase");
	anim_SinbaddeadIdle->setLoop(true);
	anim_SinbaddeadIdle->setEnabled(true);
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

		if (vivo) {
			anim_Sinbadtop->addTime(evt.timeSinceLastFrame);
			anim_Sinbaddown->addTime(evt.timeSinceLastFrame);
			anim_Sinbadmove->addTime(evt.timeSinceLastFrame);
		}

		else {
			anim_SinbaddeadTop->addTime(evt.timeSinceLastFrame);
			anim_SinbaddeadIdle->addTime(evt.timeSinceLastFrame);

			if (myTymer->getMilliseconds() >= initTime + 5000) {
				ent->sendEvent(EXPLOSION, ent);
			}
		}

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
	sinbad->detachObjectFromBone(sword);

	if (!izq) {
		sinbad->attachObjectToBone("Hand.R", sword);
	}

	else	sinbad->attachObjectToBone("Hand.L", sword);

}

void Sinbad::arma() {

	Ogre::MovableObject* swordL = mSM->createEntity("Sword.mesh");
	Ogre::MovableObject* swordR = mSM->createEntity("Sword.mesh");

	sinbad->attachObjectToBone("Hand.R", swordR);
	sinbad->attachObjectToBone("Hand.L", swordL);

}

void Sinbad::receiveEvent(MessageType msgType, EntidadIG* entidad) {

	switch (msgType)
	{
	case NADA:
		break;
	case CAMBIATEXTURE:
		break;
	case DETIENE:
		break;
	case MUERTE:
		if (vivo) {
			vivo = false;
			initTime = myTymer->getMilliseconds();
			if(anim_Sinbadmove != nullptr) anim_Sinbadmove->setEnabled(false);
			mSinbadNode->pitch(Ogre::Degree(-90));
			mSinbadNode->translate(0, -mSinbadNode->getScale().y / 2 * 10,0);
			ent = entidad;
		}
		break;
	default:
		break;
	}

}

void Sinbad::cambiaEspada() {
	arma(izq);
}

Bomba::Bomba(Ogre::SceneNode* padre) :EntidadIG(padre)
{
	bomba = padre->createChildSceneNode();
	Ogre::Entity* ent = mSM->createEntity("uv_sphere.mesh");

	ent->setMaterialName("practica2GLSL/HolesLighting");
	bomba->attachObject(ent);
	bomba->setScale(1, 1, 1);
	bomba->setPosition(0, 100, 0);

	int duration = 16;
	Ogre::Animation* animation = mSM->createAnimation("AnimVV", duration);

	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(bomba);
	Ogre::Real durPaso = duration / 4.0;
	Ogre::Vector3 keyframePos = bomba->getPosition();
	Ogre::Vector3 src(0, 0, 1);

	//ORIGEN
	Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyframePos);
	kf->setScale(bomba->getScale());
	//ARRIBA
	kf = track->createNodeKeyFrame(durPaso * 1);
	kf->setTranslate(keyframePos + Ogre::Vector3(0, 200, 0));
	kf->setScale(bomba->getScale());
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 1)));
	//ORIGEN
	kf = track->createNodeKeyFrame(durPaso * 2);
	kf->setTranslate(keyframePos);
	kf->setScale(bomba->getScale());
	//ABAJO
	kf = track->createNodeKeyFrame(durPaso * 3);
	kf->setTranslate(keyframePos + Ogre::Vector3(0, -300, 0));
	kf->setScale(bomba->getScale());
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1)));
	//ORIGEN
	kf = track->createNodeKeyFrame(durPaso * 4);
	kf->setTranslate(keyframePos);
	kf->setScale(bomba->getScale());

	Ogre::SceneNode* explosion = padre->createChildSceneNode();

	pSysExp = mSM->createParticleSystem("psSysExpB", "particles/ExplosionB");
	pSysExp->setEmitting(false);
	explosion->attachObject(pSysExp);
	explosion->translate(0, 20, 0);

	animationState = mSM->createAnimationState("AnimVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);

	parada = false;
}

void Bomba::frameRendered(const Ogre::FrameEvent& evt) {
	if (!parada) animationState->addTime(evt.timeSinceLastFrame);
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
	case EXPLOSION:
		pSysExp->setEmitting(true);
		bomba->setVisible(false);
		parada = true;
		break;
	default:
		break;
	}

}

Bicoptero::Bicoptero(Ogre::SceneNode* padre):EntidadIG(padre)
{

	BicopterCompleto = padre->createChildSceneNode();

	esferaCentral = BicopterCompleto->createChildSceneNode();
	Ogre::Entity* esfera = padre->getCreator()->createEntity("sphere.mesh");
	esfera->setMaterialName("Practica1/esferaAvion");
	esferaCentral->attachObject(esfera);
	esferaCentral->setScale(1.5, 1.5, 1.5);

	Ogre::SceneNode* Morro = BicopterCompleto->createChildSceneNode();
	Ogre::Entity* morro = padre->getCreator()->createEntity("Barrel.mesh");
	morro->setMaterialName("Practica1/alasAvion");
	Morro->attachObject(morro);
	Morro->setScale(20, 25, 20);
	Morro->pitch(Ogre::Degree(90));
	Morro->setPosition(0, 0, 90);

	Ogre::SceneNode* alaAspa1 = BicopterCompleto->createChildSceneNode();
	Aspa1 = new AspasNave(alaAspa1, 3);
	alaAspa1->setPosition(-150, 0, 0);
	alaAspa1->setScale(0.5, 0.5, 0.5);

	Ogre::SceneNode* alaAspa2 = BicopterCompleto->createChildSceneNode();
	Aspa2 = new AspasNave(alaAspa2, 3);
	alaAspa2->setPosition(150, 0, 0);
	alaAspa2->setScale(0.5, 0.5, 0.5);

}

void Bicoptero::frameRendered(const Ogre::FrameEvent& evt)
{
	Aspa1->frameRendered(evt);
	Aspa2->frameRendered(evt);
}
