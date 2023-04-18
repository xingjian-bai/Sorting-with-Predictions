#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <queue>
#include <set>
#include <map>

using namespace std;

struct Element {
    int A_index; // the index in original array
    int p; //predicted rank
    int t; //true rank
    Element () {}
    Element (int rank, int index) {
        A_index = index;
        t = rank;
    }
};
bool cmp_predicted (const Element &u, const Element &v) {
    return u.p < v.p;
}

int value_comparison_count = 0;
bool cmp_value(const Element &u, const Element &v, bool mock = false)
{
    value_comparison_count+= (mock == false);
    return u.t < v.t; // technically cheating but fine
}

typedef vector<Element> List;

struct Sorted_List { // sorted by value
    List l;

    void clear() {
        l.resize(0);
    }
    void insert (Element u, int pos) {
        Element prev = u;
        for (int i = pos; i < l.size(); i ++) {
            Element tmp = l[i];
            l[i] = prev;
            prev = tmp;
        }
        l.push_back(prev);
    }
    void insert (Element u) {
        //insert by binary search, for the first pos p with u < l[p]
        int st = 0, ed = l.size() - 1;
        if (cmp_value(l[ed], u)) {
            insert(u, l.size());
            return;
        }
        while (ed - st > 1)
        {
            int mid = ((st + ed + 1) >> 1) - 1;
            if (cmp_value(u, l[mid]))
                ed = mid + 1;
            else
                st = mid + 1;
        }
        insert(u, st);
        assert_ordered();
    }
    bool if_ordered () {
        bool ordered = true;
        for (int i = 1; i < l.size(); i++)
            ordered &= cmp_value(l[i - 1], l[i], true);
        return ordered;
    }
    void assert_ordered() {
        assert(if_ordered());
    }
};

List A;
Sorted_List sorted_A;
void init(int n = 1000) {
    srand(time(0));
    A.resize(0), sorted_A.clear();

    int rt[n];
    for (int i = 0; i < n; i ++)
        rt[i] = i;
    random_shuffle(rt, rt + n);

    for (int i = 0; i < n; i ++) {

    } 

}

int main()
{

    return 0;
}