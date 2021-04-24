#pragma once

#include <vector>
#include <cassert>

//--------------------------------------------------------------------------------
/**
	Template array class for a quick and simple Array class. Has the speed of the
	STL vector without the pain of using iterators.

	To iterate though the Array:

		Array<Object*> array;
		...
		for(array.start(); !array.finish(); array.next())
		{
			array.current()->doSomething();
		}

	WARNING: do not iterate though the same list in nested loops!
*/
template<class T>
class Array
{
public:
	// Ctor - creates an empty array.
	Array();

	// Ctor - Initializes n elements by calling their default ctor.
	Array(unsigned int n);

	// Ctor - Initializes n elements by calling their copy ctor.
	Array(unsigned int n, const T& value);

	// Get the total number of points in the list.
	unsigned int size() const { return m_items.size(); }

	// Adds an element to the array. Will increase the size of the array.
	void add(const T& item);

	void clear();

	// Direct access to an element
	T& operator[](unsigned int index);

	// Resizes the array initializing new elements with the default ctor.
	void resize(unsigned int newSize);

	// Resizes the array initializing new elements with the copy ctor.
	void resize(unsigned int newSize, const T& value);

	// Starts iteration.
	void start();

	// Increments to the next item during an iteration.
	void next();

	// Returns the current item in the iteration.
	T& current();

	// Checks whether the iteration has reached the end.
	bool finish();

private:
	std::vector<T> m_items;
	typename std::vector<T>::iterator m_iterator;
};

//--------------------------------------------------------------------------------
template<class T>
inline
Array<T>::Array()
{
	// empty
}

//--------------------------------------------------------------------------------
template<class T>
inline
Array<T>::Array(unsigned int n) :
	m_items(n)
{
	// empty
}

//--------------------------------------------------------------------------------
template<class T>
inline
Array<T>::Array(unsigned int n, const T& value) :
	m_items(n, value)
{
	// empty
}

//--------------------------------------------------------------------------------
template<class T>
inline
void
Array<T>::add(const T& item)
{
	m_items.push_back(item);
}

template<class T>
inline
void
Array<T>::clear()
{
	m_items.clear();
}

//--------------------------------------------------------------------------------
template<class T>
inline
T&
Array<T>::operator[](unsigned int index)
{
	assert(index < m_items.size());
	return m_items.at(index);
}

//--------------------------------------------------------------------------------
template<class T>
inline
void
Array<T>::resize(unsigned int newSize)
{
	m_items.resize(newSize);
}

//--------------------------------------------------------------------------------
template<class T>
inline
void
Array<T>::resize(unsigned int newSize, const T& value)
{
	m_items.resize(newSize, value);
}

//--------------------------------------------------------------------------------
template<class T>
inline
void
Array<T>::start()
{
	m_iterator = m_items.begin();
}

//--------------------------------------------------------------------------------
template<class T>
inline
void
Array<T>::next()
{
	m_iterator++;
}

//--------------------------------------------------------------------------------
template<class T>
inline
T&
Array<T>::current()
{
	return *m_iterator;
}

//--------------------------------------------------------------------------------
template<class T>
inline
bool
Array<T>::finish()
{
	return m_iterator == m_items.end();
}
