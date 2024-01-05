/** @file AnalyticsMonitor.h
* @brief Defines the AnalyticsMonitor class.
* @author Krish Chhabra
*/

#pragma once

#include <string>
#include <fstream>
#include <iostream>
using std::string, std::ofstream, std::cout, std::endl;

/**
* @class RequestQueue
* @brief Monitor that tracks and stores analytical information on load balancer simulation.
*/
class AnalyticsMonitor {
private:
    string filename;
    ofstream out;

public:
    /** Minimum number of web servers up at any given time during simulation. */
    int minServers = 0;

    /** Maximum number of web servers up at any given time during simulation. */
    int maxServers = 0;

    /** Average number of web servers up throughout simulation. */
    double avgServers = 0.0;


    /** Minimum number of requests queued at any given time during simulation. */
    int minRequests = 0;

    /** Maximum number of requests queued at any given time during simulation. */
    int maxRequests = 0;

    /** Average number of requests queued throughout simulation. */
    double avgRequests = 0.0;


    /** Total number of requests received by the load balancer. */
    int numReceived = 0;

    /** Total number of requests delegated to web servers. */
    int numDelegated = 0;

    /** Total number of requests completed. */
    int numCompleted = 0;

    /** Total number of requests blocked by the load balancer's firewall. */
    int numBlocked = 0;
    

    /**
     * @brief Construct a new, default Analytics Monitor.
     * 
     */
    AnalyticsMonitor();

    /**
     * @brief Construct a new Analytics Monitor that writes to the given file..
     * 
     * @param fname 
     */
    AnalyticsMonitor(string fname);

    /**
     * @brief Closes and finalizes the analytics monitor.
     * 
     */
    ~AnalyticsMonitor();


    /**
     * @brief Updates the analytics trackers based on the provided clock cycle's metrics.
     * 
     * @param clock Current clock cycle.
     * @param numServers Number of servers that are currently running.
     * @param numServersFull Number of servers that a busy processing a request.
     * @param numRequests Number of requests that are waiting in the request queue.
     */
    void updateServerAndRequestData(int clock, int numServers, int numServersFull, int numRequests);

    /**
     * @brief Retrieve the total number of requests received by the load balancer.
     * 
     */
    void requestReceived();

    /**
     * @brief Retrieve the total number of requests delegated to web servers.
     * 
     */
    void requestDelegated();

    /**
     * @brief Retrieve the total number of requests completed.
     * 
     */
    void requestCompleted();

    /**
     * @brief Retrieve the total number of requests blocked by the load balancer's firewall.
     * 
     */
    void requestBlocked();
};