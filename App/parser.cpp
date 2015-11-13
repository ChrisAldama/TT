#include "parser.h"

Parser::Parser(QObject *parent) : QObject(parent),
    st(STOPPED)
{
    connect(&timer, &QTimer::timeout,
            this, &Parser::tick);
    types["asig"] = ASIG;
    types["expr-op"] = EXPROP;
    types["expr-log"] = EXPRLOG;
    types["loop"] = LOOP;
    types["while"] = WHILE;
    types["if"] = IF;
    types["ifelse"] = IFELSE;
    types["begin"] = BEGIN;
    types["end"] = END;
    types["no-type"] = NO_TYPE;
    types["mess"] = MESS;

}

bool Parser::load(const QString &json, bool async)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(json.toLocal8Bit(), &error);
    if(error.error != QJsonParseError::NoError){
        return false;
    }

    auto program = document.array();
    stack.clear();
    BPoint begin;
    begin.ctx = program;
    begin.type = PROGRAM;
    begin.ins = 0;
    pc = begin.ins;

    stack.push_back(begin);
    if(async){
        timer.start(1);
    }
    st = RUNNING;
    return true;
}

void Parser::stop()
{
    st = STOPPED;
    timer.stop();
}

Parser::State Parser::state()
{
    return st;
}

QString Parser::getSimbols()
{
    QString result;
    auto sim = simbols.raw();
    for(auto it = sim.begin(); it != sim.end(); ++it){
        result +=
                QString::fromStdString(it->first) +
                " <= " +
                QString::fromStdString(it->second.valorString()) +
                "\n";
    }
    return result;
}

Variable Parser::varGuessingType(const QString &v)
{
    bool isNumber = false;
    double number = v.toDouble(&isNumber);
    if(isNumber){
        return Variable(number);
    }

    if(v.toLower() == "verdadero"){
        return Variable(true);
    }
    if(v.toLower() == "falso"){
        return Variable(false);
    }

    return Variable(v.toStdString());
}

Variable Parser::varGuessingType(const std::string &v)
{
    return varGuessingType(QString::fromStdString(v));
}

