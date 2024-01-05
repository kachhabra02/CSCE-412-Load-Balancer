/** @file OutputLog.h
* @brief Defines the OutputLog class.
* @author Krish Chhabra
*/

#pragma once

#include "Request.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using std::ofstream, std::setw, std::left, std::cout, std::endl, std::string;

/**
* @class RequestQueue
* @brief Scribe class that generates a log of the activities performed during a load balancer simulation.
*/
class OutputLog {
private:
    /** The name of the file that the log is being written to. */
    string filename;

    /** Output stream for writing to file. */
    ofstream out;

public:
    /**
     * @brief Construct a new, default Output Log.
     * 
     */
    OutputLog();

    /**
     * @brief Construct a new Output Log that writes to the given file.
     * 
     * @param fname 
     */
    OutputLog(string fname);

    /**
     * @brief Closes the output log.
     * 
     */
    ~OutputLog();


    /**
     * @brief Logs the details of the given new request.
     * 
     * @param clock Current clock cycle.
     * @param req New request received by the load balancer.
     */
    void requestReceived(size_t clock, Request req);

    /**
     * @brief Logs the details of the given bloacked request.
     * 
     * @param clock Current clock cycle.
     * @param req Request that was blocked by the load balancer's firewall.
     */
    void requestBlocked(size_t clock, Request req);

    /**
     * @brief Logs the details of the given request and the server that it was delegated to.
     * 
     * @param clock Current clock cycle.
     * @param req Request that was delegated by the load balancer.
     * @param serverNum The server that the request was delegated to.
     */
    void requestDelegated(size_t clock, Request req, size_t serverNum);

    /**
     * @brief Logs the details of the completed request and the server that it was processed on.
     * 
     * @param clock Current clock cycle.
     * @param req 
     * @param serverNum The server that the request was processed on.
     */
    void requestCompleted(size_t clock, Request req, size_t serverNum);

    /**
     * @brief Logs the addition of a web server by the load balancer.
     * 
     * @param clock Current clock cycle.
     * @param serverNum The server that was recently added.
     */
    void serverAdded(size_t clock, size_t serverNum);

    /**
     * @brief Logs the deletion of a web server by the load balancer.
     * 
     * @param clock Current clock cycle.
     * @param serverNum The server that was recently removed.
     */
    void serverRemoved(size_t clock, size_t serverNum);

    /**
     * @brief Logs the ending of the simulation.
     * 
     * @param clock Current clock cycle.
     * @param exitedEarly The status of if the simulation ended early due to no incoming requests (true) or reached the clock cyle limit (false).
     */
    void exitSimulation(size_t clock, bool exitedEarly);
};