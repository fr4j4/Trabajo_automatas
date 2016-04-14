#ifndef LISTAESTADOSFINALES_H
#define LISTAESTADOSFINALES_H

#include <QString>

class ListaEstadosFinales{
protected:
    class Estado{
       public:
        Estado *sig;
        QString nombre;
        Estado(){//constructor de la "clase interna"
            sig=0;
        }

    };
    Estado* inicio;
public:
    ListaEstadosFinales(){inicio=0;}//constructor de la clase
    bool agregar(QString n);//recibe el nombre de un estado y lo agrega a la lista, en caso de que el estado ya este agregado
                //simplemente no se agrega. Devuelve true si el estado se agregó, false si no.
    void quitar(QString n);//quita un estado de la lista
    bool existe(QString n);//devuelve true si el estado de nombre "n" está en la lista, false si no.
    void despliega(void);//imprime la lista, pero es sólo con fines de depuración del programa. no se usa para nada en la version final
    bool vacia(void){return inicio==0;}//retorna true si la lista está vacía, false si no.
};

#endif // LISTAESTADOSFINALES_H
