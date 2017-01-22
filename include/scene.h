#pragma once

#ifndef SCENE_H
#define SCENE_H


#include "QuatCamera.h"

namespace ecr
{

class Scene
{
public:
	Scene() : m_animate(true) { }
	
    /**
      Load textures, initialize shaders, etc.
      */
    virtual void initScene(ecr::QuatCamera &camera) = 0;

    /**
      This is called prior to every frame.  Use this
      to update your animation.
      */
    virtual void update( float t ) = 0;

    /**
      Draw your scene.
      */
    virtual void render(ecr::QuatCamera &camera) = 0;

    /**
      Called when screen is resized
      */
    virtual void resize(ecr::QuatCamera &camera,int, int) = 0;
    
	virtual void animate(bool a , int x) = 0;

    
protected:
	bool m_animate;
};

}

#endif // SCENE_H
