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
#define ADJUST_INTERVAL 100

class LoadBalancer {
private:
    size_t clock;
    RequestQueue req_q;
    vector<WebServer> servers;
    AnalyticsMonitor* monitor;
    OutputLog* log;
    int serversToRemove = 0;

    string ipBlockLow, ipBlockHigh;
    bool isIPBlocked(string ip);
    
public:
    LoadBalancer();
    LoadBalancer(size_t numServers);
    LoadBalancer(size_t numServers, OutputLog* out);
    LoadBalancer(size_t numServers, AnalyticsMonitor* mon);
    LoadBalancer(size_t numServers, OutputLog* out, AnalyticsMonitor* mon);

    void setIPBlocker(string low, string high);
    void tickClock();
    void receiveRequests(vector<Request> reqs);
    int numRequestsQueued();
    int numServersFull();
    size_t getClock();
};