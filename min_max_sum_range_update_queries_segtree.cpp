#include <iostream>
#include <vector>

class LAZY
{
private:
    //structure of a node in the segment tree
    struct node
    {
        long long l, r, lazy = 0;
        long long lazyval = 0, sum = 0;
        std::pair<long long, long long> maxel = {-1, -1e9};
        std::pair<long long, long long> minel = {-1, 1e9};
    };

    //The segment tree itself
    std::vector<node> st;
    //A copy of the array
    std::vector<long long> h;

    //A utility to build the segment tree
    void build(int l, int r, int k = 0)
    {
        st[k].l = l, st[k].r = r;
        if (l == r)
        {
            st[k].sum = h[l];
            st[k].maxel = {l, h[l]};
            st[k].minel = {l, h[l]};
            return;
        }
        build(l, (l + r) / 2, 2 * k + 1);
        build((l + r) / 2 + 1, r, 2 * k + 2);
        st[k].sum = st[2 * k + 1].sum + st[2 * k + 2].sum;
        if (st[2 * k + 1].maxel.second >= st[2 * k + 2].maxel.second)
            st[k].maxel = st[2 * k + 1].maxel;
        else
            st[k].maxel = st[2 * k + 2].maxel;
        if (st[2 * k + 1].minel.second <= st[2 * k + 2].minel.second)
            st[k].minel = st[2 * k + 1].minel;
        else
            st[k].minel = st[2 * k + 2].minel;
    }

    //A utility function to shift lazy value to the children of node k
    void shift(int k)
    {
        st[k].sum += (st[k].r - st[k].l + 1) * st[k].lazyval;
        st[k].maxel.second += st[k].lazyval;
        st[k].minel.second += st[k].lazyval;
        if (st[k].l != st[k].r)
        {
            st[2 * k + 1].lazyval += st[k].lazyval;
            st[2 * k + 2].lazyval += st[k].lazyval;
            st[2 * k + 1].lazy = st[2 * k + 2].lazy = 1;
        }
        st[k].lazyval = 0;
        st[k].lazy = 0;
    }

public:
    LAZY(std::vector<long long> &a)
    {
        h = a;
        st.resize(4 * h.size());
        build(0, h.size() - 1);
    }
    LAZY()
    {
    }

    //Initilaize the segtree with 0 as value for all elements and n as the size of
    //the array on which the segtree has to be built
    LAZY(int n)
    {
        st.resize(4 * n);
        h.assign(n, 0);
        build(0, n - 1);
    }

    void SetAndBuild(std::vector <long long> &a)
    {   
        if(a.size()==0)return;
        h=a;
        st.resize(4*a.size());
        build(0,a.size()-1);
    }
    //returns the sum of the elements having index between l and r both inclusive
    long long query(int l, int r, int k = 0)
    {
        if (st[k].lazy != 0)
            shift(k);
        int ll = st[k].l, rr = st[k].r, mid = (ll + rr) / 2;
        if (l > rr || ll > r)
            return 0;
        if (ll >= l && rr <= r)
            return st[k].sum;
        return query(l, r, 2 * k + 1) + query(l, r, 2 * k + 2);
    }

    //returns the leftmost element in range(l,r) which is having maximum value
    //in the form of a pair the first is the position of the element
    //and second is its value
    std::pair<long long, long long> maxquery(int l, int r, int k = 0)
    {
        if (st[k].lazy != 0)
            shift(k);
        int ll = st[k].l, rr = st[k].r, mid = (ll + rr) / 2;
        if (ll > r || l > rr)
            return {-1, -1e9 * 1000000ll};
        if (ll >= l && rr <= r)
            return st[k].maxel;
        std::pair<long long, long long> ans = maxquery(l, r, 2 * k + 1), ans2 = maxquery(l, r, 2 * k + 2);
        if (ans.second >= ans2.second)
            return ans;
        return ans2;
    }

    //returns the leftmost element in range(l,r) which is having minimum value
    //in the form of a pair the first is the position of the element
    //and second is its value
    std::pair<long long, long long> minquery(int l, int r, int k = 0)
    {
        if (st[k].lazy != 0)
            shift(k);
        int ll = st[k].l, rr = st[k].r, mid = (ll + rr) / 2;
        if (ll > r || l > rr)
            return {-1, 1e9 * 1000000ll};
        if (ll >= l && rr <= r)
            return st[k].minel;
        std::pair<long long, long long> ans = minquery(l, r, 2 * k + 1), ans2 = minquery(l, r, 2 * k + 2);
        if (ans.second <= ans2.second)
            return ans;
        return ans2;
    }

    //updates the array range(l,r) such that for each i between l and r (both inclusive)
    //sets a[i]=a[i]+x
    void update(int l, int r, long long x, int k = 0)
    {
        if (l > r)
            return;

        int ll = st[k].l, rr = st[k].r, mid = (ll + rr) / 2;

        if (ll > r || l > rr)
            return;

        if (ll >= l && rr <= r)
        {
            st[k].lazyval += x;
            st[k].lazy = 1;
            return;
        }

        if (st[k].lazy != 0)
            shift(k);

        update(l, r, x, 2 * k + 1);
        update(l, r, x, 2 * k + 2);

        if (st[2 * k + 1].lazy != 0)
            shift(2 * k + 1);

        if (st[2 * k + 2].lazy != 0)
            shift(2 * k + 2);

        st[k].sum = st[2 * k + 1].sum + st[2 * k + 2].sum;

        if (st[2 * k + 1].maxel.second >= st[2 * k + 2].maxel.second)
            st[k].maxel = st[2 * k + 1].maxel;
        else
            st[k].maxel = st[2 * k + 2].maxel;

        if (st[2 * k + 1].minel.second <= st[2 * k + 2].minel.second)
            st[k].minel = st[2 * k + 1].minel;
        else
            st[k].minel = st[2 * k + 2].minel;
    }
};

int main()
{
    LAZY temp;
    
    return 0;
}