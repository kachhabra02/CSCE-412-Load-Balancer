#pragma once

#include "WebServer.h"
#include "RequestQueue.h"
#include "AnalyticsMonitor.h"
#include "OutputLog.h"
#include <vector>
using std::vector;

#define DEFAULT_NUM_SERVERS 20
#define REMOVE_FACTOR 5
#define ADD_FACTOR 10

class LoadBalancer {
private:
    // TODO
    size_t clock;
    RequestQueue req_q;
    vector<WebServer> servers;
    AnalyticsMonitor* monitor;
    OutputLog* log;

    string ipBlockLow, ipBlockHigh;
    bool isIPBlocked(string ip);
    
public:
    // TODO
    LoadBalancer();
    LoadBalancer(size_t numServers);
    LoadBalancer(size_t numServers, OutputLog* out);
    LoadBalancer(size_t numServers, AnalyticsMonitor* mon);
    LoadBalancer(size_t numServers, OutputLog* out, AnalyticsMonitor* mon);

    void setIPBlocker(string low, string high);
    void tickClock();
    void receiveRequests(vector<Request*> reqs);
};