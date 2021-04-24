#pragma once

#include <cassert>

class ConfigItem;

//--------------------------------------------------------------------------------
/**
	Class that interfaces the specific OS functionality with the Application.
*/
class OSIF
{
public:
	// Called once when the application is lanuched
	bool init(const ConfigItem*) { assert(!"Interface not implemented"); }

	// Called at the beginning of the application loop.
	void preUpdate() { assert(!"Interface not implemented"); }

	// Called at the end of the application loop.
	void postUpdate() { assert(!"Interface not implemented"); }

	// Called once when the application closes
	void cleanUp() { assert(!"Interface not implemented"); }

	// Returns whether the OS has requested the application to quit
	bool quitRequested() { assert(!"Interface not implemented"); return false; }

	// Returns the screen width
	int GetScreenWidth() const { return m_width; }

	// Returns the screen height
	int GetScreenHeight() const { return m_height; }

	// Returns the aspect ratio
	float GetAspectRatio() const { return float(m_width) / float(m_height); }

protected:
	// Sets the screen width and height
	void SetScreenSize(int w, int h) { m_width = w; m_height = h; }

private:
	// Window size
	int m_width;
	int m_height;
};
