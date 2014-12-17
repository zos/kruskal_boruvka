#include <containers/List.h>
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

    for(int i = 0; i < 10; i++)
        l.pop_back();

    assert(l.size() == 0);
    return 0;
}
