#ifndef LISTATRANSICIONES_H
#define LISTATRANSICIONES_H

#include <QString>

class ListaTransiciones{
protected:
    class Transicion{
       protected:
       public:
        Transicion *sig;
        QString origen,simbolo,detino;
        Transicion(){
            sig=0;
        }

    };
    Transicion* inicio=0;
public:
    ListaTransiciones(void){inicio=0;}
    bool agregar(QString e1,QString s,QString e2);/*agrega una transicion donde:
                                                    e1:Estado de origen de la transicion
                                                    s:símbolo de la transición
                                                    e2:Estado de destino de la transicion
                            Devuelve true si la transición se agregó, false si no
                                                    */
    void quitar(QString,QString,QString);//Elimina una transicion con los mismos parametros que el metodo "agregar".
    QString getDestino(QString e,QString s);//devuelve un QString con el nombre del estado de destino en la transicion desde el estado "e" con el simbolo "s"
    //En caso de  no existir la transicion, devuelve "none"
    bool existe(QString e1,QString s,QString e2);//devuelve true si la transicion ocn los datos recibidos existe en la lista, false si no

    void despliega(void);//imprime en consola las transiciones
};

#endif // LISTATRANSICIONES_H
