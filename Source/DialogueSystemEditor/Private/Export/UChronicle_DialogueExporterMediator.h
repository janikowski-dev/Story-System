#pragma once

#include "UChronicle_DialogueExporterMediator.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API UChronicle_DialogueExporterMediator : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Chronicle|Dialogue")
    static UChronicle_DialogueData* ConvertToData(const UChronicle_DialogueAsset* Asset);
    
    UFUNCTION(BlueprintCallable, Category="Chronicle|Dialogue")
    static FString ConvertToJson(const UChronicle_DialogueAsset* Asset);
};