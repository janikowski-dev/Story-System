#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Graphs/UStoryGraph.h"
#include "Nodes/Unreal/UStoryNode.h"
#include "UStoryAsset.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UStoryGraph> Graph;
	UPROPERTY()
	TMap<TObjectPtr<UStoryNode>, TObjectPtr<UEdGraph>> InnerGraphsByNode;
};