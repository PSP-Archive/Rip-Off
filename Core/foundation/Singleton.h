#pragma once

//------------------------------------------------------------------------------
/**
	Template for implementing the singleton on any class. Its quick and
	easy to use.

	Declaration:

		<< SomethingManager.h >>
		class BaseSomethingManager { ... };
		typedef Singleton<BaseSomethingManager> SomethingManager;

	Usage:

		SomethingManager::get()->doSomething();
		...
		SomethingManager::release();
*/
template<class T>
class Singleton
{
public:
	// Returns the instance of the class creating it if required.
	static T* get();

	// Returns the instance of the class creating it if required.
	static void release();

private:
	// Disable copying and assigning
	Singleton();
	~Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static T* m_instance;
};

template<class T>
T* Singleton<T>::m_instance = 0;

//------------------------------------------------------------------------------
template<class T>
inline
T*
Singleton<T>::get()
{
	if(!m_instance)
	{
		m_instance = new T();
	}

	return m_instance;
}

//------------------------------------------------------------------------------
template<class T>
inline
void
Singleton<T>::release()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = 0;
	}
}
