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

#ifndef SAMPLER_H_6014714286
#define SAMPLER_H_6014714286

#include <Carna/Carna.h>
#include <Carna/base/noncopyable.h>

/** \file   Sampler.h
  * \brief  Defines \ref Carna::base::Sampler.
  */

namespace Carna
{

namespace base
{



// ----------------------------------------------------------------------------------
// Sampler
// ----------------------------------------------------------------------------------

/** \brief
  * Maintains an OpenGL texture sampler object. This class realizes the RAII-idiom.
  *
  * Sampling values from textures requires a sampler object to be bound to the same
  * texture unit as the texture is bound to. The sampler object controls how values
  * are sampled from the texture.
  *
  * \author Leonid Kostrykin
  * \date   22.2.15 - 19.3.15
  */
class CARNA_LIB Sampler
{

    NON_COPYABLE

public:

    const static unsigned int WRAP_MODE_CLAMP;           ///< Represents `GL_CLAMP_TO_EDGE`.
    const static unsigned int WRAP_MODE_REPEAT;          ///< Represents `GL_REPEAT`.
    const static unsigned int WRAP_MODE_MIRRORED_REPEAT; ///< Represents `GL_MIRRORED_REPEAT`.

    const static unsigned int FILTER_NEAREST;   ///< Represents `GL_NEAREST`.
    const static unsigned int FILTER_LINEAR;    ///< Represents `GL_LINEAR`.

    /** \brief
      * Creates new OpenGL sampler object.
      */
    Sampler
        ( unsigned int wrapModeS
        , unsigned int wrapModeT
        , unsigned int wrapModeR
        , unsigned int minFilter
        , unsigned int magFilter );

    /** \brief
      * Deletes the maintained OpenGL sampler object.
      */
    ~Sampler();

    /** \brief
      * Holds the ID of the maintained OpenGL sampler object.
      */
    const unsigned int id;

    /** \brief
      * Binds the maintained OpenGL sampler objec to texture \a unit.
      */
    void bind( int unit ) const;

    /** \brief
      * Configures sampling for \f$\left(s,t,r\right)^\mathrm T\f$ with
      * \f$s\not\in\left[0,1\right]\f$.
      */
    void setWrapModeS( unsigned int wrapMode );

    /** \brief
      * Configures sampling for \f$\left(s,t,r\right)^\mathrm T\f$ with
      * \f$t\not\in\left[0,1\right]\f$.
      */
    void setWrapModeT( unsigned int wrapMode );

    /** \brief
      * Configures sampling for \f$\left(s,t,r\right)^\mathrm T\f$ with
      * \f$r\not\in\left[0,1\right]\f$.
      */
    void setWrapModeR( unsigned int wrapMode );

    /** \brief
      * Configures sampling for when texel maps onto less than one pixel.
      */
    void setMinFilter( unsigned int minFilter );

    /** \brief
      * Configures sampling for when texel maps onto more than one pixel.
      */
    void setMagFilter( unsigned int magFilter );

}; // Sampler



}  // namespace Carna :: base

}  // namespace Carna

#endif // SAMPLER_H_6014714286
