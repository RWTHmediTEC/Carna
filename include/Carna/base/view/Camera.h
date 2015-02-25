/*
 *  Copyright (C) 2010 - 2015 Leonid Kostrykin
 *
 *  Chair of Medical Engineering (mediTEC)
 *  RWTH Aachen University
 *  Pauwelsstr. 20
 *  52074 Aachen
 *  Germany
 *
 */

#ifndef CAMERA_H_6014714286
#define CAMERA_H_6014714286

/** \file   Camera.h
  * \brief  Defines \ref Carna::base::view::Camera.
  */

#include <Carna/base/view/Spatial.h>

namespace Carna
{

namespace base
{

namespace view
{



// ----------------------------------------------------------------------------------
// Camera
// ----------------------------------------------------------------------------------

class CARNA_LIB Camera : public Spatial
{

    Matrix4f myViewTransform;

    Matrix4f myProjection;

public:

    void setProjection( const Matrix4f& );

    const Matrix4f& projection() const;

    const Matrix4f& viewTransform() const;

    virtual void updateWorldTransform() override;

}; // Camera



}  // namespace Carna :: base :: view

}  // namespace Carna :: base

}  // namespace Carna

#endif // CAMERA_H_6014714286