#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<qintptr>("qintptr");
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
