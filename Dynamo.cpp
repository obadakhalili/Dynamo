#include "Dynamo.h"

namespace dynamo {
	template <typename T>
	Array<T>::Array(int capacity) {
		capacity = capacity < 0 ? capacity * -1 : capacity;
		this->capacity = capacity;
		this->size = 0;
		this->arr = new T[capacity];
	}
	template <typename T>
	Array<T>::Array(const Array& arr) {
		this->capacity = arr.capacity;
		this->size = arr.size;
		this->arr = new T[this->size];
		this->copy(arr);
	}
	template <typename T>
	Array<T>::Array(const T* arr, const int size) {
		this->capacity = size;
		this->size = size;
		this->arr = new T[this->size];
		for (int i = 0; i < size; i++) {
			this->arr[i] = arr[i];
		}
	}
	template <typename T>
	Array<T>::~Array() {
		delete[] this->arr;
	}

	template <typename T>
	void Array<T>::extend() {
		const int newCapacity = this->capacity ? this->capacity * 2 : 1;
		T* tempArr = new T[newCapacity];
		for (int i = 0; i < this->capacity; i++) {
			tempArr[i] = this->arr[i];
		}
		delete[] arr;
		this->arr = tempArr;
		this->capacity = newCapacity;
	}
	template <typename T>
	void Array<T>::rightshift(const int stopAt, const int steps) {
		for (int i = this->size - 1; i >= stopAt; i--) {
			this->arr[i + steps] = this->arr[i];
		}
	}
	template <typename T>
	void Array<T>::leftshift(const int startAt, const int steps) {
		for (int i = startAt; i < this->size - steps; i++) {
			this->arr[i] = this->arr[i + steps];
		}
	}
	template <typename T>
	void Array<T>::quickSort(const int start, const int end, const int order) {
		if (end > start) {
			const int pivotIndex = this->partition(start, end, order);
			this->quickSort(start, pivotIndex - 1, order);
			this->quickSort(pivotIndex + 1, end, order);
		}
	}
	template <typename T>
	int Array<T>::partition(const int start, const int end, const int order) {
		int j = start - 1;
		int i = start;
		int pivotIndex = end;
		for (; i < pivotIndex; i++) {
			if (order >= 0 ? this->arr[i] <= this->arr[pivotIndex] : this->arr[i] > this->arr[pivotIndex]) {
				this->swap(this->arr[i], this->arr[++j]);
			}
		}
		this->swap(this->arr[++j], this->arr[pivotIndex]);
		return j;
	}
	template <typename T>
	void Array<T>::swap(T& a, T& b) {
		const T temp = a;
		a = b;
		b = temp;
	}

	template <typename T>
	T Array<T>::operator[](int index) {
		index = index < 0 ? index % this->size * -1 : index % this->size;
		return this->arr[index];
	}

	template <typename T>
	int Array<T>::length() {
		return this->size;
	}

	template <typename T>
	Array<T>& Array<T>::pop() {
		this->splice(this->size - 1, 1, { });
		return *this;
	}
	template <typename T>
	Array<T>& Array<T>::shift() {
		return this->splice(0, 1, { });
	}
	template <typename T>
	Array<T>& Array<T>::splice(const int startingIndex, const int noItemsToDelete, std::initializer_list<T> items) {
		const int itemsSize = items.size();
		if (startingIndex < 0 ||
			startingIndex > this->size ||
			noItemsToDelete < 0 ||
			noItemsToDelete > this->size - startingIndex) {
			return *this;
		}
		while (itemsSize > (this->capacity + noItemsToDelete) - this->size) {
			this->extend();
		}
		if (noItemsToDelete < itemsSize) {
			this->rightshift(startingIndex + noItemsToDelete, itemsSize - noItemsToDelete);
			this->size += itemsSize - noItemsToDelete;
		} else if (noItemsToDelete > itemsSize) {
			this->leftshift(startingIndex + itemsSize, noItemsToDelete - itemsSize);
			this->size -= noItemsToDelete - itemsSize;
		}
		T const* itemsPtr = items.begin();
		for (int i = startingIndex, j = 0; i < itemsSize + startingIndex; i++, j++) {
			this->arr[i] = itemsPtr[j];
		}
		
		return *this;
	}
	template <typename T>
	Array<T>& Array<T>::push(const T item) {
		return this->splice(this->size, 0, { item });
	}
	template <typename T>
	Array<T>& Array<T>::unshift(const T item) {
		return this->splice(0, 0, { item });
	}
	template <typename T>
	T Array<T>::peak(int index) {
		return this->operator[](index);
	}

