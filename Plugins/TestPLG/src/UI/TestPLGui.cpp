#include "TestPLGui.hpp"



TestPLGui::TestPLGui() : QWidget()
{
    setFixedSize(230, 120);

    m_boutonDialogue = new QPushButton("VASY CLIQUE ! ", this);
    m_boutonDialogue->move(40, 50);

    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(ouvrirDialogue()));
}

void TestPLGui::ouvrirDialogue()
{
//   QMessageBox::information(this,"TU TE CROIS CHEZ TA MERE ?","ALLER HOP CA DEGAGE !!");
  QMessageBox::critical(this,"TU TE CROIS CHEZ TA MERE ?","ALLER HOP, CA DEGAGE !!");
//    QMessageBox::warning(this,"TU TE CROIS CHEZ TA MERE ?","ALLER HOP, CA DEGAGE !!");
//     QMessageBox::question(this,"TU TE CROIS CHEZ TA MERE ?","ALLER HOP, CA DEGAGE !!");
//     QMessageBox::question(this, "Titre de la fenêtre", "Dites voir, je me posais la question comme cela, êtes-vous vraiment un Zéro ?", QMessageBox::Yes | QMessageBox::No);

    /*
    bool ok = false;

    QString pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo ?", QLineEdit::Normal, QString(), &ok);



    if (ok && !pseudo.isEmpty())

    {

        QMessageBox::information(this, "Pseudo", "Bonjour " + pseudo + ", ça va ?");

    }

    else

    {

        QMessageBox::critical(this, "Pseudo", "Vous n'avez pas voulu donner votre nom… snif.");

    }
*/

/*
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");

    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
*/









}
