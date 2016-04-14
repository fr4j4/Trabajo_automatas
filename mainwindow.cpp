#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QDebug>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    trans=new ListaTransiciones();//inicializo la lista de transiciones
    finales=new ListaEstadosFinales();//inicializo la lista de estados finales
    pal=new PilaPalabra();//inicializo la pila de la palabra
    eInicial="none";//doy un valor inicial a einicial como "none"
    eActual="none";//lo mismo para eactual
    ui->labelEstadoInicial->setText("?");//texto a mostrar por defecto en el cuadro de estado inicial
    ui->tabla_transiciones->setColumnCount(3);//setear la tabla de transiciones a 3 columnas
    ui->tabla_transiciones->setHorizontalHeaderLabels(QStringList()<<"Origen"<<"Simbolo"<<"Destino");//nombres de las columnas de la tabla de transiciones
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_botonSetEstadoInicial_clicked(){
    //cuando se presione el boton para establecer estado inicial
    QMessageBox msg;//un mensaje para mostrar en caso de errores.
    if(ui->inEstadoInicial->text().trimmed().length()>0&&ui->inEstadoInicial->text().trimmed().toLower()!="none"){
        //si se ha introducido algo  dentro del cuadro de texto que no sean espacios solamente, y si
        //lo que se ha introducido no es "none" se establecerá un estado inicial.
        //none se utiliza internamente y no se puede tomar como estado inicial
        eInicial=ui->inEstadoInicial->text().trimmed();
        ui->labelEstadoInicial->setText(eInicial);
        ui->inEstadoInicial->setText("");
    }else if(ui->inEstadoInicial->text().trimmed().length()==0){
        //en caso de que se haya ingresado un texto vacío, se mostrara un mensaje
        msg.critical(this,"No ha ingresado nada","Debe ingresar un nombre de estado inicial antes de establecer.");
    }else if(ui->inEstadoInicial->text().trimmed().toLower()=="none"){
        //en caso de que se ingrese el texto "none", se mostrará otro mensaje.
        msg.critical(this,"No se admite","El nombre \"none\" está reservado para uso interno dentro del programa.\n"
                                         "Por favor, ingrese otro nombre para el estado inicial.");
        ui->inEstadoInicial->setText("");//se cambia el texto del cuadro de texto a ""
    }
}

void MainWindow::on_botonQuitarEstadoFinal_clicked(){
    //cuando se presione el boton para eliminar un estado final de la lista
    if(ui->listaEstadosFinales->selectedItems().length()>0){
        //si hay algun estado final seleccionado de la lista
        finales->quitar(ui->listaEstadosFinales->selectedItems().at(0)->text());//se quita el estado
        //de la lista enlazadacon el nombre igual al texto seleccionado de la lista
        qDeleteAll(ui->listaEstadosFinales->selectedItems());//elimina visualmente el estado de la lista
        ui->listaEstadosFinales->sortItems(Qt::AscendingOrder);//ordena alfabeticamente los estados en la lista visual
    }
}

