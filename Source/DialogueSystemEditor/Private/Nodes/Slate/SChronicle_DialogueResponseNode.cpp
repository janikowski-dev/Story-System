#include "SChronicle_DialogueResponseNode.h"

#include "FChronicle_CharacterDirectory.h"
#include "FChronicle_EmotionDirectory.h"
#include "Editors/FChronicle_RuleEditor.h"
#include "Nodes/Unreal/UChronicle_DialogueResponseNode.h"
#include "Utils/FChronicle_Colors.h"
#include "Utils/FChronicle_EditorStyle.h"
#include "Utils/FChronicle_SlateHelper.h"

void SChronicle_DialogueResponseNode::Construct(const FArguments&, UChronicle_DialogueResponseNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

FSlateColor SChronicle_DialogueResponseNode::GetHeaderColor() const
{
	return FChronicle_Colors::Response;
}

void SChronicle_DialogueResponseNode::UpdateGraphNode()
{
	FixAssignedId();
	SChronicle_DialogueNode::UpdateGraphNode();
}

FReply SChronicle_DialogueResponseNode::OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&)
{
	OpenNodeEditor();
	return FReply::Handled();
}

FReply SChronicle_DialogueResponseNode::OpenEmotionSelectionWindow()
{
	return FChronicle_SlateHelper::OpenMenuWindow(
		FText::FromString("Select Emotion"),
		FText::FromString("No emotions to choose"),
		GetAvailableEmotions(),
		SelectEmotion()
	);
}

FReply SChronicle_DialogueResponseNode::ResetEmotion()
{
	SelectEmotion()(FGuid());
	return FReply::Handled();
}

void SChronicle_DialogueResponseNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
	Box->AddSlot()
	.AutoHeight()
	.Padding(4.0f)
	[
		FChronicle_SlateHelper::MakeCharacterDisplay(
			FChronicle_EditorStyle::Get().GetBrush("Icons.Speaker"),
			FText::FromName(FChronicle_CharacterDirectory::GetAll().GetName(TypedNode->SpeakerId))
		)
	];

	Box->AddSlot()
	.AutoHeight()
	[
		FChronicle_SlateHelper::MakeSingleLineTextField(
			TAttribute<FText>(this, &SChronicle_DialogueResponseNode::GetSubtitle),
			FOnTextCommitted::CreateSP(this, &SChronicle_DialogueResponseNode::SetSubtitle)
		)
	];
	
	Box->AddSlot()
	.AutoHeight()
	[
		FChronicle_SlateHelper::MakeTextField(
			TAttribute<FText>(this, &SChronicle_DialogueResponseNode::GetText),
			FOnTextCommitted::CreateSP(this, &SChronicle_DialogueResponseNode::SetText)
		)
	];

	Box->AddSlot()
	.AutoHeight()
	.Padding(4.0f)
	.HAlign(HAlign_Center)
	[
		FChronicle_SlateHelper::MakeEmotionSelectionButton(
			FOnClicked::CreateSP(this, &SChronicle_DialogueResponseNode::OpenEmotionSelectionWindow),
			FOnClicked::CreateSP(this, &SChronicle_DialogueResponseNode::ResetEmotion),
			FChronicle_EmotionDirectory::GetAll().GetName(TypedNode->EmotionId)
		)
	];
}

FText SChronicle_DialogueResponseNode::GetText() const
{
	return CastChecked<UChronicle_DialogueResponseNode>(GraphNode)->Text;
}

void SChronicle_DialogueResponseNode::SetText(const FText& NewText, ETextCommit::Type) const
{
	UChronicle_DialogueResponseNode* Node = CastChecked<UChronicle_DialogueResponseNode>(GraphNode);
	Node->Modify();
	Node->Text = NewText;
}

FText SChronicle_DialogueResponseNode::GetSubtitle() const
{
	return CastChecked<UChronicle_DialogueResponseNode>(GraphNode)->Subtitle;
}

void SChronicle_DialogueResponseNode::SetSubtitle(const FText& NewText, ETextCommit::Type) const
{
	UChronicle_DialogueResponseNode* Node = CastChecked<UChronicle_DialogueResponseNode>(GraphNode);
	Node->Modify();
	Node->Subtitle = NewText;
}

void SChronicle_DialogueResponseNode::OpenNodeEditor() const
{
	if (UChronicle_DialogueNode* NodeAsset = Cast<UChronicle_DialogueNode>(GraphNode))
	{
		const TSharedRef<FChronicle_RuleEditor> Editor = MakeShared<FChronicle_RuleEditor>();

		Editor->InitNodeAssetEditor(
			EToolkitMode::Standalone,
			TSharedPtr<IToolkitHost>(),
			NodeAsset
		);
	}
}

void SChronicle_DialogueResponseNode::FixAssignedId() const
{
	const bool bHasSpeaker = TypedGraph->SharedParticipantIds.ContainsByPredicate([this](const TSharedPtr<FGuid>& Id)
	{
		return Id && *Id == TypedNode->SpeakerId;
	});
	
	if (bHasSpeaker)
	{
		return;
	}

	const TSharedPtr<FGuid>* PlayerId = TypedGraph->SharedParticipantIds.FindByPredicate([](const TSharedPtr<FGuid>& Id)
	{
		return FChronicle_CharacterDirectory::GetPlayable().IsValid(*Id);
	});

	TypedNode->SpeakerId = PlayerId ? **PlayerId : FGuid();
}

TArray<TPair<FName, FGuid>> SChronicle_DialogueResponseNode::GetAvailableEmotions() const
{
	TArray<TPair<FName, FGuid>> Emotions;
	
	for (TSharedPtr SharedId : FChronicle_EmotionDirectory::GetAll().GetSharedIds())
	{
		Emotions.Emplace(FName(FChronicle_EmotionDirectory::GetAll().GetName(*SharedId)), *SharedId);
	}

	return Emotions;
}

TFunction<void(FGuid)> SChronicle_DialogueResponseNode::SelectEmotion()
{
	return [this](const FGuid EmotionId)
	{
		TypedNode->Modify();
		TypedNode->EmotionId = EmotionId;
		UpdateGraphNode();
	};
}
