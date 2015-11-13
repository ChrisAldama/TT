#include "variable.h"
#include <sstream>
#include <math.h>
#include <algorithm>
#include <iostream>

Variable::Variable(Variable::Tipo t):
    m_tipo(t)
{

}

Variable::Variable(double val):
    m_tipo(Numerico)
{
    data.numerico = val;
}

Variable::Variable(const std::string &val):
    m_tipo(Cadena)
{
    data.cadena = val;
}

Variable::Variable(const char *val):
    m_tipo(Cadena)
{
    data.cadena = std::string(val);
}

Variable::Variable(const bool val):
    m_tipo(Logico)
{
    data.logico = val;
}

Variable::Variable(const Valor &val, Variable::Tipo t):
    m_tipo(t),
    data(val)
{

}

Variable::~Variable()
{
}

Variable Variable::suma(const Variable &v) const
{
    if(m_tipo == Cadena || v.m_tipo == Cadena){
        return valorString() + v.valorString();
    }

    switch(m_tipo){
    case Numerico:
        return Variable(valorDouble() + v.valorDouble());

    case Logico:
        return Variable(bool(valorBool() || v.valorBool()));

    case SinTipo:
    default:
        break;
    }

    return Variable();
}

Variable Variable::resta(const Variable &v) const
{
    switch(mi_tipo()){
    case Numerico:
    case Logico:
        return Variable(valorDouble() - v.valorDouble());
    case Cadena:
    {
        std::string str = valorString();
        std::string str2 = v.valorString();
        size_t pos = str.find(str2);
        if(pos){
            std::string left = str.substr(0,pos);
            std::string right = str.substr(pos + str2.size(), str.size());
            return  Variable(left + right);
        }
        break;
    }
    case SinTipo:
    default:
        break;

    }

    return Variable();
}

Variable Variable::multiplicacion(const Variable &v) const
{
    if(m_tipo == Cadena || v.m_tipo == Cadena){

        std::string strOr;
        std::string strFin;
        unsigned times;

        if(m_tipo == Cadena){
            strOr = valorString();
            times = fabs(v.valorDouble());
        }
        else {
            strOr = v.valorString();
            times = fabs(valorDouble());
        }

        for(unsigned i = 0; i < times; ++i){
            strFin += strOr;
        }
        return Variable(strFin);
    }
    switch (m_tipo){
    case Numerico:
        return Variable(valorDouble() * v.valorDouble());
    case Logico:
        return Variable(valorBool() && v.valorBool());
    case SinTipo:
    default:
        break;

    }
    return Variable();
}

Variable Variable::division(const Variable &v) const
{
    switch (m_tipo) {
    case Numerico:
    {
        double div = v.valorDouble();
        if(div == 0){
            return Variable();
        }
        return Variable(valorDouble() / div);
    }
    case Logico:
    case Cadena:
    case SinTipo:
    default:
        break;
    }
    return Variable();
}

Variable Variable::modulo(const Variable &v) const
{
    switch (m_tipo) {
    case Numerico:
    {
        double div = v.valorDouble();
        if(div == 0){
            return Variable();
        }
        return Variable(double(int(valorDouble()) % int(div)));
    }
    case Logico:
    case Cadena:
    case SinTipo:
    default:
        break;
    }
    return Variable();

}

Variable Variable::mayor_que(const Variable &v) const
{
    return Variable(magnitud().valorDouble() > v.magnitud().valorDouble());

}

Variable Variable::mayor_igual_que(const Variable &v) const
{
    return Variable(magnitud().valorDouble() >= v.magnitud().valorDouble());
}

Variable Variable::menor_que(const Variable &v) const
{
    return Variable(magnitud().valorDouble() < v.magnitud().valorDouble());
}

Variable Variable::menor_igual_que(const Variable &v) const
{
    return Variable(magnitud().valorDouble() <= v.magnitud().valorDouble());
}

Variable Variable::igual_que(const Variable &v) const
{
    return Variable(magnitud().valorDouble() == v.magnitud().valorDouble());
}

Variable Variable::diferente_que(const Variable &v) const
{
    return Variable(magnitud().valorDouble() != v.magnitud().valorDouble());
}

Variable Variable::magnitud() const
{
    switch (m_tipo) {
    case Numerico:
    case Logico:
        return Variable(valorDouble());
    case Cadena:
        return Variable(double(valorString().length()));

    case SinTipo:
    default:
        break;
    }

    return Variable(double(0));
}

Variable Variable::inverso() const
{
    switch (m_tipo) {
    case Numerico:
        return Variable(-valorDouble());
    case Cadena:
    {
        std::string str = valorString();
        std::reverse(str.begin(), str.end());
        return Variable(str);
    }
    case Logico:
        return Variable(!valorBool());
    case SinTipo:
    default:
        break;
    }
    return Variable();
}

void Variable::imprimir() const
{
    if(m_tipo == Cadena){        
        std::cout << "\"" << valorString() << "\"" << std::endl; 
    }
    else {
        std::cout << valorString() << std::endl; 
    }
}

Variable Variable::comoTipo(Variable::Tipo t)
{
    switch (t) {
    case Numerico:
        return Variable(valorDouble());
    case Cadena:
        return Variable(valorString());
    case Logico:
        return Variable(valorBool());
    case SinTipo:
    default:
        break;
    }
    return Variable(SinTipo);
}

double Variable::valorDouble() const
{
    switch (m_tipo) {
    case Numerico:
        return data.numerico;
    case Cadena:
    {
        const std::string &str = data.cadena;
        return std::stod(str);
    }
    case Logico:
    {
        bool val = data.logico;
        return double(val);
    }
    case SinTipo:
    default:
        break;
    }

    return 0;
}

std::string Variable::valorString() const
{
    switch (m_tipo) {
    case Numerico:
    {
        double valor = data.numerico;
        std::ostringstream strs;
        strs << valor;
        return strs.str();
    }
    case Cadena:
        return data.cadena;

    case Logico:
    {
        bool valor = data.logico;
        if(valor == true){
            return std::string("Verdadero");
        }
        else {
            return std::string("Falso");
        }
    }
    case SinTipo:
    default:
        break;
    }
    return std::string();
}

bool Variable::valorBool() const
{
    if(m_tipo == Cadena){
        return data.cadena == std::string("Verdadero");
    }
    return bool(magnitud().valorDouble());
}

Variable Variable::operacionPorNombre(const std::string &op, const Variable &v)
{
    if(op == "+"){
        return this->suma(v);
    }
    if(op == "-"){
        return this->resta(v);
    }
    if(op == "*"){
        return this->multiplicacion(v);
    }
    if(op == "/"){
        return this->division(v);
    }
    if(op == "%"){
        return this->modulo(v);
    }
    if(op == ">"){
        return this->mayor_que(v);
    }
    if(op == ">="){
        return this->mayor_igual_que(v);
    }
    if(op == "<"){
        return this->menor_que(v);
    }
    if(op == "<="){
        return this->menor_igual_que(v);
    }
    if(op == "=="){
        return this->igual_que(v);
    }
    if(op == "!="){
        return this->diferente_que(v);
    }
    if(op == "!"){
        return this->inverso();
    }
    return Variable();

}
