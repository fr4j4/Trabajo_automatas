#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "listatransiciones.h"
#include "pilapalabra.h"

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

private:
    Ui::MainWindow *ui;
    ListaTransiciones *trans;
    PilaPalabra* pal;

};

#endif // MAINWINDOW_H
