#ifndef LIGHTEDITUI_H
#define LIGHTEDITUI_H

#include <QWidget>

namespace Ui {
class LightEditUI;
}

class LightEditUI : public QWidget
{
    Q_OBJECT

public:
    explicit LightEditUI(QWidget *parent = 0);
    ~LightEditUI();

private:
    Ui::LightEditUI *ui;
};

#endif // LIGHTEDITUI_H
