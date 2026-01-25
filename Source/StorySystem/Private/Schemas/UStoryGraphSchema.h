#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "UStoryGraphSchema.generated.h"

UCLASS()
class STORYSYSTEM_API UStoryGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	
	virtual const FPinConnectionResponse CanCreateConnection(
		const UEdGraphPin* A,
		const UEdGraphPin* B
	) const override;
	
	virtual void GetGraphContextActions(
		FGraphContextMenuBuilder& ContextMenuBuilder
	) const override;
	
	virtual bool TryCreateConnection(
		UEdGraphPin* A,
		UEdGraphPin* B
	) const override;

	virtual FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(
		int32 InBackLayerID,
		int32 InFrontLayerID,
		float InZoomFactor,
		const FSlateRect& InClippingRect,
		FSlateWindowElementList& InDrawElements,
		UEdGraph* InGraphObj)
	const override;
};