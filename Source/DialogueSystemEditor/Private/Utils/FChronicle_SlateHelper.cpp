#include "FChronicle_SlateHelper.h"

#include "FChronicle_CharacterDirectory.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

TSharedRef<SWidget> FChronicle_SlateHelper::MakeTextField(
	const TAttribute<FText>& Getter,
	const FOnTextCommitted& Setter
)
{
	return SNew(SBox)
	.HeightOverride(150.0f)
	.WidthOverride(225.0f)
	.Padding(4)
	[
		SNew(SMultiLineEditableTextBox)
		.HScrollBar(
			SNew(SScrollBar)
			.Thickness(FVector2D(0, 0))
			.AlwaysShowScrollbar(false)
			.AlwaysShowScrollbarTrack(false).
			Visibility(EVisibility::Hidden)
		)
		.Padding(6)
		.Text(Getter)
		.OnTextCommitted(Setter)
		.AutoWrapText(true)
		.WrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping)
	];
}

TSharedRef<SWidget> FChronicle_SlateHelper::MakeSingleLineTextField(
	const TAttribute<FText>& Getter,
	const FOnTextCommitted& Setter
)
{
	return SNew(SBox)
	.HeightOverride(40.0f)
	.WidthOverride(225.0f)
	.Padding(4)
	[
		SNew(SEditableTextBox)
		.Text(Getter)
		.OnTextCommitted(Setter)
	];
}

TSharedRef<SWidget> FChronicle_SlateHelper::MakeTextField(
	const TAttribute<FText>& Getter
)
{
	return SNew(SBox)
	.HeightOverride(125.0f)
	.WidthOverride(225.0f)
	.Padding(4)
	[
		SNew(SMultiLineEditableTextBox)
		.BackgroundColor(FLinearColor::Transparent)
		.HScrollBar(
			SNew(SScrollBar)
			.Thickness(FVector2D(0, 0))
			.AlwaysShowScrollbar(false)
			.AlwaysShowScrollbarTrack(false).
			Visibility(EVisibility::Hidden)
		)
		.Padding(6)
		.Text(Getter)
		.IsReadOnly(true)
		.AutoWrapText(true)
		.WrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping)
	];
}

TSharedRef<SWidget> FChronicle_SlateHelper::MakeCharacterSelector(
	const FSlateBrush* Icon,
	const TAttribute<FText>& NameGetter,
	const SComboBox<TSharedPtr<FGuid>>::FOnSelectionChanged& OnSelectionChanged,
	const TArray<TSharedPtr<FGuid>>* CharacterIds
)
{
	return SNew(SHorizontalBox)
	
	+ SHorizontalBox::Slot()
	.AutoWidth()
	.VAlign(VAlign_Center)
	[
		SNew(SBox)
		.WidthOverride(16.0f)
		.HeightOverride(16.0f)
		[
			SNew(SImage)
			.Image(Icon)
		]
	]

	+ SHorizontalBox::Slot()
	.FillWidth(1.0f)
	.Padding(FMargin(4.0f, 0.0f, 0.0f, 0.0f))
	[
		SNew(SComboBox<TSharedPtr<FGuid>>)
		.OptionsSource(CharacterIds)
		.OnGenerateWidget_Lambda([](const TSharedPtr<FGuid>& Id)
		{
			return SNew(STextBlock)
				.Text(FText::FromName(FChronicle_CharacterDirectory::GetAll().GetName(*Id)));
		})
		.Content()
		[
			SNew(STextBlock)
			.Text(NameGetter)
			.Margin(FMargin(0.0f, 4.0f))
		]
		.OnSelectionChanged(OnSelectionChanged)
	];
}

TSharedRef<SWidget> FChronicle_SlateHelper::MakeCharacterDisplay(
	const FSlateBrush* Icon,
	const TAttribute<FText>& NameGetter
)
{
	return SNew(SHorizontalBox)

	+ SHorizontalBox::Slot()
	.AutoWidth()
	.VAlign(VAlign_Center)
	[
		SNew(SBox)
		.WidthOverride(16.0f)
		.HeightOverride(16.0f)
		[
			SNew(SImage)
			.Image(Icon)
		]
	]

	+ SHorizontalBox::Slot()
	.FillWidth(1.0f)
	.VAlign(VAlign_Center)
	.Padding(FMargin(4.0f, 0.0f, 0.0f, 0.0f))
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(4)
		[
			SNew(STextBlock)
			.Text(NameGetter)
		]
	];
}

