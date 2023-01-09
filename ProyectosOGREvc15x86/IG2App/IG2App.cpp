#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <cstdlib>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}

	else if (evt.keysym.sym == SDLK_q) {
		noria->giraNoria();
	}

	else if (evt.keysym.sym == SDLK_p) {
		PN->yaw(Ogre::Degree(1.0));
	}

	else if (evt.keysym.sym == SDLK_t) {
		plano->sendEvent(DETIENE, plano);
		plano->sendEvent(CAMBIATEXTURE, plano);
	}

	else if (evt.keysym.sym == SDLK_r) {
		plano->sendEvent(NADA ,noria);
	}

	return true;
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{

}

void IG2App::shutdown()
{
	mShaderGenerator->removeSceneManager(mSM);
	mSM->removeRenderQueueListener(mOverlaySystem);

	mRoot->destroySceneManager(mSM);

	delete mTrayMgr;  mTrayMgr = nullptr;
	delete mCamMgr; mCamMgr = nullptr;

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
	// do not forget to call the base first
	IG2ApplicationContext::setup();

	mSM = mRoot->createSceneManager();

	// register our scene with the RTSS
	mShaderGenerator->addSceneManager(mSM);

	mSM->addRenderQueueListener(mOverlaySystem);

	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	
	dronesVivos = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "Drones", Ogre::DisplayString("Drones Vivos"), 300, 80);
	dronesVivos->setText(std::to_string(avispero.size()));
	dronesVivos->setTextAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);

	addInputListener(mTrayMgr);

	addInputListener(this);
	setupScene();
}

void IG2App::setupScene(void)
{
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1.0, 1.0, 1.0);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	// finally something to render
	Light* luzFoco = mSM->createLight("Luz Foco");
	luzFoco->setType(Ogre::Light::LT_SPOTLIGHT);
	luzFoco->
		setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	luzFoco->setDirection(Ogre::Vector3(1, -1, 0));
	luzFoco->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	luzFoco->setSpotlightOuterAngle(Ogre::Degree(45.0f));
	luzFoco->setSpotlightFalloff(0.0f);
	mLightNode->attachObject(luzFoco);
	EscenaBombaSinbad();

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}

void IG2App::EscenaBombaSinbad() {

	Ogre::SceneNode *mainScene =  mSM->getRootSceneNode()->createChildSceneNode();

	Ogre::SceneNode*PLN = mainScene->createChildSceneNode();
	plano = new Plano(PLN);
	PLN->setScale(Ogre::Vector3(30, 0.25, 30));

	Ogre::SceneNode *planoA = mainScene->createChildSceneNode();
	Plano* planoAmarillo = new Plano(planoA);
	planoA->setScale(Ogre::Vector3(10, 0.25, 10));
	planoA->setPosition(Ogre::Vector3(-1000, 10, -1000));
	planoAmarillo->SetMaterial("Practica1/Amarillo");

	Bomba* bomba = new Bomba(mainScene);
	
	Ogre::SceneNode * bomba2 = mainScene->createChildSceneNode();
	Ogre::Entity* ent = mSM->createEntity("uv_sphere.mesh");
	ent->setMaterialName("practica2GLSL/SpotL");
	bomba2->attachObject(ent);
	bomba2->setPosition(-500, 100, 0);
	
	Sinbad* sinbad = new Sinbad(mainScene, false, 4);
	//sinbad->arma();

	Ogre::SceneNode* NN = mainScene->createChildSceneNode();
	noria = new Noria(20, NN);
	NN->setPosition(-1500,0, -1000);

	Ogre::SceneNode* bombanode = mainScene->createChildSceneNode();
	
	Ogre::SceneNode *avionNode = bombanode->createChildSceneNode();
	Avion *avion = new Avion(avionNode, bombanode, 5,4);
	avionNode->setScale(0.5, 0.5, 0.5);
	avionNode->translate(400, 700, 0);

	Ogre::SceneNode* rota1 = avion->getAla(1)->createChildSceneNode();

	Ogre::SceneNode* bicopter = rota1->createChildSceneNode();
	bicopter->setInheritScale(false);
	Bicoptero* bico = new Bicoptero(bicopter,rota1,0);
	bicopter->setScale(0.3, 0.3, 0.3);
	bicopter->translate(-100, 2000, 0);
	bicopter->yaw(Ogre::Degree(90));

	Ogre::SceneNode* rota = avion->getAla(2)->createChildSceneNode();
	
	Ogre::SceneNode* bicopter1 = rota->createChildSceneNode();
	bicopter1->setInheritScale(false);
	Bicoptero* bico1 = new Bicoptero(bicopter1,rota,1);
	bicopter1->setScale(0.3, 0.3, 0.3);
	bicopter1->translate(100, -2000, 0);
	bicopter1->yaw(Ogre::Degree(90));
	mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -40), "practica2GLSL/space2"
		, 1, 1, true, 1.0, 100, 100);
	Ogre::SceneNode* node = mainScene->createChildSceneNode();
	Ogre::BillboardSet* bbSet = mSM->createBillboardSet(4);

	bbSet->setDefaultDimensions(200, 200);
	bbSet->setMaterialName("Practica1/antonio");
	node->attachObject(bbSet);
	for (int i = 0; i < 8; i++) {
		
	
		bbSet->createBillboard({ Ogre::Real(i*300)-1000,200,-1000 });
	}

	addInputListener(avion);
	addInputListener(bico);
	addInputListener(bico1);
	addInputListener(sinbad);
	addInputListener(plano);
	addInputListener(bomba);
	EntidadIG::addListener(avion);
	EntidadIG::addListener(bico);
	EntidadIG::addListener(bico1);
	EntidadIG::addListener(sinbad);
	EntidadIG::addListener(plano);
	EntidadIG::addListener(bomba);
}  


