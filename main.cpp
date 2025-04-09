#include "controle.h"
#include <QApplication>

Controle *controle;

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned>(time(nullptr)));
    QApplication a(argc, argv);
    controle = new Controle;
    controle->show();
    return a.exec();
}
