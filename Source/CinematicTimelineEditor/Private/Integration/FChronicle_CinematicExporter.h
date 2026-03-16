#pragma once

#include "Data/UChronicle_CinematicData.h"
#include "UChronicle_DialogueData.h"

class FChronicle_CinematicExporter
{
public:
	static UChronicle_CinematicData* ExportToCinematicData(const UChronicle_DialogueData* Input);
};
