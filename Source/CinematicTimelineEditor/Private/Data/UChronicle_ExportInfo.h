#pragma once

#include "FChronicle_CinematicEntry.h"
#include "Engine/DeveloperSettings.h"
#include "UChronicle_ExportInfo.generated.h"

UCLASS(Config=CinematicTimelineEditor, DefaultConfig, meta=(DisplayName="Export Info"))
class CINEMATICTIMELINEEDITOR_API UChronicle_ExportInfo : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	virtual FName GetCategoryName() const override;
	
	void UpdateStatus(const FString& Name, const EChronicle_CinematicAssetExportStatus Status);
	void UpdateExportInfo(const FString& Name, const FDateTime ExportTime, const FString& CinematicPath);
	void TryAdd(const FChronicle_CinematicEntry& InEntry);

public:
	UPROPERTY(Config, EditAnywhere, meta=(DisplayPriority=0))
	TArray<FChronicle_CinematicEntry> Entries;
};