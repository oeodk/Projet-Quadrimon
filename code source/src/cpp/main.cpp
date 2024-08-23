#include "widget/quadrimonthegame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuadrimonTheGame w;
    w.show();
    return a.exec();
}
