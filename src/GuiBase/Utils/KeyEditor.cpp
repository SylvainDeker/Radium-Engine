#include <GuiBase/Utils/KeyEditor.hpp>

#include "ui_KeyEditor.h"

namespace Ra
{
    namespace Gui
    {
        KeyEditor::KeyEditor() : QWidget(), m_ui(new Ui::KeyEditor)
        {
            m_ui->setupUi( this );
            connect(m_ui->cancelButton,SIGNAL(clicked()),this,SLOT(closeWindow()));
            connect(m_ui->defaultButton,SIGNAL(clicked()),this,SLOT(defaultClick()));
            connect(m_ui->okButton,SIGNAL(clicked(bool)),this,SLOT(okClick()));


            //All the shortcut editing connects. Add one when you add a shortcut
            connect(m_ui->keySequenceEdit, SIGNAL(editingFinished()), this, SLOT(truncateShortcut()));
            connect(m_ui->keySequenceEdit_2, SIGNAL(editingFinished()), this, SLOT(truncateShortcut()));
            connect(m_ui->keySequenceEdit_3, SIGNAL(editingFinished()), this, SLOT(truncateShortcut()));
            connect(m_ui->keySequenceEdit_4, SIGNAL(editingFinished()), this, SLOT(truncateShortcut()));
            connect(m_ui->keySequenceEdit_5, SIGNAL(editingFinished()), this, SLOT(truncateShortcut()));
            connect(m_ui->keySequenceEdit_6, SIGNAL(editingFinished()), this, SLOT(truncateShortcut()));
            connect(m_ui->keySequenceEdit_7, SIGNAL(editingFinished()), this, SLOT(truncateShortcut()));
        }

        KeyEditor::~KeyEditor()
        {

        }

        void KeyEditor::mouseShortcut(int i,QDomElement info1, QDomElement info2){
            if(i==0){
                info1.setAttribute("id","type");
                info1.setAttribute("modifier","NoModifier");
                info1.setAttribute("type","mouse");
                info1.setAttribute("value","MiddleButton");
                info2.setAttribute("id","action");
                info2.setAttribute("value","TRACKBALLCAMERA_MANIPULATION");
            }else if(i==1){
                info1.setAttribute("id","type");
                info1.setAttribute("modifier","NoModifier");
                info1.setAttribute("type","mouse");
                info1.setAttribute("value","LeftBouton");
                info2.setAttribute("id","action");
                info2.setAttribute("value","GIZMOMANAGER_MANIPULATION");
            }else if(i==2){
                info1.setAttribute("id","type");
                info1.setAttribute("modifier","NoModifier");
                info1.setAttribute("type","mouse");
                info1.setAttribute("value","RIGHTBUTTON");
                info2.setAttribute("id","action");
                info2.setAttribute("value","VIEWER_BUTTON_PICKING_QUERY");
            }else if(i==3){
                info1.setAttribute("id","type");
                info1.setAttribute("modifier","NoModifier");
                info1.setAttribute("type","mouse");
                info1.setAttribute("value","LeftBouton");
                info2.setAttribute("id","action");
                info2.setAttribute("value","VIEWER_BUTTON_CAST_RAY_QUERY");
            }else{
                info1.setAttribute("id","type");
                info1.setAttribute("modifier","NoModifier");
                info1.setAttribute("type","mouse");
                info1.setAttribute("value","LeftBouton");
                info2.setAttribute("id","action");
                info2.setAttribute("value","COLORWIDGET_PRESSBUTTON");
            }
        }

