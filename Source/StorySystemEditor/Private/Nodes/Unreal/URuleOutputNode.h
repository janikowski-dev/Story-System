#pragma once

#include "URuleNode.h"
#include "URuleOutputNode.generated.h"

UENUM()
enum class EOutputType : int8
{
	PreCallback,
	PostCallback,
	Requirements
};

UCLASS()
class STORYSYSTEMEDITOR_API URuleOutputNode : public URuleNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type) const override;
	virtual bool AllowMultipleInputs() const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	
public:
	UPROPERTY(EditAnywhere)
	EOutputType Type;
};
