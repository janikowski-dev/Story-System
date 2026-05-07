#pragma once

#include "FChronicle_EmotionSet.h"

class CHRONICLECOREEDITOR_API FChronicle_EmotionDirectory
{
public:
	static FChronicle_EmotionSet& GetAll();
	static void Refresh();

private:
	static FChronicle_EmotionSet AllEmotionSet;
};
