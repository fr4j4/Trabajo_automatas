#include "listatransiciones.h"
#include <QDebug>

void ListaTransiciones::agregar(QString e1, QString s, QString e2){
    if(getDestino(e1,s)=="none"){//agrega sólo si no existe transicion desde e1 con el símbolo s
        Transicion *t=new Transicion();
        t->origen=e1;
        t->simbolo=s;
        t->detino=e2;
        Transicion* aux=inicio;
        if(aux==0){inicio=t;}
        else{
            while(aux->sig){
                aux=aux->sig;
            }
            aux->sig=t;
        }
    }
}
QString ListaTransiciones::getDestino(QString e, QString s){
    QString out="none";
    Transicion *aux=inicio;
    while (aux) {
        if(aux->origen==e&&aux->simbolo==s){
            out=aux->detino;
            break;
        }
        aux=aux->sig;
    }
    return out;
}

void ListaTransiciones::quitar(QString origen, QString s, QString destino){
    Transicion* aux=inicio->sig;
    Transicion* anterior=inicio;
    bool b=false;
    while(aux){
        if(aux->origen==origen&&aux->simbolo==s&&aux->detino==destino){
            b=true;
            break;
        }
        anterior=aux;
        aux=aux->sig;
    }
    if(b){
        anterior->sig=aux->sig;
        delete(aux);
    }
}

void ListaTransiciones::despliega(void){
    Transicion* aux=inicio;
    while(aux){
        qDebug()<<aux->origen<<"--"<<aux->simbolo<<"-->"<<aux->detino;
        aux=aux->sig;
    }
}
