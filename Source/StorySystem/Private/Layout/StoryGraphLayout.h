#pragma once

class UStoryGraphNode;

constexpr float NodeHeight = 150.0f;
constexpr float NodeWidth = 275.0f;

void Layout(TArray<TObjectPtr<UEdGraphNode>> Nodes);
void Layout(const UEdGraph* Graph);