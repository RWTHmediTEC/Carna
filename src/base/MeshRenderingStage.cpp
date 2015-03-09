﻿/*
 *  Copyright (C) 2010 - 2015 Leonid Kostrykin
 *
 *  Chair of Medical Engineering (mediTEC)
 *  RWTH Aachen University
 *  Pauwelsstr. 20
 *  52074 Aachen
 *  Germany
 *
 */

#include <Carna/base/MeshRenderingStage.h>

namespace Carna
{

namespace base
{



// ----------------------------------------------------------------------------------
// MeshRenderingStageBase
// ----------------------------------------------------------------------------------

MeshRenderingStageBase::MeshRenderingStageBase( unsigned int geometryType )
    : geometryType( geometryType )
{
}


MeshRenderingStageBase::~MeshRenderingStageBase()
{
}



}  // namespace Carna :: base

}  // namespace Carna
