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

#ifndef BUFFEREDHUVOLUME_H_6014714286
#define BUFFEREDHUVOLUME_H_6014714286

/** \file   BufferedHUVolume.h
  *
  * \brief  Defines \ref Carna::base::model::BufferedHUVolume.
  *
  * \author Leonid Kostrykin
  * \date   25.7.11
  */

#include <Carna/base/model/HUVolume.h>
#include <Carna/base/Composition.h>
#include <Carna/base/CarnaException.h>
#include <vector>

namespace Carna
{

namespace base
{

namespace model
{



// ----------------------------------------------------------------------------------
// BufferedHUVolume
// ----------------------------------------------------------------------------------

/** \brief  Generic \ref HUVolume implementation.
  *
  * \invariant  <code>sizeof( VoxelType ) >= 2</code>
  *
  * Template Arguments:
  *
  * - The \a VoxelType is the data type used to store the value of a single voxel / HU-value.
  * - The \a BufferType is the data type used as voxel container.
  *
  * \author Leonid Kostrykin
  * \date   2011 - 2015
  */
template< typename VoxelType, typename BufferType = std::vector< VoxelType > >
class BufferedHUVolume : public HUVolume
{

public:

    /** \brief  Holds the used buffer type.
      */
    typedef BufferType BufferType;

    /** \brief  Holds the used voxel type.
      */
    typedef VoxelType VoxelType;

    /** \brief  Instantiates.
      */
    BufferedHUVolume( const Vector3ui& size, Association< BufferType >* buffer )
        : HUVolume( size )
        , myBuffer( buffer )
    {
        initializeBuffer();
    }

    /** \brief  Instantiates.
      *
      * This constructor is similar to:
      *
      * \code
      * BufferedHUVolume( size, new Composition< BufferType >( new BufferType( size.x * size.y * size.z ) ) );
      * \endcode
      */
    explicit BufferedHUVolume( const Vector3ui& size )
        : HUVolume( size )
        , myBuffer( new Composition< BufferType >( new BufferType( size.x() * size.y() * size.z() ) ) )
    {
        initializeBuffer();
    }


    /** \brief  Returns the buffer value corresponding to the given HU value.
      *
      * \since  \ref v_2_4
      */
    static signed short bufferValueToHUV( VoxelType voxel_value )
    {
        return static_cast< signed short >( voxel_value >> ( sizeof( VoxelType ) * 8 - 12 ) ) - 1024;
    }

    
    /** \brief  Returns the HU value corresponding to the given buffer value.
      *
      * \since  \ref v_2_4
      */
    static VoxelType HUVToBufferValue( signed short huv )
    {
        return ( static_cast< VoxelType >( huv + 1024 ) << ( sizeof( VoxelType ) * 8 - 12 ) );
    }


    /** \brief  Returns HUV of specified voxel.
      */
    signed short operator()( unsigned int x
                           , unsigned int y
                           , unsigned int z ) const
    {
        return bufferValueToHUV( myBuffer->get()->at( x + size.x() * y + size.y() * size.x() * z ) );
    }

    /** \brief  Returns HUV of specified voxel.
      */
    signed short operator()( const Vector3ui& at ) const
    {
        return ( *this )( at.x(), at.y(), at.z() );
    }


    /** \brief  Sets the HUV of a voxel.
      */
    void setVoxel( unsigned int x, unsigned int y, unsigned int z, signed short huv )
    {
        myBuffer->get()->at( x + size.x() * y + size.y() * size.x() * z ) = HUVToBufferValue( huv );
    }

    /** \brief  Sets the HUV of a voxel.
      */
    void setVoxel( const Vector3ui& at, signed short huv )
    {
        this->setVoxel( at.x(), at.y(), at.z(), huv );
    }


    /** \brief  References the underlying buffer.
      *
      * This method wasn't working prior to \ref v_2_2_2.
      */
    BufferType& buffer()
    {
        return *myBuffer->get();
    }
    
    /** \brief  References the underlying buffer.
      *
      * This method wasn't working prior to \ref v_2_2_2.
      */
    const BufferType& buffer() const
    {
        return *myBuffer->get();
    }


protected:

    /** \brief  Holds the computed data.
      *
      * The voxels are written \f$x\f$-\f$y\f$-plane wise, each plane \f$x\f$-row wise.
      *
      * To compute the position of some voxel \f$\big(\; x, y, z \;\big)\f$ in \a data:
      *
      * \f[ \mathrm{position} = x + \mathrm{width} \cdot y + \mathrm{height} \cdot \mathrm{width} \cdot z \f]
      */
    const std::unique_ptr< Association< BufferType > > myBuffer;


private:

    void initializeBuffer()
    {
        CARNA_ASSERT_EX
            ( myBuffer.get() && myBuffer->get()
            , "no volume data buffer supplied" );

        CARNA_ASSERT_EX
            ( myBuffer->get()->size() >= size.x() * size.y() * size.z()
            , "supplied volume data buffer is of size "
                << myBuffer->get()->size()
                << " bytes but must be at least "
                << size.x() * size.y() * size.z()
                << " bytes" );
    }

}; // BufferedHUVolume



}  // namesapce Carna :: base :: model

}  // namespace Carna :: base

}  // namespace Carna

#endif // BUFFEREDHUVOLUME_H_6014714286
