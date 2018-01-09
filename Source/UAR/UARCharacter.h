// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnrealNetwork.h"
#include "ActionInfoBaseStand.h"

#include "UARCharacter.generated.h"




UCLASS(config=Game)
class AUARCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AUARCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

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

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//UPROPERTY(Replicated)

	UFUNCTION(BlueprintCallable)
	void SetActionStateAttack(FString name) {
		CurAction = pUActionInfoBaseAttack;
		pUActionInfoBaseAttack->Name = name;
	}

	uint8 CurState;
	
	TWeakObjectPtr< UActionStateBase> CurAction;
	UFUNCTION(BlueprintCallable)
	int GetActionState() {
		return CurAction->CurState;
	}

	UPROPERTY(ReplicatedUsing=OnUActionStateStand)
		TWeakObjectPtr<UActionStateStand> pUActionStateStand;
	UFUNCTION()
	void OnUActionStateStand() {
		CurAction = pUActionStateStand;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("OnUActionStateStand!=%d"),(int)Role));
	}

	UPROPERTY(ReplicatedUsing=OnUActionInfoBaseAttack)
		TWeakObjectPtr<UActionInfoBaseAttack>pUActionInfoBaseAttack;
	UFUNCTION()
	void OnUActionInfoBaseAttack() {
		CurAction = pUActionInfoBaseAttack;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("OnUActionInfoBaseAttack!=%d"), (int)Role));
	}

	virtual void PostInitializeComponents() override;

	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		
		DOREPLIFETIME(AUARCharacter, pUActionStateStand);
		DOREPLIFETIME(AUARCharacter, pUActionInfoBaseAttack);
	}
};

