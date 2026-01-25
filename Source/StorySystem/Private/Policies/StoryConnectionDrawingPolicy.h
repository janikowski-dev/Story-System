#pragma once

#include "ConnectionDrawingPolicy.h"

class FStoryConnectionDrawingPolicy : public FConnectionDrawingPolicy
{
public:
	FStoryConnectionDrawingPolicy(
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
};