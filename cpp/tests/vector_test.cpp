#include <containers/Vector.h>
#include <log/Log.h>

#include <assert.h>

int main() {
    GIS::Vector<int> v;
    assert(v.size() == 0);
    assert(v.capacity() == 8);
    assert(v.empty());

    for (int i = 0; i < 10; i++)
        v.push_back(i);
    assert(v.size() == 10);
    assert(v.capacity() == 16);
    assert(v.front() == 0);
    assert(v.back() == 9);

    for (int i = 0; i < 10; i++) {
        assert(v[i] == i);
    }

    for (int i = 0; i < 9; i++) {
        assert(v.front() == i);
        v.erase(v.begin());
    }
    assert(v.front() == 9);

    v.clear();
    assert(v.size() == 0);
    assert(v.begin() == v.end());
    v.resize(10, -1);
    assert(v.size() == 10);
    for(unsigned i = 0; i < v.size(); i++) {
        assert(v[i] == -1);
    }

    GIS::Vector<int> v2;
    for (int i = 0; i < 20; i++)
        v2.push_back(i);
    v2.erase(v2.begin() + 10, v2.begin() + 15);
    for (unsigned i = 0; i < v2.size(); i++)
        LOG(v2[i]);
    v2.erase(v2.begin() + 10, v2.end());
    LOG("size: " << v2.size());
    for (unsigned i = 0; i < v2.size(); i++)
        LOG(v2[i]);
    LOG("SUCCESS!");
    return 0;
}



