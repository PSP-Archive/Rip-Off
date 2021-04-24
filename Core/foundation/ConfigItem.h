#pragma once

#include <string>
#include <map>
#include <cassert>

#include "foundation/Vector3f.h"

//--------------------------------------------------------------------------------
/**
	Single configuration item. Containes named typed variables.
	
	NOTE:
	Should always check if the item has the required variable with the
	hasXxxx() as if it does not an assert will fail (DEBUG) or a meaningless value
	will be returned (RELEASE).

	NOTE:
	Vector currently implemented as a Vector3f as Vector4f is an incomplete class.
	Should be changed to Vector4f once the class will have all funcionality
	implemented. For Color variables use Vector3fs and add the alpha as a float
	variable if it is needed.
*/
class ConfigItem
{
public:
	// Floats
	void setFloat(const std::string &name, float value) { m_floats.set(name, value); }
	bool hasFloat(const std::string &name) const { return m_floats.has(name); }
	float getFloat(const std::string &name) const { return m_floats.get(name); }

	// Ints
	void setInteger(const std::string &name, int value) { m_ints.set(name, value); }
	bool hasInteger(const std::string &name) const { return m_ints.has(name); }
	int getInteger(const std::string &name) const { return m_ints.get(name); }

	// Strings
	void setString(const std::string &name, const std::string& value) { m_strings.set(name, value); }
	bool hasString(const std::string &name) const { return m_strings.has(name); }
	std::string getString(const std::string &name) const { return m_strings.get(name); }

	// Vectors
	void setVector(const std::string &name, const Vector3f& value) { m_vectors.set(name, value); }
	bool hasVector(const std::string &name) const { return m_vectors.has(name); }
	Vector3f getVector(const std::string &name) const { return m_vectors.get(name); }


	//removes all the elements from the item
	void clear(){
		m_vectors.clear();
		m_strings.clear();
		m_ints.clear();
		m_floats.clear();
	}

private:
	// Template class that implements a named variable map
	template<typename T>
	class VariableMap
	{
	public:	
		// Sets/adds a variable
		void set(const std::string& name, const T& value);

		// Checks whether a variable is present
		bool has(const std::string& name) const;

		// Returns the value of a variable
		T get(const std::string& name) const;

		//removes all the entries
		void clear();

	private:
		std::map<std::string, T> m_vars;
		typedef typename std::map<std::string, T>::const_iterator VarIterator;
		typedef typename std::pair<std::string, T> VarEntry;
	};

	// The variable lists
	VariableMap<float> m_floats;
	VariableMap<int> m_ints;
	VariableMap<std::string> m_strings;
	VariableMap<Vector3f> m_vectors;
};


//--------------------------------------------------------------------------------
template<typename T>
inline
void
ConfigItem::VariableMap<T>::clear()
{
	m_vars.clear();
}

//--------------------------------------------------------------------------------
template<typename T>
inline
void
ConfigItem::VariableMap<T>::set(const std::string& name, const T& value)
{
	m_vars.insert(VarEntry(name, value));
}

//--------------------------------------------------------------------------------
template<typename T>
inline
bool
ConfigItem::VariableMap<T>::has(const std::string& name) const
{
	VarIterator it = m_vars.find(name);
	return it != m_vars.end();
}

//--------------------------------------------------------------------------------
template<typename T>
inline
T
ConfigItem::VariableMap<T>::get(const std::string& name) const
{
	VarIterator it = m_vars.find(name);
	if(it != m_vars.end())
	{
		return it->second;
	}
	else
	{
		// Variable not found
		assert(false);
		return T();
	}
}
