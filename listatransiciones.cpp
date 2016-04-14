#include "listatransiciones.h"
#include <QDebug>

bool ListaTransiciones::agregar(QString e1, QString s, QString e2){
   bool b=false;
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
        b=true;
    }
    return b;
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
    Transicion*aux=inicio;
    if(inicio->origen==origen&&inicio->detino==destino&&inicio->simbolo==s){
        inicio=inicio->sig;
        delete(aux);
    }else{
        while(aux->sig){
            if(aux->origen==origen&&aux->detino==destino&&aux->simbolo==s){
                Transicion*aux2=aux->sig;
                aux->sig=aux->sig->sig;
                qDebug()<<"elimada transicion: "<<aux->origen<<" - "<<aux->simbolo<<" -> "<<aux->detino;
                delete(aux2);
                break;
            }else{
                aux=aux->sig;
            }
        }
    }
}

void ListaTransiciones::despliega(void){
    Transicion* aux=inicio;
    while(aux){
        qDebug()<<aux->origen<<"--"<<aux->simbolo<<"-->"<<aux->detino;
        aux=aux->sig;
    }
}

bool ListaTransiciones::existe(QString e1, QString s, QString e2){
    bool existe=false;
    Transicion* aux=inicio;
    while(aux){
        if(aux->origen==e1&&aux->simbolo==s&&aux->detino==e2){
            existe=true;
            break;
        }
        aux=aux->sig;
    }
    return existe;
}
