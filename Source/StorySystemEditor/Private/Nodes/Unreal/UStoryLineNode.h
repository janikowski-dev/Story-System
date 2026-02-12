#pragma once

#include "CoreMinimal.h"
#include "UStoryNode.h"
#include "UStoryLineNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryLineNode : public UStoryNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	
public:
	UPROPERTY(EditAnywhere)
	FText Text;
	UPROPERTY()
	int32 LineIndex;
};