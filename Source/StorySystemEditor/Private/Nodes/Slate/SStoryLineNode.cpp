#include "SStoryLineNode.h"

#include "SGraphPanel.h"
#include "Nodes/Unreal/UStoryLineNode.h"

void SStoryLineNode::Construct(const FArguments&, UStoryLineNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

FText SStoryLineNode::GetTitle(UStoryNode* Node)
{
	return FText::Format(FText::FromString("Line #{0}"), Cast<UStoryLineNode>(Node)->LineIndex);
}

FSlateColor SStoryLineNode::GetHeaderColor() const
{
	return FSlateColor(FLinearColor::Red);
}

void SStoryLineNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
	AddTextField(
		Box,
		TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateSP(this, &SStoryLineNode::GetText)),
		FOnTextCommitted::CreateSP(this, &SStoryLineNode::SetText)
	);
}

FText SStoryLineNode::GetText() const
{
	return CastChecked<UStoryLineNode>(GraphNode)->Text;
}

void SStoryLineNode::SetText(const FText& NewText, ETextCommit::Type) const
{
	UStoryLineNode* Node = CastChecked<UStoryLineNode>(GraphNode);
	Node->Modify();
	Node->Text = NewText;
}
