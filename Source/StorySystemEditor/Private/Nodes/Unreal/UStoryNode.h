#pragma once

#include "CoreMinimal.h"
#include "UStoryNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UEdGraph* GetOrCreateInnerGraph();

public:
	UPROPERTY()
	int32 EditorIndex;
	UPROPERTY()
	bool bIsCollapsed = false;
	UPROPERTY()
	bool bIsHidden = false;
};