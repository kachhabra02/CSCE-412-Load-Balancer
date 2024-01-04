#include "WebServer.h"

WebServer::WebServer() : currRequest(nullptr), timeRemaining(0) {}

WebServer::~WebServer() {
    if (currRequest) {
        delete currRequest;
    }
}

Request* WebServer::getRequest() {
    return currRequest;
}

int WebServer::getTimeRemaining() {
    return timeRemaining;
}

bool WebServer::hasRequest() {
    return currRequest != nullptr;
}

void WebServer::receiveRequest(Request* req) {
    currRequest = req;
    timeRemaining = req->time;
}

bool WebServer::processRequest() {
    if (timeRemaining > 0) {
        --timeRemaining;
    }

    return hasCompletedRequest();
}

bool WebServer::hasCompletedRequest() {
    return (currRequest != nullptr) && (timeRemaining == 0);
}

Request* WebServer::finishRequest() {
    currRequest = nullptr;
    return currRequest;
}