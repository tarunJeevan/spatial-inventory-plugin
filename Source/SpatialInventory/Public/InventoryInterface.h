// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPATIALINVENTORY_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Return the Inventory Component owned by this actor
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
	class UInventoryComponent* GetInventoryComponent();
};
