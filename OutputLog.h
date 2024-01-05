#pragma once

#include "Request.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using std::ofstream, std::setw, std::left, std::cout, std::endl, std::string;

class OutputLog {
private:
    string filename;
    ofstream out;

public:
    OutputLog();
    OutputLog(string fname);
    ~OutputLog();

    void requestReceived(size_t clock, Request req);
    void requestBlocked(size_t clock, Request req);
    void requestDelegated(size_t clock, Request req, size_t serverNum);
    void requestCompleted(size_t clock, Request req, size_t serverNum);
    void serverAdded(size_t clock, size_t serverNum);
    void serverRemoved(size_t clock, size_t serverNum);
    void exitSimulation(size_t clock, bool exitedEarly);
};