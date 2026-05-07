#pragma once

#include "SChronicle_DialogueNode.h"
#include "Graphs/UChronicle_DialogueGraph.h"

template<typename TNodeType>
class SChronicle_DialogueEmotionNode : public SChronicle_DialogueNode<TNodeType>
{
protected:
	FReply OpenEmotionSelectionWindow();
	FReply ResetEmotion();

private:
	TArray<TPair<FName, FGuid>> GetAvailableEmotions() const;
	TFunction<void(FGuid)> SelectEmotion();
};

extern template class SChronicle_DialogueEmotionNode<UChronicle_DialogueResponseNode>;
extern template class SChronicle_DialogueEmotionNode<UChronicle_DialogueLineNode>;
