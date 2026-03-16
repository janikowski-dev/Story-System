#include "UChronicle_ExportInfo.h"

FName UChronicle_ExportInfo::GetCategoryName() const
{
	return TEXT("Chronicle");
}

check for path, not for name lol

void UChronicle_ExportInfo::UpdateStatus(const FString& Name, const EChronicle_CinematicAssetExportStatus Status)
{
	FChronicle_CinematicEntry* MatchingEntry = Entries.FindByPredicate([&Name](const FChronicle_CinematicEntry& Entry)
	{
		return Entry.AssetName == Name;
	});

	if (!MatchingEntry)
	{
		return;
	}

	MatchingEntry->Status = Status;
}

void UChronicle_ExportInfo::UpdateExportInfo(const FString& Name, const FDateTime ExportTime, const FString& CinematicPath)
{
	FChronicle_CinematicEntry* MatchingEntry = Entries.FindByPredicate([&Name](const FChronicle_CinematicEntry& Entry)
	{
		return Entry.AssetName == Name;
	});

	if (!MatchingEntry)
	{
		return;
	}

	MatchingEntry->CinematicPath = CinematicPath;
	MatchingEntry->LastExportTime = ExportTime;
}

void UChronicle_ExportInfo::TryAdd(const FChronicle_CinematicEntry& InEntry)
{
	const FChronicle_CinematicEntry* MatchingEntry = Entries.FindByPredicate([&InEntry](const FChronicle_CinematicEntry& Entry)
	{
		return Entry.AssetName == InEntry.AssetName;
	});

	if (MatchingEntry)
	{
		return;
	}

	Entries.Add(InEntry);
}