void Parser::tick()
{
    auto &last = stack.last();
    QJsonObject inst = last.ctx.at(pc).toObject();
    QString t_string = inst.value("type").toString("no-type");
    Parser::Types type = types[t_string];

    switch (type) {
    case ASIG:{
        QJsonValue var_jvalue = inst.value("var");
        QJsonValue value_jvalue = inst.value("value");
        QString var_name = var_jvalue.toString("A");
        QString var_value = value_jvalue.toString("0");
        Variable var = simbols.busca(var_value.toStdString());
        if(var.mi_tipo() == Variable::SinTipo){
            var = varGuessingType(var_value);
        }
        simbols.actuliazaCrea(var_name.toStdString(),
                              var);

    }
    break;

    case EXPROP:{
        QJsonValue var_jvalue =inst.value("var");
        QJsonValue op1_jvalue = inst.value("op1");
        QJsonValue op_jvalue = inst.value("operation");
        QJsonValue op2_jvalue = inst.value("op2");

        auto var_name = var_jvalue.toString("A").toStdString();

        auto op = op_jvalue.toString().toStdString();
        auto op1_name = op1_jvalue.toString("0").toStdString();
        Variable op1 = simbols.busca(op1_name);
        if(op1.mi_tipo() == Variable::SinTipo){
            op1 = varGuessingType(op1_name);
        }
        auto op2_name = op2_jvalue.toString("0").toStdString();
        Variable op2 = simbols.busca(op2_name);
        if(op2.mi_tipo() == Variable::SinTipo){
            op2 = varGuessingType(op2_name);
        }

        Variable var = op1.operacionPorNombre(op, op2);
        simbols.actuliazaCrea(var_name, var);
    }
    break;

    case LOOP:{
        QString times_s = inst.value("times").toString("0");
        int times = times_s.toInt();
        QJsonArray child= inst.value("children").toArray();
        BPoint ctx;
        ctx.type = LOOP;
        ctx.ctx = child;
        ctx.ins = pc;
        ctx.loop_ceiling = times;
        ctx.loop_counter = 0;
        pc = -1;

        stack.push_back(ctx);

    }
    break;

    case WHILE:{
        QJsonArray child = inst.value("children").toArray();

        QJsonObject cond_o = inst.value("conditional").toObject();
        const auto op1_name = cond_o.value("op1").toString("A").toStdString();
        const auto op_name = cond_o.value("operation").toString("!=").toStdString();
        const auto op2_name = cond_o.value("op2").toString("A").toStdString();
        BPoint ctx;
        ctx.type = WHILE;
        ctx.ctx = child;
        ctx.ins = pc;
        ctx.op1_name = op1_name;
        ctx.op2_name = op2_name;
        ctx.op_name = op_name;
        pc = -1;

        stack.push_back(ctx);

    }
    break;

    case IF:{
        QJsonObject cond_o = inst.value("conditional").toObject();
        auto op1_name = cond_o.value("op1").toString("A").toStdString();
        auto op2_name = cond_o.value("op2").toString("A").toStdString();
        auto op = cond_o.value("operation").toString("==").toStdString();
        QJsonArray childs = inst.value("children").toArray();

        Variable op1 = simbols.busca(op1_name);
        if(op1.mi_tipo() == Variable::SinTipo){
            op1 = varGuessingType(op1_name);
        }
        Variable op2 = simbols.busca(op2_name);
        if(op2.mi_tipo() == Variable::SinTipo){
            op2 = varGuessingType(op2_name);
        }
        Variable res = op1.operacionPorNombre(op, op2);
        if(res.valorBool()){
            BPoint ctx;
            ctx.type = IF;
            ctx.ins = pc;
            ctx.ctx = childs;
            pc = -1;

            stack.push_back(ctx);
        }
    }
    break;
    case IFELSE:{
        QJsonObject cond_o = inst.value("conditional1").toObject();
        auto op1_name = cond_o.value("op1").toString("A").toStdString();
        auto op2_name = cond_o.value("op2").toString("A").toStdString();
        auto op = cond_o.value("operation").toString("==").toStdString();

        Variable op1 = simbols.busca(op1_name);
        if(op1.mi_tipo() == Variable::SinTipo){
            op1 = varGuessingType(op1_name);
        }
        Variable op2 = simbols.busca(op2_name);
        if(op2.mi_tipo() == Variable::SinTipo){
            op2 = varGuessingType(op2_name);
        }
        Variable res = op1.operacionPorNombre(op, op2);
        QJsonArray child;
        BPoint ctx;
        ctx.type = IFELSE;
        ctx.ins = pc;
        if(res.valorBool()){
            child = inst.value("children1").toArray();

        }
        else{
            child = inst.value("children2").toArray();

        }
        pc = -1;
        ctx.ctx = child;
        stack.push_back(ctx);

    }
    break;

    case MESS:{
        QString m = inst.value("message").toString("Hola mundo");
        Variable var = simbols.busca(m.toStdString());
        if(var.mi_tipo() == Variable::SinTipo){
            var = varGuessingType(m);
        }
        m = QString::fromStdString(var.valorString());
        message(m);
    }
    break;

    case BEGIN:
    case END:
    case EXPRLOG:
    case NO_TYPE:
    default:
        break;
    }

    auto &ctx = stack.last();
    pc++;
    if(ctx.type == LOOP){
        if(pc >= ctx.ctx.size()){
            ctx.loop_counter++;
            if(ctx.loop_counter >= ctx.loop_ceiling){
                pc = ctx.ins + 1;
                stack.pop_back();
            }
            else{
                pc = 0;
            }
        }
    }
    else if(ctx.type == WHILE){
        if(pc >= ctx.ctx.size()){
            pc = 0;
        }

        const auto &op1_name = ctx.op1_name;
        const auto &op_name = ctx.op_name;
        const auto &op2_name = ctx.op2_name;

        Variable op1 = simbols.busca(op1_name);
        if(op1.mi_tipo() == Variable::SinTipo){
            op1 = varGuessingType(op1_name);
        }
        Variable op2 = simbols.busca(op2_name);
        if(op2.mi_tipo() == Variable::SinTipo){
            op2 = varGuessingType(op2_name);
        }

        Variable res = op1.operacionPorNombre(op_name, op2);
        if(res.valorBool() == false){
            pc = ctx.ins + 1;
            stack.pop_back();
        }
    }
    else if(ctx.type == IF || ctx.type == IFELSE){
        if(pc >= ctx.ctx.size()){
            pc = ctx.ins + 1;
            stack.pop_back();
        }

    }
    else if(ctx.type == PROGRAM){
        if(pc >= ctx.ctx.size()){
            stop();
            st = FINISHED;
        }
    }

}

//poner break;

