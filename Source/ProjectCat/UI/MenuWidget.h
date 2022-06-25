// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UButton;
class UPanelWidget;

/**
 * User widget used for main menu
 * - Start a new game
 * - Credits list
 * - Tutorial
 * - Quit
 */
UCLASS()
class PROJECTCAT_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	/** A panel contains basic options widgets */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UPanelWidget* Main_Panel = nullptr;

	/** A panel contains tutorials info */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UPanelWidget* Tutorials_Panel = nullptr;

	/** A panel contains credits information */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UPanelWidget* Credits_Panel = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* StartGame_Button = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Tutorials_Button = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Credits_Button = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Quit_Button = nullptr;

	/** The button for returning to the main menu status */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Back_Button = nullptr;

public:
	virtual void NativeConstruct() override final;

	UFUNCTION()
	void OnStartGameButtonClicked();

	UFUNCTION()
	void OnTutorialsButtonClicked();

	UFUNCTION()
	void OnCreditsButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();
};
