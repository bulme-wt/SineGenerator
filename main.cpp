#include "mainwindow.h"
#include "sinedataproducer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SineDataProducer sine_producer;
    MainWindow w{sine_producer};
    w.show();
    return a.exec();
}
