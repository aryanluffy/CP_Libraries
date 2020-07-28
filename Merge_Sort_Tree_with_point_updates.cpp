#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

//build function
//supports update and query 
class merge_sort_tree
{
    #define v32 vector <int>
    #define vt vector

  public:
	struct node
    {
      int l,r;
      __gnu_pbds::tree<int,__gnu_pbds::null_type,std::less<int>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> mp;
    };
	std::v32 a;
    std::vt <node> st; 
	
    merge_sort_tree(std::v32 b){
        a=b;
        st.resize(4*a.size());
        build(0,a.size()-1);
    }
    void build(int l,int r,int k=0){
        st[k].l=l,st[k].r=r;
        if(l==r){
            st[k].mp.insert(a[l]);
            return;
        }
        for(int i=l;i<r+1;i++)st[k].mp.insert(a[i]);
        build(l,(l+r)/2,2*k+1);
        build((l+r)/2+1,r,2*k+2);
    }
    void update(int id,int orig,int val,int k=0){
        int l=st[k].l,r=st[k].r;
        if(id<l || id>r) return;
        if(l==id && id==r){
            st[k].mp.erase(orig);
            st[k].mp.insert(val);
            return;
        }
        st[k].mp.erase(orig);
        st[k].mp.insert(val);
        update(id,orig,val,2*k+1);
        update(id,orig,val,2*k+2);
    }
    int query(int l,int r,int upper,int k=0){
        if(l>r)return 0;
        int ll=st[k].l,rr=st[k].r;
        if(r<ll || rr<l) return 0;
        if(l<=ll && rr<=r){
            return st[k].mp.order_of_key(upper);
        }
        return query(l,r,upper,2*k+1)+query(l,r,upper,2*k+2);   
    }
};

int main(){
    return 0;
}
