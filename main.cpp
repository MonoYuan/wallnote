#include "wallnote.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    Wallnote w;
    w.show();
    return a.exec();
}
