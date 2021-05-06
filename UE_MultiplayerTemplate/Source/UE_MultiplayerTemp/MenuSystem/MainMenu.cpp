// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	// Binding to a button in Main Menu (Host)
	if (!ensure(HostButton != nullptr)) return false;
	// Call for binding
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	
	// Binding to a button in Main Menu (Join)
	if (!ensure(JoinButton != nullptr)) return false;
	// Call for binding
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	// Binding to a button in Main Menu (Back)
	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	// Call for binding
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

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

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);


}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}