#pragma once
#include "pch.h"

class Header
{
public:
	enum class match
	{
		allMatch = 0,
		identifierMatch = 1,
		noMatch = -1
	};

	struct header
	{
		uint8_t identifier[identifierSize];
		uint8_t version[versionSize];

		bool operator ==(const header& a) const
		{
			return a.identifier == this->identifier && a.version == this->version;
		}
	};

	static void HeaderWrite(header& h)
	{
		for (size_t i = 0; i < identifierSize; ++i)
			h.identifier[i] = IDENTIFIER[i];
		for (size_t i = 0; i < versionSize; ++i)
			h.version[i] = VERSION[i];
	}
};

