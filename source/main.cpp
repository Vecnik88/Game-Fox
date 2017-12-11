#include <QApplication>
#include "include/mainwindow.h"

int main(int argc, char *argv[])
{
    const QString type = "fox";
    const QString path = "/home/anton/qt_project/red/image/fox.png";

    QApplication a(argc, argv);

    MainWindow main(type, path);
    main.show();

    return a.exec();
}
