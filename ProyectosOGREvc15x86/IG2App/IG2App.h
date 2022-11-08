#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
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
  Ogre::SceneNode* Scene1 = nullptr;
  Ogre::SceneNode* Scene2 = nullptr;
  Ogre::SceneNode* Scene3 = nullptr;
  Ogre::SceneNode* Scene4 = nullptr;
  Ogre::SceneNode* PN;
  Noria* noria = nullptr;
  Munyeco* olaf = nullptr;
  Plano* plano = nullptr;

  Ogre::SceneNode* AvionCompleto;
  std::vector<Ogre::SceneNode*>avispero;
  Dron* drone;

};

#endif
