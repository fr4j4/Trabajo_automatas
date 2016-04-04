#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    trans=new ListaTransiciones();
    pal=new PilaPalabra();
    eInicial="none";
    ui->label_eInicial->setText("?");
    /*codigo para probar la pila de palabra
    qDebug()<<"pila de palabra vacia?: "<<pal->vacia();
    pal->setPalabra("Hola");
    qDebug()<<"agregada palabra: Hola";
    qDebug()<<"pila de palabra vacia?: "<<pal->vacia();
    pal->setPalabra("Chao");
    qDebug()<<"agregada palabra: Chao";
    */

    /*CODIGO PARA PROBAR SI FUNCIONA LA LISTA DE TRANSICIONES
    trans->agregar("q0","1","q1");
    trans->agregar("q1","1","q2");
    trans->agregar("q2","1","q3");
    trans->agregar("q3","1","q4");
    trans->agregar("q4","1","q5");
    trans->despliega();
    trans->quitar("q3","1","q4");
    qDebug()<<"Eliminada (q3,1,q4)";
    trans->despliega();
    qDebug()<<"destino de q1 con 1: "<<trans->getDestino("q1","1");
    */
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_boton_agregar_clicked(){
    if(ui->in_simbolo->text().length()==1&&ui->in_origen->text().length()>0&&ui->in_destino->text().length()>0){
        trans->agregar(ui->in_origen->text(),ui->in_simbolo->text(),ui->in_destino->text());
    }
}

void MainWindow::on_boton_eliminar_select_clicked(){
    qDebug()<<"transiciones:";
    trans->despliega();
}
