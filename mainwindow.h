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

private slots:
    void on_boton_agregar_clicked();

    void on_boton_eliminar_select_clicked();

    void on_botonSetEstadoInicial_clicked();

    void on_botonAgregarTransiciones_clicked();

    void on_botonQuitarEstadoFinal_clicked();

    void on_botonProbarPalabra_clicked();

    void on_bton_eliminar_todas_clicked();

    void on_in_simbolo_textChanged(const QString &arg1);

    void on_in_origen_textChanged(const QString &arg1);

    void on_in_destino_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    ListaTransiciones *trans;
    ListaEstadosFinales *finales;
    PilaPalabra* pal;
    QString eInicial,eActual;
    void msg(QString text,QString color);


};

#endif // MAINWINDOW_H
