#ifndef TestPLGUI_HPP_
#define TestPLGUI_HPP_



#include <QApplication>

#include <QWidget>

#include <QPushButton>

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>



class TestPLGui : public QWidget

{

    Q_OBJECT

    public:

    TestPLGui();



    public slots:

    void ouvrirDialogue();



    private:

    QPushButton *m_boutonDialogue;

};



#endif
