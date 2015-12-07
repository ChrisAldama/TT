#include<QApplication>
#include<QString>
#include<QDebug>
#include<iostream>
#include <memory>
#include <assert.h>
#include"mainwindow.h"
#include "filemanager.h"
#include "parser.h"
#include "commserial.h"

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
    FileManager file(&w);
    std::unique_ptr<CommSerial> c(new CommSerial);
    c->open();
    Parser parser(c.get());

    w.loadPage();
    w.registerObjectInJs("parser", &parser);
    w.registerObjectInJs("file", &file);

    w.show();
    return app.exec();
}

#endif

