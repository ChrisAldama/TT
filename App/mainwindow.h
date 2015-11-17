#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyReleaseEvent(QKeyEvent *ev);


public slots:
    void loadPage();
    void registerObjectInJs(const QString &name, QObject *obj);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
