#include "listaestadosfinales.h"

#include <QDebug>
void ListaEstadosFinales::agregar(QString n){
    Estado* e=new Estado();
    e->nombre=n;
    Estado* aux=inicio;
    if(aux==0){inicio=e;}
    else{
        while(aux->sig){
            aux=aux->sig;
        }
        aux->sig=e;
    }
}

void ListaEstadosFinales::quitar(QString n){
    if(inicio->nombre==n){
        Estado*aux=inicio;
        inicio=inicio->sig;
        delete(aux);
    }else{
        Estado* aux=inicio->sig;
        Estado* anterior=inicio;
        bool b=false;
        while(aux){
            if(aux->nombre==n){
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
}

bool ListaEstadosFinales::existe(QString n){
    bool existe=false;
    Estado* aux=inicio;
    while(aux){
        if(aux->nombre==n){
            existe=true;
            break;
        }
        aux=aux->sig;
    }
    return existe;
}

void ListaEstadosFinales::despliega(void){
    Estado* aux=inicio;
    qDebug()<<"************";
    while(aux){
        qDebug()<<aux->nombre;
        aux=aux->sig;
    }
}
