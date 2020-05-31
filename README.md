# Dynamo

This library was designed to be similar to the modern high-level scripting languages array API, but specifically similar to the JavaScript array API.

## Code Integration
If you want to link this library statically into your code, You can watch [this](https://www.youtube.com/watch?v=Wt4dxDNmDA8) video from TheCherno to knowhow.

## Usage
### Declaration
```	c++
dynamo::Array<[type]> name([constructor option]);
```
The constructor option could be one of three things:
1. Array Capacity (type: number, default value: 10).
2. Copy Constructor (copying other array object contents).
3. Array Pointer (size should be specified).
#### Examples:
```c++
dynamo::Array<int> arr1; // default capacity to 10
dynamo::Array<int> arr2(7); // capacity
dynamo::Array<int> arr3(arr2); // copy constructor

int numbers[3] = { 1, 2, 3 };
dynamo::Array<int> arr4(numbers, 3); // array pointer
```
### Data Access
You can access data in two ways. The array subscripting operators ``[]`` or the ``.peak()`` method.
#### Examples:
```c++
int numbers[3] = { 1, 2, 3 };
dynamo::Array<int> arr(numbers, 3);

arr[0]; // 1
arr.peak(1); // 2
```
**Note:  the array subscripting operators can't be used to manipulate data. Only used to access it.**
### Data Manipulation
All available member functions for data manipulation are:
1. ``.pop()`` Removes the array last element.
2. ``.shift()`` Removes the array first element.
3. ``.splice(startingIndex, numberOfItemsToDelete, { elements to add })`` Similar to the JavaScript array ``.splice()`` method. It takes a starting index, removes elements as much as you want starting from the specified starting point, then starts to add elements from there.
4. ``.push(item)`` Adds an element at the end of the array.
5. ``.unshift(item)`` Adds an element at the start of the array.
6. ``.sort(order, start, end)``  Sorts an array in both ascending and descending order.
	``.sort()`` by default sorts ascendingly, but if you want to change the order, you can use positive and negative integers to specify that. For example, to sort descendingly you can write ``.sort(-1)``.
7. ``.copy()`` Takes other array object and copies its content.
8. ``.concat()`` Takes both an array object and ``initializer_list `` and concatenate its content to an array. 
#### Examples:
```c++
dynamo::Array<int> arr1, arr2;

arr1.push(-1).push(2).push(7).push(5).unshift(-3); // appends -1, 2, 7, and 5 to the end of the array

arr1.sort(); // sorts the specified array

arr1.pop().shift(); // removes the first and last array element

arr1.concat({ 10, 20, 30, 40 }); // concatenate { 10, 20, 30, 40 } to the end of the array

arr1.splice(1, 2, { 100, 5 }); // starting at index 1. It removes the first 2 elements and replaces them with 100 and 5

arr2.copy(arr1); // copies arr1 content to arr2

for (int i = 0; i < arr2.length(); i++) {
  std::cout << arr2[i] << std::endl; // -1, 100, 5, 10, 20, 30, 40
}
```
**Note: all the mentioned methods can be chained together.**
## Informative Methods
1. ``.length()`` Returns the arrays size.
2. ``.includes(item)`` Returns true if the passed item is inside the array, and returns false otherwise.
3. ``indexOf(item)`` Returns the index of the specified element and returns -1 otherwise.
4. ``lastIndexOf(item)`` Returns the index of the specified element starting from the last element, and returns -1 otherwise.
5. ``.begin()`` Returns a pointer to the array first element.
6. ``.end()`` Returns a pointer to the array last element.

### Higher-Order Array Methods
Dynamo has ``.forEach()``, ``.map()``, ``.filter()``, ``.reduce()``,  ``.find()``, and ``.findIndex()`` that works exactly the same way JavaScruipt higher-order methods works with a few exceptions to the ``.reduce()`` method.
**If you are not aware of the JavaScript higher-order array methods and how they work, Check out this
[article](https://blog.bitsrc.io/understanding-higher-order-functions-in-javascript-75461803bad) You are missing a lot!.**

However, you will find a small explination for each method and what it does.
#### Examples:
```c++
#include "Dynamo.cpp"

#include <iostream>

int timesTwo(const int number, const int index) {
  return number * 2;
}

int main() {
  dynamo::Array<int> numbers;

  numbers.concat({ 1, 2, 10, 5, 7 });

  /* Iterate over each item and execute the given callback
  function for each, Note that I'm using the lambda
  function notation, however, you can use a normal function. */
  numbers.forEach([](const int number, const int index) {
    if (number % 2 == 0) {
      printf("Index: %d, Item: %d\n", index, number);
    }
  });
  /* Prints:
  Index: 1, Item: 2
  Index: 2, Item: 10
  */

  /* Map over each item and execute the given callback
  function for each, and place each returned item in its
  position in the new array.
  */
  dynamo::Array<int> mappedNumbers = numbers.map(timesTwo); // mappedNumbers => { 2, 4, 20, 10, 14 }.

  dynamo::Array<std::string> strings;

  strings.concat({ "a", "ab", "abc", "abcd", "abcde" });

  /* Iterate over each item and execute the given callback
  function for each, and only returns the item to the new array
  if the item, size is greater than 2.
  */
  dynamo::Array<std::string> filteredStrings = strings.filter([](std::string string, const int index) {
    return string.size() > 2;
  }); // filteredNames => { "abc", "abcd", "abcde" }.

  /* Summarize (reduce) the given array into one value
  And prints its output to the console. Note that the accumulator initial value starts at "a, ab".
  */
  std::cout << filteredStrings.reduce([](std::string acc, std::string string, const int index) {
    return acc + ", " + string;
  }, "a, ab"); // Prints: a, ab, abc, abcd, abcde.


  // Returns the first element that satisfies the given condition.
  numbers.find([](const int number, const int index) {
    return number > 5;
  }); // Returns 10.

  // Returns the index of the first element that satisfies the given condition.
  numbers.findIndex([](const int number, const int index) {
    return number > 5;
  }); // Returns 2.

  return 0;
}
```