void MainWindow::on_botonProbarPalabra_clicked(){
    //cuando el boton de probar palabra se presione
    ui->salida->setText("");//se borra lo que haya escrito en la salida
    ui->salida2->setStyleSheet("background:transparent;color:black;");
    //se pone el fondo color transparente de la salida y el texto color negro
    if(eInicial!="none"&&!finales->vacia()){
        //si se ha establecido previamente un estado inicial y al menos hay un estado final en la lista...
        eActual=eInicial;//eActual va a guardar el nombre de cada estado que nos lleven las transiciones.
        QString c="";//guarda el caracter extraido de la pila para analizarlo
        QString ultimoEstado="";//guarda el último estado antes que termine el proceso
        /*Guardar el ultimo estado es útil en el caso de que se lea un simbolo que no esté en ninguna transicion
         * esto implicaria que el estado actual sea "none" por lo que necesitaríamos saber cual fué
         * el último estado antes de que llegaramos a "none"
        */
        pal->setPalabra(ui->inPalabra->text());//toma la palabra ingresada por el usuario y la ingresa a la pila
        if(pal->vacia()){//si la pila está vacía despues de que se agregara la palabra que el usuario ha ingresado
                        //significa que se está probando la palabra vacía
            msg("Se probará la palabra vacía.","#ffff00");//mensaje en la salida detallada
        }else{
            //se imprime un mensaje en la salida detallada de la palabra que se ha ingresado a la pila
            msg("Palabra ingresada a la pila: \""+ui->inPalabra->text()+"\"","#ffff00");
        }
        //AQUI COMIENZA EL TEST DE LA PALABRA, RECORRIENDO ESTADO POR ESTADO CON LAS TRANSICIONES DEFINIDAS
        msg("==========]    - TEST -    [==============","#ffff00");
        //COMIENZA EL CICLO
        while(!pal->vacia()&&eActual!="none"){
            //este ciclo termina cuando la pila esté vacía y el estado actual sea distinto de "none"
            /*
             * Si el ciclo termina por que el estado actual es "none", quiere decir que el último simbolo que se
             * leyó no estaba presente en ninguna transicion definida, por lo que la palabra debería ser rechazada.
             *
             * Si el ciclo termina por que la pila está vacía significa que la palabra se leyo completamente, lo que implica que
             * puede que sea válida, pero está la posibilidad de que exista un último símbolo que no se ha leido y quizas la palabra
             * no debería ser aceptada. eso se verifica un poco mas abajo
            */
            c=pal->extraer();//se extrae el primer símbolo de la palabra
            msg("-> Estoy en "+eActual+", leo el simbolo \""+c+"\"","yellow");//mensaje indicando en estado actual
            ultimoEstado=eActual;//guarda el ultimo estado antes de cambiar el estado actual.
            eActual=trans->getDestino(eActual,c);//el estado actual ahora es el estado que devuelve el método getDestino
            //en caso de que el símbolo no este en alguna transicion, estadoActual será "none"
            if(eActual!="none"){
                msg("    he llegado a "+eActual,"yellow");//un mensaje para indicar a que estado se ha llegado
                //decidimos que no se mostrará este mensaje si se llega a "none", ya que "none" no es un estado
            }
        }
        //TERMINA EL CICLO
        if(pal->vacia()&&finales->existe(eActual)&&eActual!="none"&&finales->existe(eActual)){
            /*
             * Si la pila está vacía, quiere decir que se leyó toda la palabra con éxito, pero además, si
             * el estado actual es distinto de "none", quiere decir que se ha llegado a un estado al menos.
             * Si el método existe de la lista de estados finales devuelve true, el estado al que se llego
             * es un estado final y la palabra es totalmente aceptada
            */
            msg("Se leyó la palabra completa y estado "+eActual+" es final.","#00ff00");
            msg("=> PALABRA ACEPTADA","#00ff00");
            ui->salida2->setText("Palabra\nAceptada");//se impeime un mensaje de que la palabra
                                                     //fue aceptada
            ui->salida2->setStyleSheet("background:#00ff00;color:white;");//se cambia el color de la salida a verde
        }else{
            //ahora, todos estos if's que vienen son para identificar por que la palabra no es aceptada
            if(eActual=="none"){
                //si se ha llegado a "none", quiere decir que el último caracter leido no estaba presente
                //en ninguna trnasicion
                msg("La transicion del estado "+ultimoEstado+" con el simbolo \""+c+"\" no está definida.","#ff0000");
            }
            if(!pal->vacia()){
                //si la pila no está vacía, quiere decir que faltaron simbolos por leer, pero se dejó de hacerlo
                //por que se ha llegado a "none"
                msg("No se ha leido la palabra completa.","#ff0000");
            }
            else if(!finales->existe(eActual)&&eActual!="none"){
                //si el estado al que se ha llegado es distinto de "none", quiere decir
                //que el último estado al que se llegó leyendo completamente la palabra
                //no era un estado final, por lo que la palabra es rechazada de todas formas
                msg("Estado "+eActual+" no es final.","#ff0000");
            }
            msg("=> Palabra rechazada.","red");//se imprime un mensaje de que la palabra fue rechazada
            ui->salida2->setText("Palabra\nRechazada");
            ui->salida2->setStyleSheet("background:#ff0000;color:white;");//se cambia el color de la salida a rojo
        }
        msg("==========] - FIN TEST - [==============","#ffff00");
    }else if(eInicial=="none"){
        //se llega aqui si al presionar el boton de probar palabra, no se ha establecido previamente
        //un estado inicial y/o algun estado final
        ui->salida2->setText("Debe establecer\nun estado inicial.");
        msg("Debe establecer un estado inicial.","#ff0000");
    }else if(finales->vacia()){
        ui->salida2->setText("Debe establecer\nal menos un\nestado final.");
        msg("Debe establecer al menos un estado final..","#ff0000");
    }
}

