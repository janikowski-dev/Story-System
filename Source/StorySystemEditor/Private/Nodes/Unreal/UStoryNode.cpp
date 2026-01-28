#include "UStoryNode.h"

#include "Assets/UStoryAsset.h"
#include "Schemas/UStoryNodeGraphSchema.h"

void UStoryNode::PostInitProperties()
{
	Super::PostInitProperties();
}

void UStoryNode::PostLoad()
{
	Super::PostLoad();
	InitGraph();
}

UEdGraph* UStoryNode::GetInnerGraph()
{
	if (const UStoryAsset* Asset = GetTypedOuter<UStoryAsset>())
	{
		if (const TObjectPtr<UEdGraph>* Found = Asset->InnerGraphsByNode.Find(this))
		{
			return Found->Get();
		}
		else
		{
			InitGraph();
		}
		if (const TObjectPtr<UEdGraph>* Found = Asset->InnerGraphsByNode.Find(this))
		{
			return Found->Get();
		}
	}
	
	return nullptr;
}

void UStoryNode::InitGraph()
{
	UStoryAsset* Asset = GetTypedOuter<UStoryAsset>();
	
	if (!Asset)
	{
		return;
	}

	if (Asset->InnerGraphsByNode.Contains(this))
	{
		return;
	}

	UEdGraph* InnerGraph = NewObject<UEdGraph>(
		Asset,
		UEdGraph::StaticClass(),
		NAME_None,
		RF_Transactional
	);
	
	InnerGraph->Schema = UStoryNodeGraphSchema::StaticClass();

	Asset->InnerGraphsByNode.Add(this, InnerGraph);
}
