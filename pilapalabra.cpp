#include "pilapalabra.h"
#include <QDebug>

bool PilaPalabra::vacia(){
    return tope==0;
}
void PilaPalabra::setPalabra(QString p){
    while (!vacia()) {
        qDebug()<<extraer();
    }
    for(int i=p.length()-1;i>=0;i--){
        Caracter* aux=new Caracter();
        aux->setValor(QString(p[i]));
        aux->sig=tope;
        tope=aux;
    }
}
QString PilaPalabra::extraer(){
    QString s="none";
    if(!vacia()){
        Caracter* aux=tope;
        s=tope->getvalor();
        tope=tope->sig;
        delete(aux);
    }
    return s;
}
