#pragma once

#include "FCharacterSet.h"
#include "IChronicle_CharacterSet.h"

class FChronicle_CombinedCharacterSet : public IChronicle_CharacterSet
{
public:
	FChronicle_CombinedCharacterSet(FCharacterSet& InSet1, FCharacterSet& InSet2);
	
public:
	virtual void Refresh(const TArray<FChronicleCharacter>& Characters) override;
	virtual TArray<TSharedPtr<FGuid>> GetSharedIds() const override;
	virtual FName GetName(FGuid Id) const override;
	virtual bool IsValid(FGuid Id) const override;

private:
	FCharacterSet& Set1;
	FCharacterSet& Set2;
};
