#include<QApplication>
#include<QString>
#include<QDebug>
#include<iostream>
#include <memory>
#include"mainwindow.h"
#include "parser.h"
#include "comm.h"

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
    std::unique_ptr<Comm> c(new Comm);
    Parser parser(c.get());
    w.loadPage();
    w.registerObjectInJs("parser", &parser);

    w.show();
    return app.exec();
}

#endif

