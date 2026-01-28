#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "UStoryNodeGraphSchema.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryNodeGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	virtual void GetGraphContextActions(
		FGraphContextMenuBuilder& ContextMenuBuilder
	) const override;

	virtual const FPinConnectionResponse CanCreateConnection(
		const UEdGraphPin* A,
		const UEdGraphPin* B
	) const override;

	virtual bool TryCreateConnection(
		UEdGraphPin* A,
		UEdGraphPin* B
	) const override;
};