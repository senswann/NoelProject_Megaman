// Fill out your copyright notice in the Description page of Project Settings.


#include "NBG_MegamanSystem.h"
#include "Kismet/GameplayStatics.h"

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

    // Utilisez un switch ou une autre logique pour d�terminer le nom de la carte en fonction de l'index
    switch (_index)
    {
    case 0:
        MapName = TEXT("MainMenu");
        break;
    case 1:
        MapName = TEXT("Level");
        break;
    default:
        MapName = TEXT("DefaultMap");
        break;
    }
    SetGameOnlyInputMode();
    // Chargez la carte en utilisant le nom d�termin�
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

void ANBG_MegamanSystem::SetUIOnlyInputMode()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // Cr�ez une structure FInputModeUIOnly
        FInputModeUIOnly InputMode;

        // Sp�cifiez le widget sur lequel le focus doit �tre mis
        InputMode.SetWidgetToFocus(Menu_W->TakeWidget());

        // Appliquez le mode d'entr�e
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
        // Cr�ez une structure FInputModeGameOnly
        FInputModeGameOnly InputMode;

        // Appliquez le mode d'entr�e
        PlayerController->SetInputMode(InputMode);

        // Affichez le curseur de la souris
        PlayerController->bShowMouseCursor = false;
    }
}
