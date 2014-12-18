#include <containers/Vector.h>
#include <assert.h>
#include <iostream>

int main() {
    GIS::Vector<int> v;
    assert(v.size() == 0);
    assert(v.capacity() == 8);
    assert(v.empty());

    for (int i = 0; i < 10; i++)
        v.push_back(i);

    assert(v.size() == 10);
    assert(v.capacity() == 16);

    for (int i = 0; i < 10; i++) {
        assert(v[i] == i);
    }
    return 0;
}



