#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AChronicle_ParticipantPoint.generated.h"

UCLASS()
class CINEMATICTIMELINEEDITOR_API AChronicle_ParticipantPoint : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UStaticMeshComponent* DebugMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	int32 ShotIndex;

public:
	AChronicle_ParticipantPoint();

	virtual void PostInitProperties() override;
};