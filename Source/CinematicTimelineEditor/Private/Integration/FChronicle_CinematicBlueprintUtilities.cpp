#include "FChronicle_CinematicBlueprintUtilities.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "CineCameraActor.h"
#include "MovieScene.h"
#include "Animation/SkeletalMeshActor.h"
#include "Sections/MovieSceneAudioSection.h"
#include "Sections/MovieSceneCameraCutSection.h"
#include "Tracks/MovieSceneCameraCutTrack.h"
#include "Tracks/MovieSceneAudioTrack.h"
#include "Tracks/MovieSceneSpawnTrack.h"
#include "UObject/SavePackage.h"
#include "LevelSequence.h"
#include "Tracks/MovieScene3DTransformTrack.h"
#include "Sections/MovieScene3DTransformSection.h"
#include "Channels/MovieSceneDoubleChannel.h"

FChronicle_SequenceInfo FChronicle_CinematicBlueprintUtilities::InitSequence(
	ULevelSequence* LevelSequence,
	UChronicle_CinematicData* CinematicData,
	const FChronicle_SequenceData& SequenceData
)
{
	UMovieScene* MovieScene = nullptr;
	
	if (TryGetMovieScene(LevelSequence, MovieScene))
	{
		const FSequenceInfo Info = ConvertToInfo(MovieScene, CinematicData, SequenceData);
		PopulateCameraCutTrack(MovieScene, Info);
		PopulateAudioTrack(MovieScene, Info);
		ApplyInfo(MovieScene, Info);
		ApplyChanges(LevelSequence, CinematicData, SequenceData);
		return ConvertToRuntimeInfo(LevelSequence, Info, CinematicData, SequenceData);
	}

	return {};
}

UBlueprint* FChronicle_CinematicBlueprintUtilities::CreateBlueprintFromParent(
	UClass* ParentClass,
	const FString& PackagePath,
	const FString& BlueprintName,
	const FChronicle_DialogueInfo& Info,
	const FTransform& ResponseTransform
)
{
	if (!Info.Id.IsValid() || !ParentClass)
	{
		return nullptr;
	}

	const FString FullPath = PackagePath / BlueprintName;
	UPackage* Package = CreatePackage(*FullPath);
	UBlueprint* Blueprint = LoadObject<UBlueprint>(Package, *BlueprintName);
	
	if (!Blueprint)
	{
		Blueprint = FKismetEditorUtilities::CreateBlueprint(
			ParentClass,
			Package,
			*BlueprintName,
			BPTYPE_Normal,
			UBlueprint::StaticClass(),
			UBlueprintGeneratedClass::StaticClass()
		);

		FKismetEditorUtilities::CompileBlueprint(Blueprint);
	}

	if (Blueprint->GeneratedClass)
	{
		if (UObject* CDO = Blueprint->GeneratedClass->GetDefaultObject())
		{
			FProperty* InfoProperty = FindFProperty<FProperty>(Blueprint->GeneratedClass, TEXT("Info"));

			if (FStructProperty* StructProperty = CastField<FStructProperty>(InfoProperty))
			{
				void* StructPtr = StructProperty->ContainerPtrToValuePtr<void>(CDO);
				StructProperty->Struct->CopyScriptStruct(StructPtr, &Info);
				FPropertyChangedEvent PropertyChangedEvent(StructProperty);
				CDO->PostEditChangeProperty(PropertyChangedEvent);
				Blueprint->Modify();
				FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
			}
			
			FProperty* ResponseTransformProperty = FindFProperty<FProperty>(Blueprint->GeneratedClass, TEXT("ResponseTransform"));

			if (FStructProperty* StructProperty = CastField<FStructProperty>(ResponseTransformProperty))
			{
				void* StructPtr = StructProperty->ContainerPtrToValuePtr<void>(CDO);
				StructProperty->Struct->CopyScriptStruct(StructPtr, &ResponseTransform);
				FPropertyChangedEvent PropertyChangedEvent(StructProperty);
				CDO->PostEditChangeProperty(PropertyChangedEvent);
				Blueprint->Modify();
				FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
			}
		}
	}

	FAssetRegistryModule::AssetCreated(Blueprint);
	Blueprint->MarkPackageDirty();
	Package->MarkPackageDirty();

	FKismetEditorUtilities::CompileBlueprint(Blueprint);

	const FString PackageFileName = FPackageName::LongPackageNameToFilename(
		Package->GetName(),
		FPackageName::GetAssetPackageExtension()
	);

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.Error = GError;

	UPackage::SavePackage(Package, Blueprint, *PackageFileName, SaveArgs);
	
	return Blueprint;
}

