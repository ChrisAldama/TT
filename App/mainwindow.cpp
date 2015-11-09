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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPage(const QString &s, const QString &path)
{
    QFile file(s);
    qDebug() << path;
    file.open(QFile::ReadOnly);
    QString content = file.readAll();
    ui->webView->setHtml(content, QUrl(path));

}
