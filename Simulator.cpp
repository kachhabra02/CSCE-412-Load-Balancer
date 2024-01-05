/** @file Simulator.cpp
* @brief Driver for load balancer simulation.
* @author Krish Chhabra
*/

#include "LoadBalancer.h"
#include "RequestGenerator.h"
#include <math.h>

using std::cout, std::cin, std::endl;

#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

#define PROB_FAST 2
#define PROB_MODERATE 4
#define PROB_SLOW 7
#define PROB_V_SLOW 12

#define TIME_MIN_SHORT 2
#define TIME_MAX_SHORT 40
#define TIME_MIN_MED 4
#define TIME_MAX_MED 100
#define TIME_MIN_LONG 20
#define TIME_MAX_LONG 200
#define TIME_MIN_V_LONG 100
#define TIME_MAX_V_LONG 300

#define START_REQ_FACTOR 20

/**
 * @brief Runs the simulation UI that generates a customized scenario to demonstrate the load balancer.
 */
int main() {
    cout << "How many web servers would you like to start with? ";
    int numServers;
    cin >> numServers;

    cout << "How many clock cycles would you like to simumlate? ";
    int numCycles;
    cin >> numCycles;

    cout << "How frequently would you like requests to be generated (";
    cout << RED << "0 = very slow" << RESET << ", " << YELLOW << "1 = slow" << RESET << ", ";
    cout << GREEN << "2 = moderate" << RESET << ", " << BLUE << "3 = fast" << RESET << ")? ";
    int requestSpeed;
    cin >> requestSpeed;

    int reqProb;
    if (requestSpeed == 0) {
        reqProb = PROB_V_SLOW;
    }
    else if (requestSpeed == 1) {
        reqProb = PROB_SLOW;
    }
    else if (requestSpeed == 3) {
        reqProb = PROB_FAST;
    }
    else {
        reqProb = PROB_MODERATE;
    }

    cout << "How long would you like your requests to be (";
    cout << RED << "0 = short" << RESET << ", " << YELLOW << "1 = medium" << RESET << ", ";
    cout << GREEN << "2 = long" << RESET << ", " << BLUE << "3 = very long" << RESET << ")? ";
    int requestLength;
    cin >> requestLength;

    int reqTimeMin, reqTimeMax;
    if (requestLength == 0) {
        reqTimeMin = TIME_MIN_SHORT;
        reqTimeMax = TIME_MAX_SHORT;
    }
    else if (requestLength == 2) {
        reqTimeMin = TIME_MIN_LONG;
        reqTimeMax = TIME_MAX_LONG;
    }
    else if (requestLength == 3) {
        reqTimeMin = TIME_MIN_V_LONG;
        reqTimeMax = TIME_MAX_V_LONG;
    }
    else {
        reqTimeMin = TIME_MIN_MED;
        reqTimeMax = TIME_MAX_MED;
    }

    cout << "Would you like to add a " << RED << "firewall" << RESET << " to the load balancer (y/n)? ";
    char hasFirewall;
    cin >> hasFirewall;

    string ipBlockLow = "", ipBlockHigh = "";
    if (hasFirewall == 'y' || hasFirewall == 'Y') {
        cout << "What IP address is the lower bound of addresses to block? ";
        cin >> ipBlockLow;

        cout << "What IP address is the upper bound of addresses to block? ";
        cin >> ipBlockHigh;
    }

    OutputLog* log = new OutputLog();
    AnalyticsMonitor* monitor = new AnalyticsMonitor();
    LoadBalancer lb(numServers, log, monitor);

    RequestGenerator reqGen(reqTimeMin, reqTimeMax, reqProb);

    cout << "Settings For Simulation:" << endl;
    cout << "\tStarting With " << numServers << " Web Servers" << endl;
    cout << "\tSimulating " << numCycles << " Clock Cycles" << endl;
    
    cout << "\tRequests Generated At ";
    if (requestSpeed == 0) {
        cout << RED << "Very Slow" << RESET;
    }
    else if (requestSpeed == 1) {
        cout << YELLOW << "Slow" << RESET;
    }
    else if (requestSpeed == 3) {
        cout << BLUE << "Fast" << RESET;
    }
    else {
        cout << GREEN << "Moderate" << RESET;
    }
    cout << " Frequency" << endl;

    cout << "\tRequests Generated Are ";
    if (requestLength == 0) {
        cout << RED << "Short" << RESET << " (" << TIME_MIN_SHORT << " to " << TIME_MAX_SHORT << " cycles)" << endl;
    }
    else if (requestLength == 2) {
        cout << GREEN << "Long" << RESET << " (" << TIME_MIN_LONG << " to " << TIME_MAX_LONG << " cycles)" << endl;
    }
    else if (requestLength == 3) {
        cout << BLUE << "Very Long" << RESET << " (" << TIME_MIN_V_LONG << " to " << TIME_MAX_V_LONG << " cycles)" << endl;
    }
    else {
        cout << YELLOW << "Medium Length" << RESET << " (" << TIME_MIN_MED << " to " << TIME_MAX_MED << " cycles)" << endl;
    }

    if (hasFirewall == 'y' || hasFirewall == 'Y') {
        lb.setIPBlocker(ipBlockLow, ipBlockHigh);
        cout << GREEN << "\tFirewall Blocks IP Addresses Between " << ipBlockLow << " And " << ipBlockHigh << RESET << endl << endl;
    }
    else {
        cout << RED << "\tNo Firewall Set For Load Balancer" << RESET << endl << endl;
    }

    cout << "Beginning Simulation With " << (numServers * START_REQ_FACTOR) << " Requests Queued" << endl << endl;

    for (int i = 0; i <= numCycles; ++i) {
        lb.receiveRequests((i == 0) ? reqGen.getRequests(numServers * START_REQ_FACTOR) : reqGen.getRequests());
        lb.tickClock();

        if (lb.numRequestsQueued() == 0 && lb.numServersFull() == 0) {
            break;
        }
    }
    
    log->exitSimulation(lb.getClock(), lb.numRequestsQueued() == 0 && lb.numServersFull() == 0);
    cout << GREEN << "Simulation Completed At Clock Cycle " << lb.getClock();
    cout << " With " << lb.numRequestsQueued() << " Requests Still Queued" << RESET << endl << endl;

    cout << "Simulation Summary:" << endl;
    cout << "\tNumber of Requests Received by Load Balancer: " << monitor->numReceived << endl;
    cout << "\tNumber of Requests Delegated to a Web Server: " << monitor->numDelegated << endl;
    cout << "\tNumber of Requests Completed/Fulfilled: " << monitor->numCompleted << endl;
    cout << "\tNumber of Requests Blocked by Firewall: " << monitor->numBlocked << endl << endl;
    cout << "\tMinimum Number of Queued Requests: " << monitor->minRequests << endl;
    cout << "\tMaximum Number of Queued Requests: " << monitor->maxRequests << endl;
    cout << "\tAverage Number of Queued Requests: " << (int) ceil(monitor->avgRequests) << endl << endl;
    cout << "\tMinimum Number of Web Servers Live: " << monitor->minServers << endl;
    cout << "\tMaximum Number of Web Servers Live: " << monitor->maxServers << endl;
    cout << "\tAverage Number of Web Servers Live: " << (int) ceil(monitor->avgServers) << endl << endl;

    delete log;
    delete monitor;
}