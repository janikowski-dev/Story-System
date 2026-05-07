#pragma once

#include "IPropertyTypeCustomization.h"

class CHARACTERSYSTEMEDITOR_API FChronicle_EmotionIdCustomization : public IPropertyTypeCustomization
{
private:
	TArray<TSharedPtr<FString>> ComboOptions;
	
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(
		TSharedRef<IPropertyHandle> StructPropertyHandle,
		FDetailWidgetRow& HeaderRow,
		IPropertyTypeCustomizationUtils& StructCustomizationUtils
	) override;

	virtual void CustomizeChildren(
		TSharedRef<IPropertyHandle> StructPropertyHandle,
		IDetailChildrenBuilder& StructBuilder,
		IPropertyTypeCustomizationUtils& StructCustomizationUtils
	) override;
};