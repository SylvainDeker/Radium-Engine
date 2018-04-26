#include "LightEditUI.h"
#include "ui_LightEditUI.h"

LightEditUI::LightEditUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightEditUI)
{
    ui->setupUi(this);
}

LightEditUI::~LightEditUI()
{
    delete ui;
}
