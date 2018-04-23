#include "LightPathUI.hpp"
#include "ui_LightPathUI.h"

namespace LightPathPlugin {
  LightPathUI::LightPathUI( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::LightPathUI ) { ui->setupUi( this ); }
  
  LightPathUI::~LightPathUI() { delete ui; }

  void LightPathUI::on__amazingButton_clicked()
    {
      emit amazingSignal();
    }
  
} // namespace LightPathPlugin
