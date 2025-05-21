// Copyright Moonlit Night Studios Ltd. All rights Reserved.

#include "InteractionComponent.h"
#include "Net/UnrealNetwork.h"

FInteractionEvent UInteractionComponent::OnInteractionBegin;
FInteractionEvent UInteractionComponent::OnInteractionEnd;

const TArray<AActor*>& UInteractionComponent::GetInteractables() const
{
	return Interactables;
}

void UInteractionComponent::SetFocussedInteractable(AActor* Interactable)
{
	if (Interactables.Contains(Interactable))
	{
		FocussedInteractable = Interactable;
	}
}

void UInteractionComponent::BeginInteraction()
{
	if (FocussedInteractable)
	{
		Server_BeginInteraction(FocussedInteractable);
	}
}

void UInteractionComponent::EndInteraction()
{
	if (FocussedInteractable)
	{
		Server_EndInteraction(FocussedInteractable);
	}
}

FInteractionEvent& UInteractionComponent::GetOnInteractionBeginDelegate()
{
	return OnInteractionBegin;
}

FInteractionEvent& UInteractionComponent::GetOnInteractionEndDelegate()
{
	return OnInteractionEnd;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnEndOverlap);

	//Setup initial interaction list
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->Implements<UInteractable>())
		{
			Interactables.Add(Actor);
		}
	}
	if (Interactables.Num() > 0)
	{
		OnInteractablesListChanged.Broadcast(Interactables);
	}
}

void UInteractionComponent::Server_BeginInteraction_Implementation(AActor* Interactable)
{
	if (Interactables.Contains(Interactable))
	{
		BroadcastBeginInteraction(Interactable);
	}
}

void UInteractionComponent::Server_EndInteraction_Implementation(AActor* Interactable)
{
	if (Interactables.Contains(Interactable))
	{
		BroadcastEndInteraction(Interactable);
	}
}

void UInteractionComponent::BroadcastBeginInteraction_Implementation(AActor* Interactable)
{
	IInteractable::Execute_OnBeginInteraction(Interactable, GetOwner());
	OnInteractionBegin.Broadcast(GetOwner(), Interactable);
}

void UInteractionComponent::BroadcastEndInteraction_Implementation(AActor* Interactable)
{
	IInteractable::Execute_OnEndInteraction(Interactable, GetOwner());
	OnInteractionEnd.Broadcast(GetOwner(), Interactable);
}

void UInteractionComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UInteractable>())
	{
		Interactables.Add(OtherActor);
		OnInteractablesListChanged.Broadcast(Interactables);
	}
}

void UInteractionComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UInteractable>())
	{
		if (FocussedInteractable == OtherActor)
		{
			FocussedInteractable = nullptr;
		}
		Interactables.RemoveSwap(OtherActor);
		OnInteractablesListChanged.Broadcast(Interactables);
	}
}
