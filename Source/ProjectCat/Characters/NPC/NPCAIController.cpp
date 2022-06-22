// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(this) && GetPawn())
	{
		GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), GetWorld()->GetFirstPlayerController()->GetPawn());
	}
}
