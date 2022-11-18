#include "mw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MW w;
    QFile file(":/QTDark.stylesheet");
    file.open(QIODevice::ReadOnly);

    w.setStyleSheet(QString::fromUtf8(file.readAll()));
    w.show();
    return a.exec();
}
