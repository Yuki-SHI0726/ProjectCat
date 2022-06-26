// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

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
	StartGame_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGameButtonClicked);
	Tutorials_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnTutorialsButtonClicked);
	Credits_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnCreditsButtonClicked);
	Quit_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitButtonClicked);

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
	Main_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Main_Panel->SetIsEnabled(false);

	Tutorials_Panel->SetVisibility(ESlateVisibility::Visible);
	Tutorials_Panel->SetIsEnabled(true);
	Back_Button->SetVisibility(ESlateVisibility::Visible);
	Back_Button->SetIsEnabled(true);
}

void UMenuWidget::OnCreditsButtonClicked()
{
	Main_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Main_Panel->SetIsEnabled(false);

	Credits_Panel->SetVisibility(ESlateVisibility::Visible);
	Credits_Panel->SetIsEnabled(true);
	Back_Button->SetVisibility(ESlateVisibility::Visible);
	Back_Button->SetIsEnabled(true);
}

void UMenuWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
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
	Credits_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Credits_Panel->SetIsEnabled(false);
	Tutorials_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Tutorials_Panel->SetIsEnabled(false);

	Back_Button->SetVisibility(ESlateVisibility::Collapsed);
	Back_Button->SetIsEnabled(false);
	
	Main_Panel->SetVisibility(ESlateVisibility::Visible);
	Main_Panel->SetIsEnabled(true);
}
