#pragma once
#include <string>

class ListOrigin
{
public:
	virtual void load_from_file(const std::string &name) = 0;
};