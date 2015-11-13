#ifndef TABLAVARIABLES_H
#define TABLAVARIABLES_H

#include "variable.h"
#include <string>
#include <map>

class TablaVariables
{
public:
    TablaVariables();

    void crearVariable(const std::string &nombre, const Valor &v, const Variable::Tipo &tipo);
    void actualizar(const std::string &nombre, const Valor &v, const Variable::Tipo &tipo);
    void actuliazaCrea(const std::string &nombre, const Variable &var);
    Variable remover(const std::string &nombre);
    Variable busca(const std::string &nombre);
    Variable busca(const std::string &nombre, bool &exito);

    std::map<std::string, Variable> raw();

private:
    std::map<std::string, Variable> misVariables;

};

#endif // TABLAVARIABLES_H
