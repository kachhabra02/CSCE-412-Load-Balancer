#pragma once

#include <string>
#include <fstream>
#include <iostream>
using std::string, std::ofstream, std::endl;

class AnalyticsMonitor {
private:
    string filename;
    ofstream out;

public:
    int minServers = 0, maxServers = 0, minRequests = 0, maxRequests = 0;
    int numReceived = 0, numDelegated = 0, numCompleted = 0, numBlocked = 0;
    double avgServers = 0.0, avgRequests = 0.0;

    AnalyticsMonitor();
    AnalyticsMonitor(string fname);
    ~AnalyticsMonitor();

    void updateServerAndRequestData(int clock, int numServers, int numServersFull, int numRequests);
    void requestReceived();
    void requestDelegated();
    void requestCompleted();
    void requestBlocked();
};