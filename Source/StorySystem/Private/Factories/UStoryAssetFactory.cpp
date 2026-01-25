#include "UStoryAssetFactory.h"
#include "Assets/UStoryAsset.h"
#include "Graphs/UStoryGraph.h"
#include "Schemas/UStoryGraphSchema.h"

UStoryAssetFactory::UStoryAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UStoryAsset::StaticClass();
}

UObject* UStoryAssetFactory::FactoryCreateNew(
	UClass* InClass,
	UObject* InParent,
	const FName InName,
	const EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn
)
{
	UStoryAsset* Asset = NewObject<UStoryAsset>(
		InParent,
		InClass,
		InName,
		Flags | RF_Transactional
	);

	Asset->Graph = NewObject<UStoryGraph>(
		Asset,
		UStoryGraph::StaticClass(),
		NAME_None,
		RF_Transactional
	);

	Asset->Graph->Schema = UStoryGraphSchema::StaticClass();
	Asset->Graph->GetSchema()->CreateDefaultNodesForGraph(*Asset->Graph);
	Asset->Graph->Modify();
	Asset->Modify();

	return Asset;
}