#include "mainwindow.h"
#include "ui_mainwindow.h"

double firstNum;                        //глобал чтобы equal_pressed видел значение, которое инициализируется в binary_operation_pressed. Я знаю что это плохой тон
bool userTypingSecondDigit = false;     //нужна для того, чтобы пользователь мог вводить несколько чисел, после бинарного оператора

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //кнопки 0-9
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    //унарные операторы: кнопки . +/- % C =
    connect(ui->pushButton_decimal,SIGNAL(released()),this,SLOT(decimal_pressed()));
    connect(ui->pushButton_plus_min,SIGNAL(released()),this,SLOT(unary_buttons_pressed()));
    connect(ui->pushButton_percent,SIGNAL(released()),this,SLOT(unary_buttons_pressed()));
    connect(ui->pushButton_clear,SIGNAL(released()),this,SLOT(clear_pressed()));
    connect(ui->pushButton_equal,SIGNAL(released()),this,SLOT(equal_pressed()));

    //бинарные операторы
    connect(ui->pushButton_add,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_mult,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->pushButton_add->setCheckable(true);            //чтобы можно было проверять какая кнопка нажата в binary_operation_pressed()
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    double displayNumber;
    QString DisplayText;

    if ((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() ||
           ui->pushButton_mult->isChecked() || ui->pushButton_divide->isChecked()) && (!userTypingSecondDigit))
    {
        displayNumber = button->text().toDouble();
        userTypingSecondDigit = true;
        DisplayText = QString::number(displayNumber,'g',15);
    }
    else
    {
        if (ui->display->text().contains(".")&& button->text() == "0")
        {
            DisplayText = ui->display->text() + button->text();
        }
        else
        {
            displayNumber = (ui->display->text() + button->text()).toDouble();
            DisplayText = QString::number(displayNumber,'g',15);
        }
    }


    ui->display->setText(DisplayText);
}

void MainWindow::decimal_pressed()
{
    if (ui->display->text().contains("."))                 //чтобы  нельзя было ввести несколько точек
    {
        ui->display->setText(ui->display->text());
    }
    else
    {
        ui->display->setText(ui->display->text() + ".");
    }
}

void MainWindow::unary_buttons_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    double displayNumber;
    QString DisplayText;

    if (button->text() == "+/-")
    {
        displayNumber = ui->display->text().toDouble();
        displayNumber *= -1;
        DisplayText = QString::number(displayNumber,'g',15);
        ui->display->setText(DisplayText);
    }

    if (button->text() == "%")
    {
        displayNumber = ui->display->text().toDouble();
        displayNumber *= 0.01;
        DisplayText = QString::number(displayNumber,'g',15);
        ui->display->setText(DisplayText);
    }
}

void MainWindow::binary_operation_pressed()
{
    QPushButton *button = (QPushButton*)sender();

    firstNum = ui->display->text().toDouble();

    button->setChecked(true);
}

void MainWindow::clear_pressed()
{
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    userTypingSecondDigit = false;

    ui->display->setText("0");
}

void MainWindow::equal_pressed()
{
    double displayNumber;
    double secondNum = ui->display->text().toDouble();
    QString DisplayText;

    if (ui->pushButton_add->isChecked())
    {
        qDebug() << "New request: " << firstNum << " + " << secondNum;
        displayNumber = compute(add,firstNum,secondNum);
        DisplayText = QString::number(displayNumber,'g',15);
        ui->display->setText(DisplayText);
        ui->pushButton_add->setChecked(false);
    }
    else if (ui->pushButton_subtract->isChecked())
    {
        qDebug() << "New request: " << firstNum << " - " << secondNum;
        displayNumber = compute(substract,firstNum,secondNum);;
        DisplayText = QString::number(displayNumber,'g',15);
        ui->display->setText(DisplayText);
        ui->pushButton_subtract->setChecked(false);
    }
    else if (ui->pushButton_mult->isChecked())
    {
        qDebug() << "New request: " << firstNum << " * " << secondNum;
        displayNumber = compute(mult,firstNum,secondNum);;
        DisplayText = QString::number(displayNumber,'g',15);
        ui->display->setText(DisplayText);
        ui->pushButton_mult->setChecked(false);
    }
    else if (ui->pushButton_divide->isChecked())
    {
        qDebug() << "New request: " << firstNum << " / " << secondNum;
        try
        {
            displayNumber = compute(divide,firstNum,secondNum);;
            if (secondNum == 0.0) {throw 1; }
            DisplayText = QString::number(displayNumber,'g',15);
            ui->display->setText(DisplayText);
            ui->pushButton_divide->setChecked(false);
        }
        catch (int e)
        {
            qDebug() << "Error: You cannot divide by zero!";
        }
        ui->pushButton_divide->setChecked(false);          //чтобы можно было продолжить пользоваться программой, после деления на 0
    }

    userTypingSecondDigit = false;
}

double MainWindow::compute(int Type, double OperandA, double OperandB)
{
    switch (Type) {
        case add:
        {
            return OperandA + OperandB;
        }
        case substract:
        {
            return OperandA - OperandB;
        }
        case mult:
        {
            return OperandA * OperandB;
        }
        case divide:
        {
            return OperandA / OperandB;
        }
    }
}



