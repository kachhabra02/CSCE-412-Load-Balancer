/** @file LoadBalancer.h
* @brief Defines the LoadBalancer class.
* @author Krish Chhabra
*/

#pragma once

#include "WebServer.h"
#include "RequestQueue.h"
#include "AnalyticsMonitor.h"
#include "OutputLog.h"
#include <vector>
#include <bitset>
#include <sstream>
using std::vector;

#define DEFAULT_NUM_SERVERS 20
#define REMOVE_FACTOR 15
#define ADD_FACTOR 25
#define ADJUST_INTERVAL 50

/**
* @class LoadBalancer
* @brief Load balancer that manages incoming requests and distributes them across various web server endpoints.
*/
class LoadBalancer {
private:
    /** Clock that tracks the current cycle of the simulation. */
    size_t clock;

    /** Queue to store incoming requests waiting to be processed. */
    RequestQueue req_q;

    /** Dynamic vector of web servers to process requests. */
    vector<WebServer> servers;

    /** Monitor for tracking statistics of simulation. */
    AnalyticsMonitor* monitor;

    /** Log for tracking operations performed during the simulation. */
    OutputLog* log;

    /** Number of servers that need to be removed when they become idle. */
    int serversToRemove = 0;


    /** IP address for lower bound of firewall. */
    string ipBlockLow;
    
    /** IP address for upper bound of firewall. */
    string ipBlockHigh;

    /**
     * @brief Checks if a given IP address is blocked by the current firewall configurations.
     * 
     * @param ip IP address to test against firewall.
     * @return True if the current firewall blocks requests from this address, false otherwise.
     */
    bool isIPBlocked(string ip);
    
public:
    /**
     * @brief Construct a new, default Load Balancer.
     * 
     */
    LoadBalancer();

    /**
     * @brief Construct a new Load Balancer with the gievn number of starting servers.
     * 
     * @param numServers Number of web servers that the load balancer starts with.
     */
    LoadBalancer(size_t numServers);

    /**
     * @brief Construct a new Load Balancer with the given number of starting servers and output log.
     * 
     * @param numServers Number of web servers that the load balancer starts with.
     * @param out Pointer to output log for the simulation.
     */
    LoadBalancer(size_t numServers, OutputLog* out);

    /**
     * @brief Construct a new Load Balancer with the given number of starting servers and analytics monitor.
     * 
     * @param numServers Number of web servers that the load balancer starts with.
     * @param mon Pointer to analytics monitor for the simulation.
     */
    LoadBalancer(size_t numServers, AnalyticsMonitor* mon);

    /**
     * @brief Construct a new Load Balancer with the given number of starting servers, output log, and analytics monitor.
     * 
     * @param numServers Number of web servers that the load balancer starts with.
     * @param out Pointer to output log for the simulation.
     * @param mon Pointer to analytics monitor for the simulation.
     */
    LoadBalancer(size_t numServers, OutputLog* out, AnalyticsMonitor* mon);


    /**
     * @brief Sets the firewall for the load balancer to block requests from IP addresses in the given range.
     * 
     * @param low Lower bound of IP addresses to block.
     * @param high Upper bound of IP addresses to block.
     */
    void setIPBlocker(string low, string high);

    /**
     * @brief Performs one clock cycle of delegating and processing received requests.
     * 
     */
    void tickClock();

    /**
     * @brief Receives/queues or blocks incoming requests.
     * 
     * @param reqs Vector of incoming requests.
     */
    void receiveRequests(vector<Request> reqs);

    /**
     * @brief Retrieves the number of requests that are currently queued for processing.
     * 
     * @return Number of queued requests (int).
     */
    int numRequestsQueued();

    /**
     * @brief Retrieves the number of servers that are currently processing a request (not idle).
     * 
     * @return Number of servers that are not idle (int).
     */
    int numServersFull();

    /**
     * @brief Retrives the current clock cycle.
     * 
     * @return The current clock cycle (size_t) 
     */
    size_t getClock();
};