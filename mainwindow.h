#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <thread>

enum operationType { add, substract, mult, divide };

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double compute( int Type, double OperandA, double OperandB);                     //функция вычислений

private:
    Ui::MainWindow *ui;

private slots:
    void on_set_delay_clicked();

    void digit_pressed();
    void decimal_pressed();
    void unary_buttons_pressed();
    void binary_operation_pressed();
    void clear_pressed();
    void equal_pressed();
};

#endif // MAINWINDOW_H
