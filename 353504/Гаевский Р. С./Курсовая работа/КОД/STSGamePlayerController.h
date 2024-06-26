#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ResourceInterface.h"
#include "DamagableInterface.h"
#include "CharacterDetailsUI.h"
#include "InventoryUI.h"
#include "ContextUnitUI.h"
#include "RTSGamePlayerController.generated.h"

class UDecalComponent;
class UBoxComponent;
class ARTSGameCharacter;
class ARTSOverseerer;
class ITeamInterface;
class UUnitButtons;

//typedef void (*TestFunc) (void);

UCLASS()
class ARTSGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSGamePlayerController();
	virtual void OnPossess(APawn* InPawn) override;

protected:
	typedef void (ARTSGamePlayerController::*FunctionPtrType)(void);
	FunctionPtrType FunctionsToRun[10];
	uint32 leftMouseDown : 1;

	float MoveSpeed;
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	void CalculateMovement(float DeltaSeconds);

	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnResetVR();
	void MoveToMouseCursor();
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	void SetNewMoveDestination(const FVector DestLocation);

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void AttackTarget(IDamagableInterface* target);
	void GatherResources(IResourceInterface* res);
	void RightClick();
	void MoveUnits(FVector loc);
	void SelectUnits();
	void ClearDelegates();

	void GenerateUI();
	IResourceInterface* GetResource(AActor* other);
	ITeamInterface* GetTeam(AActor* other);
	IDamagableInterface* GetDamagable(AActor* other);

	void ZoomIn();
	ARTSOverseerer* GetOversereer();
	void ZoomOut();
private:
	TArray<AActor*> selectedUnits;
	TMap<EResourceType, UMaterial*> materialCursors;
	UDecalComponent* CursorToWorld;

	int32 maxZoom;
	int32 minZoom;

	float zoomRate;
	float mouseDownTime;
	float dist;

	UBoxComponent* selectionArea;
	ARTSOverseerer* overseerer;

	FVector mouseStart;
	FVector mouseEnd;
	FVector centerMouseLocation;
	FVector selectionSize;

	FHitResult hit;

	TSubclassOf<UUserWidget> characterUItemplate;
	UCharacterDetailsUI* characterUI;

	TSubclassOf<UUserWidget> inventoryTemplate;
	UInventoryUI* inventoryUI;

	TSubclassOf<UUserWidget> contextTemplate;
	UContextUnitUI* contextUnitUI;

};