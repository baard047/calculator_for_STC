#include "queuerequest.h"

QueueRequest::QueueRequest()
{

}

std::queue<Request>* QueueRequest::requests = new std::queue<Request>();

std::mutex* QueueRequest::m1 = new std::mutex();
