#include "Mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Xant_Nero");
    QCoreApplication::setApplicationName("Roads Modelling");
    QTranslator trans;
    trans.load("translations/russian.qm");
    a.installTranslator(&trans);
    MainWindow w;
    w.show();
//    QProcess* model = new QProcess(&w);
//    QStringList l = QStringList("/home/dmitry/Courseproject-Modelling-road-traffic/test.mdl");
//    model->setProgram("/home/dmitry/Courseproject-Modelling-road-traffic/main");
//    //model->setArguments(l);
//    model->start();
    return a.exec();
}
