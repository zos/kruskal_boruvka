#include <log/Log.h>
#include <sort/QuickSort.h>

#include <algorithm>
#include <assert.h>
#include <vector>

int main() {
    std::vector<int> v = {10, 9, 2, 7, 6, 5, 1, 8, 3, 4};
    GIS::QuickSort::sort(v.begin(), v.end());

    for (unsigned i = 0; i < v.size(); i++)
        assert(v[i] == (int)i+1);

    std::vector<int> vbig;

    for ( unsigned i = 0; i < 1000000; i++)
        vbig.push_back(i);

    for (int i = 0; i < 100; i++) {
        GIS::QuickSort::sort(vbig.begin(), vbig.end());
        for (unsigned i = 0; i < vbig.size(); i++)
            assert(vbig[i] == (int)i);
        std::next_permutation(vbig.begin(), vbig.end());
    }
    LOG("SUCCESS!");
    return 0;
}




