// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventoryUtils.generated.h"

class UItemObject;

UCLASS()
class SPATIALINVENTORY_API UInventoryUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * @brief Spawn an ItemActor when the corresponding ItemObject is removed from the inventory
	 * 
	 * @param ItemObject ItemObject containing the data of the ItemActor to spawn
	 * @param Actor Actor to spawn the ItemActor from
	 * @param bGroundClamp Flag to determine whether spawned ItemActor should be ground-clamped
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	static void SpawnItemFromActor(UItemObject* ItemObject, AActor* Actor, bool bGroundClamp);
};
