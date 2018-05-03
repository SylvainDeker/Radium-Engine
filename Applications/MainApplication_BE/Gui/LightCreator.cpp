#include <Gui/LightCreator.hpp>
#include <QPushButton>
#include <QColorDialog>
#include <QPalette>


namespace Ra {
namespace Gui {
LightCreator::LightCreator( QWidget* parent ) : QWidget( parent )    {
    setupUi( this );
    color = QColor(255,255,255);
    QPalette p;

    p.setColor(QPalette::Background,color);
    result_color->setAutoFillBackground(true);
    result_color->setPalette(p);
    connect(button_color,&QPushButton::clicked,this,&LightCreator::open_dialogColor);

}


void LightCreator::open_dialogColor(){
  color = QColorDialog::getColor ();
  QPalette p;

  p.setColor(QPalette::Background,color);
  result_color->setPalette(p);

}



} // namespace Gui
} // namespace Ra
