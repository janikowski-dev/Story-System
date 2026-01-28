#pragma once

#include "AssetTypeActions_Base.h"
#include "Assets/UStoryAsset.h"

class FStoryAsset_OpenEditor : public FAssetTypeActions_Base
{
public:
	virtual void OpenAssetEditor(
		const TArray<UObject*>& InObjects,
		TSharedPtr<IToolkitHost> EditWithinLevelEditor
	) override;
	
	virtual FText GetName() const override
	{
		return NSLOCTEXT("Assets", "StoryAsset", "Story Asset");
	}

	virtual FColor GetTypeColor() const override
	{
		return FColor::Purple;
	}

	virtual UClass* GetSupportedClass() const override
	{
		return UStoryAsset::StaticClass();
	}

	virtual uint32 GetCategories() override
	{
		return EAssetTypeCategories::Misc;
	}
};
