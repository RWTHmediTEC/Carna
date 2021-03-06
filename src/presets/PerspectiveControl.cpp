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

#include <Carna/presets/PerspectiveControl.h>
#include <Carna/base/math.h>

namespace Carna
{

namespace presets
{



// ----------------------------------------------------------------------------------
// PerspectiveControl :: Details
// ----------------------------------------------------------------------------------

struct PerspectiveControl::Details
{
    Details();
    
    float fovHorizontal;
};


PerspectiveControl::Details::Details()
    : fovHorizontal( DEFAULT_FOV_HORIZONTAL )
{
}



// ----------------------------------------------------------------------------------
// PerspectiveControl
// ----------------------------------------------------------------------------------

const float PerspectiveControl::DEFAULT_FOV_HORIZONTAL = 3.14f * 45 / 180.f;


PerspectiveControl::PerspectiveControl()
    : pimpl( new Details() )
{
}


PerspectiveControl::~PerspectiveControl()
{
}


void PerspectiveControl::setFovHorizontal( float radians )
{
    CARNA_ASSERT( radians > 0 );
    if( !base::math::isEqual( pimpl->fovHorizontal, radians ) )
    {
        pimpl->fovHorizontal = radians;
        invalidateProjection();
    }
}


float PerspectiveControl::fovHorizontal() const
{
    return pimpl->fovHorizontal;
}


void PerspectiveControl::updateProjection( base::math::Matrix4f& projection ) const
{
    CARNA_ASSERT_EX
        ( minimumVisibleDistance() > 0
        , "PerspectiveControl does not support 'minimumVisibleDistance' set to 0!" );
    
    const float aspect = viewportHeight() / static_cast< float >( viewportWidth() );
    const float zNear  = minimumVisibleDistance();
    const float zFar   = maximumVisibleDistance();
    projection = base::math::frustum4f( pimpl->fovHorizontal, aspect, zNear, zFar );
    setProjectionValidated();
}



}  // namespace Carna :: presets

}  // namespace Carna

