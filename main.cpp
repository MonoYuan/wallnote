#include "wallnote.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    //传入true, 确认这个是主窗口
    Wallnote w(true,0,nullptr);
    w.setWindowIcon(QIcon(":/images/icon.ico"));
    w.show();
    return a.exec();
}
