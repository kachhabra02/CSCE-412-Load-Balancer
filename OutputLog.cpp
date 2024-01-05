/** @file OutputLog.cpp
* @brief Implements the OutputLog class.
* @author Krish Chhabra
*/

#include "OutputLog.h"

OutputLog::OutputLog() : filename("Simulation_Log.txt"), out("Simulation_Log.txt") {
    out << setw(10) << left << "Clock";
    out.copyfmt(cout);
    out << " | Message" << endl;
}

OutputLog::OutputLog(string fname) : filename(fname), out(fname) {
    out << setw(10) << left << "Clock";
    out.copyfmt(cout);
    out << " | Message" << endl;
}

OutputLog::~OutputLog() {
    out.flush();
    out.close();
    cout << "Full Output Log for Simulation Written to '" << filename << "'." << endl;
}

void OutputLog::requestReceived(size_t clock, Request req) {
    out << setw(10) << left << clock;
    out.copyfmt(cout);
    out << " | Received New Request (" << req.srcIP << " -> " << req.dstIP << ", " << req.time << " cycles)" << endl;
}

void OutputLog::requestBlocked(size_t clock, Request req) {
    out << setw(10) << left << clock;
    out.copyfmt(cout);
    out << " | Firewall Blocked Incoming Request (" << req.srcIP << " -> " << req.dstIP << ", " << req.time << " cycles)" << endl;
}

void OutputLog::requestDelegated(size_t clock, Request req, size_t serverNum) {
    out << setw(10) << left << clock;
    out.copyfmt(cout);
    out << " | Request Delegated to Web Server " << serverNum << " (" << req.srcIP << " -> " << req.dstIP;
    out << ", " << req.time << " cycles)" << endl;
}

void OutputLog::requestCompleted(size_t clock, Request req, size_t serverNum) {
    out << setw(10) << left << clock;
    out.copyfmt(cout);
    out << " | Request Completed by Web Server " << serverNum << " (" << req.srcIP << " -> " << req.dstIP;
    out << ", " << req.time << " cycles)" << endl;
}

void OutputLog::serverAdded(size_t clock, size_t serverNum) {
    out << setw(10) << left << clock;
    out.copyfmt(cout);
    out << " | Added Web Server " << serverNum << endl;
}

void OutputLog::serverRemoved(size_t clock, size_t serverNum) {
    out << setw(10) << left << clock;
    out.copyfmt(cout);
    out << " | Removed Web Server " << serverNum << endl;
}

void OutputLog::exitSimulation(size_t clock, bool exitedEarly) {
    out << setw(10) << left << clock;
    out.copyfmt(cout);
    if (exitedEarly) {
        out << " | Exited Early Due to an Empty Request Queue" << endl;
    }
    else {
        out << " | Clock Cycle Limit Reached" << endl;
    }   
}