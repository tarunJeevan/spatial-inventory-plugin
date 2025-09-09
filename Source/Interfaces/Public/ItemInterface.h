// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERFACES_API IItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Return item data to the inventory component
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Inventory")
	FItemData GetItemData();
};
