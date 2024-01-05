#pragma once

#include "Request.h"

class WebServer {
private:
    Request currRequest;
    bool isWorking;
    int timeRemaining;

public:
    WebServer();

    Request getRequest();
    int getTimeRemaining();

    bool hasRequest();
    void receiveRequest(Request req);
    bool processRequest();
    bool hasCompletedRequest();
    Request finishRequest();
};