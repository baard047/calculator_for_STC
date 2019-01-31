#include "request.h"


Request::Request(int type, double operandA, double operandB, int delayMS)
{
    this->m_type = type;
    this->m_operandA = operandA;
    this->m_operandB = operandB;
    this->m_delayMS = delayMS;
}
