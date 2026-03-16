#include "UChronicle_CinematicFunctionLibrary.h"

#include "FChronicle_CinematicExporter.h"
#include "Data/UChronicle_ExportInfo.h"

UChronicle_CinematicData* UChronicle_CinematicFunctionLibrary::ExportToCinematicData(const UChronicle_DialogueData* Asset)
{
	return FChronicle_CinematicExporter::ExportToCinematicData(Asset);
}

void UChronicle_CinematicFunctionLibrary::UpdateStatus(const FString Name, const EChronicle_CinematicAssetExportStatus Status)
{
	GetMutableDefault<UChronicle_ExportInfo>()->UpdateStatus(Name, Status);
}

void UChronicle_CinematicFunctionLibrary::UpdateExportInfo(const FString Name, const FDateTime ExportTime, const FString& CinematicPath)
{
	GetMutableDefault<UChronicle_ExportInfo>()->UpdateExportInfo(Name, ExportTime, CinematicPath);
}

void UChronicle_CinematicFunctionLibrary::TryAdd(FChronicle_CinematicEntry Entry)
{
	GetMutableDefault<UChronicle_ExportInfo>()->TryAdd(Entry);
}

TArray<FChronicle_CinematicEntry> UChronicle_CinematicFunctionLibrary::GetAll()
{
	return GetDefault<UChronicle_ExportInfo>()->Entries;
}
