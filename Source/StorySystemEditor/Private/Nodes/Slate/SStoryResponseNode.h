#pragma once

#include "SStoryTextNode.h"

class UStoryResponseNode;

class SStoryResponseNode : public SStoryTextNode
{
public:
	SLATE_BEGIN_ARGS(SStoryResponseNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStoryResponseNode* InNode);

protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FText GetTitle(UStoryNode* Node) override;
	virtual FSlateColor GetHeaderColor() const override;
	virtual FReply OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&) override;

private:
	FText GetText() const;
	void SetText(const FText& NewText, ETextCommit::Type) const;
	void OpenNodeEditor() const;
};
