// Fill out your copyright notice in the Description page of Project Settings.


#include "NBG_MegamanSystem.h"
#include "Kismet/GameplayStatics.h"

int32 ANBG_MegamanSystem::indexLevel = 1;

void ANBG_MegamanSystem::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (GetWorld())
        {
            if (indexLevel == 0) {
                UE_LOG(LogTemp, Warning, TEXT("MainMenu"));
                MainMenu_W = CreateWidget<UUserWidget>(PlayerController, MainMenu_Class);
                MainMenu_W->AddToViewport();
                //SetUIOnlyInputMode();
            }
            else {
                /*Menu_W = CreateWidget<UNBG_Menu>(PlayerController, Menu_Class);
                Menu_W->AddToViewport();
                Menu();*/
            }
        }
    }
}

void ANBG_MegamanSystem::AddPoint(int32 _point){
	CountPoint += _point;
	HUD->AddPoint(CountPoint);
}

void ANBG_MegamanSystem::Menu()
{
    UE_LOG(LogTemp, Warning, TEXT("Menu"));
    if (visibility) {
        Menu_W->SetVisibility(ESlateVisibility::Visible);
        //SetUIOnlyInputMode();
    }else{
        Menu_W->SetVisibility(ESlateVisibility::Hidden);
        //SetGameOnlyInputMode();
    }
    visibility = !visibility;
}

void ANBG_MegamanSystem::Load(int32 _index)
{
    FString MapName;
    indexLevel = _index;
    UE_LOG(LogTemp, Warning, TEXT("Load : %d"), indexLevel);
    // Utilisez un switch ou une autre logique pour déterminer le nom de la carte en fonction de l'index
    switch (indexLevel)
    {
    case 0:
        MapName = TEXT("MainMenu");
        break;
    case 1:
        MapName = TEXT("Master");
        break;
    default:
        MapName = TEXT("DefaultMap");
        break;
    }
    SetGameOnlyInputMode();
    // Chargez la carte en utilisant le nom déterminé
    UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName), true);
}

void ANBG_MegamanSystem::Quit()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if (PlayerController)
    {
        PlayerController->ConsoleCommand("Quit");
    }
}

void ANBG_MegamanSystem::GameOver()
{
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (GetWorld())
        {
            GameOver_W = CreateWidget<UUserWidget>(PlayerController, GameOver_Class);
            GameOver_W->AddToViewport();
            //SetUIOnlyInputMode();
        }
    }
}

void ANBG_MegamanSystem::StageSelection()
{
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (GetWorld())
        {
            StageSelection_W = CreateWidget<UUserWidget>(PlayerController, StageSelection_Class);
            StageSelection_W->AddToViewport();
            //SetUIOnlyInputMode();
        }
    }
}

void ANBG_MegamanSystem::SetUIOnlyInputMode()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // Créez une structure FInputModeUIOnly
        FInputModeUIOnly InputMode;

        // Spécifiez le widget sur lequel le focus doit être mis
        InputMode.SetWidgetToFocus(Menu_W->TakeWidget());

        // Appliquez le mode d'entrée
        PlayerController->SetInputMode(InputMode);

        // Masquez le curseur de la souris
        PlayerController->bShowMouseCursor = true;
    }
}

void ANBG_MegamanSystem::SetGameOnlyInputMode()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // Créez une structure FInputModeGameOnly
        FInputModeGameOnly InputMode;

        // Appliquez le mode d'entrée
        PlayerController->SetInputMode(InputMode);

        // Affichez le curseur de la souris
        PlayerController->bShowMouseCursor = false;
    }
}
