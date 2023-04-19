#include "mainwindow.h"
#include <QApplication>
#include "ui_mainwindow.h"
#include <QDir>
#include <QSystemTrayIcon>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString str1 = QDir::toNativeSeparators(QCoreApplication::applicationDirPath());
    QByteArray ba = str1.toLocal8Bit();
    char *c_str2 = ba.data();
    strcat(c_str2, "\\icon.png");
    a.setWindowIcon(QIcon(c_str2));
    MainWindow w;

    return a.exec();
}
