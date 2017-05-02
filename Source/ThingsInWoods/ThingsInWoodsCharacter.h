// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Engine.h"
#include "BaseItem.h"
#include "ThingsInWoodsSpectator.h"
#include "ThingsInWoodsCharacter.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseItem*> Item;

	FInventoryItem()
	{

	}
};

USTRUCT(BlueprintType)
struct FGroundSounds
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class USoundBase* Jump_Start;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class USoundBase* Jump_Landing;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class USoundBase* Step;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class USoundBase* Step_Run;

	FGroundSounds()
	{

	}
};

USTRUCT(BlueprintType)
struct FGroundSoundsMaterials
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGroundSounds FDefault;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGroundSounds FGrass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGroundSounds FDirt;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGroundSounds FMetal;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGroundSounds FWater;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGroundSounds FWood;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGroundSounds FStone;

	FGroundSounds* GetDefault() { return &FDefault; }
	FGroundSounds* GetGrass() { return &FGrass; }
	FGroundSounds* GetDirt() { return &FDirt; }
	FGroundSounds* GetMetal() { return &FMetal; }
	FGroundSounds* GetWater() { return &FWater; }
	FGroundSounds* GetWood() { return &FWood; }
	FGroundSounds* GetStone() { return &FStone; }

	FGroundSoundsMaterials()
	{

	}
};

UCLASS(config=Game)
class AThingsInWoodsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	/** 1st person view mesh (arms; seen only by self) */
	UPROPERTY(EditAnywhere, Category=Mesh)
		class USkeletalMeshComponent* Mesh1P;

	/** Item scene: 1st person view (seen only by self) */
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* FP_Gun;

	/** Item scene: 3rd person view (seen only by others) */
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* TP_Gun;

	/* AUDIO COMPONENTS */
	UPROPERTY(EditAnywhere, Category = Sound)
		class UAudioComponent* VoiceAudioComponent;
	UPROPERTY(EditAnywhere, Category = Sound)
		class UAudioComponent* FootAudioComponent;
	UPROPERTY(EditAnywhere, Category = Sound)
		class UAudioComponent* VarAudioComponent;

	/* Third person inventory slots */
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* TP_Mesh_Inv1;
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* TP_Mesh_Inv2;
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* TP_Mesh_Inv3;
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* TP_Mesh_Inv4;
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* TP_Mesh_Inv5;

