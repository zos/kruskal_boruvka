#pragma once
#include <iterator>
#include <utility>

namespace GIS {
namespace QuickSort {

template<class Iterator>
Iterator partition(Iterator first, Iterator last) {
	auto diff = (last - first)/2;
	auto pivot = first + diff;

	std::swap(*pivot, *last);
	auto storeIt = first;
	for(auto it = first; it != last; ++it) {
		if (*it < *last) {
			if (it != storeIt) {
				std::swap(*it, *storeIt);
			}
			storeIt++;
		}
	}
	std::swap(*storeIt, *last);
	return storeIt;

}

template<class Iterator>
void sort(Iterator first, Iterator last) {
	if (first < last) {
		auto pivot = partition<Iterator>(first, std::prev(last));
		sort(first, pivot);
		sort(pivot + 1, last);
	}
}
} // namespace QuickSort

} // namespace GIS
