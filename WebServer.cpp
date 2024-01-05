#include "WebServer.h"

WebServer::WebServer() : currRequest(), timeRemaining(0), isWorking(false) {}

Request WebServer::getRequest() {
    return currRequest;
}

int WebServer::getTimeRemaining() {
    return timeRemaining;
}

bool WebServer::hasRequest() {
    return isWorking;
}

void WebServer::receiveRequest(Request req) {
    currRequest = req;
    timeRemaining = req.time;
    isWorking = true;
}

bool WebServer::processRequest() {
    if (timeRemaining > 0) {
        --timeRemaining;
    }

    return hasCompletedRequest();
}

bool WebServer::hasCompletedRequest() {
    return (isWorking) && (timeRemaining == 0);
}

Request WebServer::finishRequest() {
    isWorking = false;
    timeRemaining = 0;
    return currRequest;
}