bool FChronicle_CinematicBlueprintUtilities::TryGetMovieScene(const ULevelSequence* LevelSequence, UMovieScene*& MovieScene)
{
	if (!LevelSequence)
	{
		return false;
	}

	MovieScene = LevelSequence->GetMovieScene();
	
	if (MovieScene == nullptr)
	{
		return false;
	}
	
	MovieScene->SetClockSource(EUpdateClockSource::Audio);
	return true;
}

void FChronicle_CinematicBlueprintUtilities::ApplyInfo(UMovieScene* MovieScene, const FSequenceInfo& SequenceInfo)
{
	MovieScene->SetPlaybackRange(TRange<FFrameNumber>(0, SequenceInfo.TotalFrameCount));
}

FChronicle_SequenceInfo FChronicle_CinematicBlueprintUtilities::ConvertToRuntimeInfo(
	const ULevelSequence* LevelSequence,
	const FSequenceInfo& SequenceInfo,
	const UChronicle_CinematicData* CinematicData,
	const FChronicle_SequenceData& SequenceData
)
{
	FChronicle_SequenceInfo RuntimeInfo;

	for (FTrackInfo Track : SequenceInfo.Tracks)
	{
		RuntimeInfo.StartFrameByNodeIds.Add(Track.Id, Track.StartFrame);
	}

	RuntimeInfo.Sequence = TSoftObjectPtr<ULevelSequence>(FSoftObjectPath(LevelSequence));
	RuntimeInfo.bIsEntrySequence = SequenceData.bIsEntrySequence;
	RuntimeInfo.Id = SequenceInfo.Id;

	if (SequenceData.NextNodeId != FGuid())
	{
		FChronicle_TransitionInfo Transition;

		for (FChronicle_SequenceData OtherData : CinematicData->SequencesData)
		{
			const FChronicle_DialogueNodeData* MatchingNode = OtherData.Nodes.FindByPredicate([SequenceData](const FChronicle_DialogueNodeData& Node)
			{
				return SequenceData.NextNodeId == Node.Id;
			});

			if (!MatchingNode)
			{
				continue;
			}
			
			Transition.Type = EChronicle_TransitionType::AutoContinue;
			Transition.NodeId = SequenceData.NextNodeId;
			Transition.Rules = MatchingNode->Rules;
			Transition.SequenceId = OtherData.Id;
			break;
		}
		
		RuntimeInfo.Transitions.Add(Transition);
	}

	for (FGuid SequenceOrNodeId : SequenceData.BranchSequenceIds)
	{
		bool bFoundSequence = false;
		
		for (FChronicle_SequenceData OtherData : CinematicData->SequencesData)
		{
			if (SequenceOrNodeId != OtherData.Id)
			{
				continue;
			}
			
			FChronicle_TransitionInfo Transition;

			Transition.Type = EChronicle_TransitionType::Response;
			Transition.Rules = OtherData.Nodes[0].Rules;
			Transition.NodeId = OtherData.Nodes[0].Id;
			Transition.SequenceId = SequenceOrNodeId;
			
			RuntimeInfo.Transitions.Add(Transition);
			bFoundSequence = true;
			break;
		}

		if (!bFoundSequence)
		{
			FChronicle_TransitionInfo Transition;

			for (FChronicle_SequenceData OtherData : CinematicData->SequencesData)
			{
				const FChronicle_DialogueNodeData* MatchingNode = OtherData.Nodes.FindByPredicate([SequenceOrNodeId](const FChronicle_DialogueNodeData& Node)
				{
					return SequenceOrNodeId == Node.Id;
				});

				if (!MatchingNode)
				{
					continue;
				}
			
				Transition.Type = EChronicle_TransitionType::AutoContinue;
				Transition.Rules = MatchingNode->Rules;
				Transition.SequenceId = OtherData.Id;
				Transition.NodeId = SequenceOrNodeId;
				break;
			}
		
			RuntimeInfo.Transitions.Add(Transition);
		}
	}

	if (RuntimeInfo.Transitions.IsEmpty())
	{
		FChronicle_TransitionInfo Transition;
		
		Transition.Type = EChronicle_TransitionType::Game;
		
		RuntimeInfo.Transitions.Add(Transition);
	}
	
	return RuntimeInfo;
}
FSequenceInfo FChronicle_CinematicBlueprintUtilities::ConvertToInfo(
	UMovieScene* MovieScene,
	const UChronicle_CinematicData* CinematicData,
	const FChronicle_SequenceData& SequenceData
)
{
	FFrameNumber FrameCounter = 0;
	FSequenceInfo SequenceInfo;

	for (const FChronicle_DialogueNodeData& Node : SequenceData.Nodes)
	{
		FTrackInfo TrackInfo;
		
		const USoundBase* Sound = CinematicData->SoundsByLine[Node.Id].LoadSynchronous();
		const FFrameRate TickResolution = MovieScene->GetTickResolution();
		const double SoundDuration = Sound->GetDuration();
		const FFrameNumber FrameDuration = (SoundDuration * TickResolution).FloorToFrame();

		TrackInfo.Sound = CinematicData->SoundsByLine[Node.Id];
		TrackInfo.StartFrame = FrameCounter;
		TrackInfo.EndFrame = FrameDuration + FrameCounter;
		TrackInfo.ParticipantId = Node.SpeakerId;
		TrackInfo.Id = Node.Id;

		SequenceInfo.Tracks.Add(TrackInfo);

		FrameCounter += FrameDuration;
	}

	SequenceInfo.TotalFrameCount = FrameCounter;
	SequenceInfo.Id = SequenceData.Id;

	const UChronicle_ShotPresetData* Preset = CinematicData->PresetData.LoadSynchronous();
	const int ParticipantCount = CinematicData->ParticipantIds.Num();

	for (int i = 0; i < ParticipantCount; i++)
	{
		const FGuid& ParticipantId = CinematicData->ParticipantIds[i];

		const FShotPair* MatchingPair = Preset ? Preset->ShotPairs.FindByPredicate([i](const FShotPair& Pair)
		{
			return Pair.ShotIndex == i;
		}) : nullptr;

		FTransform ParticipantTransform;
		FTransform CameraTransform;

		if (MatchingPair)
		{
			ParticipantTransform = MatchingPair->ParticipantTransform;
			CameraTransform = MatchingPair->CameraTransform;
		}

		SequenceInfo.TransformByParticipantIds.Add(ParticipantId, ParticipantTransform);

		FGuid CameraId = AddCamera(MovieScene, CameraTransform);
		SequenceInfo.CameraIdByParticipantIds.Add(ParticipantId, CameraId);

		USkeletalMesh* SkeletalMesh = CinematicData->ActorsById[ParticipantId].LoadSynchronous();
		FGuid ModelId = AddModel(MovieScene, SkeletalMesh, ParticipantTransform);
		SequenceInfo.ModelIdByParticipantIds.Add(ParticipantId, ModelId);
	}
	
	return SequenceInfo;
}

