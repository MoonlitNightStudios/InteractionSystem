// Copyright Moonlit Night Studios Ltd. All rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractableInterface.h"
#include "InteractionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractablesListChangedSignature, const TArray<AActor*>&, Interactables);
DECLARE_MULTICAST_DELEGATE_TwoParams(FInteractionEvent, AActor*, AActor*);


UCLASS(ClassGroup = "Interaction", meta = (DisplayName = "Interaction Component", BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractionComponent : public USphereComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TArray<AActor*>& GetInteractables() const;

	UFUNCTION(BlueprintCallable)
	void SetFocussedInteractable(AActor* Interactable);

	UFUNCTION(BlueprintCallable)
	void BeginInteraction();

	UFUNCTION(BlueprintCallable)
	void EndInteraction();

	static FInteractionEvent& GetOnInteractionBeginDelegate();
	static FInteractionEvent& GetOnInteractionEndDelegate();

	UPROPERTY(BlueprintAssignable)
	FOnInteractablesListChangedSignature OnInteractablesListChanged;

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void Server_BeginInteraction(AActor* Interactable);

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void Server_EndInteraction(AActor* Interactable);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void BroadcastBeginInteraction(AActor* Interactable);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void BroadcastEndInteraction(AActor* Interactable);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	static FInteractionEvent OnInteractionBegin;
	static FInteractionEvent OnInteractionEnd;

	TArray<AActor*> Interactables;
	AActor* FocussedInteractable = nullptr;
};