public:
	AThingsInWoodsCharacter();

	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	//------------------------------------------------------------------------
	//Sounds
	USoundBase* GetSound_Jump(EPhysicalSurface PhysSurface);
	USoundBase* GetSound_Landed(EPhysicalSurface PhysSurface);
	USoundBase* GetSound_Step(EPhysicalSurface PhysSurface);
	USoundBase* GetSound_Step_Run(EPhysicalSurface PhysSurface);
	FHitResult GetGroundHit();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sounds)
		class USoundBase* Pain;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sounds)
		class USoundBase* Death;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sounds)
		class USoundBase* Slender_Scare;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sounds)
		FGroundSoundsMaterials FSounds_Ground;

	bool Slender_Scare_Playing;
	void Slender_Sound_Stop();
	void PlaySound_Steps();

	/* ---------
	* Stats
	*/
	protected:
		/* Stamina */
		UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = Stats)
			int iStamina;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			int iStaminaMax;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fStaminaHitTime;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fStaminaGainTime;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fStaminaGainFactor;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fStaminaReducementFactor;
		float fNextStaminaHitTime;

		/* Health */
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
			float fHealth;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fHealthMax;
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
			bool bIsAlive;

		/* Movement */
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
			bool bIsRunning;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fMinimumStaminaToRun;

		/* Walkspeed */
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fMaxWalkSpeed;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fMaxWalkSpeedRunning;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fMaxWalkSpeedInjured;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fMaxWalkSpeedRunningInjured;

		/* Item Usage */
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Actions)
			bool bIsUsingItem;
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Actions)
			bool bIsUsingPrimary;
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Actions)
			bool bIsUsingOverTime;
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Actions)
			float fUsingPercentage;
		AThingsInWoodsCharacter* AActionTarget;

		/* Blackout */
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
			bool bIsBlackout;
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
			float fBlackoutPercentage;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fBlackoutFactor;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
			float fBlackoutHitTimeInSeconds;
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
			float fBlackoutNextHitTime;

		/* Game Mode Slenderman */
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			float fScareFactorReduce;
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
			float fScare_Current;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			float fScare_Max;
		float fNextScarePostProcessUpdateTime;

		/* Inventory */
		UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
			int iInventorySelectedObject;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			EAnimationType ECurrentAnimationType;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			float fPickupDistance;

	public:

	/* Stamina */
		int GetStamina() { return iStamina; }
		int SetStamina( int iNewStamina) { iStamina = iNewStamina; return iStamina; }
		int GetMaxStamina() { return iStaminaMax; }
		int SetMaxStamina( int iNewMaxStamina) { iStaminaMax = iNewMaxStamina; return iStaminaMax; }
		float GetNextStaminaHitTime() { return fNextStaminaHitTime; }
		float SetNextStaminaHitTime( float fNewNextStaminaHitTime ) { fNextStaminaHitTime = fNewNextStaminaHitTime; return fNextStaminaHitTime; }
		float GetStaminaHitTime() { return fStaminaHitTime; }
		float SetStaminaHitTime( float fNewStaminaHitTime ) { fStaminaHitTime = fNewStaminaHitTime; return fStaminaHitTime; }
		float GetStaminaGainTime() { return fStaminaGainTime; }
		float SetStaminaGainTime( float fNewStaminaGainTime ) { fStaminaGainTime = fNewStaminaGainTime; return fStaminaGainTime; }
		float GetStaminaGainFactor() { return fStaminaGainFactor; }
		float SetStaminaGainFactor( float fNewStaminaGainFactor ) { fStaminaGainFactor = fNewStaminaGainFactor; return fStaminaGainFactor; }
		float GetStaminaReducementFactor() { return fStaminaReducementFactor; }
		float SetStaminaReducementFactor( float fNewStaminaReducementFactor ) { fStaminaReducementFactor = fNewStaminaReducementFactor; return fStaminaReducementFactor; }

	/* Health */
		float GetHealth() { return fHealth; }
		float SetHealth(float fNewHealth) { fHealth = fNewHealth; return fHealth; }
		float GetMaxHealth() { return fHealthMax; }
		float SetMaxHealth(float fNewMaxHealth ) { fHealthMax = fNewMaxHealth; return fHealthMax; }
		bool GetIsAlive() { return bIsAlive; }
		bool SetIsAlive(bool bNewIsAlive) { bIsAlive = bNewIsAlive; return bIsAlive; }

	/* Movement */
		bool GetIsRunning() { return bIsRunning; }
		bool SetIsRunning(bool bNewIsRunning) { bIsRunning = bNewIsRunning; return bIsRunning; }
		float GetMinimumStaminaToRun() { return fMinimumStaminaToRun; }
		float SetMinimumStaminaToRun(float fNewMinimumStaminaToRun) { fMinimumStaminaToRun = fNewMinimumStaminaToRun; return fMinimumStaminaToRun; }
	
	/* Walkspeed */
		float GetMaxWalkSpeed() { return fMaxWalkSpeed; }
		float SetMaxWalkSpeed(float fNewMaxWalkSpeed) { fMaxWalkSpeed = fNewMaxWalkSpeed; return fMaxWalkSpeed; }
		float GetMaxWalkSpeedRunning() { return fMaxWalkSpeedRunning; }
		float SetMaxWalkSpeedRunning(float fNewMaxWalkSpeedRunning) { fMaxWalkSpeedRunning = fNewMaxWalkSpeedRunning; return fMaxWalkSpeedRunning; }
		float GetMaxWalkSpeedInjured() { return fMaxWalkSpeedInjured; }
		float SetMaxWalkSpeedInjured(float fNewMaxWalkSpeedInjured) { fMaxWalkSpeedInjured = fNewMaxWalkSpeedInjured; return fMaxWalkSpeed; }
		float GetMaxWalkSpeedRunningInjured() { return fMaxWalkSpeedRunningInjured; }
		float SetMaxWalkSpeedRunningInjured(float fNewMaxWalkSpeedRunningInjured) { fMaxWalkSpeedRunningInjured = fNewMaxWalkSpeedRunningInjured; return fMaxWalkSpeedRunningInjured; }

	/* Item Usage */
		bool GetIsUsingItem() { return bIsUsingItem; }
		bool SetIsUsingItem(bool bNewIsUsingItem) { bIsUsingItem = bNewIsUsingItem; return bIsUsingItem; }
		bool GetIsUsingPrimary() { return bIsUsingPrimary; }
		bool SetIsUsingPrimary(bool bNewIsUsingPrimary) { bIsUsingPrimary = bNewIsUsingPrimary; return bIsUsingPrimary; }
		bool GetIsUsingOverTime() { return bIsUsingOverTime; }
		bool SetIsUsingOverTime(bool bNewIsUsingOverTime) { bIsUsingOverTime = bNewIsUsingOverTime; return bIsUsingOverTime; }
		float GetUsingPercentage() { return fUsingPercentage; }
		float SetUsingPercentage(float fNewUsingPercentage) { fUsingPercentage = fNewUsingPercentage; return fUsingPercentage; }
		AThingsInWoodsCharacter* GetActionTarget() { return AActionTarget; }
		AThingsInWoodsCharacter* SetActionTarget(AThingsInWoodsCharacter* ANewActionTarget) { AActionTarget = ANewActionTarget; return AActionTarget; }

	/* Blackout */
		bool GetIsBlackout() { return bIsBlackout; }
		bool SetIsBlackout(bool bNewIsBlackout) { bIsBlackout = bNewIsBlackout; return bIsBlackout; }
		float GetBlackoutPercentage() { return fBlackoutPercentage; }
		float SetBlackoutPercentage(float fNewBlackoutPercentage) { fBlackoutPercentage = fNewBlackoutPercentage; return fBlackoutPercentage; }
		float GetBlackoutFactor() { return fBlackoutFactor; }
		float SetBlackoutFactor(float fNewBlackoutFactor) { fBlackoutFactor = fNewBlackoutFactor; return fBlackoutFactor; }
		float GetBlackoutHitTimeInSeconds() { return fBlackoutHitTimeInSeconds; }
		float SetBlackoutHitTimeInSeconds(float fNewBlackoutHitTimeInSeconds) { fBlackoutHitTimeInSeconds = fNewBlackoutHitTimeInSeconds; return fBlackoutHitTimeInSeconds; }
		float GetBlackoutNextHitTime() { return fBlackoutNextHitTime; }
		float SetBlackoutNextHitTime(float fNewBlackoutNextHitTime) { fBlackoutNextHitTime = fNewBlackoutNextHitTime; return fBlackoutNextHitTime; }

	/* Game Mode Slenderman */
		float GetScareFactorReduce() { return fScareFactorReduce; }
		float SetScareFactorReduce(float fNewScareFactorReduce) { fScareFactorReduce = fNewScareFactorReduce; return fScareFactorReduce; }
		float GetScare() { return fScare_Current; }
		float SetScare(float fNewScare) { fScare_Current = fNewScare; return fScare_Current; }
		float GetMaxScare() { return fScare_Max; }
		float SetMaxScare(float fNewMaxScare) { fScare_Max = fNewMaxScare; return fScare_Max; }
		float GetNextScarePostProcessUpdateTime() { return fNextScarePostProcessUpdateTime; }
		float SetNextScarePostProcessUpdateTime(float fNewNextScarePostProcessUpdateTime) { fNextScarePostProcessUpdateTime = fNewNextScarePostProcessUpdateTime; return fNextScarePostProcessUpdateTime; }

	/* inventory */
		int GetInventorySelectedObject() { return iInventorySelectedObject; }
		int SetInventorySelectedObject(int iNewInventorySelectedObject) { iInventorySelectedObject = iNewInventorySelectedObject; return iInventorySelectedObject; }
		EAnimationType GetCurrentAnimationType() { return ECurrentAnimationType; }
		EAnimationType SetCurrentAnimationType(EAnimationType ENewAnimationType) { ECurrentAnimationType = ENewAnimationType; return ECurrentAnimationType; }
		float GetPickupDistance() { return fPickupDistance; }
		float SetPickupDistance(float fNewPickupDistance) { fPickupDistance = fNewPickupDistance; return fPickupDistance; }

	/* Audio */
		FGroundSoundsMaterials* GetGroundSounds() { return &FSounds_Ground; }
		FGroundSounds* AThingsInWoodsCharacter::GetGroundSoundStack(EPhysicalSurface PhysSurface);

	//------------------------------------------------------------------------
	// Movement
	//------------------------------------------------------------------------
	//RunToggle(...)
	void execRunToggle(bool bNewIsRunning);
	UFUNCTION(Client, Reliable, WithValidation)
		void RunToggle(bool bNewIsRunning);
	virtual bool RunToggle_Validate(bool bNewIsRunning);
	virtual void RunToggle_Implementation(bool bNewIsRunning);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_RunToggle(bool bNewIsRunning);
	virtual bool Server_RunToggle_Validate(bool bNewIsRunning);
	virtual void Server_RunToggle_Implementation(bool bNewIsRunning);
	//-------
	void StaminaHandle();
	void SetMaximumWalkSpeed(float fNewMaximumWalkSpeed);
	bool CanMove();
	
	//------------------------------------------------------------------------
	// Stats
	//------------------------------------------------------------------------
	bool GetIsInjured();
	void Heal(unsigned int iHealAmount);
	//Server_DeathHandle()
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_DeathHandle();
	virtual bool Server_DeathHandle_Validate();
	virtual void Server_DeathHandle_Implementation();

	//------------------------------------------------------------------------
	// Audio
	//------------------------------------------------------------------------
	//PlaySound(...)
	void execPlaySound(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	UFUNCTION(Client, Reliable, WithValidation, BlueprintCallable, Category = Stats)
		void PlaySound(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	virtual bool PlaySound_Validate(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	virtual void PlaySound_Implementation(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_PlaySound(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	virtual bool Server_PlaySound_Validate(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	virtual void Server_PlaySound_Implementation(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	UFUNCTION(NetMulticast, Reliable, WithValidation) /* Do we need this? */
		void Multi_PlaySound(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	virtual bool Multi_PlaySound_Validate(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	virtual void Multi_PlaySound_Implementation(USoundBase* Sound, UAudioComponent* AudioComponent, bool ifAvailable);
	
	//------------------------------------------------------------------------
	// Unrelated Stuff
	//------------------------------------------------------------------------
	//SayHello(...)
	void execSayHallo(AThingsInWoodsCharacter* PlayerCharacter);
	UFUNCTION(Client, Reliable, WithValidation)
		void SayHallo();
	virtual bool SayHallo_Validate();
	virtual void SayHallo_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SayHallo();
	virtual bool Server_SayHallo_Validate();
	virtual void Server_SayHallo_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_SayHallo(AThingsInWoodsCharacter* PlayerCharacter);
	virtual bool Multi_SayHallo_Validate(AThingsInWoodsCharacter* PlayerCharacter);
	virtual void Multi_SayHallo_Implementation(AThingsInWoodsCharacter* PlayerCharacter);

	//--------- RESORT -----------------
	//----- BlackoutHandle
	void execBlackoutHandle();
	UFUNCTION(Client, Reliable, WithValidation, BlueprintCallable, Category = Stats)
		void BlackoutHandle();
	virtual bool BlackoutHandle_Validate();
	virtual void BlackoutHandle_Implementation();
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_BlackoutHandle();
	virtual bool Server_BlackoutHandle_Validate();
	virtual void Server_BlackoutHandle_Implementation();
	
	//----- EnableBlackout mode
	void execEnableBlackout();
	UFUNCTION(Client, Reliable, WithValidation, BlueprintCallable, Category = Stats)
		void EnableBlackout();
	virtual bool EnableBlackout_Validate();
	virtual void EnableBlackout_Implementation();
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_EnableBlackout();
	virtual bool Server_EnableBlackout_Validate();
	virtual void Server_EnableBlackout_Implementation();
	UFUNCTION(NetMulticast, Reliable, WithValidation) /* Do we need this? */
		void Multi_EnableBlackout();
	virtual bool Multi_EnableBlackout_Validate();
	virtual void Multi_EnableBlackout_Implementation();
	
	//----- ApplyDamage
	void execApplyDamage(float fDamageAmount);
	UFUNCTION(Client, Reliable, WithValidation, BlueprintCallable, Category = Stats)
		void ApplyDamage(float fDamageAmount);
	virtual bool ApplyDamage_Validate(float fDamageAmount);
	virtual void ApplyDamage_Implementation(float fDamageAmount);
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_ApplyDamage(float fDamageAmount);
	virtual bool Server_ApplyDamage_Validate(float fDamageAmount);
	virtual void Server_ApplyDamage_Implementation(float fDamageAmount);
	
	//----- PickupObject
	void execPickupObject(ABaseItem* PickUpObject);
	UFUNCTION(Client, Reliable, WithValidation)
		void PickupObject(ABaseItem* PickUpObject);
	virtual bool PickupObject_Validate(ABaseItem* PickUpObject);
	virtual void PickupObject_Implementation(ABaseItem* PickUpObject);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_PickupObject(ABaseItem* PickUpObject);
	virtual bool Server_PickupObject_Validate(ABaseItem* PickUpObject);
	virtual void Server_PickupObject_Implementation(ABaseItem* PickUpObject);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_PickupObject(ABaseItem* PickUpObject);
	virtual bool Multi_PickupObject_Validate(ABaseItem* PickUpObject);
	virtual void Multi_PickupObject_Implementation(ABaseItem* PickUpObject);
	
	//------ InventoryDrop
	void execInventoryDrop();
	UFUNCTION(Client, Reliable, WithValidation)
		void InventoryDrop();
	virtual bool InventoryDrop_Validate();
	virtual void InventoryDrop_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_InventoryDrop();
	virtual bool Server_InventoryDrop_Validate();
	virtual void Server_InventoryDrop_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_InventoryDrop();
	virtual bool Multi_InventoryDrop_Validate();
	virtual void Multi_InventoryDrop_Implementation();
	
	//------- InventorySelect
	void execInventorySelect(int iInventoryIndex);
	UFUNCTION(Client, Reliable, WithValidation)
		void InventorySelect(int iInventoryIndex);
	virtual bool InventorySelect_Validate(int iInventoryIndex);
	virtual void InventorySelect_Implementation(int iInventoryIndex);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_InventorySelect(int iInventoryIndex);
	virtual bool Server_InventorySelect_Validate(int iInventoryIndex);
	virtual void Server_InventorySelect_Implementation(int iInventoryIndex);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_InventorySelect(int iInventoryIndex);
	virtual bool Multi_InventorySelect_Validate(int iInventoryIndex);
	virtual void Multi_InventorySelect_Implementation(int iInventoryIndex);

	//--------- InventoryDeselect
	void execInventoryDeselect();
	UFUNCTION(Client, Reliable, WithValidation)
		void InventoryDeselect();
	virtual bool InventoryDeselect_Validate();
	virtual void InventoryDeselect_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_InventoryDeselect();
	virtual bool Server_InventoryDeselect_Validate();
	virtual void Server_InventoryDeselect_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_InventoryDeselect();
	virtual bool Multi_InventoryDeselect_Validate();
	virtual void Multi_InventoryDeselect_Implementation();

	//---------- Primary
	void execPrimary();
	UFUNCTION(Client, Reliable, WithValidation)
		void Primary();
	virtual bool Primary_Validate();
	virtual void Primary_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Primary();
	virtual bool Server_Primary_Validate();
	virtual void Server_Primary_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_Primary();
	virtual bool Multi_Primary_Validate();
	virtual void Multi_Primary_Implementation();

	//----------- StopPrimary
	void execStopPrimary();
	UFUNCTION(Client, Reliable, WithValidation)
		void StopPrimary();
	virtual bool StopPrimary_Validate();
	virtual void StopPrimary_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_StopPrimary();
	virtual bool Server_StopPrimary_Validate();
	virtual void Server_StopPrimary_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_StopPrimary();
	virtual bool Multi_StopPrimary_Validate();
	virtual void Multi_StopPrimary_Implementation();

	//----------- Secondary
	void execSecondary();
	UFUNCTION(Client, Reliable, WithValidation)
		void Secondary();
	virtual bool Secondary_Validate();
	virtual void Secondary_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Secondary();
	virtual bool Server_Secondary_Validate();
	virtual void Server_Secondary_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_Secondary();
	virtual bool Multi_Secondary_Validate();
	virtual void Multi_Secondary_Implementation();

	//----------- StopSecondary
	void execStopSecondary();
	UFUNCTION(Client, Reliable, WithValidation)
		void StopSecondary();
	virtual bool StopSecondary_Validate();
	virtual void StopSecondary_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_StopSecondary();
	virtual bool Server_StopSecondary_Validate();
	virtual void Server_StopSecondary_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_StopSecondary();
	virtual bool Multi_StopSecondary_Validate();
	virtual void Multi_StopSecondary_Implementation();

	//----------- ItemUsageHandle
	void execItemUsageHandle();
	UFUNCTION(Client, Reliable, WithValidation)
		void ItemUsageHandle();
	virtual bool ItemUsageHandle_Validate();
	virtual void ItemUsageHandle_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_ItemUsageHandle();
	virtual bool Server_ItemUsageHandle_Validate();
	virtual void Server_ItemUsageHandle_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_ItemUsageHandle();
	virtual bool Multi_ItemUsageHandle_Validate();
	virtual void Multi_ItemUsageHandle_Implementation();
	//----------------------- REDONE END ----------------------
	//----------------------- REDONE END ----------------------
	//----------------------- REDONE END ----------------------
	//----------------------- REDONE END ----------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* HUDIcon;
	void AddItemToInventory(int iInventorySlot, ABaseItem* Object);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	TArray<FInventoryItem> Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		bool NightVisionEnabled;

	void ToggleNightVision();
	bool HasNightVisionInInventory();
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	void UseUsageObject(ABaseItem* object);
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	//------------- Item Usage
	//---
	//------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AThingsInWoodsCharacter*> ActivePlayers;
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	FHitResult TraceLine(FVector Start, FVector End, bool Debug);
	void PlantObject();
	//------------------------------------------------------------------------
	//SLENDERMAN GAME MODE
	//-----------------------

	void HandleScare(float DeltaTime);
	void ReceiveSlenderScare(float Amount);
	//------------------------------------------------------------------------
	//Movement
	//---
	void HandleMovement(FVector WorldDirection, float ScaleValue);
	void HandleTurnRotation(float fRate);
	void HandleUpRotation(float fRate);
	void HandleJump();
	void HandleStopJump();
	void HandleUseInput();
	virtual void Landed(const FHitResult & Hit) override;

protected:
	
public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};
