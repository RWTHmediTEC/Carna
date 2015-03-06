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

#ifndef NODE_H_6014714286
#define NODE_H_6014714286

#include <Carna/base/Spatial.h>
#include <set>

/** \file   Node.h
  * \brief  Defines \ref Carna::base::Node.
  */

namespace Carna
{

namespace base
{



// ----------------------------------------------------------------------------------
// Node
// ----------------------------------------------------------------------------------

/** \brief
  * Defines the inner node of a \ref SceneGraph "scene graph". Implements a
  * \ref Spatial "spatial scene element" that is allowed to have children, but cannot
  * be rendered.
  *
  * Each node possesses it's children.
  *
  * \author Leonid Kostrykin
  * \date   21.2.15 - 6.3.15
  */
class CARNA_LIB Node : public Spatial
{

    std::set< Spatial* > children;

public:

    virtual ~Node();

    /** \brief
      * Attaches \a child to this node and takes it's possession.
      *
      * If \a child already has another parent, it is first detached from that one.
      */
    void attachChild( Spatial* child );
    
    /** \brief
      * Detaches \a child from this node. The caller takes possession of the child.
      *
      * \returns
      * Possessing pointer to the child if it has successfully been detached or \c nullptr
      * if something went wrong, e.g. this node is not the \a child's parent.
      */
    Spatial* detachChild( Spatial& child );

    bool hasChild( const Spatial& child ) const;
    
    void deleteAllChildren();
    
    void visitChildren( bool recursively, const MutableVisitor& );
    
    void visitChildren( bool recursively, const ImmutableVisitor& ) const;
    
    /** \brief
      * Computes the transformation to world space for this node just
      * \ref Spatial::updateWorldTransform "like the base class does",
      * than orders it's children to do the same.
      */
    virtual void updateWorldTransform() override;

}; // Node



}  // namespace Carna :: base

}  // namespace Carna

#endif // NODE_H_6014714286
