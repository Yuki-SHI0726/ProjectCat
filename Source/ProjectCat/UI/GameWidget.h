// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

class UImage;
class UButton;
class UPanelWidget;
class UTextBlock;

/**
 * UI Widget used in gameplay level
 * - Pause game
 */
UCLASS()
class PROJECTCAT_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	//----------------------------------------------------------------------------------------------
	// Gameplay scene
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* Scoreboard_Gameplay_Text = nullptr;

	//----------------------------------------------------------------------------------------------
	// Paused scene
	/** A panel contains widgets when game paused */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UPanelWidget* Paused_Panel = nullptr;

	/** Resumes the game state from pause */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Resume_Button = nullptr;

	/** Back to the main menu */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* BackToMainMenu_Button = nullptr;

	/** Quit the game */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Quit_Button = nullptr;

	//----------------------------------------------------------------------------------------------
	// Game over scene
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UPanelWidget* GameOver_Panel = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* Scoreboard_GameOver_Text = nullptr;

public:
	virtual void NativeConstruct() override final;

	/** Should be called by the entity who paused the game */
	void OnToggleGamePaused(bool bIsGamePaused);

	/** Update Gameplay Score */
	UFUNCTION(BlueprintCallable)
	void UpdateGameplayScore(int32 ScoreToDisplay);

	/** Shows the game over's UI */
	UFUNCTION(BlueprintCallable)
	void ShowGameOverUI(int32 ScoreToDisplay);

	/** Toggle the ink overlay UI */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ToggleInkOverlay();

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();
};
