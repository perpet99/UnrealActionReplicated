// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/NetSerialization.h"
#include "Runtime/Core/Public/Serialization/BufferArchive.h"
#include "Runtime/Core/Public/Serialization/MemoryReader.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealNetwork.h"
#include "ActionInfoBaseStand.generated.h"




UCLASS(BlueprintType)
class UActionStateBase : public UObject
{
public:
	GENERATED_BODY()

		virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

	virtual uint8 GetActionID() { return CurState; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 CurState;
	class AUARCharacter *player;
};

UCLASS()
class UActionStateStand : public UActionStateBase
{
public:
	GENERATED_BODY()


	UPROPERTY(ReplicatedUsing = OnRep_Name)
	FString Name;
	UFUNCTION()
		void OnRep_Name() {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OnRep_Name!"));
	}
	

	virtual void Serialize(FArchive &Ar) {
		/*uint8 a = GetClassID();
		Ar << a;*/
	}

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);

		DOREPLIFETIME(UActionStateStand, Name);
	}

	//virtual bool Deserialize(TArray<uint8>) {};

	//virtual uint8 GetClassID() {};

};

UCLASS()
class UActionInfoBaseAttack : public UActionStateBase
{
public:
	GENERATED_BODY()


	UPROPERTY(ReplicatedUsing = OnRep_Name)
		FString Name;
	UFUNCTION()
		void OnRep_Name() {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("OnRep_Name! = %s"), *Name));
	}


	virtual bool IsSupportedForNetworking() const override;

	virtual void Serialize(FArchive &Ar) {
		/*uint8 a = GetClassID();
		Ar << a;*/
	}

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	//void PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker);
	//virtual bool Deserialize(TArray<uint8>) {};

	//virtual uint8 GetClassID() {};

};
