// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_MultiplayerTemp/MenuSystem/InGameEscMenu.h"
#include "Components/Button.h"

bool UInGameEscMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	// Bindings
	if (!ensure(EscMenuResumeButton != nullptr)) return false;
	EscMenuResumeButton->OnClicked.AddDynamic(this, &UInGameEscMenu::ResumePressed);


	return true;
}

void UInGameEscMenu::ResumePressed()
{
	MenuTeardown();
}
