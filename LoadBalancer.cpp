#include "LoadBalancer.h"

uint32_t ipToInt(const std::string& ip) {
    std::istringstream iss(ip);
    uint32_t result = 0;
    std::string segment;
    while (std::getline(iss, segment, '.')) {
        result = (result << 8) | std::stoi(segment);
    }
    return result;
}

bool LoadBalancer::isIPBlocked(string ip) {
    if (ipBlockLow == "" || ipBlockHigh == "") {
        return false;
    }

    uint32_t ipInt = ipToInt(ip);
    uint32_t lowerBoundInt = ipToInt(ipBlockLow);
    uint32_t upperBoundInt = ipToInt(ipBlockHigh);

    return (ipInt >= lowerBoundInt) && (ipInt <= upperBoundInt);
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
            ++serversToRemove;
        }
    }

    if (monitor) {
        monitor->updateServerAndRequestData(clock, servers.size(), numServersFull(), req_q.size());
    }

    for (int i = 0; i < servers.size(); ++i) {
        bool readyForNewReq = true;
        if (servers[i].hasRequest()) {
            servers[i].processRequest();

            if (servers[i].hasCompletedRequest()) {
                Request req = servers[i].finishRequest();

                if (log) {
                    log->requestCompleted(clock, req, i + 1);
                }

                if (monitor) {
                    monitor->requestCompleted();
                }

                if ((i == servers.size() - 1) && serversToRemove > 0) {
                    servers.pop_back();
                    --serversToRemove;

                    if (log) {
                        log->serverRemoved(clock, servers.size() + 1);
                    }
                }
            }
            else {
                readyForNewReq = false;
            }
        }

        if (!req_q.empty() && readyForNewReq) {
            Request req = req_q.pop();
            servers[i].receiveRequest(req);

            if (log) {
                log->requestDelegated(clock, req, i + 1);
            }

            if (monitor) {
                monitor->requestDelegated();
            }
        }
    }

    ++clock;
}

void LoadBalancer::receiveRequests(vector<Request> reqs) {
    for (Request req : reqs) {
        if (isIPBlocked(req.srcIP)) {
            if (log) {
                log->requestBlocked(clock, req);
            }

            if (monitor) {
                monitor->requestBlocked();
            }
            
            continue;
        }

        req_q.push(req);

        if (log) {
            log->requestReceived(clock, req);
        }

        if (monitor) {
            monitor->requestReceived();
        }
    }
}

int LoadBalancer::numRequestsQueued() {
    return req_q.size();
}

int LoadBalancer::numServersFull() {
    int count = 0;
    for (WebServer& server : servers) {
        if (server.hasRequest()) {
            ++count;
        }
    }

    return count;
}

size_t LoadBalancer::getClock() {
    return clock;
}