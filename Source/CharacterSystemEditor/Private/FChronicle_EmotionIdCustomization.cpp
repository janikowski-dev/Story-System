#include "FChronicle_EmotionIdCustomization.h"

#include "DetailWidgetRow.h"
#include "PropertyHandle.h"
#include "FChronicle_EmotionId.h"
#include "FChronicle_EmotionDirectory.h"
#include "Widgets/Text/STextBlock.h"

TSharedRef<IPropertyTypeCustomization> FChronicle_EmotionIdCustomization::MakeInstance()
{
	return MakeShareable(new FChronicle_EmotionIdCustomization());
}

void FChronicle_EmotionIdCustomization::CustomizeHeader(
    TSharedRef<IPropertyHandle> StructPropertyHandle,
    FDetailWidgetRow& HeaderRow,
    IPropertyTypeCustomizationUtils& StructCustomizationUtils
)
{
    FChronicle_EmotionDirectory::Refresh();

    ComboOptions.Empty();
    ComboOptions.Add(MakeShared<FString>(TEXT("None")));

    for (TSharedPtr SharedId : FChronicle_EmotionDirectory::GetAll().GetSharedIds())
    {
        FString Name = FChronicle_EmotionDirectory::GetAll().GetName(*SharedId);
        ComboOptions.Add(MakeShared<FString>(Name));
    }

    TSharedPtr<IPropertyHandle> IdHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FChronicle_EmotionId, Id));

    auto GetCurrentLabel = [this, IdHandle]() -> FText
    {
        FString GuidStr;
        
        if (IdHandle.IsValid() && IdHandle->GetValueAsFormattedString(GuidStr) == FPropertyAccess::Success)
        {
            FGuid CurrentGuid;
            
            if (FGuid::Parse(GuidStr, CurrentGuid) && CurrentGuid.IsValid())
            {
                const FString Name = FChronicle_EmotionDirectory::GetAll().GetName(CurrentGuid);
                
                if (!Name.IsEmpty())
                {
                    return FText::FromString(Name);
                }
            }
        }
        return FText::FromString(TEXT("None"));
    };

    HeaderRow
    .NameContent()
    [
        StructPropertyHandle->CreatePropertyNameWidget()
    ]
    .ValueContent()
    .MinDesiredWidth(200.0f)
    [
        SNew(SComboBox<TSharedPtr<FString>>)
        .OptionsSource(&ComboOptions)
        .OnGenerateWidget_Lambda([](const TSharedPtr<FString>& Item)
        {
            return SNew(STextBlock).Text(FText::FromString(*Item));
        })
        .OnSelectionChanged_Lambda([this, IdHandle](const TSharedPtr<FString>& SelectedName, ESelectInfo::Type)
        {
            if (!SelectedName.IsValid() || *SelectedName == TEXT("None"))
            {
                if (IdHandle.IsValid())
                {
                    IdHandle->SetValueFromFormattedString(FGuid().ToString());
                }
                return;
            }
            
            for (TSharedPtr SharedId : FChronicle_EmotionDirectory::GetAll().GetSharedIds())
            {
                if (FString Name = FChronicle_EmotionDirectory::GetAll().GetName(*SharedId); Name == *SelectedName)
                {
                    if (IdHandle.IsValid())
                    {
                        IdHandle->SetValueFromFormattedString(SharedId->ToString());
                    }
                    
                    break;
                }
            }
        })
        .Content()
        [
            SNew(STextBlock)
            .Text_Lambda(GetCurrentLabel)
        ]
    ];
}

void FChronicle_EmotionIdCustomization::CustomizeChildren(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& ChildBuilder,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils
)
{
}
