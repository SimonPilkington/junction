#pragma once
#include "Directory.h"
#include "JunctionReparseData.h"

class JunctionManager
{
private:
	Directory& m_dirTarget;

public:
	JunctionManager(const JunctionManager& other) = delete;
	
	JunctionManager(Directory &dirTarget) : m_dirTarget(dirTarget)
	{ }

	std::unique_ptr<JunctionReparseData> GetJunctionData() const;
	void CreateJunction(const TCHAR *pTarget) const;
};