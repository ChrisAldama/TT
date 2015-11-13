#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>

class Exp
{
    enum ExpType{
        Matematica,
    };

    virtual void throwExp(ExpType e) = 0;
};


struct Valor {
 std::string cadena;
 double numerico;
 bool logico;
};

class Variable {
public:
    enum Tipo {
        Numerico,
        Cadena,
        Logico,
        SinTipo
    };
    explicit Variable(Tipo t = SinTipo);
    Variable(double val);
    Variable(const std::string &val);
    Variable(const char *val);
    Variable(const bool val);
    Variable(const Valor &val, Tipo t);
     ~Variable();

    Tipo mi_tipo() const {return m_tipo;}
     Variable suma(const Variable &v) const;
     Variable resta(const Variable &v) const;
     Variable multiplicacion(const Variable &v) const;
     Variable division(const Variable &v) const;
     Variable modulo(const Variable &v) const;

     Variable mayor_que(const Variable &v) const;
     Variable mayor_igual_que(const Variable &v) const;
     Variable menor_que(const Variable &v) const;
     Variable menor_igual_que(const Variable &v) const;
     Variable igual_que(const Variable &v) const;
     Variable diferente_que(const Variable &v) const;
     Variable magnitud() const;
     Variable inverso() const;
     void imprimir() const;

    Variable comoTipo(Tipo t);
    double valorDouble() const;
    std::string valorString() const ;
    bool valorBool() const;

    Variable operator +(const Variable &v) const { return suma(v);}
    Variable operator -(const Variable &v) const { return resta(v);}
    Variable operator *(const Variable &v) const { return multiplicacion(v);}
    Variable operator /(const Variable &v) const { return division(v);}
    Variable operator %(const Variable &v) const { return modulo(v);}
    Variable operator >(const Variable &v) const { return mayor_que(v);}
    Variable operator >=(const Variable &v) const { return mayor_igual_que(v);}
    Variable operator <(const Variable &v) const { return menor_que(v);}
    Variable operator <=(const Variable &v) const {return menor_igual_que(v);}
    Variable operator == (const Variable &v) const { return igual_que(v);}
    Variable operator != (const Variable &v) const { return diferente_que(v);}
    Variable operator !() const { return inverso();}
    Variable operacionPorNombre(const std::string &op, const Variable &v = Variable());


protected:
  Tipo m_tipo;
  Valor data;
  static Exp *exp;
};

#endif
