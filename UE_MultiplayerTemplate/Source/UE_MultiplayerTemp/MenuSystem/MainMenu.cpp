// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	// Binding to a button in Main Menu (Host)
	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	P_MenuInterface = MenuInterface;
}

void UMainMenu::Setup()
{
	// Display Menu
	this->AddToViewport();

	// Get World
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	// Get first Player Controller
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	// *** 
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	// Set Input mode for Player Controller
	PlayerController->SetInputMode(InputModeData);

	// Set Mouse visibility = true for Player Controller
	PlayerController->SetShowMouseCursor(true);
	//***1
}

void UMainMenu::MenuTeardown()
{
	// Remove Menu From Veiwport
	this->RemoveFromViewport();

	// Get World
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	// Get first Player Controller
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	// Set Input mode for Player Controller
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	// Set Mouse visibility = true for Player Controller
	PlayerController->SetShowMouseCursor(false);

}

void UMainMenu::HostServer()
{
	//UE_LOG(LogTemp, Warning, TEXT("I'm Going to host a Server!"));

	if (P_MenuInterface != nullptr)
	{
		P_MenuInterface->Host();
	}

}