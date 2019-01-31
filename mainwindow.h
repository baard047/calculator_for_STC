#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <thread>
#include <QQueue>

#include "calculateprocessthread.h"

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

    CalculateProcessThread* m_thread;

private:
    Ui::MainWindow *ui;

    int delay_ms = 0;
    double firstNum;
    double secondNum;

    double displayNumber;                                              //сюда записывается результат вычислений
    QString DisplayText;                                               //текстовая переменная, которую видет пользователь на дисплее
    bool userTypingSecondDigit = false;                                //нужна для того, чтобы пользователь мог вводить несколько чисел, после бинарного оператора


private slots:
    void on_set_delay_clicked();

    void digit_pressed();
    void decimal_pressed();
    void unary_buttons_pressed();
    void binary_operation_pressed();
    void clear_pressed();
    void equal_pressed();

    void displayResult(double result);
};

#endif // MAINWINDOW_H
