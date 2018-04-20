#ifndef LIGHTPATHUI_H
#define LIGHTPATHUI_H

#include <QWidget>
#include "LightPathPlugin.hpp"

namespace Ui {
  class LightPathUI;
}

namespace LightPathPlugin {
  class LightPathUI : public QWidget
  {
    Q_OBJECT

  public:
    explicit LightPathUI(QWidget *parent = 0);
    ~LightPathUI();
  private:
    Ui::LightPathUI *ui;
  };

} // namespace LightPathPlugin

#endif // LIGHTPATHUI_H
