#include "LoadBalancer.h"

bool LoadBalancer::isIPBlocked(string ip) {
    if (ipBlockLow == "" || ipBlockHigh == "") {
        return false;
    }

    size_t pos_low = 0, pos_high = 0, pos_test = 0;
    for (int i = 0; i < 3; ++i) {
        size_t pos_low_new = ipBlockLow.find('.', pos_low);
        size_t pos_high_new = ipBlockHigh.find('.', pos_high);
        size_t pos_test_new = ip.find('.', pos_test);

        size_t low_num = stoi(ipBlockLow.substr(pos_low, pos_low_new - pos_low));
        size_t high_num = stoi(ipBlockHigh.substr(pos_high, pos_high_new - pos_high));
        size_t test_num = stoi(ip.substr(pos_test, pos_test_new - pos_test));

        if (test_num < low_num || test_num > high_num) {
            return true;
        }

        pos_low = pos_low_new + 1;
        pos_high = pos_high_new + 1;
        pos_test = pos_test_new + 1;
    }

    size_t low_num = stoi(ipBlockLow.substr(pos_low));
    size_t high_num = stoi(ipBlockHigh.substr(pos_high));
    size_t test_num = stoi(ip.substr(pos_test));

    if (test_num < low_num || test_num > high_num) {
        return true;
    }

    return false;
}

LoadBalancer::LoadBalancer() : clock(0), monitor(nullptr), log(nullptr) {
    for (int i = 0; i < DEFAULT_NUM_SERVERS; ++i) {
        servers.push_back(std::move(WebServer()));
    }

    setIPBlocker("", "");
}

LoadBalancer::LoadBalancer(size_t numServers) : clock(0), monitor(nullptr), log(nullptr) {
    for (int i = 0; i < numServers; ++i) {
        servers.push_back(std::move(WebServer()));
    }

    setIPBlocker("", "");
}

LoadBalancer::LoadBalancer(size_t numServers, OutputLog* out) : clock(0), monitor(nullptr), log(out) {
    for (int i = 0; i < numServers; ++i) {
        servers.push_back(std::move(WebServer()));
    }

    setIPBlocker("", "");
}

LoadBalancer::LoadBalancer(size_t numServers, AnalyticsMonitor* mon) : clock(0), monitor(mon), log(nullptr) {
    for (int i = 0; i < numServers; ++i) {
        servers.push_back(std::move(WebServer()));
    }

    setIPBlocker("", "");
}

LoadBalancer::LoadBalancer(size_t numServers, OutputLog* out, AnalyticsMonitor* mon) : clock(0), monitor(mon), log(out) {
    for (int i = 0; i < numServers; ++i) {
        servers.push_back(std::move(WebServer()));
    }

    setIPBlocker("", "");
}

void LoadBalancer::setIPBlocker(string low, string high) {
    ipBlockLow = low;
    ipBlockHigh = high;
}

void LoadBalancer::tickClock() {
    if (clock > 0 && clock % ADJUST_INTERVAL == 0) {
        if (req_q.size() > servers.size() * ADD_FACTOR) {
            servers.push_back(std::move(WebServer()));

            if (log) {
                log->serverAdded(clock, servers.size());
            }
        }

        else if (servers.size() > 1 && req_q.size() < servers.size() * REMOVE_FACTOR) {
            servers.pop_back();

            if (log) {
                log->serverRemoved(clock, servers.size() + 1);
            }
        }
    }

    if (monitor) {
        // TODO: Log number of servers and requests
    }

    for (int i = 0; i < servers.size(); ++i) {
        bool readyForNewReq = true;
        if (servers[i].hasRequest()) {
            servers[i].processRequest();

            if (servers[i].hasCompletedRequest()) {
                Request* req = servers[i].finishRequest();

                if (log) {
                    log->requestCompleted(clock, req, i + 1);
                }

                if (monitor) {
                    // TODO: Update Completed Requests
                }

                delete req;
            }
            else {
                readyForNewReq = false;
            }
        }

        else if (!req_q.empty() && readyForNewReq) {
            Request* req = req_q.pop();
            servers[i].receiveRequest(req);

            if (log) {
                log->requestDelegated(clock, req, i + 1);
            }

            if (monitor) {
                // TODO: Update Recieved Requests By Server
            }
        }
    }

    ++clock;
}

void LoadBalancer::receiveRequests(vector<Request*> reqs) {
    for (Request* req : reqs) {
        if (isIPBlocked(req->srcIP)) {
            if (log) {
                log->requestBlocked(clock, req);
            }

            if (monitor) {
                // TODO: Update Blocked Requests
            }
            
            continue;
        }

        req_q.push(req);

        if (log) {
            log->requestReceived(clock, req);
        }

        if (monitor) {
            // TODO: Update Recieved Requests
        }
    }
}

int LoadBalancer::numRequestsQueued() {
    return req_q.size();
}