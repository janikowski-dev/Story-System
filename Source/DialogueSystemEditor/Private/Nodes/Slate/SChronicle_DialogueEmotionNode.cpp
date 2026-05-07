#include "SChronicle_DialogueEmotionNode.h"

#include "FChronicle_EmotionDirectory.h"
#include "Utils/FChronicle_SlateHelper.h"
#include "Nodes/Unreal/UChronicle_DialogueResponseNode.h"
#include "Nodes/Unreal/UChronicle_DialogueLineNode.h"

template <typename TNodeType>
FReply SChronicle_DialogueEmotionNode<TNodeType>::OpenEmotionSelectionWindow()
{
	return FChronicle_SlateHelper::OpenMenuWindow(
		FText::FromString("Select Emotion"),
		FText::FromString("No emotions to choose"),
		GetAvailableEmotions(),
		SelectEmotion()
	);
}

template <typename TNodeType>
FReply SChronicle_DialogueEmotionNode<TNodeType>::ResetEmotion()
{
	SelectEmotion()(FGuid());
	return FReply::Handled();
}

template <typename TNodeType>
TArray<TPair<FName, FGuid>> SChronicle_DialogueEmotionNode<TNodeType>::GetAvailableEmotions() const
{
	TArray<TPair<FName, FGuid>> Emotions;
	
	for (TSharedPtr SharedId : FChronicle_EmotionDirectory::GetAll().GetSharedIds())
	{
		Emotions.Emplace(FName(FChronicle_EmotionDirectory::GetAll().GetName(*SharedId)), *SharedId);
	}

	return Emotions;
}

template <typename TNodeType>
TFunction<void(FGuid)> SChronicle_DialogueEmotionNode<TNodeType>::SelectEmotion()
{
	return [this](const FGuid EmotionId)
	{
        this->TypedNode->Modify();
        this->TypedNode->EmotionId = EmotionId;
        this->UpdateGraphNode();
	};
}

template class SChronicle_DialogueEmotionNode<UChronicle_DialogueResponseNode>;
template class SChronicle_DialogueEmotionNode<UChronicle_DialogueLineNode>;
