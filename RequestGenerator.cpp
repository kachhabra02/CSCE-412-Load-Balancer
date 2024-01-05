/** @file RequestGenerator.cpp
* @brief Implements the RequestGenerator class.
* @author Krish Chhabra
*/

#include "RequestGenerator.h"

string RequestGenerator::generateIP() {
    return to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256);
}

RequestGenerator::RequestGenerator() : reqTimeMin(DEFAULT_MIN_TIME), reqTimeMax(DEFAULT_MAX_TIME), reqProb(5) {
    srand(time(0));
}

RequestGenerator::RequestGenerator(int prob) : reqTimeMin(DEFAULT_MIN_TIME), reqTimeMax(DEFAULT_MAX_TIME), reqProb(prob) {
    srand(time(0));
}

RequestGenerator::RequestGenerator(int timeMin, int timeMax) : reqTimeMin(timeMin), reqTimeMax(timeMax), reqProb(5) {
    srand(time(0));
}

RequestGenerator::RequestGenerator(int timeMin, int timeMax, int prob) : reqTimeMin(timeMin), reqTimeMax(timeMax), reqProb(prob) {
    srand(time(0));
}

void RequestGenerator::setRequestProbability(int prob) {
    reqProb = prob;
}

vector<Request> RequestGenerator::getRequests() {
    vector<Request> requests;

    while ((rand() % reqProb) == 0) {
        Request r;
        r.srcIP = generateIP();
        r.dstIP = generateIP();
        r.time = rand() % (reqTimeMax - reqTimeMin + 1) + reqTimeMin;

        requests.push_back(std::move(r));
    }

    return requests;
}

vector<Request> RequestGenerator::getRequests(int numRequests) {
    vector<Request> requests;

    for (int i = 0; i < numRequests; ++i) {
        Request r;
        r.srcIP = generateIP();
        r.dstIP = generateIP();
        r.time = rand() % (reqTimeMax - reqTimeMin + 1) + reqTimeMin;

        requests.push_back(std::move(r));
    }

    return requests;
}