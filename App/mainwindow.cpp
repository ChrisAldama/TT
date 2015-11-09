#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPage(const QString &channel)
{
    QUrl url("qrc:/Html/index.html");
    QString query = "webChannelBaseUrl=" + channel;
    url.setQuery(query);
    QString url_s = url.toString();
    qDebug() << url_s;
    ui->webView->setUrl(url);
}


