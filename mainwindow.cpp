#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QDebug>
#include <QTableWidgetItem>
#include <QTableWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    trans=new ListaTransiciones();
    finales=new ListaEstadosFinales();
    pal=new PilaPalabra();
    eInicial="none";
    eActual="none";
    ui->labelEstadoInicial->setText("?");
    ui->tabla_transiciones->setColumnCount(3);
    ui->tabla_transiciones->setHorizontalHeaderLabels(QStringList()<<"Origen"<<"Simbolo"<<"Destino");
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

void MainWindow::on_botonSetEstadoInicial_clicked(){
    eInicial=ui->inEstadoInicial->text().trimmed();
    ui->labelEstadoInicial->setText(eInicial);
    ui->inEstadoInicial->setText("");
}

void MainWindow::on_botonAgregarTransiciones_clicked(){
    if(ui->inEstadoFinal->text().trimmed().length()>0&&!finales->existe(ui->inEstadoFinal->text().trimmed())){
        finales->agregar(ui->inEstadoFinal->text());
        ui->listaEstadosFinales->addItem(ui->inEstadoFinal->text());
        ui->inEstadoFinal->setText("");
        ui->listaEstadosFinales->sortItems(Qt::AscendingOrder);
    }
}

void MainWindow::on_botonQuitarEstadoFinal_clicked(){
    if(ui->listaEstadosFinales->selectedItems().length()>0){
        finales->quitar(ui->listaEstadosFinales->selectedItems().at(0)->text());
        qDeleteAll(ui->listaEstadosFinales->selectedItems());
        ui->listaEstadosFinales->sortItems(Qt::AscendingOrder);
    }
}

void MainWindow::on_botonProbarPalabra_clicked(){
    ui->salida->setText("");
    ui->salida2->setStyleSheet("background:transparent;color:black;");
    if(eInicial!="none"&&!finales->vacia()){
        eActual=eInicial;
        QString c="";
        QString ultimoEstado="";
        pal->setPalabra(ui->inPalabra->text());
        qDebug()<<"Palabra ingresada a la pila: "<<ui->inPalabra->text();
        msg("Palabra ingresada a la pila: "+ui->inPalabra->text(),"#00ff00");
        msg("=======] - TEST - [=========","#00ff00");
        qDebug()<<"==========] - TEST - [==============";
        while(!pal->vacia()&&eActual!="none"){
            c=pal->extraer();
            qDebug()<<"Estoy en "<<eActual<<", leo el simbolo "<<c<<"";
            msg("Estoy en "+eActual+", leo el simbolo "+c,"yellow");
            ultimoEstado=eActual;
            eActual=trans->getDestino(eActual,c);
            if(eActual!="none"){
                qDebug()<<"he llegado a "<<eActual<<"\n----------";
                msg("he llegado a "+eActual,"yellow");
            }
        }
        if(pal->vacia()&&finales->existe(eActual)&&eActual!="none"){
            qDebug()<<"Pila vacia y estado "<<eActual<<" es final...\nPalabra Aceptada!.";
            msg("Pila vacia y estado "+eActual+" es final.","blue");
            msg("=> PALABRA ACEPTADA","#00ff00");
            ui->salida2->setText("Palabra\nAceptada");
            ui->salida2->setStyleSheet("background:#00ff00;color:white;");
        }else{
            if(eActual=="none"){
                qDebug()<<"La transicion del estado "<<ultimoEstado<<" con el simbolo "<<c<<"no está definida.";
                msg("La transicion del estado "+ultimoEstado+" con el simbolo "+c+" no está definida.","blue");
            }
            if(!pal->vacia()){
                qDebug()<<"Pila de la palabra no está vacía.";
                msg("Pila de la palabra no está vacía.","blue");
            }
            else if(!finales->existe(eActual)&&eActual!="none"){
                qDebug()<<"Estado "<<eActual<<" no es final.";
                msg("Estado "+eActual+" no es final.","blue");
            }
            qDebug()<<"Palabra Rechazada!!";
            msg("=> Palabra rechazada.","red");
            ui->salida2->setText("Palabra\nRechazada");
            ui->salida2->setStyleSheet("background:#ff0000;color:white;");
        }
        qDebug()<<"==========] - FIN TEST - [==============";
        msg("==========] - FIN TEST - [==============","#00ff00");
    }else if(eInicial=="none"){
        qDebug()<<"Debe establecer un estado inicial.";
        ui->salida2->setText("Debe establecer\nun estado inicial.");
        msg("Debe establecer un estado inicial.","#ff0000");
    }else if(finales->vacia()){
        qDebug()<<"Debe establecer al menos un estado final.";
        ui->salida2->setText("Debe establecer\nal menos un\nestado final.");
        msg("Debe establecer al menos un estado final..","#ff0000");
    }
}

