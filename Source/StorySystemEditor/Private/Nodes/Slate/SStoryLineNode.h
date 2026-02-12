#pragma once

#include "SStoryTextNode.h"

class UStoryLineNode;

class SStoryLineNode : public SStoryTextNode
{
public:
	SLATE_BEGIN_ARGS(SStoryLineNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, UStoryLineNode* InNode);
	
protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FText GetTitle(UStoryNode* Node) override;
	virtual FSlateColor GetHeaderColor() const override;

private:
	FText GetText() const;
	void SetText(const FText& NewText, ETextCommit::Type CommitType) const;
};
