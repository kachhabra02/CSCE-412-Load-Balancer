/** @file RequestQueue.h
* @brief Defines the RequestQueue class.
* @author Krish Chhabra
*/

#pragma once

#include "Request.h"
#include <queue>
#include <string>
using std::queue, std::string;

/**
* @class RequestQueue
* @brief Queue for holding Request objects.
*/
class RequestQueue {
private:
    /** 
    * @brief Underlying queue storing the requests.
    */
    queue<Request> q;

public:
    /**
    * @brief Constructs an empty request queue.
    */
    RequestQueue();
    
    
    /**
    * @brief Retrieves number of requests in queue.
    * @return Number of requests in queue.
    */
    size_t size();

    /**
    * @brief Checks if their are any requests in the queue.
    * @return True is no requests in the queue, false otherwise.
    */
    bool empty();

    /**
    * @brief Adds a request to the end of the queue.
    * @param req Request to add to queue.
    */
    void push(Request req);

    /**
    * @brief Removes request from the front of the queue.
    * @return Request that was removed from the queue.
    */
    Request pop();

    /**
    * @brief Retrieves request from the front of the queue.
    * @return Request at the front of the queue.
    */
    Request front();
};