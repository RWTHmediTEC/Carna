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

#include <Carna/base/glew.h>
#include <Carna/base/glError.h>
#include <Carna/base/ManagedTexture3D.h>
#include <Carna/base/CarnaException.h>
#include <Carna/base/text.h>

namespace Carna
{

namespace base
{



// ----------------------------------------------------------------------------------
// computeTextureCoordinatesCorrection
// ----------------------------------------------------------------------------------

static base::math::Matrix4f computeTextureCoordinatesCorrection( const math::Vector3ui& size )
{
    const base::math::Vector3f texelSize   = size.cast< float >().cwiseInverse();
    const base::math::Vector3f texelOffset = texelSize / 2;
    const base::math::Vector3f texelScale  = base::math::Vector3f( 1, 1, 1 ) - texelSize;

    base::math::Matrix4f m;
    m << texelScale.x(),              0,              0, texelOffset.x(),
                      0, texelScale.y(),              0, texelOffset.y(),
                      0,              0, texelScale.z(), texelOffset.z(),
                      0,              0,              0,               1;
    return m;
}



// ----------------------------------------------------------------------------------
// ManagedTexture3D
// ----------------------------------------------------------------------------------

ManagedTexture3D::ManagedTexture3D
        ( const math::Vector3ui& size
        , int internalFormat
        , int pixelFormat
        , int bufferType
        , const void* bufferPtr )
    : size( size )
    , internalFormat( internalFormat )
    , pixelFormat( pixelFormat )
    , bufferType( bufferType )
    , bufferPtr( bufferPtr )
    , textureCoordinatesCorrection( computeTextureCoordinatesCorrection( size ) )
{
}


ManagedTexture3D::~ManagedTexture3D()
{
}


bool ManagedTexture3D::controlsSameVideoResource( const GeometryFeature& ) const
{
    return false;
}


ManagedTexture3DInterface* ManagedTexture3D::acquireVideoResource()
{
    return new ManagedTexture3DInterface( *this );
}



}  // namespace Carna :: base

}  // namespace Carna
