// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ThirdPersonCharacter.h"
#include "PlayerCharacter.generated.h"

class UGameWidget;

class USpringArmComponent;
class UCameraComponent;

/**
 * Third-Person player class used in gameplay
 */
UCLASS(config=Game)
class APlayerCharacter : public AThirdPersonCharacter
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate = 45.0f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate = 45.0f;

	/** Widget used in gameplay */
	UPROPERTY(BlueprintReadWrite, Category = UI)
	UGameWidget* GameWidget = nullptr;

	/** Time to keep the lose streak effect */
	UPROPERTY(BlueprintReadWrite, Category = UI)
	float LoseStreakEffectTime = 1.0f;

public:
	APlayerCharacter();

protected:
	/** Event to call on game over */
	UFUNCTION(BlueprintCallable)
	void OnGameOver();

	/** Event to call on lose stream occurs */
	UFUNCTION(BlueprintCallable)
	void OnLoseStreak();

	void TogglePauseGame();

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
};

