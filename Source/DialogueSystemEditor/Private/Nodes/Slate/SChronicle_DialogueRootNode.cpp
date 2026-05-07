#include "SChronicle_DialogueRootNode.h"

#include "FChronicle_CharacterDirectory.h"
#include "Nodes/Unreal/UChronicle_DialogueRootNode.h"
#include "Utils/FChronicle_Colors.h"
#include "Utils/FChronicle_EditorStyle.h"
#include "Utils/FChronicle_SlateHelper.h"

void SChronicle_DialogueRootNode::Construct(const FArguments&, UChronicle_DialogueRootNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

FSlateColor SChronicle_DialogueRootNode::GetHeaderColor() const
{
	return FChronicle_Colors::Root;
}

void SChronicle_DialogueRootNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
    AddCurrentParticipantList(Box);
    AddNewParticipantButton(Box);
}

void SChronicle_DialogueRootNode::AddCurrentParticipantList(const TSharedRef<SVerticalBox>& Box) const
{
	for (TSharedPtr ParticipantId : TypedGraph->SharedParticipantIds)
	{
		const bool bIsPlayer = FChronicle_CharacterDirectory::GetPlayable().IsValid(*ParticipantId);
		
		Box->AddSlot()
		.AutoHeight()
		.Padding(4.0f, 2.0f)
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(0.0f, 0.0f, 5.0f, 0.0f)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(FChronicle_EditorStyle::Get().GetBrush(
					bIsPlayer ? "Icons.Player" : "Icons.Other")
				)
				.DesiredSizeOverride(FVector2D(16.0f, 16.0f))
			]

			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromName(FChronicle_CharacterDirectory::GetAll().GetName(*ParticipantId)))
			]

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
				.OnClicked_Lambda([this, ParticipantId]
				{
					TypedGraph->RemoveParticipant(ParticipantId);
					return FReply::Handled();
				})
				[
					SNew(SImage)
					.Image(FAppStyle::GetBrush("Icons.Minus"))
				]
			]
		];
	}
}

void SChronicle_DialogueRootNode::AddNewParticipantButton(const TSharedRef<SVerticalBox>& Box) const
{
	Box->AddSlot()
	.AutoHeight()
	.Padding(4.0f, 4.0f, 4.0f, 0.0f)
	[
		SNew(SSeparator)
		.Thickness(1.0f)
	];
	
	Box->AddSlot()
	.AutoHeight()
	.Padding(4.0f, 6.0f, 4.0f, 4.0f)
	.HAlign(HAlign_Center)
	[
		SNew(SButton)
		.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
		.OnClicked(this, &SChronicle_DialogueRootNode::OpenAddParticipantWindow)
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.Padding(2.0f, 2.0f, 0.0f, 1.5f)
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush("Icons.Plus"))
			]

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(5.0f, 2.0f, 2.0f, 1.5f)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Add Participant"))
			]
		]
	];
}

FReply SChronicle_DialogueRootNode::OpenAddParticipantWindow() const
{
	return FChronicle_SlateHelper::OpenMenuWindow(
		FText::FromString("Add Participant"),
		FText::FromString("No characters to add"),
		GetAvailableCharacters(),
		HandleParticipantSelection()
	);
}

TArray<TPair<FName, FGuid>> SChronicle_DialogueRootNode::GetAvailableCharacters() const
{
	TArray<TPair<FName, FGuid>> AvailableCharacters;
	
	const bool bHasPlayer = TypedGraph->SharedParticipantIds.ContainsByPredicate(
		[](const TSharedPtr<FGuid>& Id)
		{
			return FChronicle_CharacterDirectory::GetPlayable().IsValid(*Id);
		});

	for (const TSharedPtr<FGuid>& CharacterId : FChronicle_CharacterDirectory::GetAll().GetSharedIds())
	{
		if (TypedGraph->HasParticipant(CharacterId))
		{
			continue;
		}

		const bool bIsPlayer = FChronicle_CharacterDirectory::GetPlayable().IsValid(*CharacterId);

		if (bHasPlayer && bIsPlayer)
		{
			continue;
		}

		const FName CharacterName = FChronicle_CharacterDirectory::GetAll().GetName(*CharacterId);
		AvailableCharacters.Emplace(CharacterName, *CharacterId);
	}

	return AvailableCharacters;
}

TFunction<void(FGuid)> SChronicle_DialogueRootNode::HandleParticipantSelection() const
{
	return [this](const FGuid CharacterId)
	{
		for (TSharedPtr SharedId : FChronicle_CharacterDirectory::GetAll().GetSharedIds())
		{
			if (*SharedId != CharacterId)
			{
				continue;
			}

			TypedGraph->AddParticipant(SharedId);
			break;
		}
	};
}
