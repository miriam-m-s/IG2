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
	else if (evt.keysym.sym == SDLK_g) {
		/* auto mClockNode = mSM->getRootSceneNode()->getChild("Clock");

		 mClockNode->roll(Ogre::Degree(-8));*/
	}
	else if (evt.keysym.sym == SDLK_y) {
		/* auto nHours = mSM->getRootSceneNode()->getChild("Clock")->getChild("Hours");

		 nHours->yaw(Ogre::Degree(-8));*/
	}
	else if (evt.keysym.sym == SDLK_q) {
		noria->giraNoria();
	}

	else if (evt.keysym.sym == SDLK_p) {
		PN->yaw(Ogre::Degree(1.0));
	}

	else if (evt.keysym.sym == SDLK_r) {
		plano->sendEvent(NADA ,noria);
	}

	return true;
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
	
	for (auto it = avispero.begin(); it != avispero.end();) {
		Ogre::SceneNode* avispa = *it;
		if (AvionCompleto->_getWorldAABB().intersects(avispa->_getWorldAABB())) {
			//avispa->setVisible(false);
			avispa->getParent()->removeChild(*it);;
			it=avispero.erase(it);
			dronesVivos->setCaption(std::to_string(avispero.size()));
		}
		else {
			++it;
		}
	}

	if (avispero.size() == 0) {
		drone->changeColor();
	}
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

	dronesVivos = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "DronesVivos", std::to_string(avispero.size()), 50, 50);
	
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
	luz->setDiffuseColour(0.9, 0.9, 0.9);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(-0.5, -1, 1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	// finally something to render

	//Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

	//mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	//mSinbadNode->attachObject(ent);

	////mSinbadNode->setPosition(400, 100, -300);
	//mSinbadNode->setScale(20, 20, 20);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	//mSinbadNode->setVisible(false);

	//Ogre::SceneNode* mClockNode = mSM->getRootSceneNode()->createChildSceneNode("Clock");
	//mClockNode->setPosition(0,0,0);
	//Ogre::SceneNode* mHoursNode = mClockNode->createChildSceneNode("Hours");

	//double angle = 90;
	//double radius = 200;

	//for (int i = 0; i < 12; i++) {

	   // Ogre::Entity* hora = mSM->createEntity("uv_sphere.mesh");

	   // Ogre::SceneNode* Hora = mHoursNode->createChildSceneNode("Hora"+std::to_string(i+1));
	   // Hora->attachObject(hora);

	   // Hora->setScale(0.2, 0.2, 0.2);
	   // Hora->setPosition(Ogre::Math::Cos(Ogre::Math::DegreesToRadians(angle)) *radius, 
		  //  Ogre::Math::Sin(Ogre::Math::DegreesToRadians(angle))*radius , 0);

	   // angle += 360 / 12;
	//}

	//EJ 2
   /*  for (int i = 0; i < 12; i+=2) {
		auto s=mHoursNode->getChild("Hora" + std::to_string(i + 1));
		s->setScale(0.1, 0.1, 0.1);
	}*/

	//Ogre::Entity* agujaM = mSM->createEntity("cube.mesh");
	//Ogre::SceneNode* AgujaM = mClockNode->createChildSceneNode();
	//AgujaM->attachObject(agujaM);
	//AgujaM->setScale(0.2, 1.75, 0.1);
	//AgujaM->setPosition(mClockNode->getPosition().x, mClockNode->getPosition().y + radius / 4 , 0);

	//Ogre::Entity* agujaH = mSM->createEntity("cube.mesh");
	//Ogre::SceneNode* AgujaH = mClockNode->createChildSceneNode();
	//AgujaH->attachObject(agujaH);
	//AgujaH->setScale(0.1, 1.5, 0.1);
	//AgujaH->setPosition(mClockNode->getPosition().x + radius/4, mClockNode->getPosition().y, 0);
	//AgujaH->roll(Ogre::Degree(90));

	//Ogre::Entity* agujaS = mSM->createEntity("cube.mesh");
	//Ogre::SceneNode* AgujaS = mClockNode->createChildSceneNode();
	//AgujaS->attachObject(agujaS);
	//AgujaS->setScale(0.1/2, 1.5, 0.1);
	//AgujaS->roll(Ogre::Degree(-60));
	//AgujaS->setPosition(mClockNode->getPosition().x-50, mClockNode->getPosition().y - radius / 4+20, 0);

	//mSinbadNode->setPosition(400, 100, -300);
	//mSinbadNode->setScale(20, 20, 20);

	//creacion de plano
	PN = mSM->getRootSceneNode()->createChildSceneNode();
	//plano = new Plano(PN);
	

	//creacion de noria
	//Ogre::SceneNode* NN = PN->createChildSceneNode();
	//noria = new Noria(20, PN);

	//creacion del muñeco
	//Ogre::SceneNode* MUNY = PN->createChildSceneNode();
	//olaf = new Munyeco(MUNY);
	//MUNY->setPosition(PN->getScale().x / 1.25, 800, -PN->getScale().z / 1.25);
	//MUNY->yaw(Ogre::Degree(-45));

	//addInputListener(noria);
	//addInputListener(olaf);

	//EntidadIG::addListener(plano);
	//EntidadIG::addListener(noria);
	//EntidadIG::addListener(olaf);

	PlanetaAvispa();

	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}

void IG2App::PlanetaAvispa()
{
	Ogre::SceneNode* centroPlaneta = mSM->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* planeta = mSM->createEntity("uv_sphere.mesh");
	planeta->setMaterialName("Practica1/cian");
	centroPlaneta->attachObject(planeta);
	centroPlaneta->setScale(4, 4, 4);

	Ogre::SceneNode* nodoMove = centroPlaneta->createChildSceneNode();
	nodoMove->setInheritScale(false);
    AvionCompleto = nodoMove->createChildSceneNode();
	
	Avion* avion = new Avion(AvionCompleto, nodoMove, 5);
	AvionCompleto->setScale(0.2, 0.2, 0.2);
	AvionCompleto->translate(0, 420, 0);

	EntidadIG::addListener(avion);
	addInputListener(avion);

	for (int i = 0; i < 100; i++) {

		double pitch = rand() % 360 + 1;
		double yaw = rand() % 360 + 1;

		Ogre::SceneNode* centro = centroPlaneta->createChildSceneNode();
		centro->setInheritScale(false);

		Ogre::SceneNode* Dronenode = centro->createChildSceneNode();
		Dronenode->setScale(0.2, 0.2, 0.2);
		Dronenode->translate(0, 400, 0);
		Dronenode->roll(Ogre::Degree(90));

		Ogre::SceneNode* Enjambre = centro->createChildSceneNode();
		Enjambre->roll(Ogre::Degree(90));
		Enjambre->translate(0, 400, 0);
		Enjambre->setScale(0.1, 0.1, 0.1);

		if (i == 0) {
			drone = new Dron(Dronenode, 3, false, centro);
			addInputListener(drone);
		}

		else {
			Ogre::SceneNode* AvispaDronenode = Enjambre->createChildSceneNode("Avispa" + std::to_string(i + 1));
			avispero.push_back(AvispaDronenode);
			Dron* droneAvispa = new Dron(AvispaDronenode, 3, true, centro);

			addInputListener(droneAvispa);
		}

		centro->yaw(Ogre::Degree(yaw));
		centro->pitch(Ogre::Degree(pitch));

	}


}


