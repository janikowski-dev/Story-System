#pragma once

#include "FChronicle_AnimationExecutionToken.h"
#include "Channels/MovieSceneObjectPathChannel.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "FChronicle_AnimationTrackEvaluator.generated.h"

USTRUCT()
struct FChronicle_AnimationTrackEvaluator : public FMovieSceneEvalTemplate
{
	GENERATED_BODY()

	UPROPERTY()
	FMovieSceneObjectPathChannel AnimationChannel;

	virtual UScriptStruct& GetScriptStructImpl() const override
	{
		return *StaticStruct();
	}

	virtual void Evaluate(
		const FMovieSceneEvaluationOperand& Operand,
		const FMovieSceneContext& Context,
		const FPersistentEvaluationData& PersistentData,
		FMovieSceneExecutionTokens& ExecutionTokens
	) const override
	{
		UObject* Value;
		
		if (!AnimationChannel.Evaluate(Context.GetTime(), Value))
		{
			return;
		}

		ExecutionTokens.Add(FChronicle_AnimationExecutionToken(Cast<UAnimSequence>(Value)));
	}
};