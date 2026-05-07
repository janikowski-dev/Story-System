#pragma once

#include "Data/FChronicle_EmotionData.h"
#include "UChronicle_EmotionSettings.generated.h"

UCLASS(Config=ChronicleCoreEditor, DefaultConfig, meta=(DisplayName="Emotions"))
class CHRONICLECOREEDITOR_API UChronicle_EmotionSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	virtual FName GetCategoryName() const override;

	TArray<FChronicle_EmotionData> GetAllEmotions() const;
	FChronicle_EmotionData GetEmotion(FGuid Id) const;
	FString GetName(FGuid Id) const;

public:
	UPROPERTY(Config, EditAnywhere)
	TArray<FChronicle_EmotionData> Emotions;
};