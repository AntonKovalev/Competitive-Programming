#include <algorithm>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <array>
#include <string>
#include <sstream>

using namespace std;

// Note 'src' snd 'dest' are irrelevant in this problem.
struct call
{
public:
    call(int32_t src, int32_t dest, int32_t start, int32_t dur)
        : m_src(src), m_dest(dest), m_start(start), m_dur(dur)
    {
    }

    int32_t m_src, m_dest, m_start, m_dur;
};
using Interval = pair<int32_t, int32_t>;

bool overlap(call _call, pair<int32_t, int32_t> interval)
{
    auto end_call = _call.m_start + _call.m_dur;
    auto end_interval = interval.first + interval.second;

    if (end_interval > _call.m_start && interval.first < end_call)
    {
        return true;
    }

    return false;
}

int32_t calculate(vector<call> &calls, Interval &interval)
{
    int32_t ans = 0;
    for (auto i = 0; i < calls.size(); ++i)
    {
        if (overlap(calls[i], interval))
        {
            ans++;
        }
    }
    return ans;
}

int main()
{
    int n, m, src, dest, start, dur;
    vector<call> calls;
    vector<Interval> intervals;
    cin >> n >> m;
    calls.reserve(n + 1);
    intervals.reserve(m + 1);
    while (n != 0 && m != 0)
    {
        for (auto i = 0; i < n; ++i)
        {
            cin >> src >> dest >> start >> dur;
            call m_call = {src, dest, start, dur};
            calls.push_back(m_call);
        }
        for (auto j = 0; j < m; ++j)
        {
            cin >> start >> dur;
            Interval m_interval = {start, dur};
            intervals.push_back(m_interval);
        }

        for (auto i = 0; i < intervals.size(); ++i)
        {
            cout << calculate(calls, intervals[i]) << endl;
        }

        cin >> n >> m;
        calls.clear();
        intervals.clear();
    }
    return 0;
}
