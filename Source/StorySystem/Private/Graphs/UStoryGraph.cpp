#include "UStoryGraph.h"

#include "Layout/StoryGraphLayout.h"
#include "Nodes/URootGraphNode.h"
#include "Nodes/UStoryGraphNode.h"

void UStoryGraph::PostLoad()
{
	Super::PostLoad();
	Layout(Nodes);
}

int32 UStoryGraph::GetNodeColumn(const UStoryGraphNode* Node) const
{
	const UEdGraphNode* Root = GetRootNode();

	if (Node == Root)
	{
		return 0;
	}

	TMap<const UEdGraphNode*, int32> Depths;
	TQueue<const UEdGraphNode*> Queue;

	Depths.Add(Root, 0);
	Queue.Enqueue(Root);

	while (!Queue.IsEmpty())
	{
		const UEdGraphNode* Current;
		Queue.Dequeue(Current);

		const int32 CurrentDepth = Depths[Current];

		for (const UEdGraphPin* Pin : Current->Pins)
		{
			if (Pin->Direction != EGPD_Output)
			{
				continue;
			}

			for (const UEdGraphPin* Linked : Pin->LinkedTo)
			{
				const UEdGraphNode* Child = Linked->GetOwningNode();

				if (!Child || Depths.Contains(Child))
				{
					continue;
				}

				Depths.Add(Child, CurrentDepth + 1);
				Queue.Enqueue(Child);
			}
		}
	}

	if (const int32* Depth = Depths.Find(Node))
	{
		return *Depth;
	}

	return -1;
}

int32 UStoryGraph::GetNodeRow(const UStoryGraphNode* Node) const
{
	for (const UEdGraphNode* Other : Nodes)
	{
		const UStoryGraphNode* Parent = Cast<UStoryGraphNode>(Other);
		
		if (!Parent)
		{
			continue;
		}
	
		for (const UEdGraphPin* Pin : Parent->Pins)
		{
			if (Pin->Direction != EGPD_Output)
			{
				continue;
			}
	
			for (int32 i = 0; i < Pin->LinkedTo.Num(); ++i)
			{
				if (Pin->LinkedTo[i]->GetOwningNode() == Node)
				{
					return i;
				}
			}
		}
	}

	return 0;
}

UStoryGraphNode* UStoryGraph::GetRootNode() const
{
	for (UEdGraphNode* Node : Nodes)
	{
		if (auto* Root = Cast<URootGraphNode>(Node))
		{
			return Root;
		}
	}
	return nullptr;
}