void MainWindow::on_boton_eliminar_select_clicked(){
    if(ui->tabla_transiciones->selectedItems().length()>0){
        //si al presionar el boton de eliminar transicion seleccionada hay al menos una transicion seleccionada...
        QString o,s,d;
        o=ui->tabla_transiciones->item(ui->tabla_transiciones->selectedItems().at(0)->row(),0)->text();
        s=ui->tabla_transiciones->item(ui->tabla_transiciones->selectedItems().at(0)->row(),1)->text();
        d=ui->tabla_transiciones->item(ui->tabla_transiciones->selectedItems().at(0)->row(),2)->text();
        //se obtienen de la transicion seleccionada los nombres de estado de origen, destino y el simbolo
        if(trans->existe(o,s,d)){//se verifica que exista esta transicion
            //en caso de que la transicion exista, se elimina de la lista enlazada
            trans->quitar(o,s,d);
            //despues se elimina viualmente
            ui->tabla_transiciones->removeRow(ui->tabla_transiciones->selectedItems().at(0)->row());
        }
    }
}

void MainWindow::on_in_simbolo_textChanged(const QString &arg1){
    //con esto evito el ingreso de un caracter "blanco" (" ")
    ui->in_simbolo->setText(ui->in_simbolo->text().trimmed().replace(" ",""));
}

void MainWindow::on_in_origen_textChanged(const QString &arg1){
    //con esto evito el ingreso de un caracter "blanco" (" ") y que contenga espacios extremos
    ui->in_origen->setText(ui->in_origen->text().trimmed().replace(" ",""));
}

void MainWindow::on_in_destino_textChanged(const QString &arg1){
    //con esto evito el ingreso de un caracter "blanco" (" ") y que contenga espacios extremos
    ui->in_destino->setText(ui->in_destino->text().trimmed().replace(" ",""));
}

void MainWindow::msg(QString text, QString color){
    if(ui->salida->toPlainText().length()>0){
        ui->salida->setText(ui->salida->toHtml()+"<font color="+color+">"+text+"</font>");
    }else{
        ui->salida->setText("<font color="+color+">"+text+"</font>");
    }
}

void MainWindow::on_inEstadoInicial_textChanged(const QString &arg1){
     //con esto evito el ingreso de un caracter "blanco" (" ") y que contenga espacios extremos
    ui->inEstadoInicial->setText(ui->inEstadoInicial->text().trimmed());
}

void MainWindow::on_inEstadoFinal_textChanged(const QString &arg1){
     //con esto evito el ingreso de un caracter "blanco" (" ") y que contenga espacios extremos
    ui->inEstadoFinal->setText(ui->inEstadoFinal->text().trimmed());
}

void MainWindow::on_inEstadoInicial_returnPressed(){
    //si se presiona enter en la entrada de texto del estado inicial se llama al metodo
    //de cuando se presiona el boton de establecer estado inicial
    on_botonSetEstadoInicial_clicked();
}

void MainWindow::on_inEstadoFinal_returnPressed(){
    //lo mismo para la entrada de texto del estado inicial pero para la entrada del estado final
    on_botonAgregarFinal_clicked();
}

void MainWindow::on_inPalabra_returnPressed(){
    //lo mismo para la entrada de texto del estado inicial pero para la palabra
    on_botonProbarPalabra_clicked();
}

void MainWindow::on_in_origen_returnPressed(){
    //si se ha presionado enter estando en la entrada de texto de origen en la seccion de transiciones
    if(ui->in_origen->text().length()>0&&ui->in_destino->text().length()>0&&ui->in_simbolo->text().length()==1){
        //si se ha ingresado algo valido en las entradas de texto de las transiciones
        //(origen,simbolo,destino) se llama al metodo de agregar transicion
        on_boton_agregar_transicion_clicked();
    }
}

void MainWindow::on_in_simbolo_returnPressed(){
    //si se ha presionado enter estando en la entrada de texto de simbolo en la seccion de transiciones
    if(ui->in_origen->text().length()>0&&ui->in_destino->text().length()>0&&ui->in_simbolo->text().length()==1){
        on_boton_agregar_transicion_clicked();
        //si se ha ingresado algo valido en las entradas de texto de las transiciones
        //(origen,simbolo,destino) se llama al metodo de agregar transicion
    }
}

