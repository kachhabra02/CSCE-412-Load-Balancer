#pragma once

#include "Request.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
using std::string, std::to_string, std::vector;

class RequestGenerator {
private:
    int reqTimeMin, reqTimeMax;
    int reqProb;

    string generateIP();

public:
    RequestGenerator();
    RequestGenerator(int prob);
    RequestGenerator(int timeMin, int timeMax);
    RequestGenerator(int timeMin, int timeMax, int prob);

    void setRequestProbability(int prob);

    vector<Request*> getRequests();
    vector<Request*> getRequests(int numRequests);
};