// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
// Not Modular <Here>
#include "UE_MultiplayerTemp/MenuSystem/MenuInterface.h"

#include "MasterGameInstance.generated.h"

UCLASS()
class UE_MULTIPLAYERTEMP_API UMasterGameInstance : public UGameInstance, public IMenuInterface
{
    GENERATED_BODY()

public:
    UMasterGameInstance(const FObjectInitializer& ObjectInitializer);

    virtual void Init();

    UFUNCTION(Exec)
        void Host();

    UFUNCTION(Exec)
        void Join(const FString& Address);

    UFUNCTION(BlueprintCallable)
        void LoadMenu();

private:
    // Added "Class" for forward declaration as no include added
    TSubclassOf<class UUserWidget> MenuClass;

    class UMainMenu* Menu;
};