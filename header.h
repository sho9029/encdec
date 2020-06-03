#pragma once
#include "pch.h"

class header
{
public:
	enum match
	{
		allMatch = 0,
		identifierMatch = 1,
		noMatch = -1
	};
	struct _header
	{
		uint8_t identifier[identifierSize];
		uint8_t version[versionSize];
	};
};