        void KeyEditor::Xml()
        {
          //this part construct the shortcut tab
                QString keyTab[7];
                QString firstShortcutPart = "Key_";
                QKeySequence tempoKeySequence;
                //Shortcut n°1
                m_ui->keySequenceEdit->setKeySequence(tempoKeySequence);
                if(tempoKeySequence.isEmpty())
                {
                    keyTab[0]="Key_A";
                }else{
                    QString shortcut = tempoKeySequence.toString();
                    keyTab[0] = (firstShortcutPart + shortcut);
                }
                //Shortcut n°2
                m_ui->keySequenceEdit->setKeySequence(tempoKeySequence);
                if(tempoKeySequence.isEmpty())
                {
                    keyTab[1]="Key_V";
                }else{
                    QString shortcut = tempoKeySequence.toString();
                    keyTab[1] = (firstShortcutPart + shortcut);
                }
                //Shortcut n°3
                m_ui->keySequenceEdit->setKeySequence(tempoKeySequence);
                if(tempoKeySequence.isEmpty())
                {
                    keyTab[2]="Key_E";
                }else{
                    QString shortcut = tempoKeySequence.toString();
                    keyTab[2] =(firstShortcutPart + shortcut);
                }
                //Shortcut n°4
                m_ui->keySequenceEdit->setKeySequence(tempoKeySequence);
                if(tempoKeySequence.isEmpty())
                {
                    keyTab[3]="Key_T";
                }else{
                    QString shortcut = tempoKeySequence.toString();
                    keyTab[3] = (firstShortcutPart + shortcut);
                }
                //Shortcut n°5
                m_ui->keySequenceEdit->setKeySequence(tempoKeySequence);
                if(tempoKeySequence.isEmpty())
                {
                    keyTab[4]="Key_C";
                }else{
                    QString shortcut = tempoKeySequence.toString();
                    keyTab[4] = (firstShortcutPart + shortcut);
                }
                //Shortcut n°6
                m_ui->keySequenceEdit->setKeySequence(tempoKeySequence);
                if(tempoKeySequence.isEmpty())
                {
                    keyTab[5]="Key_R";
                }else{
                    QString shortcut = tempoKeySequence.toString();
                    keyTab[5] = (firstShortcutPart + shortcut);
                }
                //Shortcut n°7
                m_ui->keySequenceEdit->setKeySequence(tempoKeySequence);
                if(tempoKeySequence.isEmpty())
                {
                    keyTab[6]="Key_Z";
                }else{
                    QString shortcut = tempoKeySequence.toString();
                    keyTab[6] = (firstShortcutPart + shortcut);
                }

            //this part generate xml doc
            QString tab[7] = {"TRACKBALLCAMERA_ROTATE_AROUND", "FEATUREPICKING_VERTEX",
                              "FEATUREPICKING_EDGE", "FEATUREPICKING_TRIANGLE",
                              "FEATUREPICKING_MULTI_CIRCLE","VIEWER_RAYCAST_QUERY",
                              "VIEWER_TOGGLE_WIREFRAME"};

            QDomDocument doc;

            QFile xml_doc("Configs/alternative.xml");

            if ( xml_doc.open( QIODevice::WriteOnly | QIODevice::Text ) )

            {

                QTextStream stream(&xml_doc);

                QDomElement root = doc.createElement("keymaps");

                doc.appendChild(root);

                QDomProcessingInstruction instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"ISO-8859-1\" ");

                doc.insertBefore(instruction,root);

                for(int i = 0;i<12;i++)

                {
                    QDomElement parent = doc.createElement("keymap");
                    root.appendChild(parent);
                    QDomElement info1 = doc.createElement("information");
                    parent.appendChild(info1);
                    QDomElement info2 = doc.createElement("information");
                    parent.appendChild(info2);
                    if(i<5)
                    {
                      this->mouseShortcut(i,info1,info2);
                    }else{
                    info1.setAttribute("id","type");
                    info1.setAttribute("modifier","NoModifier");
                    info1.setAttribute("type","key");
                    info1.setAttribute("value",keyTab[i-5]);
                    info2.setAttribute("id","action");
                    info2.setAttribute("value",tab[i-5]);
                    }
                    parent.appendChild(info1);
                    parent.appendChild(info2);
               }

                doc.save(stream,4);

                xml_doc.close();

            }
        }

        /*slot for button close
         * just close the window without change shortcut
         */
        void KeyEditor::closeWindow()
        {
            this->close();
        }

        /*slot for button default
         * load the default shortcut configuration
         * close the window
         */
        void KeyEditor::defaultClick()
        {
            keymappingmanager= new KeyMappingManager();
            keymappingmanager->loadConfiguration();
            this->close();
        }

        /*slort for button ok
         * set news shorcuts
         * close window
         */
        void KeyEditor::okClick()
        {
            this->Xml();
            keymappingmanager= new KeyMappingManager();
            keymappingmanager->loadConfiguration("Configs/alternative.xml");
            this->close();
        }

        void KeyEditor::truncateShortcut()
        {
            /* To add a shortcut, simply follow the skeleton below */
            //Shortcut 1
            int value = m_ui->keySequenceEdit->keySequence()[0];
            QKeySequence shortcut(value);
            m_ui->keySequenceEdit->setKeySequence(shortcut);

            //Shortcut 2
            value = m_ui->keySequenceEdit_2->keySequence()[0];
            QKeySequence shortcut2(value);
            m_ui->keySequenceEdit_2->setKeySequence(shortcut2);

            //Shortcut 3
            value = m_ui->keySequenceEdit_3->keySequence()[0];
            QKeySequence shortcut3(value);
            m_ui->keySequenceEdit_3->setKeySequence(shortcut3);

            //Shortcut 4
            value = m_ui->keySequenceEdit_4->keySequence()[0];
            QKeySequence shortcut4(value);
            m_ui->keySequenceEdit_4->setKeySequence(shortcut4);

            //Shortcut 5
            value = m_ui->keySequenceEdit_5->keySequence()[0];
            QKeySequence shortcut5(value);
            m_ui->keySequenceEdit_5->setKeySequence(shortcut5);

            //Shortcut 6
            value = m_ui->keySequenceEdit_6->keySequence()[0];
            QKeySequence shortcut6(value);
            m_ui->keySequenceEdit_6->setKeySequence(shortcut6);

            //Shortcut 7
            value = m_ui->keySequenceEdit_7->keySequence()[0];
            QKeySequence shortcut7(value);
            m_ui->keySequenceEdit_7->setKeySequence(shortcut7);
        }
    }
}