void FChronicle_CinematicBlueprintUtilities::PopulateCameraCutTrack(
	UMovieScene* MovieScene,
	const FSequenceInfo& SequenceInfo
)
{
	UMovieSceneTrack* CutTrack = MovieScene->AddCameraCutTrack(UMovieSceneCameraCutTrack::StaticClass());
	CutTrack->SetSortingOrder(1);
	
	UMovieSceneCameraCutTrack* CameraCutTrack = Cast<UMovieSceneCameraCutTrack>(MovieScene->GetCameraCutTrack());

	for (const FTrackInfo& Track : SequenceInfo.Tracks)
	{
		UMovieSceneCameraCutSection* CameraSection = Cast<UMovieSceneCameraCutSection>(CameraCutTrack->CreateNewSection());
		CameraSection->SetRange(TRange<FFrameNumber>(Track.StartFrame, Track.EndFrame));

		FMovieSceneObjectBindingID CameraBindingID(SequenceInfo.CameraIdByParticipantIds[Track.ParticipantId]);
		CameraSection->SetCameraBindingID(CameraBindingID);
		CameraCutTrack->AddSection(*CameraSection);
	}
}

void FChronicle_CinematicBlueprintUtilities::PopulateAudioTrack(
	UMovieScene* MovieScene,
	const FSequenceInfo& SequenceInfo
)
{
	UMovieSceneTrack* AudioTrack = MovieScene->AddTrack<UMovieSceneAudioTrack>();

	if (UMovieSceneNameableTrack* Nameable = Cast<UMovieSceneNameableTrack>(AudioTrack))
	{
		Nameable->SetDisplayName(FText::FromString("Main Track"));
	}
	
	AudioTrack->SetSortingOrder(0);

	for (const FTrackInfo& Track : SequenceInfo.Tracks)
	{
		UMovieSceneAudioSection* AudioSection = Cast<UMovieSceneAudioSection>(AudioTrack->CreateNewSection());
		AudioSection->SetRange(TRange<FFrameNumber>(Track.StartFrame, Track.EndFrame));
		
		USoundBase* Sound = Track.Sound.LoadSynchronous();
		AudioTrack->AddSection(*AudioSection);
		AudioSection->SetIsLocked(true);
		AudioSection->SetSound(Sound);
	}
}

