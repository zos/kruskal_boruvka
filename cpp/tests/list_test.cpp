#include <containers/List.h>
#include <log/Log.h>

#include <assert.h>


int main() {
    GIS::List<int> l;
    l.push_back(1);
    assert(l.size() == 1);

    l.erase(l.begin());
    assert(l.size() == 0);

    for(int i = 0; i < 10; i++)
        l.push_back(i);
    assert(l.size() == 10);
    assert(l.front() == 0);
    assert(l.back() == 9);

    int j = 0;
    for(GIS::List<int>::iterator it = l.begin(); it != l.end(); it++) {
        assert(*it == j);
        j++;
    }

    GIS::List<int> l2 = l;
    assert(l.size() == l2.size());

    for(int i = 0; i < 10; i++)
        l.pop_back();

    assert(l.size() == 0);

    l2.erase(l2.begin(), l2.end());
    assert(l2.size() == 0);

    LOG("SUCCESS!");
    return 0;
}