void MainWindow::on_in_destino_returnPressed(){
    //si se ha presionado enter estando en la entrada de texto de destino en la seccion de transiciones
    if(ui->in_origen->text().length()>0&&ui->in_destino->text().length()>0&&ui->in_simbolo->text().length()==1){
        on_boton_agregar_transicion_clicked();
        //si se ha ingresado algo valido en las entradas de texto de las transiciones
        //(origen,simbolo,destino) se llama al metodo de agregar transicion
    }
}

void MainWindow::on_botonAgregarFinal_clicked(){
    //cuando se presiona el boton agregar estado final
    QMessageBox msg;//mensaje para mostrar al usuario en caso de algun error
    if(ui->inEstadoFinal->text().trimmed().length()>0){
        //si el texto en la entrada de texto de estado final no es vacio...
        if(finales->agregar(ui->inEstadoFinal->text())){
            //...si se ha agregado ele stado ingresado...
            ui->listaEstadosFinales->addItem(ui->inEstadoFinal->text());//se agrega el estado final visualmente
            ui->inEstadoFinal->setText("");//se borra el texto de la entrada de estado final
            ui->listaEstadosFinales->sortItems(Qt::AscendingOrder);//se ordenan los estados finales alfabeticamente
            ui->inEstadoFinal->setFocus();//se mueve el cursor a la entrada de estado final por si se quiere agregar otro
        }else if(finales->existe(ui->inEstadoFinal->text().trimmed())){
            //en caso de que no se haya agregado el estado final, si ya existía previamente, se muestra el emnsaje al usuario
                msg.critical(this,"Estado final ya ingresado","El estado final que desea agregar ya está agregado.");
            }
    }else{
        if(ui->inEstadoFinal->text().trimmed().length()==0){
            //en caso de que la entrada de texto contenga un texto vacio, se muestra el mensaje al usuario
            msg.critical(this,"No ha ingresado nada","Debe ingresar un nombre de estado final antes de agregar.");
        }

    }
}



void MainWindow::on_boton_agregar_transicion_clicked(){
    //al presionar el boton de agregar transicion se llama a este metodo...
    //... se extraen los valores de las entradas de origen, simbolo y destino en la seccion de transiciones
    QString ori=ui->in_origen->text();
    QString sim=ui->in_simbolo->text();
    QString dest=ui->in_destino->text();

    if(ori.length()>0 && sim.length()==1 && dest.length()>0){
        //si las entradas tienen texto valido se entra a este if...
        if(trans->agregar(ori,sim,dest)){
            //si se ha podido agregar la nueva transicion a la lista enlazada, se agrega visualmente
            QTableWidgetItem * item_origen=new QTableWidgetItem();
            QTableWidgetItem * item_simbolo=new QTableWidgetItem();
            QTableWidgetItem * item_destino=new QTableWidgetItem();
            item_origen->setText(ori);
            item_simbolo->setText(sim);
            item_destino->setText(dest);
            ui->tabla_transiciones->insertRow(ui->tabla_transiciones->rowCount());
            ui->tabla_transiciones->setItem(ui->tabla_transiciones->rowCount()-1,0,item_origen);
            ui->tabla_transiciones->setItem(ui->tabla_transiciones->rowCount()-1,1,item_simbolo);
            ui->tabla_transiciones->setItem(ui->tabla_transiciones->rowCount()-1,2,item_destino);

            //abajo, se borra el etxto en las entradas de la transicion
            ui->in_origen->setText("");
            ui->in_simbolo->setText("");
            ui->in_destino->setText("");
            ui->in_origen->setFocus();//se mueve el cursor a la entrada de texto "origen" por si se quiere ingresar
                                        //otra transicion
        }else{
            //en caso de que no se haya podido agregar la nueva transicion se identificará la falla...
            QMessageBox msg;//mensajebox para mostrar el error en un mensaje visual
            if(trans->getDestino(ori,sim)==dest){
                //si la transicion ingresada ya existia, se muestra el mensaje
                msg.critical(this,"Transicion ya ingresada","La transición que desea ingresar ya está ingresada.");
            }else{
                //si el estado de origen y el simbolo ya existian en otra transicion se muestra el mensaje
                msg.critical(this,"Transicion ya definida","No se ha agregado la transición, ya que desde el estado de origen indicado\n"
                                                           "existe otra transición con el mismo símbolo.");
            }
        }

    }else{
        if(ori.length()==0||sim.length()==0||dest.length()==0){
            //si alguna de las entradas no contenia texto, se muestra el mensaje al usuario
            QMessageBox msg;
            msg.critical(this,"Faltan datos","No se puede agregar la transición por que faltan datos.\nRevise e intente nuevamente.");
        }
    }
}

