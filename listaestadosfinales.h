#ifndef LISTAESTADOSFINALES_H
#define LISTAESTADOSFINALES_H

#include <QString>

class ListaEstadosFinales{
protected:
    class Estado{
       public:
        Estado *sig;
        QString nombre;
        Estado(){
            sig=0;
        }

    };
    Estado* inicio;
public:
    ListaEstadosFinales(){inicio=0;}
    void agregar(QString n);
    void quitar(QString n);
    bool existe(QString n);
    void despliega(void);
    bool vacia(void){return inicio==0;}
};

#endif // LISTAESTADOSFINALES_H
