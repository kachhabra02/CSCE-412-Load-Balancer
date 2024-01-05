#include "AnalyticsMonitor.h"

AnalyticsMonitor::AnalyticsMonitor() : filename("Analytics.csv"), out("Analytics.csv") {
    out << "Clock,Number of Servers,Number of Servers in Use,Number of Requests" << endl;
}

AnalyticsMonitor::AnalyticsMonitor(string fname) : filename(fname), out(fname) {
    out << "Clock,Number of Servers,Number of Servers in Use,Number of Requests" << endl;
}

AnalyticsMonitor::~AnalyticsMonitor() {
    out.flush();
    out.close();
    cout << "Analytics History for Simulation Written to '" << filename << "'." << endl;
}

void AnalyticsMonitor::updateServerAndRequestData(int clock, int numServers, int numServersFull, int numRequests) {
    if (clock == 0) {
        minServers = numServers;
        maxServers = numServers;
        avgServers = numServers;

        minRequests = numRequests;
        maxRequests = numRequests;
        avgRequests = numRequests;
    }
    else {
        minServers = (numServers < minServers) ? numServers : minServers;
        maxServers = (numServers > maxServers) ? numServers : maxServers;
        avgServers = (clock * avgServers + numServers) / (clock + 1);

        minRequests = (numRequests < minRequests) ? numRequests : minRequests;
        maxRequests = (numRequests > maxRequests) ? numRequests : maxRequests;
        avgRequests = (clock * avgRequests + numRequests) / (clock + 1);
    }

    out << clock << "," << numServers << "," << numServersFull << "," << numRequests << endl;
}

void AnalyticsMonitor::requestReceived() {
    ++numReceived;
}

void AnalyticsMonitor::requestDelegated() {
    ++numDelegated;
}

void AnalyticsMonitor::requestCompleted() {
    ++numCompleted;
}

void AnalyticsMonitor::requestBlocked() {
    ++numBlocked;
}