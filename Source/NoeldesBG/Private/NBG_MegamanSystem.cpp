// Fill out your copyright notice in the Description page of Project Settings.


#include "NBG_MegamanSystem.h"
#include "Kismet/GameplayStatics.h"

int32 ANBG_MegamanSystem::indexLevel = 0;

void ANBG_MegamanSystem::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (indexLevel == 0) {
            UE_LOG(LogTemp, Warning, TEXT("MainMenu"));
            MainMenu_W = CreateWidget<UUserWidget>(PlayerController, MainMenu_Class);
            if (MainMenu_W) {
                MainMenu_W->AddToViewport();
                SetUIOnlyInputMode(MainMenu_W);
            }
        }
        else {
            Menu_W = CreateWidget<UUserWidget>(PlayerController, Menu_Class);
            if (Menu_W) {
                Menu_W->AddToViewport();
                Menu();
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
    UE_LOG(LogTemp, Warning, TEXT("Menu : %d"), visibility);
    if (visibility) {
        Menu_W->SetVisibility(ESlateVisibility::Visible);
        SetUIOnlyInputMode(Menu_W);
    }else{
        Menu_W->SetVisibility(ESlateVisibility::Hidden);
        SetGameOnlyInputMode();
    }
    SetGamePaused(visibility);

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
        SetGamePaused(true);
        if (GetWorld())
        {
            GameOver_W = CreateWidget<UUserWidget>(PlayerController, GameOver_Class);
            GameOver_W->AddToViewport();
            SetUIOnlyInputMode(GameOver_W);
        }
    }
}

void ANBG_MegamanSystem::EndGame()
{
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        SetGamePaused(true);
        if (GetWorld())
        {
            EndGame_W = CreateWidget<UUserWidget>(PlayerController, EndGame_Class);
            EndGame_W->AddToViewport();
            SetUIOnlyInputMode(EndGame_W);
        }
    }
}

void ANBG_MegamanSystem::StageSelection()
{
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if(indexLevel==1)
            SetGamePaused(true);
        if (GetWorld())
        {
            StageSelection_W = CreateWidget<UUserWidget>(PlayerController, StageSelection_Class);
            StageSelection_W->AddToViewport();
            SetUIOnlyInputMode(StageSelection_W);
        }
    }
}

void ANBG_MegamanSystem::SetUIOnlyInputMode(UUserWidget* _widget)
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // Créez une structure FInputModeUIOnly
        FInputModeUIOnly InputMode;

        // Spécifiez le widget sur lequel le focus doit être mis
        InputMode.SetWidgetToFocus(_widget->TakeWidget());

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

void ANBG_MegamanSystem::SetGamePaused(bool isPause)
{
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PlayerController->SetPause(isPause);
    }
}
