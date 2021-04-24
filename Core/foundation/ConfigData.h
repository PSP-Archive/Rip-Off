#pragma once

#include <string>
#include <map>
#include <vector>
#include "foundation/ConfigItem.h"

//--------------------------------------------------------------------------------
/**
	Container for named ConfigItem objects. Items are accesible from their 
	handle which should be stored the first time it is reuqested to improve
	performance.

	Usage:

		ConfigData data;
		...
		ItemHandle handle = data.getItemHandle("SHIP1");
		const ConfigItem* item = data.getItem(handle);
		
		if(item->hasFloat("power"))
		{
			float p = item->getFloat("power");
			...
		}
*/
class ConfigData
{
public:
	// Handle type for quick access to a ConfigItem
	typedef int ItemHandle;
	const static ItemHandle INVALID_HANDLE = -1;
	
	// Ctor
	ConfigData();
	~ConfigData();

	// Adds an item. ConfigData will take care of deleting them upon
	// destruction. Returns the handle to the item. If the name is already
	// present INVALID_HANDLE is returned.
	ItemHandle addItem(const std::string& name, const ConfigItem*);

	// Returns the handle to an item. Returns ConfigData::INVALID_HANDLE
	// if the item with the specified name does not exist.
	ItemHandle getItemHandle(const std::string& name) const;

	// Returns an item. Returns NULL if the handle is not a valid one.
	const ConfigItem* getItem(ItemHandle handle) const;

private:
	// Prevent copying
	ConfigData(const ConfigData&);
	ConfigData& operator=(const ConfigData&);

	// Containers and types
	std::map<std::string, unsigned int> m_handles;
	typedef std::map<std::string, unsigned int>::const_iterator HandleIt;
	typedef std::pair<std::string, unsigned int> HandleEntry;
	std::vector<const ConfigItem*> m_items;
	unsigned int m_currentIndex;

	// ConfigItem delete functor
	struct DeleteConfigItems : std::unary_function<const ConfigItem*, void> {
		void operator()(const ConfigItem* item) { delete item; } };
};
