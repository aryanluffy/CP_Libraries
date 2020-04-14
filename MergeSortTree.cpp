#include <vector>
#include <iostream>
#include <algorithm>

class MergeSortTree
{
private:
    long long CountInArray(long long x, std::vector<int> &arr)
    {
        long long n = arr.size();
        std::vector<int>::iterator low, high;
        low = lower_bound(arr.begin(), arr.end(), x);
        if (low == (arr.end()) || *low != x)
            return 0;
        high = upper_bound(low, arr.end(), x);
        return high - low;
    }
    long long get_last_smaller(std::vector<int> &v, int x)
    {
        long long first = 0, last = v.size() - 1;
        while (first <= last)
        {
            long long mid = (first + last) / 2;
            if (v[mid] >= x)
                last = mid - 1;
            else
                first = mid + 1;
        }
        return first - 1 < 0 ? -1 : first - 1;
    }
    struct node
    {
        int l, r;
        std::vector<int> arr;
    };
    std::vector<int> a;
    std::vector<node> st;
    void build(int l, int r, int k = 0)
    {
        st[k].l = l, st[k].r = r;
        for (int i = l; i < r + 1; i++)
            st[k].arr.push_back(a[i]);
        sort(st[k].arr.begin(), st[k].arr.end());
        if (l == r)
            return;
        build(l, (l + r) / 2, 2 * k + 1);
        build((l + r) / 2 + 1, r, 2 * k + 2);
    }

public:
    MergeSortTree(std::vector<int> &b)
    {
        st.resize(4 * b.size());
        a = b;
        build(0, b.size() - 1);
    }
    //counts the number of occurences of t in the range(l,r)
    long long CountInRange(int l, int r, int t, int k = 0)
    {
        if (l > r)
            return 0;
        int ll = st[k].l, rr = st[k].r, mid = (ll + rr) / 2;
        if (ll > r || l > rr)
            return 0;
        if (ll >= l && rr <= r)
            return CountInArray(t, st[k].arr);
        return CountInRange(l, r, t, 2 * k + 1) + CountInRange(l, r, t, 2 * k + 2);
    }

    // returns number of values less than t in the range (l,r) of the array on which tree is built
    long long CountLessThan(int l, int r, int t, int k = 0)
    {
        if (l > r)
            return 0;
        int ll = st[k].l, rr = st[k].r, mid = (ll + rr) / 2;
        if (l > rr || ll > r)
            return 0;
        if (ll >= l && rr <= r)
            return get_last_smaller(st[k].arr, t) + 1;
        long long ans = 0;
        return CountLessThan(l, r, t, 2 * k + 1) + CountLessThan(l, r, t, 2 * k + 2);
    }
};

int main()
{
    return 0;
}