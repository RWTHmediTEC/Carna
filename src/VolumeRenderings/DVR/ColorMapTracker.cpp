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

#include <Carna/VolumeRenderings/DVR/ColorMapTracker.h>
#include <Carna/VolumeRenderings/DVR/ColorMapEditor.h>
#include <Carna/base/qt/MultiSpanSliderTracker.h>
#include <Carna/base/qt/ColorPickerPainter.h>
#include <QPainter>

namespace Carna
{

namespace VolumeRenderings
{

namespace DVR
{



// ----------------------------------------------------------------------------------
// DVR :: ColorMapTracker
// ----------------------------------------------------------------------------------

void ColorMapTracker::paint( const base::IntSpan& span
                           , unsigned int span_index
                           , Qt::Orientation orientation
                           , QPainter& painter
                           , Role mode )
{
    const bool selected = widget->getSelectedSpan() == &span;

    if( selected )
    {
        const int space_width = widget->width() - painter.transform().dx() - MultiSpanSliderTracker::trackerWidth;

        const int mainbox_width  = ColorMapEditor::trackerEditorBoxWidth;
        const int mainbox_height = ColorMapEditor::trackerEditorBoxHeight;

        const int vbox_height = MultiSpanSliderTracker::trackerHeight;
        const int vbox_width  = space_width - mainbox_width / 2;

        const int hbox_width  = vbox_height;
        int hbox_height;
        int hbox_top;

        if( mode == begin )
        {
            hbox_height = painter.transform().dy();
            hbox_top = vbox_height - hbox_height;
        }
        else
        {
            hbox_height = widget->height();
            hbox_top = 0;
        }

        const QRect vbox_rect( 1, 0, vbox_width - 1, vbox_height );
        const QRect hbox_rect( vbox_width - hbox_width / 2, hbox_top, hbox_width, hbox_height );

        painter.save();

        painter.translate( trackerWidth, 0 );

        if( mode == begin )
        {
            painter.translate( 0, -vbox_height );
        }

        painter.setPen( Qt::NoPen );
        painter.setBrush( Qt::white );
        painter.drawRect( vbox_rect );
        painter.drawRect( hbox_rect );


        painter.restore();
    }

    base::qt::MultiSpanSliderTracker::paint( span, span_index, orientation, painter, mode );

    const QColor& color = ( mode == begin ? widget->getFirstColor( span_index ) : widget->getLastColor( span_index ) );

    base::qt::ColorPickerPainter cpp;
    const QRect color_rect( base::qt::MultiSpanSliderTracker::trackerWidth / 3 - 1
                          , 1
                          , base::qt::MultiSpanSliderTracker::trackerWidth * 2 / 3 + 1
                          , base::qt::MultiSpanSliderTracker::trackerHeight - 2 );
    painter.setPen( Qt::white );
    painter.setBrush( Qt::NoBrush );
    painter.drawRect( color_rect );
    cpp.paint( painter, color_rect.adjusted( 1, 1, 0, 0 ), color );
}


bool ColorMapTracker::testHit( const QPoint& p, Qt::Orientation orientation, Role mode )
{
    return base::qt::MultiSpanSliderTracker::testHit( p, orientation, mode );
}



}  // namespace Carna :: VolumeRenderings :: DVR

}  // namespace Carna :: VolumeRenderings

}  // namespace Carna
