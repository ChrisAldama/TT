#include<QApplication>
#include<QString>
#include<QDebug>
#include<iostream>
#include"mainwindow.h"
#include"channel.h"
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
    auto startChannel = Channel::makeChannel();
    Channel::WebChannel webChannel = startChannel();
    webChannel.channel->registerObject("parser", &parser);

    std::cout << "WebChannel: " << webChannel.url.toStdString() << std::endl;

    w.show();
    return app.exec();
}

#endif

