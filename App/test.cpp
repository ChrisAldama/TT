#include "test.h"
#include "parser.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include <QStringList>

static const QStringList files = QStringList()
        << ":/p_test.olinki"
        << ":/p_test_sino.olinki";

Test::Test()
{

}

bool Test::progam(const QString &filename)
{
    QFile prog(filename);
    prog.open(QFile::ReadOnly);
    QString json = prog.readAll();
    prog.close();
    Parser parser;
    parser.load(json, false);
    while(parser.state() == Parser::RUNNING){
        parser.tick();
    }
    QString r = parser.getSimbols();
    qDebug() << r;
    return true;
}

bool Test::test()
{
    bool res = true;
    for(const QString &f : files){
        res |= progam(f);
    }

    return res;
}

