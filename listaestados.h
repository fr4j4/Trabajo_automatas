#ifndef LISTAESTADOS_H
#define LISTAESTADOS_H
#include <QString>
#include <QHash>
#include <QStringList>

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

    void agregarTransicion(QString e1,QString s,QString e2);//busca el estado "e1", y agrega la trsncicion en el hash que contiene con el símbolo "s" y el estado "e2"
    void quitarTransiciones(QString e);//Busca ele stado "e" dentro de la lista y elimina todas las transiciones relacionadas con ese estado

    bool existeEstado(QString e);//true: el estado e está en la lista. false, si no.
    bool inicial(QString e);//true: el estado e es estado inicial. false, si no.
    bool final(QString e);//true: el estado e es estado final. false, si no.
    bool inicialYFinal();//true: Hay un estado inicial y al menos un estado final en la lista. false, si no.
    QString destino(QString e,QString s);//Devuelve el nombre el estado al que se llega desde e con el simblo s, en caso
    //de que la transición no exista, devuelve "none"

    QStringList getEstados();//Devuelve un qstringlist con los estados presentes en la lista
    void despliega();//imprime en consola la lista enlazada
};

#endif // LISTAESTADOS_H
