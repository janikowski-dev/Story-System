#pragma once

struct FChronicleCharacter;

class IChronicle_CharacterSet
{
public:
	virtual ~IChronicle_CharacterSet() = default;

public:
	virtual void Refresh(const TArray<FChronicleCharacter>& Characters) = 0;
	virtual TArray<TSharedPtr<FGuid>> GetSharedIds() const = 0;
	virtual FName GetName(FGuid Id) const = 0;
	virtual bool IsValid(FGuid Id) const = 0;
};