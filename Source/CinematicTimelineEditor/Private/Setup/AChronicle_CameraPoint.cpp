#include "AChronicle_CameraPoint.h"

#include "Interfaces/IPluginManager.h"

AChronicle_CameraPoint::AChronicle_CameraPoint()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = Root;

	DebugMesh = CreateEditorOnlyDefaultSubobject<UStaticMeshComponent>(TEXT("DebugMesh"));
    DebugMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DebugMesh->SetupAttachment(RootComponent);
}

void AChronicle_CameraPoint::PostInitProperties()
{
	Super::PostInitProperties();

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("Chronicle"));
	const FString PackagePath = FString::Printf(TEXT("/%s/Gizmos/Camera.Camera"), *Plugin->GetName());
    
	if (UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr,PackagePath))
	{
		DebugMesh->SetStaticMesh(Mesh);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DebugMesh: debug mesh not found"));
	}
}
