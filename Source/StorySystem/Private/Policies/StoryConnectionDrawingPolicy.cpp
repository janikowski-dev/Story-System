#include "StoryConnectionDrawingPolicy.h"

FStoryConnectionDrawingPolicy::FStoryConnectionDrawingPolicy(
	const int32 InBackLayerID,
	const int32 InFrontLayerID,
	const float InZoomFactor,
	const FSlateRect& InClippingRect,
	FSlateWindowElementList& InDrawElements
)
	: FConnectionDrawingPolicy(
		InBackLayerID,
		InFrontLayerID,
		InZoomFactor,
		InClippingRect,
		InDrawElements
	)
{
}

void FStoryConnectionDrawingPolicy::DrawSplineWithArrow(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint,
	const FConnectionParams& Params
)
{
	TArray<FVector2f> Points;
	
	FVector2f TopAnchor;
	TopAnchor.X = (StartPoint.X + EndPoint.X) * 0.5f;
	TopAnchor.Y = StartPoint.Y;
	
	FVector2f BottomAnchor;
	BottomAnchor.X = (StartPoint.X + EndPoint.X) * 0.5f;
	BottomAnchor.Y = EndPoint.Y;
	
	Points.Add(StartPoint);
	Points.Add(TopAnchor);
	Points.Add(BottomAnchor);
	Points.Add(EndPoint);

	FSlateDrawElement::MakeLines(
		DrawElementsList,
		100,
		FPaintGeometry(),
		Points,
		ESlateDrawEffect::None,
		Params.WireColor,
		true,
		Params.WireThickness
	);
}