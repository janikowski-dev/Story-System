#include "UChronicle_PlaybackFunctionLibrary.h"

#include "CineCameraActor.h"
#include "LevelSequencePlayer.h"

void UChronicle_PlaybackFunctionLibrary::OffsetSpawnableTransforms(
    ALevelSequenceActor* LevelSequenceActor,
    const FVector& LocationOffset,
    const FRotator& RotationOffset
)
{
    const ULevelSequence* LevelSequence = Cast<ULevelSequence>(LevelSequenceActor->GetSequence());
    
    if (!LevelSequence)
    {
        return;
    }

    UMovieScene* MovieScene = LevelSequence->GetMovieScene();
    
    if (!MovieScene)
    {
        return;
    }

    ULevelSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();

    const FTransform ParentTransform(RotationOffset, LocationOffset);

    for (int i = 0; i < MovieScene->GetSpawnableCount(); i++)
    {
        const FMovieSceneSpawnable& Spawnable = MovieScene->GetSpawnable(i);
        TArray<UObject*> BoundObjects = Player->GetBoundObjects(FMovieSceneObjectBindingID(Spawnable.GetGuid()));

        for (UObject* BoundObject : BoundObjects)
        {
            AActor* Actor = Cast<AActor>(BoundObject);
            const FTransform LocalTransform = Actor->GetActorTransform();
            const FTransform WorldTransform = LocalTransform * ParentTransform;
            Actor->SetActorTransform(WorldTransform);
        }
    }
}

void UChronicle_PlaybackFunctionLibrary::OffsetCamera(
    const ALevelSequenceActor* LevelSequenceActor,
    const FTransform& OwnerTransform,
    const FTransform& ResponseTransform,
    const float VerticalOffset,
    const float ForwardOffset
)
{
    ULevelSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();
    const ULevelSequence* LevelSequence = Cast<ULevelSequence>(LevelSequenceActor->GetSequence());
    UMovieScene* MovieScene = LevelSequence->GetMovieScene();
    
    const FTransform WorldResponseTransform = ResponseTransform * OwnerTransform;

    const FVector Forward = WorldResponseTransform.GetRotation().GetForwardVector();
    const FVector ParticipantLocation = WorldResponseTransform.GetLocation();
    const FVector CameraLocation = ParticipantLocation + Forward * ForwardOffset + FVector::UpVector * VerticalOffset;
    const FVector LookAtTarget = ParticipantLocation + FVector::UpVector * VerticalOffset;
    const FRotator CameraRotation = (LookAtTarget - CameraLocation).Rotation();

    for (int i = 0; i < MovieScene->GetSpawnableCount(); i++)
    {
        const FMovieSceneSpawnable& Spawnable = MovieScene->GetSpawnable(i);
        if (!Spawnable.GetObjectTemplate()->IsA<ACineCameraActor>()) continue;

        TArray<UObject*> BoundObjects = Player->GetBoundObjects(
            FMovieSceneObjectBindingID(Spawnable.GetGuid())
        );

        for (UObject* BoundObject : BoundObjects)
        {
            AActor* Actor = Cast<AActor>(BoundObject);
            
            if (!Actor)
            {
                continue;
            }

            Actor->SetActorLocationAndRotation(CameraLocation, CameraRotation);
        }
    }
}

void UChronicle_PlaybackFunctionLibrary::SetPlaybackPosition(
    ALevelSequenceActor* LevelSequenceActor,
    const FFrameNumber StartFrame
)
{
    const ULevelSequence* LevelSequence = Cast<ULevelSequence>(LevelSequenceActor->GetSequence());
    const UMovieScene* MovieScene = LevelSequence->GetMovieScene();
    
    const FFrameRate TickResolution = MovieScene->GetTickResolution();
    const FFrameRate DisplayRate = MovieScene->GetDisplayRate();

    const double Seconds = TickResolution.AsSeconds(StartFrame);
    const FFrameTime DisplayFrame = DisplayRate.AsFrameTime(Seconds);

    FMovieSceneSequencePlaybackParams Params;
    
    Params.Frame = DisplayFrame;
    Params.PositionType = EMovieScenePositionType::Frame;
    Params.UpdateMethod = EUpdatePositionMethod::Jump;

    LevelSequenceActor->GetSequencePlayer()->SetPlaybackPosition(Params);
}
