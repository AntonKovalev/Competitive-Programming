#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstdint>

using namespace std;
// Partly made from pseudo code on Wikipedia :)

//! Takes a container with numerical values and
//! returns the longest incresing subsequece.
template <class ContainerT, class ValueT>
void lis(ContainerT& sequence,
         ContainerT& answer)
{
    int32_t N = sequence.size();
    ValueT P[N], M[N + 1];
    int32_t L, lo, hi, mid, newL, k;
    L = 0;

    for (int i = 0; i < N; ++i)
    {
        // Binary search for the largest positive j = L
        // such that X[M[j]] < X[i]
        lo = 1;
        hi = L;
        while (lo <= hi)
        {
            mid = ceil((lo + hi) / 2.0);
            if (sequence[M[mid]] < sequence[i])
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        // After searching, lo is 1 greater than the
        // length of the longest prefix of X[i]
        newL = lo;

        // The predecessor of X[i] is the last index of
        // the subsequence of length newL-1
        P[i] = M[newL - 1];
        M[newL] = i;

        // If we found a subsequence longer than any we've
        // found yet, update L
        if (newL > L)
            L = newL;
    }
    // Reconstruct the longest increasing subsequence
    k = M[L];
    answer.resize(L);
    for (int i = L - 1; i >= 0; i--)
    {
        answer[i] = k;
        k = P[k];
    }
    /*printf("%d\n", L);
    for (int i = 0; i <= L - 1; i++)
    {
        if (i == L - 1)
            printf("%d\n ", S[i]);
        else
            printf("%d ", S[i]);
    }*/
}

int main()
{
    int N;
    while (scanf("%d", &N) == 1)
    {
        vector<int32_t> seq;
        seq.resize(N);
        for (int i = 0; i < N; i++)
            scanf("%d", &seq[i]);
        vector<int32_t> ans;
        lis<vector<int>,int32_t>(seq,ans);
        printf("%d\n", ans.size());
        for (int i = 0; i <= ans.size() - 1; i++)
        {
            if (i == ans.size() - 1)
                printf("%d\n ", ans[i]);
            else
                printf("%d ", ans[i]);
        }
    }
    return 0;
}