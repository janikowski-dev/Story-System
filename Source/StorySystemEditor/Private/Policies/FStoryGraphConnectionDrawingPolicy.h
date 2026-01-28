#pragma once

#include "ConnectionDrawingPolicy.h"

struct FLineSegment
{
	FVector2f A;
	FVector2f B;
};

class FStoryGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy
{
public:
	FStoryGraphConnectionDrawingPolicy(
		int32 InBackLayerID,
		int32 InFrontLayerID,
		float InZoomFactor,
		const FSlateRect& InClippingRect,
		FSlateWindowElementList& InDrawElements
	);

protected:
	virtual void DrawSplineWithArrow(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FConnectionParams& Params
	) override;

	void DrawStraightConnection(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FConnectionParams& Params
	) const;

	void DrawAngledConnection(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FVector2f& PinOffset,
		const FConnectionParams& Params
	) const;

	void DrawArrow(
		const FVector2f& EndPoint,
		const FVector2f& PinOffset,
		const FConnectionParams& Params
	) const;

	TArray<FLineSegment> BuildOrthogonalWire(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FVector2f& PinOffset,
		const FConnectionParams& Params
	) const;

	FVector2f GetPinOffset() const;

	bool IsStraightConnection(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint
	) const;
};