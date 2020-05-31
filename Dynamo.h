#ifndef _DYNAMO_H_
#define _DYNAMO_H_

#include <initializer_list>

namespace dynamo {
	template <typename T>
	class Array {
	private:
		T* arr;
		int size, capacity;
		void extend();
		void rightshift(const int stopAt, const int steps);
		void leftshift(const int startAt, const int steps);
		void quickSort(const int start, const int end, const int order);
		int partition(const int start, const int end, const int order);
		void swap(T& a, T& b);
	public:
		Array(const int capacity = 10);
		Array(const Array& arr);
		Array(const T* arr, const int size);
		~Array();

		T operator[](int index);
		T peak(int index);
		
		int length();

		Array<T>& pop();
		Array<T>& shift();
		Array<T>& splice(const int startingIndex, const int noItemsToDelete, std::initializer_list<T> items);
		Array<T>& push(const T item);
		Array<T>& unshift(const T item);

		bool sort(const int start, const int end, const int order = 1);
		bool sort(const int order = 1);

		Array<T>& copy(const Array& arr);
		Array<T>& concat(const Array& arr);
		Array<T>& concat(std::initializer_list<T> arr);

		bool includes(const T item);
		int indexOf(const T item);
		int lastIndexOf(const T item);

		T* begin();
		T* end();

		void forEach(void(*callback)(T item, int index));
		Array<T> map(T(*callback)(T item, int index));
		Array<T> filter(bool(*callback)(T item, int index));
		T reduce(T(*callback)(T acc, T item, int index), const T initialiValue);
		T reduce(T(*callback)(T acc, T item, int index));
		T find(bool(*callback)(T item, int index));
		int findIndex(bool(*callback)(T item, int index));
	};
}

#endif;