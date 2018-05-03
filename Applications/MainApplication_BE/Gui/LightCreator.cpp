#include <Gui/LightCreator.hpp>
#include <QPushButton>
#include <QColorDialog>
#include <QPalette>


namespace Ra {
namespace Gui {
LightCreator::LightCreator( QWidget* parent ) : QWidget( parent )    {
    setupUi( this );
    m_color = QColor(255,255,255);
    QPalette p;

    p.setColor(QPalette::Background,m_color);
    m_result_color->setAutoFillBackground(true);
    m_result_color->setPalette(p);
    connect(m_button_color,&QPushButton::clicked,this,&LightCreator::open_dialogColor);

}


void LightCreator::open_dialogColor(){
  m_color = QColorDialog::getColor ();
  QPalette p;

  p.setColor(QPalette::Background,m_color);
  m_result_color->setPalette(p);

}



} // namespace Gui
} // namespace Ra