TSharedRef<SWidget> FChronicle_SlateHelper::MakeEmotionSelectionButton(
	const FOnClicked& OnClickedEmpty,
	const FOnClicked& OnClickedSet,
	const FString& Name
)
{
	return SNew(SButton)
	
	.OnClicked(Name.IsEmpty() ? OnClickedEmpty : OnClickedSet)
	.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
	.Cursor(EMouseCursor::Type::Hand)
	[
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(2.0f, 2.0f, 2.0f, 1.5f)
		[
			SNew(SImage)
			.Visibility(Name.IsEmpty() ? EVisibility::Visible : EVisibility::Collapsed)
			.Image(FAppStyle::Get().GetBrush("Icons.Plus"))
		]

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(5.0f, 2.0f, 2.0f, 1.5f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Name.IsEmpty() ? "Pick Emotion" : Name))
			.Justification(ETextJustify::Type::Center)
		]

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(2.0f, 2.0f, 2.0f, 1.5f)
		[
			SNew(SImage)
			.Visibility(Name.IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible)
			.Image(FAppStyle::Get().GetBrush("Icons.X"))
		]
	];
}

FReply FChronicle_SlateHelper::OpenMenuWindow(
	const FText& HeaderText,
	const FText& EmptyMessage,
	const TArray<TPair<FName, FGuid>>& Items,
	TFunction<void(FGuid)> ItemClickCallback
)
{
	const TSharedRef<SVerticalBox> ItemList = SNew(SVerticalBox);

	for (const TPair<FName, FGuid>& Item : Items)
	{
		const FName CapturedName = Item.Key;
		const FGuid CapturedId = Item.Value;

		ItemList->AddSlot()
		.AutoHeight()
		[
			SNew(SButton)
			.ButtonStyle(FAppStyle::Get(), "Menu.Button")
			.ContentPadding(FMargin(16.0f, 6.0f))
			.HAlign(HAlign_Left)
			.OnClicked_Lambda([ItemClickCallback, CapturedId]
			{
				FSlateApplication::Get().DismissAllMenus();
				ItemClickCallback(CapturedId);
				return FReply::Handled();
			})
			[
				SNew(STextBlock)
				.Text(FText::FromName(CapturedName))
				.TextStyle(FAppStyle::Get(), "Menu.Label")
			]
		];
	}
	
    const TSharedRef<SBorder> Menu =
    SNew(SBorder)
    .BorderImage(FAppStyle::GetBrush("Menu.Background"))
    [
        SNew(SVerticalBox)

        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(12.0f, 8.0f, 12.0f, 6.0f)
        [
            SNew(STextBlock)
            .Text(HeaderText)
            .TextStyle(FAppStyle::Get(), "Menu.Heading")
            .ColorAndOpacity(FSlateColor::UseSubduedForeground())
        ]

        + SVerticalBox::Slot()
        .AutoHeight()
        [
            SNew(SSeparator)
            .Thickness(1.0f)
        ]

        + SVerticalBox::Slot()
        .AutoHeight()
        [
            SNew(SBox)
            .MinDesiredWidth(120.0f)
            .MaxDesiredHeight(200.0f)
            [
                ItemList->GetChildren()->Num() > 0
                ? StaticCastSharedRef<SWidget>(
                    SNew(SScrollBox)
                    + SScrollBox::Slot()
                    [
                        ItemList
                    ]
                )
                : StaticCastSharedRef<SWidget>(
                    SNew(SBox)
                    .Padding(12.0f, 8.0f)
                    [
                        SNew(STextBlock)
                        .Text(EmptyMessage)
                        .TextStyle(FAppStyle::Get(), "SmallText")
                        .ColorAndOpacity(FSlateColor::UseSubduedForeground())
                    ]
                )
            ]
        ]
    ];

    FSlateApplication::Get().PushMenu(
        FSlateApplication::Get().GetActiveTopLevelWindow().ToSharedRef(),
        FWidgetPath(),
        Menu,
        FSlateApplication::Get().GetCursorPos(),
        FPopupTransitionEffect::ContextMenu
    );

    return FReply::Handled();
}