#include "foundation/ConfigDataLoader.h"
#include "foundation/File.h"
#include "foundation/ConfigItem.h"
#include "foundation/ConfigData.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

const char* ConfigDataLoader::PARSE_NEW_ITEM = "item";
const char* ConfigDataLoader::PARSE_END_ITEM = "enditem";
const char* ConfigDataLoader::PARSE_FLOAT = "float";
const char* ConfigDataLoader::PARSE_INTEGER = "integer";
const char* ConfigDataLoader::PARSE_STRING = "string";
const char* ConfigDataLoader::PARSE_VECTOR = "vector";

//--------------------------------------------------------------------------------
bool
ConfigDataLoader::load(const std::string& filepath, ConfigData& config)
{
	// Open file
	File file;
	if(!file.open(filepath))
	{
		return false;
	}

	bool errorFlag = true;
	std::string buffer;
	ConfigItem* item = NULL;
	std::string token;
	std::string name;
	unsigned int lineNumber = 0;


	// Scan all lines
	while(file.readLine(buffer))
	{
		++lineNumber;
		
		// Read line and check for comment line, prevent string stream
		//if ((buffer.size() == 0) || (buffer[0] == '/' && buffer[1] == '/'))
		//{
		//	continue;
		//}

		// Read line and check for blank or comment line.
		std::istringstream line;
		line.str(buffer);
		line.clear();
		if(!(line >> token) || (token[0] == '/' && token[1] == '/'))
		{
			line.clear();
			continue;
		}
		
		// Declaring a new item
		if(PARSE_NEW_ITEM == token)
		{
			// Check if not already in a declared item
			if(item == NULL)
			{
				// Check if name
				if((line >> name) && config.getItemHandle(name) == ConfigData::INVALID_HANDLE)
				{
					item = new ConfigItem();
				}
				else
				{
					errorFlag = false;
					debugMessage(filepath, lineNumber, "Duplicate or missing item name.");
				}
			}
			else
			{
				errorFlag = false;
				debugMessage(filepath, lineNumber, "New item declared before previous one was closed.");
			}
		}
		// Closing the current item
		else if(PARSE_END_ITEM == token)
		{
			// Check if in a declared item
			if(item != NULL)
			{
				// Add the item to the config file as we already checked if the name is a duplicate.
				config.addItem(name, item);
				item = NULL;
			}
			else
			{
				errorFlag = false;
				debugMessage(filepath, lineNumber, "Invalid item end");
			}
		}
		// Float parameter
		else if(PARSE_FLOAT == token)
		{
			errorFlag &= parseFloat(line, item, filepath, lineNumber);
		}
		// Integer parameter
		else if(PARSE_INTEGER == token)
		{
			errorFlag &= parseInteger(line, item, filepath, lineNumber);
		}
		// String parameter
		else if(PARSE_STRING == token)
		{
			errorFlag &= parseString(line, item, filepath, lineNumber);
		}
		// String parameter
		else if(PARSE_VECTOR == token)
		{
			errorFlag &= parseVector(line, item, filepath, lineNumber);
		}
		// Invalid command
		else
		{
			debugMessage(filepath, lineNumber, "Invalid command");
		}

	}

	// Check if there is an unclosed item
	if(item != NULL)
	{
		config.addItem(name, item);
		item = NULL;

		errorFlag = false;
		debugMessage(filepath, lineNumber, "Unclosed item at the end of file, closing autoamtically");
	}

	file.close();
	return errorFlag;
}

//--------------------------------------------------------------------------------
void
ConfigDataLoader::debugMessage(const std::string& file, unsigned int line,
	const std::string& message)
{
	std::ostringstream output;
	output << "PARSE ERROR: \"" << message << "\" in file \"" << file << "\" on line " << line;
	Debug::get()->output(output.str());
}

//--------------------------------------------------------------------------------
bool
ConfigDataLoader::parseFloat(std::istringstream& line, ConfigItem* item, const std::string& filepath,
		unsigned int lineNumber)
{
	std::string token;
	
	// Check if in a declared item
	if(item != NULL)
	{
		// Check name
		if((line >> token))
		{
			float value = 0.0f;
			line >> value;
			item->setFloat(token, value);
		}
		else
		{
			debugMessage(filepath, lineNumber, "Missing float variable name");
			return false;
		}
	}
	else
	{
		debugMessage(filepath, lineNumber, "Float variable not in an item");
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------
bool
ConfigDataLoader::parseInteger(std::istringstream& line, ConfigItem* item, const std::string& filepath,
		unsigned int lineNumber)
{
	std::string token;
	
	// Check if in a declared item
	if(item != NULL)
	{
		// Check name
		if((line >> token))
		{
			int value = 0;
			line >> value;
			item->setInteger(token, value);
		}
		else
		{
			debugMessage(filepath, lineNumber, "Missing integer variable name");
			return false;
		}
	}
	else
	{
		debugMessage(filepath, lineNumber, "Integer variable not in an item");
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------
bool
ConfigDataLoader::parseString(std::istringstream& line, ConfigItem* item, const std::string& filepath,
		unsigned int lineNumber)
{
	std::string token;

	// Check if in a declared item
	if(item != NULL)
	{
		// Check name
		if((line >> token))
		{
			std::string value;
			line >> value;
			item->setString(token, value);
		}
		else
		{
			debugMessage(filepath, lineNumber, "Missing string variable name");
			return false;
		}
	}
	else
	{
		debugMessage(filepath, lineNumber, "String variable not in an item");
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------
bool
ConfigDataLoader::parseVector(std::istringstream& line, ConfigItem* item, const std::string& filepath,
		unsigned int lineNumber)
{
	std::string token;

	// Check if in a declared item
	if(item != NULL)
	{
		// Check name
		if((line >> token))
		{
			Vector3f value(0.0f, 0.0f, 0.0f);
			line >> value[0];
			line >> value[1];
			line >> value[2];
			item->setVector(token, value);
		}
		else
		{
			debugMessage(filepath, lineNumber, "Missing vector variable name");
			return false;
		}
	}
	else
	{
		debugMessage(filepath, lineNumber, "Vector variable not in an item");
		return false;
	}

	return true;
}

