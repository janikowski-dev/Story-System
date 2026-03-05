#pragma once

#include "FRuleSet.h"
#include "SDialogueNode.h"
#include "IChronicle_CharacterSet.h"

class URuleInputNode;

class SRuleInputNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SRuleInputNode) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments&,
		URuleInputNode* InNode,
		const FRuleSet& InRuleSet,
		const IChronicle_CharacterSet& InCharacterSet
	);
	
	virtual void UpdateGraphNode() override;

private:
	TSharedRef<SWidget> GetInputBody() const;
	TSharedRef<SWidget> GetRuleSelectionBody() const;
	TSharedRef<SWidget> GetIntegerInputBody() const;
	TSharedRef<SWidget> GetCharacterSelectionBody() const;
	
	void Cache(URuleInputNode* InNode);
	void Cache(const FRuleSet& InSet);
	void Cache(const IChronicle_CharacterSet& InSet);
	
private:
	TWeakObjectPtr<URuleInputNode> TypedNode;
	
	const IChronicle_CharacterSet* CharacterSet = nullptr;
	const FRuleSet* RuleSet = nullptr;
	
	TArray<TSharedPtr<FGuid>> CharacterIds;
	TArray<TSharedPtr<FGuid>> RuleIds;
};