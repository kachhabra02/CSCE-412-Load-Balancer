#pragma once

#include "Request.h"
#include <queue>
#include <string>
using std::queue, std::string;

class RequestQueue {
private:
    queue<Request*> q;

public:
    RequestQueue();
    ~RequestQueue();
    
    size_t size();
    bool empty();
    void push(Request* req);
    Request* pop();
    Request* front();
};