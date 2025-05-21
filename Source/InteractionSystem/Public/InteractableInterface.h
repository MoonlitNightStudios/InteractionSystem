// Copyright Moonlit Night Studios Ltd. All rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


class INTERACTIONSYSTEM_API IInteractable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractionSystem|Interactable")
	void GetDisplayText(FText& OutText);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractionSystem|Interactable")
	void OnBeginInteraction(AActor* InteractedBy);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractionSystem|Interactable")
	void OnEndInteraction(AActor* InteractedBy);

};
