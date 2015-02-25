/*
 *  Copyright (C) 2010 - 2014 Leonid Kostrykin
 *
 *  Chair of Medical Engineering (mediTEC)
 *  RWTH Aachen University
 *  Pauwelsstr. 20
 *  52074 Aachen
 *  Germany
 *
 */

#pragma once

#include <Carna/base/view/Renderer.h>
#include <Carna/base/Visualization.h>

namespace Carna
{

namespace testing
{



// ----------------------------------------------------------------------------------
// MyRenderer
// ----------------------------------------------------------------------------------

class MyRenderer : public Carna::base::view::Renderer
{

public:

    MyRenderer
        ( Carna::base::Visualization& module
        , Carna::base::view::SceneProvider& provider
        , QObject* parent = nullptr );


protected:

    virtual void renderColor() override;

    virtual void renderDepth() override;


    virtual void fetchSceneMatrix
        ( Carna::base::Transformation& sceneMatrix
        , const Carna::base::Transformation& cameraMatrix
        , const Carna::base::Transformation& projectionMatrix ) const override;

};



// ----------------------------------------------------------------------------------
// MyVisualization
// ----------------------------------------------------------------------------------

class MyVisualization : public Carna::base::Visualization
{

protected:

    virtual Carna::base::view::Renderer* createRenderer( Carna::base::view::SceneProvider& provider ) override;

};



}  // namespace testing

}  // namespace Carna