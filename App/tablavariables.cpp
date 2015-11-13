#include "tablavariables.h"
#include <utility>


TablaVariables::TablaVariables()
{
}

void TablaVariables::crearVariable(const std::string &nombre, const Valor &v, const Variable::Tipo &tipo)
{
    Variable var;
    switch (tipo) {
    case Variable::Numerico:
        var = Variable(v.numerico);
        break;
    case Variable::Cadena:
        var = Variable(v.cadena);
        break;
    case Variable::Logico:
        var = Variable(v.logico);
        break;
    default:
        break;
    }

    std::pair<std::string, Variable>insertar(nombre, var);
    misVariables.insert(insertar);
}

void TablaVariables::actualizar(const std::string &nombre, const Valor &v, const Variable::Tipo &tipo)
{
    auto var = misVariables.find(nombre);
    bool exito = var != misVariables.end();
    if(exito){
        (*var).second = Variable(v, tipo);
    }
}

void TablaVariables::actuliazaCrea(const std::string &nombre, const Variable &var)
{
    auto vari = misVariables.find(nombre);
    bool exito = vari != misVariables.end();
    if(exito){
        (*vari).second = var;
    }
    else {
        misVariables[nombre] = var;
    }

}

Variable TablaVariables::remover(const std::string &nombre)
{
    Variable result;
    auto var = misVariables.find(nombre);
    bool exito = var != misVariables.end();
    if(exito){
        result = (*var).second;
        misVariables.erase(var);
    }
    return result;

}

Variable TablaVariables::busca(const std::string &nombre)
{
    bool v;
    return busca(nombre, v);
}

Variable TablaVariables::busca(const std::string &nombre, bool &exito)
{
    Variable result;
    auto var = misVariables.find(nombre);
    exito = var != misVariables.end();
    if(exito){
        result = (*var).second;
    }
    return result;
}

std::map<std::string, Variable> TablaVariables::raw()
{
    return misVariables;
}
