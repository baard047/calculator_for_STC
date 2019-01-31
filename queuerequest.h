#ifndef QUEUEREQUEST_H
#define QUEUEREQUEST_H

#include <queue>
#include <mutex>
#include "request.h"

class QueueRequest
{
public:
    static std::queue<Request>* requests;           //статик т.к. чтобы создавать очередь запросов, не нужно создавать объект класса
    static std::mutex* m1;
private:
    QueueRequest();
};

#endif // QUEUEREQUEST_H
