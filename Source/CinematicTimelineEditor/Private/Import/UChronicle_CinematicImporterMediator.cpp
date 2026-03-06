#include "UChronicle_CinematicImporterMediator.h"

#include "FChronicle_CinematicImporter.h"

UChronicle_CinematicData* UChronicle_CinematicImporterMediator::ConvertToCinematicData(const UChronicle_DialogueData* Asset)
{
	return FChronicle_CinematicImporter::ConvertToCinematicData(Asset);
}
