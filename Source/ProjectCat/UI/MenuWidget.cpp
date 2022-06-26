// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"

/** Paw offset from buttons */
static const FVector2D PawOffset(-100.0f, -10.0f);

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetOwningPlayer()->SetShowMouseCursor(true);

	// Grab all the tutorial images in array. Only set visible the first item
	for (UWidget* Child : TutorialImages_Panel->GetAllChildren())
	{
		if (UImage* TutorialImage = Cast<UImage>(Child))
		{
			TutorialImages.Emplace(TutorialImage);
			if (TutorialImages.Num() > 1)
			{
				TutorialImage->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}

	Credits_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Credits_Panel->SetIsEnabled(false);
	Tutorials_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Tutorials_Panel->SetIsEnabled(false);
	Back_Button->SetVisibility(ESlateVisibility::Collapsed);
	Back_Button->SetIsEnabled(false);

	// Main
	Paw_Image->SetVisibility(ESlateVisibility::Collapsed);
	StartGame_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGameButtonClicked);
	Tutorials_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnTutorialsButtonClicked);
	Credits_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnCreditsButtonClicked);
	Quit_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitButtonClicked);

	Tutorials_Button->OnHovered.AddDynamic(this, &UMenuWidget::OnTutorialsButtonHovered);
	Credits_Button->OnHovered.AddDynamic(this, &UMenuWidget::OnCreditsButtonHovered);
	Quit_Button->OnHovered.AddDynamic(this, &UMenuWidget::OnQuitButtonHovered);

	Tutorials_Button->OnUnhovered.AddDynamic(this, &UMenuWidget::OnButtonUnhovered);
	Credits_Button->OnUnhovered.AddDynamic(this, &UMenuWidget::OnButtonUnhovered);
	Quit_Button->OnUnhovered.AddDynamic(this, &UMenuWidget::OnButtonUnhovered);

	// General
	Back_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnBackButtonClicked);

	// Tutorials
	ToLeft_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnToLeftButtonClicked);
	ToRight_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnToRightButtonClicked);
}

void UMenuWidget::OnStartGameButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level_Main"));
}

void UMenuWidget::OnTutorialsButtonClicked()
{
	if (ButtonClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ButtonClickSound);
	}

	Main_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Main_Panel->SetIsEnabled(false);

	Tutorials_Panel->SetVisibility(ESlateVisibility::Visible);
	Tutorials_Panel->SetIsEnabled(true);
	Back_Button->SetVisibility(ESlateVisibility::Visible);
	Back_Button->SetIsEnabled(true);
}

void UMenuWidget::OnTutorialsButtonHovered()
{
	if (ButtonHoverSound)
	{
		UGameplayStatics::PlaySound2D(this, ButtonHoverSound);
	}

	Paw_Image->SetVisibility(ESlateVisibility::Visible);

	UCanvasPanelSlot* PawImageCanvasSlot = Cast<UCanvasPanelSlot>(Paw_Image->Slot);
	UCanvasPanelSlot* TutorialsButtonCanvasSlot = Cast<UCanvasPanelSlot>(Tutorials_Button->Slot);

	const FVector2D TutorialsButtonPosition = TutorialsButtonCanvasSlot->GetPosition();
	const FVector2D PawImageNewPosition = TutorialsButtonPosition + PawOffset;

	PawImageCanvasSlot->SetPosition(PawImageNewPosition);
}

void UMenuWidget::OnCreditsButtonClicked()
{
	if (ButtonClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ButtonClickSound);
	}

	Main_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Main_Panel->SetIsEnabled(false);

	Credits_Panel->SetVisibility(ESlateVisibility::Visible);
	Credits_Panel->SetIsEnabled(true);
	Back_Button->SetVisibility(ESlateVisibility::Visible);
	Back_Button->SetIsEnabled(true);
}

void UMenuWidget::OnCreditsButtonHovered()
{
	if (ButtonHoverSound)
	{
		UGameplayStatics::PlaySound2D(this, ButtonHoverSound);
	}

	Paw_Image->SetVisibility(ESlateVisibility::Visible);

	UCanvasPanelSlot* PawImageCanvasSlot = Cast<UCanvasPanelSlot>(Paw_Image->Slot);
	UCanvasPanelSlot* CreditsButtonCanvasSlot = Cast<UCanvasPanelSlot>(Credits_Button->Slot);

	const FVector2D CreditsButtonPosition = CreditsButtonCanvasSlot->GetPosition();
	const FVector2D PawImageNewPosition = CreditsButtonPosition + PawOffset;

	PawImageCanvasSlot->SetPosition(PawImageNewPosition);
}

void UMenuWidget::OnQuitButtonClicked()
{
	if (ButtonClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ButtonClickSound);
	}

	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UMenuWidget::OnQuitButtonHovered()
{
	if (ButtonHoverSound)
	{
		UGameplayStatics::PlaySound2D(this, ButtonHoverSound);
	}

	Paw_Image->SetVisibility(ESlateVisibility::Visible);

	UCanvasPanelSlot* PawImageCanvasSlot = Cast<UCanvasPanelSlot>(Paw_Image->Slot);
	UCanvasPanelSlot* QuitButtonCanvasSlot = Cast<UCanvasPanelSlot>(Quit_Button->Slot);

	const FVector2D QuitButtonPosition = QuitButtonCanvasSlot->GetPosition();
	const FVector2D PawImageNewPosition = QuitButtonPosition + PawOffset;

	PawImageCanvasSlot->SetPosition(PawImageNewPosition);
}

void UMenuWidget::OnButtonUnhovered()
{
	Paw_Image->SetVisibility(ESlateVisibility::Collapsed);
}

void UMenuWidget::OnToLeftButtonClicked()
{
	if (PageIndex > 0)
	{
		FlipPage(true);
	}
}

void UMenuWidget::OnToRightButtonClicked()
{
	if (PageIndex < TutorialImages.Num() - 1)
	{
		FlipPage(false);
	}
}

void UMenuWidget::FlipPage(bool bToLeft)
{
	// Play flip sound if there's any
	if (FlipPageSound)
	{
		UGameplayStatics::PlaySound2D(this, FlipPageSound);
	}

	TutorialImages[PageIndex]->SetVisibility(ESlateVisibility::Collapsed);

	if (bToLeft)
	{
		--PageIndex;
	}
	else
	{
		++PageIndex;
	}

	TutorialImages[PageIndex]->SetVisibility(ESlateVisibility::Visible);
}

void UMenuWidget::OnBackButtonClicked()
{
	if (ButtonClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ButtonClickSound);
	}

	Credits_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Credits_Panel->SetIsEnabled(false);
	Tutorials_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Tutorials_Panel->SetIsEnabled(false);

	Back_Button->SetVisibility(ESlateVisibility::Collapsed);
	Back_Button->SetIsEnabled(false);
	
	Main_Panel->SetVisibility(ESlateVisibility::Visible);
	Main_Panel->SetIsEnabled(true);
}
