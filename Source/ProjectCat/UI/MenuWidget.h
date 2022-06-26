// Fill out		your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utils/TypeDefs.h"
#include "MenuWidget.generated.h"

class UButton;
class UImage;
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
	//----------------------------------------------------------------------------------------------
	// Main menu
	/** A panel contains basic options widgets */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UPanelWidget* Main_Panel = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* StartGame_Button = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Tutorials_Button = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Credits_Button = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Quit_Button = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UImage* Paw_Image = nullptr;

	//----------------------------------------------------------------------------------------------
	// Tutorials
	/** A panel contains tutorials info */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UPanelWidget* Tutorials_Panel = nullptr;

	/** Move to left page */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* ToLeft_Button = nullptr;

	/** Move to right page */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* ToRight_Button = nullptr;

	/** A panel contains tutorials images */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UPanelWidget* TutorialImages_Panel = nullptr;

	/** Stores all tutorials images */
	TArray<UImage*> TutorialImages;
	int32 PageIndex = 0;

	//----------------------------------------------------------------------------------------------
	// Credits
	/** A panel contains credits information */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UPanelWidget* Credits_Panel = nullptr;

	/** The button for returning to the main menu status */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Back_Button = nullptr;

	//----------------------------------------------------------------------------------------------
	// Sounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USoundBase* FlipPageSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USoundBase* ButtonClickSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USoundBase* ButtonHoverSound = nullptr;

public:
	virtual void NativeConstruct() override final;

	UFUNCTION()
	void OnBackButtonClicked();

	//----------------------------------------------------------------------------------------------
	// Main menu
	UFUNCTION()
	void OnStartGameButtonClicked();

	UFUNCTION()
	void OnTutorialsButtonClicked();

	UFUNCTION()
	void OnTutorialsButtonHovered();

	UFUNCTION()
	void OnCreditsButtonClicked();

	UFUNCTION()
	void OnCreditsButtonHovered();

	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnQuitButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();

	//----------------------------------------------------------------------------------------------
	// Tutorials
	UFUNCTION()
	void OnToLeftButtonClicked();

	UFUNCTION()
	void OnToRightButtonClicked();

private:
	void FlipPage(bool bToLeft);
};
