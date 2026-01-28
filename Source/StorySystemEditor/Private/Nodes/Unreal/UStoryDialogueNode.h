#pragma once

#include "CoreMinimal.h"
#include "UStoryNode.h"
#include "UStoryDialogueNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryDialogueNode : public UStoryNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;

public:
	UPROPERTY(EditAnywhere)
	FText DialogueText;
};