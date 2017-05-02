// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UENUM(BlueprintType)
enum class EAnimationType : uint8
{
	AS_NORMAL		UMETA(DisplayName = "NORMAL"),
	AS_RIFLE		UMETA(DisplayName = "RIFLE")
};

UENUM(BlueprintType)
enum class EObjectState : uint8
{
	OS_WORLD		UMETA(DisplayName = "WORLD"),
	OS_INVENTORY	UMETA(DisplayName = "INVENTORY"),
	OS_STACKED		UMETA(DisplayName = "STACKED"),
	OS_PLACED		UMETA(DisplayName = "PLACED")
};

UENUM(BlueprintType)
enum class EUsageTarget : uint8
{
	UT_WORLD		UMETA(DisplayName = "WORLD"),
	UT_PLAYER		UMETA(DisplayName = "PLAYER"),
	UT_NONE			UMETA(DisplayName = "NO TARGET")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	IT_PICKUP		UMETA(DisplayName = "PICKUP"),
	IT_USAGE		UMETA(DisplayName = "USAGE")
};

USTRUCT(BlueprintType)
struct FUsage
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		EUsageTarget ETargetType;
	UPROPERTY(EditDefaultsOnly)
		float fTargetDistanceMax;
	UPROPERTY(EditDefaultsOnly)
		bool bIsOverTime;
	UPROPERTY(EditDefaultsOnly)
		float fTimeFactor;
public:
	FUsage() { /* be sure to set in default */ }
	EUsageTarget GetTargetType() { return ETargetType; }
	EUsageTarget SetTargetType(EUsageTarget ENewTargetType) { ETargetType = ENewTargetType; return ETargetType; }
	float GetMaximumTargetDistance() { return fTargetDistanceMax; }
	float SetMaximumTargetDistance(float fNewTargetDistance) { fTargetDistanceMax = fNewTargetDistance; return fTargetDistanceMax; }
	bool GetIsOverTime() { return bIsOverTime; }
	bool SetIsOverTime(bool bNewIsOverTime) { bIsOverTime = bNewIsOverTime; return bIsOverTime; }
	float GetTimeFactor() { return fTimeFactor; }
	float SetTImeFactor(float fNewTimeFactor) { fTimeFactor = fNewTimeFactor; return fTimeFactor; }
};


UCLASS()
class THINGSINWOODS_API ABaseItem : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* RootScene;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, Category = Sound)
		class UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bIsStackable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int iStackSize;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString FItemName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EAnimationType EAnimationTypeCurrent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FUsage FPrimarySkill;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FUsage FSecondarySkill;

	bool GetIsStackable() { return bIsStackable; }
	bool SetIsStackable(bool bNewIsStackable) { bIsStackable = bNewIsStackable; return bIsStackable; }
	int GetStackSize() { return iStackSize; }
	int SetStackSize(int iNewStackSize) { iStackSize = iNewStackSize; return iStackSize; }
	FString GetItemName() { return FItemName; }
	FString SetItemName(FString FNewItemName) { FItemName = FNewItemName; return FItemName; }
	EAnimationType GetAnimationType() { return EAnimationTypeCurrent; }
	EAnimationType SetAnimationType(EAnimationType ENewAnimationType) { EAnimationTypeCurrent = ENewAnimationType; return EAnimationTypeCurrent; }
	FUsage* GetPrimarySkill() { return &FPrimarySkill; }
	FUsage* SetPrimarySkill(FUsage FNewPrimarySkill) { FPrimarySkill = FNewPrimarySkill; return &FPrimarySkill; }
	FUsage* GetSecondarySkill() { return &FSecondarySkill; }
	FUsage* SetSecondarySkill(FUsage FNewSecondarySkill) { FSecondarySkill = FNewSecondarySkill; return &FSecondarySkill; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UTexture2D* InventoryIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EItemType ItemType;

	float currentUsageProgression; //0.0f - 100.0f
	float GetUsageProgression() { return currentUsageProgression; };
	float NextUsageHitTime;

	bool isCurrentlyUsed;
	bool isPrimaryUsed;

	bool isOwned;

	UPROPERTY(ReplicatedUsing = OnRep_Flag)
		FTransform LastKnownTransform;
	UFUNCTION()
		void OnRep_Flag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FTransform MeshRelativeTransform;

	bool checkPrimary() { return true; };
	bool checkSecondary() { return true; };

	// Sets default values for this actor's properties
	ABaseItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	virtual void CustomTick();

	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	EObjectState ObjectState;
	EObjectState GetObjectState() { return ObjectState; }

	void execSetState(EObjectState state, FVector Location = FVector(0,0,0));
	UFUNCTION(Client, Reliable, WithValidation)
		void SetState(EObjectState state, FVector Location = FVector(0, 0, 0));
	virtual bool SetState_Validate(EObjectState state, FVector Location = FVector(0, 0, 0));
	virtual void SetState_Implementation(EObjectState state, FVector Location = FVector(0, 0, 0));

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SetState(EObjectState state, FVector Location = FVector(0, 0, 0));
	virtual bool Server_SetState_Validate(EObjectState state, FVector Location = FVector(0, 0, 0));
	virtual void Server_SetState_Implementation(EObjectState state, FVector Location = FVector(0, 0, 0));
	//------------------------------------------------------------------------
	//Sounds
	void execPlaySound(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	UFUNCTION(Client, Reliable, WithValidation, BlueprintCallable, Category = Stats)
		void PlaySound(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	virtual bool PlaySound_Validate(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	virtual void PlaySound_Implementation(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_PlaySound(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	virtual bool Server_PlaySound_Validate(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	virtual void Server_PlaySound_Implementation(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	UFUNCTION(NetMulticast, Reliable, WithValidation) /* Do we need this? */
		void Multi_PlaySound(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	virtual bool Multi_PlaySound_Validate(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	virtual void Multi_PlaySound_Implementation(USoundBase* Sound, UAudioComponent* Audio_Component, bool ifAvailable);
	//------------------------------------------------------------------------

	virtual void execPrimary();
	virtual void execSecondary();
	void Primary();
	void StopPrimary();
	void Secondary();
	void StopSecondary();
	void HandleUsage();
	virtual void ActivateObject();
	virtual void DisableObject();
	virtual void UseObject();

	void HandlePhysicPositionCheck();


	/** Returns Mesh subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh() const { return Mesh; }
};