#pragma once

#include "CoreMinimal.h"
#include "UStoryNode.h"
#include "UStoryResponseNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryResponseNode : public UStoryNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	
public:
	UPROPERTY(EditAnywhere)
	FText Text;
	UPROPERTY()
	int32 ParentIndex;
	UPROPERTY()
	int32 OrderIndex;
};