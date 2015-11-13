#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QTimer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QMap>

#include "tablavariables.h"
#include "variable.h"
#include <QJsonArray>
#include <QList>

using ProgramCounter = int;

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);
    Q_INVOKABLE bool load(const QString &json, bool async = true);
    Q_INVOKABLE void stop();

    enum Types {
        ASIG,
        EXPROP,
        EXPRLOG,
        LOOP,
        WHILE,
        IF,
        IFELSE,
        MESS,
        BEGIN,
        END,
        PROGRAM,
        NO_TYPE

    };

    enum State {
        STOPPED,
        RUNNING,
        FINISHED
    };

    struct BPoint{
        QJsonArray ctx;     //Contexto actual
        Parser::Types type; //Tipo de Contexto
        ProgramCounter ins; //Punto de entrada de proximo ctx
        int loop_counter = 0;
        int loop_ceiling = 0;
        std::string op1_name;
        std::string op2_name;
        std::string op_name;

    };

    State state();
    QString getSimbols();
    Variable varGuessingType(const QString &v);
    Variable varGuessingType(const std::string &v);


signals:
    void message(const QString &m);

public slots:
       void tick();
private:
    QTimer timer;
    QMap<QString, Types> types;
    TablaVariables simbols;
    ProgramCounter pc;
    QList<BPoint> stack;
    State st;
private slots:


};



#endif // PARSER_H
