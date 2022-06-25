// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetOwningPlayer()->SetShowMouseCursor(true);

	Credits_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Credits_Panel->SetIsEnabled(false);
	Tutorials_Panel->SetVisibility(ESlateVisibility::Collapsed);
	Tutorials_Panel->SetIsEnabled(false);
	Back_Button->SetVisibility(ESlateVisibility::Collapsed);
	Back_Button->SetIsEnabled(false);

	StartGame_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGameButtonClicked);
	Tutorials_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnTutorialsButtonClicked);
	Credits_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnCreditsButtonClicked);
	Quit_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitButtonClicked);
	Back_Button->OnClicked.AddDynamic(this, &UMenuWidget::OnBackButtonClicked);
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
