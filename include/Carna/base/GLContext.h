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

#ifndef GLCONTEXT_H_6014714286
#define GLCONTEXT_H_6014714286

#include <Carna/Carna.h>
#include <Carna/base/CarnaException.h>
#include <Carna/base/noncopyable.h>
#include <stack>
#include <memory>

/** \file   GLContext.h
  * \brief  Defines \ref Carna::base::GLContext.
  */

namespace Carna
{

namespace base
{



// ----------------------------------------------------------------------------------
// GLContext
// ----------------------------------------------------------------------------------

/** \brief
  * Wraps and represents an OpenGL context.
  *
  * This is a good explanation of the essence of OpenGL contexts:
  *
  * > An OpenGL context represents many things. A context stores all of the state
  * > associated with this instance of OpenGL. [...] Each context can represent a
  * > separate viewable surface, like a window in an application. Contexts can share
  * > many kinds of objects between each other. Any OpenGL object types which are not
  * > containers are sharable, as well as [...] GLSL Objects. [...] In order for any
  * > OpenGL commands to work, a context must be current; all OpenGL commands affect
  * > the state of whichever context is current. The current context is a
  * > thread-local variable, so a single process can have several threads, each of
  * > which has its own current context.
  *
  * Reference: https://www.opengl.org/wiki/OpenGL_Context
  *
  * %Carna assumes that all OpenGL contexts within your application are capable of
  * sharing objects. %Carna does not support multi-threading environments, i.e. all
  * %Carna-related code must be run on the same thread. The states are maintained
  * through the \ref RenderState class.
  *
  * \author Leonid Kostrykin
  * \date   22.2.15 - 15.3.15
  */
class CARNA_LIB GLContext
{

    const ShaderProgram* myShader;

    const std::unique_ptr< RenderState > myRenderState;

protected:

    explicit GLContext( bool isDoubleBuffered );

    friend class RenderState;

    std::stack< const RenderState* > renderStates;

public:

    const static unsigned int DEPTH_BUFFER_BIT;
    const static unsigned int COLOR_BUFFER_BIT;

    virtual ~GLContext();

    const bool isDoubleBuffered;

    static GLContext& current();

    virtual void makeCurrent() const = 0;

    bool isCurrent() const;

    void setShader( const ShaderProgram& );

    const ShaderProgram& shader() const;

    void clearBuffers( unsigned int flags );

}; // GLContext



// ----------------------------------------------------------------------------------
// QGLContextAdapter
// ----------------------------------------------------------------------------------

/** \brief
  * If you're using Qt, this class template implements the abstract \ref GLContext
  * class as an adapter to the \c QGLContext class from Qt.
  *
  * Example:
  *
  *     \code
  *     #include <QGLContext>
  *     #include <QGLFormat>
  *     typedef Carna::base::QGLContextAdapter< QGLContext, QGLFormat > GLContext;
  *     \endcode
  *
  * \author Leonid Kostrykin
  * \date   22.2.15 - 20.3.15
  */
template< typename QGLContext, typename QGLFormat >
class QGLContextAdapter : public GLContext
{

    QGLContext& qglcontext;

public:

    QGLContextAdapter();
    
    static QGLFormat desiredFormat();

    virtual void makeCurrent() const override;

}; // QGLContextAdapter


template< typename QGLContext, typename QGLFormat >
QGLContextAdapter< QGLContext, QGLFormat >::QGLContextAdapter()
    : GLContext( QGLContext::currentContext()->format().doubleBuffer() )
    , qglcontext( const_cast< QGLContext& >( *QGLContext::currentContext() ) )
{
    const QGLFormat& format = QGLContext::currentContext()->format();
    if( format.majorVersion() < 3 || ( format.majorVersion() == 3 && format.minorVersion() < 3 ) )
    {
        std::stringstream msg;
        msg << "OpenGL context version " << format.majorVersion() << "." << format.minorVersion() << " is too low.";
        CARNA_FAIL( msg.str() );
    }
    else
    {
        CARNA_ASSERT( format.profile() != QGLFormat::NoProfile );
        std::stringstream msg;
        msg << "Recognized OpenGL " << format.majorVersion() << "." << format.minorVersion() << " context (";
        msg << ( format.profile() == QGLFormat::CoreProfile ? "core" : "compatibility" ) << " profile)";
        Log::instance().record( Log::debug, msg.str() );
    }
}

    
template< typename QGLContext, typename QGLFormat >
QGLFormat QGLContextAdapter< QGLContext, QGLFormat >::desiredFormat()
{
    QGLFormat format = QGLFormat::defaultFormat();
    format.setVersion( 3, 3 );
    format.setProfile( QGLFormat::CompatibilityProfile );
    return format;
}


template< typename QGLContext, typename QGLFormat >
void QGLContextAdapter< QGLContext, QGLFormat >::makeCurrent() const
{
    qglcontext.makeCurrent();
}



}  // namespace Carna :: base

}  // namespace Carna

#endif // GLCONTEXT_H_6014714286
