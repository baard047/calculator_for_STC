#include "calculateprocessthread.h"

CalculateProcessThread::CalculateProcessThread()
{

}

CalculateProcessThread::~CalculateProcessThread()
{

}

void CalculateProcessThread::run()
{
    // вычислительный процесс
    while (true)
    {
        if (!QueueRequest::requests->empty())
        {
            std::lock_guard<std::mutex> guard(*QueueRequest::m1);
            Request req = QueueRequest::requests->front();
            double result = this->compute(req.m_type, req.m_operandA, req.m_operandB);
            this->msleep(req.m_delayMS);                                                // делей
            emit processDone(result);
            QueueRequest::requests->pop();
        }
    }
}


double CalculateProcessThread::compute(int Type, double OperandA, double OperandB)      //сама функция вычислений
{
    switch (Type)
    {
        case 0:  {return OperandA + OperandB; }

        case 1:  {return OperandA - OperandB; }

        case 2:  {return OperandA * OperandB; }

        case 3:  {return OperandA / OperandB; }
    }

return 1;
}
