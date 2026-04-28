#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AChronicle_CameraPoint.generated.h"

UCLASS()
class CINEMATICTIMELINEEDITOR_API AChronicle_CameraPoint : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UStaticMeshComponent* DebugMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	int32 ShotIndex;

public:
	AChronicle_CameraPoint();

	virtual void PostInitProperties() override;
};