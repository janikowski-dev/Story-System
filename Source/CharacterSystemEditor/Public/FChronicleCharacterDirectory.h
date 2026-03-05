#pragma once

#include "FCharacterSet.h" 
#include "FChronicle_CombinedCharacterSet.h"

class CHARACTERSYSTEMEDITOR_API FChronicleCharacterDirectory
{
public:
	static FChronicle_CombinedCharacterSet& GetAll();
	static FCharacterSet& GetNonPlayable();
	static FCharacterSet& GetPlayable();
	static void Refresh();

private:
	static FChronicle_CombinedCharacterSet AllCharacterSet;
	static FCharacterSet NonPlayableCharacterSet;
	static FCharacterSet PlayableCharacterSet;
};
