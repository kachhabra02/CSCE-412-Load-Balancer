#pragma once

#include "Request.h"

class WebServer {
private:
    Request* currRequest;
    int timeRemaining;

public:
    WebServer();
    ~WebServer();

    Request* getRequest();
    int getTimeRemaining();

    bool hasRequest();
    void receiveRequest(Request* req);
    bool processRequest();
    bool hasCompletedRequest();
    Request* finishRequest();
};