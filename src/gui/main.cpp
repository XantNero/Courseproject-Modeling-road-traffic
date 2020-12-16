#include "Mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Xant_Nero");
    QCoreApplication::setApplicationName("Roads Modelling");
    QTranslator ts;
    ts.load("translations/russian.qm");
    app.installTranslator(&ts);
    MainWindow window;
    window.show();
//    QProcess* model = new QProcess(&w);
//    QStringList l = QStringList("/home/dmitry/Courseproject-Modelling-road-traffic/test.mdl");
//    model->setProgram("/home/dmitry/Courseproject-Modelling-road-traffic/main");
//    //model->setArguments(l);
//    model->start();
    return app.exec();
}
