#pragma once

#include "SStoryGraphNode.h"

class UDialogueGraphNode;

class SDialogueGraphNode : public SStoryGraphNode
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UDialogueGraphNode* InNode);
	virtual void UpdateGraphNode() override;
	void OnDialogueCommitted(const FText& NewText, ETextCommit::Type CommitType) const;
	FText GetDialogueText() const;
};
