#ifndef LISTAESTADOS_H
#define LISTAESTADOS_H
#include <QString>
#include <QHash>

class ListaEstados{
private:
    class Estado{
        private:
            QString etiqueta;//Guarda el nombre del estado, por ejemplo "q0"
        public:
            Estado *sig;//puntero al estado siguiente EN LA LISTA
            bool es_final;//true: es estado final, false: lo contrario
            bool es_inicial;//true: es estado inicial, false: lo contrario
            QHash transiciones;//Hash que guarda las transiciones del estado representado con otros
    };
    Estado *inicio;
public:
    ListaEstados(){inicio=0;}
    void agregarEstado(QString);//Recibe el nombre del nuevo estado y lo agrega a la lista enlazada
    void quitarEstado(QString);//Recibe el nombre del estado a eliminar y en caso de que se encuentre, se elimina
};

#endif // LISTAESTADOS_H
