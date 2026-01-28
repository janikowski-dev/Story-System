#pragma once

#include "SStoryNode.h"

class UStoryDialogueNode;

class SStoryDialogueNode : public SStoryNode
{
public:
	SLATE_BEGIN_ARGS(SStoryDialogueNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStoryDialogueNode* InNode);
	virtual void UpdateGraphNode() override;
	void OnDialogueCommitted(const FText& NewText, ETextCommit::Type CommitType) const;
	FText GetDialogueText() const;
};