FGuid FChronicle_CinematicBlueprintUtilities::AddCamera(
	UMovieScene* MovieScene,
	const FTransform& SpawnTransform
)
{
	ACineCameraActor* TmpTemplate = NewObject<ACineCameraActor>(
		MovieScene,
		ACineCameraActor::StaticClass(),
		MakeUniqueObjectName(MovieScene, ACineCameraActor::StaticClass()),
		RF_NoFlags
	);

	TmpTemplate->SetActorTransform(SpawnTransform);

	const FGuid CameraGuid = MovieScene->AddSpawnable(TEXT("Camera"), *TmpTemplate);

	if (UMovieSceneSpawnTrack* SpawnTrack = MovieScene->AddTrack<UMovieSceneSpawnTrack>(CameraGuid))
	{
		SpawnTrack->Modify();
		SpawnTrack->AddSection(*SpawnTrack->CreateNewSection());
	}

	return CameraGuid;
}

FGuid FChronicle_CinematicBlueprintUtilities::AddModel(
	UMovieScene* MovieScene,
	USkeletalMesh* SkeletalMesh,
	const FTransform& SpawnTransform
)
{
	ASkeletalMeshActor* TmpTemplate = NewObject<ASkeletalMeshActor>(
		MovieScene,
		ASkeletalMeshActor::StaticClass(),
		MakeUniqueObjectName(MovieScene, ASkeletalMeshActor::StaticClass()),
		RF_NoFlags
	);

	TmpTemplate->GetSkeletalMeshComponent()->SetSkeletalMesh(SkeletalMesh);
	TmpTemplate->SetActorTransform(SpawnTransform);

	const FGuid MeshGuid = MovieScene->AddSpawnable(*SkeletalMesh->GetName(), *TmpTemplate);

	if (UMovieSceneSpawnTrack* SpawnTrack = MovieScene->AddTrack<UMovieSceneSpawnTrack>(MeshGuid))
	{
		SpawnTrack->Modify();
		SpawnTrack->AddSection(*SpawnTrack->CreateNewSection());
	}

	return MeshGuid;
}

void FChronicle_CinematicBlueprintUtilities::ApplyChanges(
	ULevelSequence* LevelSequence,
	UChronicle_CinematicData* CinematicData,
	const FChronicle_SequenceData& SequenceData
)
{
	if (!LevelSequence)
	{
		return;
	}

	LevelSequence->MarkPackageDirty();

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.Error = GError;

	const FString LevelSequenceFileName = FPackageName::LongPackageNameToFilename(
		LevelSequence->GetPackage()->GetName(),
		FPackageName::GetAssetPackageExtension()
	);

	UPackage::SavePackage(LevelSequence->GetPackage(), LevelSequence, *LevelSequenceFileName, SaveArgs);
	
	for (FChronicle_SequenceData& SequencesData : CinematicData->SequencesData)
	{
		if (SequencesData.Id != SequenceData.Id)
		{
			continue;
		}

		SequencesData.Sequence = TSoftObjectPtr<ULevelSequence>(FSoftObjectPath(LevelSequence));
		break;
	}
	
	CinematicData->MarkPackageDirty();

	const FString PackageFileName = FPackageName::LongPackageNameToFilename(
		CinematicData->GetPackage()->GetName(),
		FPackageName::GetAssetPackageExtension()
	);

	UPackage::SavePackage(CinematicData->GetPackage(), CinematicData, *PackageFileName, SaveArgs);
}
