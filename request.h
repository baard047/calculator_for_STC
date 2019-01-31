#ifndef REQUEST_H
#define REQUEST_H


class Request
{
public:
    Request(int type, double operandA, double operandB, int delayMS = 0);

    int m_type;
    double m_operandA;
    double m_operandB;

    unsigned long m_delayMS;
};

#endif // REQUEST_H
