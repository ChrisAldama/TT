#include<QApplication>
#include<QString>
#include<QDebug>
#include<iostream>
#include"mainwindow.h"
#include "parser.h"

//#define TEST

#ifdef TEST
#include "test.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Test test;
    QTimer timer;
    timer.connect(&timer, &QTimer::timeout,
                  [&](){
        test.test();
        app.exit();

    });
    timer.start(0);
    return app.exec();
}

#else

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    Parser parser;
    w.loadPage();
    w.registerObjectInJs("parser", &parser);

    w.show();
    return app.exec();
}

#endif

