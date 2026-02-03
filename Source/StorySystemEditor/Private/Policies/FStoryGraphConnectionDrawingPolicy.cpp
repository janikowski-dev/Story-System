#include "FStoryGraphConnectionDrawingPolicy.h"

#include "Nodes/Unreal/UStoryNode.h"

FStoryGraphConnectionDrawingPolicy::FStoryGraphConnectionDrawingPolicy(
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

void FStoryGraphConnectionDrawingPolicy::DrawSplineWithArrow(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint,
	const FConnectionParams& Params
)
{
	if (!IsTargetNodeEnabled(Params))
	{
		return;
	}
	
	const FVector2f PinOffset = GetPinOffset();
	
	if (IsStraightConnection(StartPoint, EndPoint))
	{
		DrawStraightConnection(StartPoint + PinOffset, EndPoint - PinOffset, Params);
	}
	else
	{
		DrawAngledConnection(StartPoint, EndPoint, PinOffset, Params);
	}
	
	DrawArrow(EndPoint, PinOffset, Params);
}

void FStoryGraphConnectionDrawingPolicy::DrawAngledConnection(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint,
	const FVector2f& PinOffset,
	const FConnectionParams& Params
) const
{
	const TArray<FLineSegment> Segments = BuildOrthogonalWire(StartPoint, EndPoint, PinOffset, Params);

	for (const auto& [A, B] : Segments)
	{
		DrawStraightConnection(A, B, Params);
	}
}

void FStoryGraphConnectionDrawingPolicy::DrawStraightConnection(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint,
	const FConnectionParams& Params
) const
{
	TArray<FVector2f> Points;
	
	Points.Add(StartPoint);
	Points.Add(EndPoint);
	
	FSlateDrawElement::MakeLines(
		DrawElementsList,
		WireLayerID,
		FPaintGeometry(),
		Points,
		ESlateDrawEffect::NoBlending,
		Params.WireColor,
		true,
		Params.WireThickness
	);
}

void FStoryGraphConnectionDrawingPolicy::DrawArrow(
	const FVector2f& EndPoint,
	const FVector2f& PinOffset,
	const FConnectionParams& Params
) const
{
	if (ArrowImage == nullptr)
	{
		return;
	}

	const FVector2f ArrowPoint = EndPoint - ArrowRadius - PinOffset;

	FSlateDrawElement::MakeBox(
		DrawElementsList,
		ArrowLayerID,
		FPaintGeometry(ArrowPoint, ArrowImage->ImageSize * ZoomFactor, ZoomFactor),
		ArrowImage,
		ESlateDrawEffect::None,
		Params.WireColor
	);
}

TArray<FLineSegment> FStoryGraphConnectionDrawingPolicy::BuildOrthogonalWire(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint,
	const FVector2f& PinOffset,
	const FConnectionParams& Params
) const
{
	TArray<FLineSegment> Segments;

	const FVector2f HorizontalAnchorOffset(
		Params.WireThickness * 0.5f,
		0.0f
	);
	
	const FVector2f VerticalAnchorOffset(
		0.0f,
		Params.WireThickness * 0.5f
	);
	
	const FVector2f StartAnchor(
		(StartPoint.X + EndPoint.X) * 0.5f,
		StartPoint.Y
	);

	const FVector2f EndAnchor(
		(StartPoint.X + EndPoint.X) * 0.5f,
		EndPoint.Y
	);

	FVector2f BottomAnchor;
	FVector2f TopAnchor;

	if (StartAnchor.Y > EndAnchor.Y)
	{
		BottomAnchor = EndAnchor;
		TopAnchor = StartAnchor;
	}
	else
	{
		BottomAnchor = StartAnchor;
		TopAnchor = EndAnchor;
	}

	Segments.Add(FLineSegment(StartPoint + PinOffset, StartAnchor + HorizontalAnchorOffset));
	Segments.Add(FLineSegment(TopAnchor + VerticalAnchorOffset, BottomAnchor - VerticalAnchorOffset));
	Segments.Add(FLineSegment(EndAnchor - HorizontalAnchorOffset, EndPoint - PinOffset));
	
	return Segments;
}

FVector2f FStoryGraphConnectionDrawingPolicy::GetPinOffset() const
{
	const FVector2f PinOffset(
		17.5f,
		0.0f
	);

	return PinOffset * ZoomFactor;
}

bool FStoryGraphConnectionDrawingPolicy::IsStraightConnection(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint
) const
{
	return StartPoint.Y == EndPoint.Y;
}

bool FStoryGraphConnectionDrawingPolicy::IsTargetNodeEnabled(const FConnectionParams& Params) const
{
	UEdGraphNode* Node = Params.AssociatedPin2->GetOwningNode();
	const UStoryNode* TypedNode = Cast<UStoryNode>(Node);
	return !TypedNode->bIsHidden;
}
