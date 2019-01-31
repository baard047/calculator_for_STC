#ifndef CALCULATEPROCESSTHREAD_H
#define CALCULATEPROCESSTHREAD_H

#include <qthread.h>
#include <QDebug>
#include "queuerequest.h"

class CalculateProcessThread :    public QThread
{
    Q_OBJECT

public:
    CalculateProcessThread();
    ~CalculateProcessThread();
    void run();

    double compute( int Type, double OperandA, double OperandB);       //функция вычислений
signals:
    void processDone(double);                                          //сигнал чтобы показать что процесс закончен

private:
    std::mutex m1;
};

#endif // CALCULATEPROCESSTHREAD_H
