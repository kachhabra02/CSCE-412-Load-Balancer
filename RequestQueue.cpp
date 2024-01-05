#include "RequestQueue.h"

RequestQueue::RequestQueue() {}

RequestQueue::~RequestQueue() {
    while (!q.empty()) {
        delete q.front();
        q.pop();
    }
}

size_t RequestQueue::size() {
    return q.size();
}

bool RequestQueue::empty() {
    return q.size() == 0;
}

void RequestQueue::push(Request* req) {
    q.push(req);
}

Request* RequestQueue::pop() {
    Request* front = q.front();
    q.pop();
    return front;
}

Request* RequestQueue::front() {
    return q.front();
}