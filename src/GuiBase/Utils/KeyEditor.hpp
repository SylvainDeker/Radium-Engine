#ifndef DEF_KEYEDITOR
#define DEF_KEYEDITOR


#include <QWidget>
#include <QtXml/QtXml>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <GuiBase/RaGuiBase.hpp>
#include <QKeySequenceEdit>
#include <QKeySequence>
#include <QApplication>
#include<bits/stdc++.h>
#include "KeyMappingManager.hpp"
using namespace std;


#define NB_SHORTCUT
//#include <ui_KeyEditor.h>
namespace Ui {
class KeyEditor;
}

namespace Ra
{
    namespace Gui
    {
        class KeyEditor : public QWidget
        {
            Q_OBJECT

        public:
            KeyEditor();
            ~KeyEditor();

        public slots:
            void closeWindow();
            void okClick();
            void defaultClick();
            void truncateShortcut();
            void mouseShortcut(int i, QDomElement info1, QDomElement info2);
            void Xml();

        private:
            Ui::KeyEditor *m_ui;
            KeyMappingManager *keymappingmanager;


        };
    }
}

#endif //DEF_KEYEDITOR
