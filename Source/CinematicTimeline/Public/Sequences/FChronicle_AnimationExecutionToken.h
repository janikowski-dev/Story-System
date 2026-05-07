#pragma once

#include "AChronicle_CharacterActor.h"
#include "IMovieScenePlayer.h"
#include "MovieSceneExecutionToken.h"

struct FChronicle_AnimationExecutionToken : IMovieSceneExecutionToken
{
	TObjectPtr<UAnimSequence> Animation;

	explicit FChronicle_AnimationExecutionToken(const TObjectPtr<UAnimSequence> InAnimation) : Animation(InAnimation)
	{
	}

	virtual void Execute(
		const FMovieSceneContext& Context,
		const FMovieSceneEvaluationOperand& Operand,
		FPersistentEvaluationData& PersistentData,
		IMovieScenePlayer& Player
	) override
	{
		for (TWeakObjectPtr BoundObject : Player.FindBoundObjects(Operand.ObjectBindingID, Operand.SequenceID))
		{
			if (AChronicle_CharacterActor* Character = Cast<AChronicle_CharacterActor>(BoundObject.Get()))
			{
				Character->PlayAnimation(Animation);
			}
		}
	}
};