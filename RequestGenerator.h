/** @file RequestGenerator.h
* @brief Defines the RequestGenerator class.
* @author Krish Chhabra
*/

#pragma once

#include "Request.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
using std::string, std::to_string, std::vector;

#define DEFAULT_MIN_TIME 4
#define DEFAULT_MAX_TIME 100

/**
* @class RequestGenerator
* @brief Generator of randomized requests.
*/
class RequestGenerator {
private:
    /** The minimum length of a request to be generated. */
    int reqTimeMin;

    /** The maximum length of a request to be generated. */
    int reqTimeMax;

    /** The likelihood of generating a request (1 / reqProb), with higher reqProb leading to less frequent requests. */
    int reqProb;


    /**
     * @brief Generates a random IP address.
     * 
     * @return The random IP address that was generated (string).
     */
    string generateIP();

public:
    /**
     * @brief Construct a new, default Request Generator.
     * 
     */
    RequestGenerator();

    /**
     * @brief Construct a new Request Generator with the given request frequency.
     * 
     * @param prob Probability that a request will be generated (1 / prob).
     */
    RequestGenerator(int prob);

    /**
     * @brief Construct a new Request Generator object with the given length restraints.
     * 
     * @param timeMin Minimum length of a single request that is generated.
     * @param timeMax Maximum length of a single request that is generated.
     */
    RequestGenerator(int timeMin, int timeMax);

    /**
     * @brief Construct a new Request with the given length restraints and request frequency.
     * 
     * @param timeMin Minimum length of a single request that is generated.
     * @param timeMax Maximum length of a single request that is generated.
     * @param prob Probability that a request will be generated (1 / prob).
     */
    RequestGenerator(int timeMin, int timeMax, int prob);


    /**
     * @brief Sets the probability of a request being generated.
     * 
     * @param prob Probability that a request will be generated (1 / prob).
     */
    void setRequestProbability(int prob);

    /**
     * @brief Generates a series of requests with the given likelihood and length restraints.
     * 
     * @return Vector of random Requests generated.
     */
    vector<Request> getRequests();

    /**
     * @brief Generates a series of the given number of requests with the given length restraints.
     * 
     * @param numRequests Number of random requests to be generated.
     * @return Vector of random Requests generated.
     */
    vector<Request> getRequests(int numRequests);
};