void MainWindow::on_bton_eliminar_todas_clicked(){
    qDebug()<<"transiciones:";
    trans->despliega();
}
void MainWindow::on_boton_agregar_clicked(){
    if(ui->in_simbolo->text().length()==1&&ui->in_origen->text().length()>0&&ui->in_destino->text().length()>0&&!trans->existe(ui->in_origen->text(),ui->in_simbolo->text(),ui->in_destino->text())){
        trans->agregar(ui->in_origen->text(),ui->in_simbolo->text(),ui->in_destino->text());
        QTableWidgetItem * item_origen=new QTableWidgetItem();
        QTableWidgetItem * item_simbolo=new QTableWidgetItem();
        QTableWidgetItem * item_destino=new QTableWidgetItem();
        item_origen->setText(ui->in_origen->text());
        item_simbolo->setText(ui->in_simbolo->text());
        item_destino->setText(ui->in_destino->text());
        ui->tabla_transiciones->insertRow(ui->tabla_transiciones->rowCount());
        ui->tabla_transiciones->setItem(ui->tabla_transiciones->rowCount()-1,0,item_origen);
        ui->tabla_transiciones->setItem(ui->tabla_transiciones->rowCount()-1,1,item_simbolo);
        ui->tabla_transiciones->setItem(ui->tabla_transiciones->rowCount()-1,2,item_destino);
    }
}
void MainWindow::on_boton_eliminar_select_clicked(){
    if(ui->tabla_transiciones->selectedItems().length()>0){
        QString o,s,d;
        o=ui->tabla_transiciones->item(ui->tabla_transiciones->selectedItems().at(0)->row(),0)->text();
        s=ui->tabla_transiciones->item(ui->tabla_transiciones->selectedItems().at(0)->row(),1)->text();
        d=ui->tabla_transiciones->item(ui->tabla_transiciones->selectedItems().at(0)->row(),2)->text();
        if(trans->existe(o,s,d)){
            qDebug()<<o<<"--"<<s<<"-->"<<d;
            trans->quitar(o,s,d);
            ui->tabla_transiciones->removeRow(ui->tabla_transiciones->selectedItems().at(0)->row());
        }
    }
}

void MainWindow::on_in_simbolo_textChanged(const QString &arg1){
    //con esto evito el ingreso de un caracter "blanco" (" ")
    ui->in_simbolo->setText(ui->in_simbolo->text().trimmed().replace(" ",""));
}

void MainWindow::on_in_origen_textChanged(const QString &arg1){
    //con esto evito el ingreso de un caracter "blanco" (" ") y que contenga espacios
    ui->in_origen->setText(ui->in_origen->text().trimmed().replace(" ",""));
}

void MainWindow::on_in_destino_textChanged(const QString &arg1){
    //con esto evito el ingreso de un caracter "blanco" (" ") y que contenga espacios
    ui->in_destino->setText(ui->in_destino->text().trimmed().replace(" ",""));
}
void MainWindow::msg(QString text, QString color){
    if(ui->salida->toPlainText().length()>0){
        ui->salida->setText(ui->salida->toHtml()+"<font color="+color+">"+text+"</font>");
    }else{
        ui->salida->setText("<font color="+color+">"+text+"</font>");
    }
}
