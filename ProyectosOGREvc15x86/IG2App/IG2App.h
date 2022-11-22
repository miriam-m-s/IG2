#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include<OgreBillboardSet.h>
#include<OgreParticleSystem.h>
#include <vector>
#include "EntidadIG.h"


class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { delete noria; };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  void EscenaBombaSinbad();
  void EscenaPlanetaSinbad();
  void NoriaMunyeco();
  void PlanetaAvispa();

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
  virtual void frameRendered(const Ogre::FrameEvent& evt);
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;   
  OgreBites::CameraMan* mCamMgr = nullptr;
  OgreBites::TextBox* dronesVivos;

  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* PN = nullptr;

  Ogre::ParticleSystem* pSysExp;
  
  Noria* noria = nullptr;

  Plano* plano = nullptr;

  Ogre::SceneNode* AvionCompleto;
  std::vector<Ogre::SceneNode*>avispero;
  Dron* drone;

};

#endif
