#pragma once

#include "Data/FChronicle_EmotionData.h"

class CHRONICLECOREEDITOR_API FChronicle_EmotionSet
{
public:
	void Refresh(const TArray<FChronicle_EmotionData>& Emotions);
	TArray<TSharedPtr<FGuid>> GetSharedIds() const;
	FString GetName(FGuid Id) const;
	bool IsValid(FGuid Id) const;
	
private:
	TArray<TSharedPtr<FGuid>> Ids;
	TMap<FGuid, FString> NamesById;
};
