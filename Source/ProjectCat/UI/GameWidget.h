// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

class UImage;
class UButton;
class UPanelWidget;

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

public:
	virtual void NativeConstruct() override final;

	/** Should be called by the entity who paused the game */
	void OnToggleGamePaused(bool bIsGamePaused);

	/** 
	 * Toggle the ink overlay UI
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ToggleInkOverlay();

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();
};
