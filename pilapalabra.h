#ifndef PILAPALABRA_H
#define PILAPALABRA_H
#include <QString>

class PilaPalabra{
private:
    class Caracter{//guarda un caracter de la palabra que almacena la pila
        private:
            QString valor;//guarda el valor en QString del caracter representado
        public:
            Caracter *sig;//puntero al siguiente nodo
            QString valor();//devuelve el valor representado
            Caracter(){sig=0;}
    };
    Caracter *tope;//puntero al tope de la pila

public:
    PilaPalabra(){tope=0;}
    bool vacia();//devuelve true si la pila está vacía, false si no
    QString extraer();//Extrae el tope de la pila y retorna el caracter que almacenaba
    void setPalabra(QString);//Recibe una palabra y la ingresa en la pila (en caso de que contenga alguna palabra anterior, es vaciada primero)
};

#endif // PILAPALABRA_H
