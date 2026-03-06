#pragma once

#include "Data/UChronicle_CinematicData.h"
#include "UChronicle_DialogueData.h"

class FChronicle_CinematicImporter
{
public:
	static UChronicle_CinematicData* ConvertToCinematicData(const UChronicle_DialogueData* Input);
};
