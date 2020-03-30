#ifndef TCG_H
#define TCG_H

#include "custom_header.hpp"

class RTCG
{
private:
    std::random_device rd;
    std::mt19947 gen;
    std::uniform_int_distribution<int> dis;

public:
    RTCG();
    pair<pii, pii> rtc();
    vector<pair<pii, pii>> rtcs();
};

RTCG::RTCG()
{
    gen = std::mt19947(rd());
    dis = std::uniform_int_distribution<int>(0, N);
}

pair<pii, pii> RTCG::rtc()
{
    pair<pii, pii> tc;
    tc.X.X = dis(gen);
    tc.X.Y = dis(gen);
    tc.Y.X = dis(gen);
    tc.Y.Y = dis(gen);
    return tc;
}

vector<pair<pii, pii>> RTCG::rtcs(int n)
{
    vector<pair<pii, pii>, n> tcs;
    rep(i, 0, n) tcs[i] = rtc();
    return tcs;
}


#endif