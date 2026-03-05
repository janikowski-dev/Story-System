#pragma once

#include "FChronicle_CharacterSet.h"
#include "IChronicle_CharacterSet.h"

class FChronicle_CombinedCharacterSet : public IChronicle_CharacterSet
{
public:
	FChronicle_CombinedCharacterSet(FChronicle_CharacterSet& InSet1, FChronicle_CharacterSet& InSet2);
	
public:
	virtual void Refresh(const TArray<FChronicle_Character>& Characters) override;
	virtual TArray<TSharedPtr<FGuid>> GetSharedIds() const override;
	virtual FName GetName(FGuid Id) const override;
	virtual bool IsValid(FGuid Id) const override;

private:
	FChronicle_CharacterSet& Set1;
	FChronicle_CharacterSet& Set2;
};
