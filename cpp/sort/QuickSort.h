#pragma once
#include <functional>
#include <iterator>
#include <utility>

namespace GIS {
namespace QuickSort {

template<class Iterator, class Compare>
Iterator partition(Iterator first, Iterator last, Compare comp) {
	auto diff = (last - first)/2;
	auto pivot = first + diff;

	std::swap(*pivot, *last);
	auto storeIt = first;
	for(auto it = first; it != last; ++it) {
		if (comp(*it, *last)) {
			if (it != storeIt) {
				std::swap(*it, *storeIt);
			}
			storeIt++;
		}
	}
	std::swap(*storeIt, *last);
	return storeIt;

}

template<class Iterator, class Compare>
void sort(Iterator first, Iterator last, Compare comp) {
	if (first < last) {
		auto pivot = GIS::QuickSort::partition<Iterator, Compare>(first, std::prev(last), comp);
		GIS::QuickSort::sort(first, pivot, comp);
		GIS::QuickSort::sort(pivot + 1, last, comp);
	}
}

template<class Iterator>
void sort(Iterator first, Iterator last) {
    typedef typename std::iterator_traits<Iterator>::value_type ValueType;
    GIS::QuickSort::sort(first, last, std::less<ValueType>());
}
} // namespace QuickSort

} // namespace GIS