	template <typename T>
	bool Array<T>::sort(const int start, const int end, const int order) {
		if (start < 0 || start > this->size - 1 || end < 0 || end > this->size - 1) {
			return false;
		}
		this->quickSort(start, end, order);
		return true;
	}
	template <typename T>
	bool Array<T>::sort(const int order) {
		return this->sort(0, this->length() - 1, order);
	}

	template <typename T>
	Array<T>& Array<T>::copy(const Array& obj) {
		this->size = obj.size;
		for (int i = 0; i < obj.size; i++) {
			this->splice(i, 1, { obj.arr[i] });
		}
		return *this;
	}	
	template <typename T>
	Array<T>& Array<T>::concat(const Array& obj) {
		for (int i = 0; i < obj.size; i++) {
			this->splice(this->size, 0, { obj.arr[i] });
		}
		return *this;
	}
	template <typename T>
	Array<T>& Array<T>::concat(std::initializer_list<T> arr) {
		this->splice(this->size, 0, arr);
		return *this;
	}

	template <typename T>
	bool Array<T>::includes(const T item) {
		for (int i = 0; i < this->size; i++) {
			if (this->arr[i] == item) {
				return true;
			}
		}
		return false;
	}
	template <typename T>
	int Array<T>::indexOf(const T item) {
		for (int i = 0; i < this->size; i++) {
			if (this->arr[i] == item) {
				return i;
			}
		}
		return -1;
	}
	template <typename T>
	int Array<T>::lastIndexOf(const T item) {
		for (int i = this->size - 1; i >= 0; i--) {
			if (this->arr[i] == item) {
				return i;
			}
		}
		return -1;
	}

	template <typename T>
	T* Array<T>::begin() {
		return this->arr;
	}
	template <typename T>
	T* Array<T>::end() {
		return this->arr + this->size - 1;
	}

	template <typename T>
	void Array<T>::forEach(void(*callback)(T item, int index)) {
		for (int i = 0; i < this->size; i++) {
			callback(this->arr[i], i);
		}
	}
	template <typename T>
	Array<T> Array<T>::map(T(*callback)(T item, int index)) {
		Array<T> arr(this->size);
		for (int i = 0; i < this->size; i++) {
			arr.push(callback(this->arr[i], i));
		}
		return arr;
	}
	template <typename T>
	Array<T> Array<T>::filter(bool(*callback)(T item, int index)) {
		Array<T> arr(this->size / 2);
		for (int i = 0; i < this->size; i++) {
			if (callback(this->arr[i], i)) {
				arr.push(this->arr[i]);
			}
		}
		return arr;
	}
	template <typename T>
	T Array<T>::reduce(T(*callback)(T acc, T item, int index), const T initialiValue) {
		T accumulator = initialiValue;
		for (int i = 0; i < this->size; i++) {
			accumulator = callback(accumulator, this->arr[i], i);
		}
		return accumulator;
	}
	template <typename T>
	T Array<T>::reduce(T(*callback)(T acc, T item, int index)) {
		return this->reduce(callback, this->arr[0]);
	}
	template <typename T>
	T Array<T>::find(bool(*callback)(T item, int index)) {
		for (int i = 0; i < this->size; i++) {
			if (callback(this->arr[i], i)) {
				return this->arr[i];
			}
		}
		return this->arr[this->size - 1];
	}
	template <typename T>
	int Array<T>::findIndex(bool(*callback)(T item, int index)) {
		for (int i = 0; i < this->size; i++) {
			if (callback(this->arr[i], i)) {
				return i;
			}
		}
		return -1;
	}
}
