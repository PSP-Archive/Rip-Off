#pragma once

#include <string>
#include <sstream>

// Forward
class ConfigData;
class ConfigItem;

//--------------------------------------------------------------------------------
/**
	Loads the config data from a file. Th config file should have the following
	structure:
		
		item FirstItemName
			float	FloatName	10.0
			integer IntegerName 10
			string	StringName	"hello world"
			vector	Vector2Name	12.0 18.0
			vector	Vector3Name	2.0 5.0 8.0
		enditem
		// Comment line
		item SeconItemName
			...
		enditem
		...

	It is possible to load multiple config files in the same ConfigData by simply
	calling the loader with the same ConfigData but different filepaths:

		ConfigDataLoader loader;
		ConfigData data;

		loader.load("config1.dat", data);
		loader.load("config2.dat", data);

	NOTE:
	There is only one vector type. Any missed out components will be set to zero.
	This makes it usable for Vector3, Vector2 and Vector1 (and potentially Vector0,
	but that would mean that our game collapsed in a non-dimentional space and would
	be unplayable, so don't use it).

*/
class ConfigDataLoader
{
public:
	// Loads the passed file into the passed config data. Returns false if there
	// were loading errors. Note that the loader will attempt to load all possible
	// items, so it might returns false but still have loaded some valid items.
	bool load(const std::string& filepath, ConfigData& config);

private:
	// Utility function for printing a debig message
	void debugMessage(const std::string& file, unsigned int line, const std::string& message);
	
	// Utility methods for variable parsing
	bool parseFloat(std::istringstream& line, ConfigItem* item, const std::string& filepath,
		unsigned int lineNumber);
	bool parseInteger(std::istringstream& line, ConfigItem* item, const std::string& filepath,
		unsigned int lineNumber);
	bool parseString(std::istringstream& line, ConfigItem* item, const std::string& filepath,
		unsigned int lineNumber);
	bool parseVector(std::istringstream& line, ConfigItem* item, const std::string& filepath,
		unsigned int lineNumber);

	// File command names
	static const char* PARSE_NEW_ITEM;
	static const char* PARSE_END_ITEM;
	static const char* PARSE_FLOAT;
	static const char* PARSE_INTEGER;
	static const char* PARSE_STRING;
	static const char* PARSE_VECTOR;
};
