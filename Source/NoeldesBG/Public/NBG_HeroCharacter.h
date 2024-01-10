// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Widget/NBG_HUD.h"
#include "NBG_E_Hero.h"
#include "NBG_MegamanSystem.h"
#include "NBG_HeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
//pour le spawn de l'arme
class UArrowComponent;

struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class NOELDESBG_API ANBG_HeroCharacter : public ACharacter
{
	GENERATED_BODY()
								/** COMPONENT */

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Arrow de tir */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ShootArrowComponent;
	/** Capsule de collision */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleColision;

								/** INPUT */
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

								/** VARIABLE */

	//pour stocker le pointeur de la DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Value, meta = (AllowPrivateAccess = "true"))
    UDataTable* DT_ValueInGame;
	
	//HUD du joueur
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UNBG_HUD> HUD_Class;
	UNBG_HUD* HUD;

	//HP du joueur
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 HP=0;

	//HP du joueur
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 HP_Max=0;

	//HP du joueur
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	bool IsInvicible=false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Value, meta = (AllowPrivateAccess = "true"))
	NBG_E_Hero State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Value, meta = (AllowPrivateAccess = "true"))
	NBG_E_Hero Prev_State;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ANBG_Projectiles> ProjectileClass;

public:
	UFUNCTION(BlueprintCallable, Category = "MyFunctions")
	void Stun();

	void Invicibility();
	// Sets default values for this character's properties
	ANBG_HeroCharacter();

	//fonction pour prendre des dégats.
	void GetDamage(int32 _dmg);

	void SetHP(int32 _hp);

protected:

	/** Called for movement input */
	void IA_Move(const FInputActionValue& Value);
	void IA_Move_Completed(const FInputActionValue& Value);

	/** Called for looking input */
	void IA_Shoot(const FInputActionValue& Value);

	void IA_Jump(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 GetDataTableValue(const FString RowName);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
