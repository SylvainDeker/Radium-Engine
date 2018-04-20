#include "LightPathUI.hpp"
#include "ui_LightPathUI.h"

#include <QComboBox>


namespace LightPathPlugin {
  LightPathUI::LightPathUI(QWidget *parent) : QWidget( parent ), ui(new Ui::LightPathUI)
  {
    ui->setupUi(this);
  }
  
  LightPathUI::~LightPathUI()
  {
    delete ui;
  }
  
} // namespace LightPathPlugin
