#include <algorithm>
#include "foundation/ConfigData.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
ConfigData::ConfigData() : 
	m_items(10),
	m_currentIndex(0)
{
	// empty
}

//--------------------------------------------------------------------------------
ConfigData::~ConfigData()
{
	std::for_each(m_items.begin(), m_items.end(), DeleteConfigItems());
}

//--------------------------------------------------------------------------------
ConfigData::ItemHandle
ConfigData::addItem(const std::string& name, const ConfigItem* item)
{
	assert(item);

	// If name is already present return invalid handle and dont add the item.
	if(m_handles.find(name) != m_handles.end())
	{
		return INVALID_HANDLE;
	}
	
	// If the vector is full, resize it
	if(m_currentIndex >= m_items.size())
	{
		m_items.resize(m_items.size() * 3);
	}
	
	// Add the item and create the handle
	m_items.at(m_currentIndex) = item;
	m_handles.insert(HandleEntry(name, m_currentIndex));
	++m_currentIndex;

	return m_currentIndex-1;
}

//--------------------------------------------------------------------------------
ConfigData::ItemHandle
ConfigData::getItemHandle(const std::string& name) const
{
	HandleIt it = m_handles.find(name);
	if(it != m_handles.end())
	{
		return it->second;
	}
	else
	{
		return INVALID_HANDLE;
	}
}

//--------------------------------------------------------------------------------
const ConfigItem*
ConfigData::getItem(ItemHandle handle) const
{
	if(handle >= 0 && handle < static_cast<int>(m_currentIndex))
	{
		return m_items.at(handle);
	}
	else
	{
		return NULL;
	}
}
