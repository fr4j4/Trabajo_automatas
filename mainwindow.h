#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "listatransiciones.h"
#include "pilapalabra.h"
#include "listaestadosfinales.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots://los slots se generan automaticamente
    void on_boton_eliminar_select_clicked();

    void on_botonSetEstadoInicial_clicked();

    void on_botonQuitarEstadoFinal_clicked();

    void on_botonProbarPalabra_clicked();

    void on_in_simbolo_textChanged(const QString &arg1);

    void on_in_origen_textChanged(const QString &arg1);

    void on_in_destino_textChanged(const QString &arg1);

    void on_inEstadoInicial_textChanged(const QString &arg1);

    void on_inEstadoFinal_textChanged(const QString &arg1);

    void on_inEstadoInicial_returnPressed();

    void on_inEstadoFinal_returnPressed();

    void on_botonAgregarFinal_clicked();

    void on_inPalabra_returnPressed();

    void on_boton_agregar_transicion_clicked();

    void on_in_origen_returnPressed();

    void on_in_simbolo_returnPressed();

    void on_in_destino_returnPressed();

private:
    Ui::MainWindow *ui;
    ListaTransiciones *trans;//lista enlazada de transiciones
    ListaEstadosFinales *finales;//lista enlazada de estados finales
    PilaPalabra* pal;//pila para guardar la palabra
    QString eInicial,eActual;//variables que ayudarán en el testeo de la palabra
    void msg(QString text,QString color);//imprime un mensaje en la slaida detallada con un color específico


};

#endif // MAINWINDOW_H
