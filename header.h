#pragma once
#include "pch.h"
#include <cstring>

class Header
{
public:
	enum class match
	{
		Match = 0,
		noMatch = -1
	};

	struct header
	{
		uint8_t identifier[identifierSize];
		uint8_t version[versionSize];

		bool operator ==(const header& a) const
		{
			return memcmp(identifier, a.identifier, identifierSize) == 0 &&
				   memcmp(version, a.version, versionSize) == 0;
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
