/** @file Request.h
* @brief Declares the Request data struct.
* @author Krish Chhabra
*/

#pragma once

#include <string>
using std::string;

/** 
* @struct Request
* @brief Stores information about a client request.
*/
struct Request {
    /** Source IP address */
    string srcIP;

    /** Source IP address */
    string dstIP;

    /** Duration of the request */
    int time;
};