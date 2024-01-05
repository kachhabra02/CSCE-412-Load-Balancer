/** @file WebServer.h
* @brief Defines the WebServer class.
* @author Krish Chhabra
*/

#pragma once

#include "Request.h"

/**
* @class WebServer
* @brief Represents a web server endpoint that processes incoming requests.
*/
class WebServer {
private:
    /** The current request being processed by the server. */
    Request currRequest;

    /** The status of if the server is currently processing a request. */
    bool isWorking;

    /** The time remaining for the current request to finish processing. */
    int timeRemaining;

public:
    /**
     * @brief Constructs a new Web Server.
     */
    WebServer();


    /**
     * @brief Retrieves the request currently being processed.
     * 
     * @return Request being processed.
     */
    Request getRequest();

    /**
     * @brief Retrieves the time remaining to finish processing the current request.
     * 
     * @return Time remaining in current process (int).
     */
    int getTimeRemaining();


    /**
     * @brief Checks status of if the server is currently processing a request.
     * 
     * @return True if the web server is processing a request, false if it is idle.
     */
    bool hasRequest();

    /**
     * @brief Receives request to be processed.
     * 
     * @param req The new request the server will begin processing.
     */
    void receiveRequest(Request req);

    /**
     * @brief Processes the current request for a single clock cycle.
     * 
     * @return True if the request has been completed, false otherwise.
     */
    bool processRequest();

    /**
     * @brief Retrieves the status of if the current process has been fully processed.
     * 
     * @return True if the request has been completed, false otherwise.
     */
    bool hasCompletedRequest();

    /**
     * @brief Finishes the request currently being processed and returns the server to an idle state.
     * 
     * @return Request that has been finished.
     */
    Request finishRequest();
};