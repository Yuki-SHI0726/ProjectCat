// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnResumeButtonClicked();

	GameOver_Panel->SetVisibility(ESlateVisibility::Collapsed);
	GameOver_Panel->SetIsEnabled(false);

	Resume_Button->OnClicked.AddDynamic(this, &UGameWidget::OnResumeButtonClicked);
	BackToMainMenu_Button->OnClicked.AddDynamic(this, &UGameWidget::OnBackButtonClicked);
	Quit_Button->OnClicked.AddDynamic(this, &UGameWidget::OnQuitButtonClicked);
}

void UGameWidget::OnToggleGamePaused(bool bIsGamePaused)
{
	GetOwningPlayer()->SetShowMouseCursor(bIsGamePaused);
	Paused_Panel->SetIsEnabled(bIsGamePaused);
	if (bIsGamePaused)
	{
		Paused_Panel->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Paused_Panel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UGameWidget::UpdateGameplayScore(int32 ScoreToDisplay)
{
	Scoreboard_Gameplay_Text->SetText(FText::AsNumber(ScoreToDisplay));
}

void UGameWidget::ShowGameOverUI(int32 ScoreToDisplay)
{
	GameOver_Panel->SetVisibility(ESlateVisibility::Visible);
	GameOver_Panel->SetIsEnabled(true);

	Scoreboard_GameOver_Text->SetText(FText::AsNumber(ScoreToDisplay));
}

void UGameWidget::OnResumeButtonClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	OnToggleGamePaused(false);
}

void UGameWidget::OnBackButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level_Menu"));
}

void UGameWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
