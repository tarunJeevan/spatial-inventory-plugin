// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventoryUtils.generated.h"

class UItemObject;

/**
 * 
 */
UCLASS()
class SPATIALINVENTORY_API UInventoryUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	static void SpawnItemFromActor(UItemObject* ItemObject, AActor* Actor, bool bGroundClamp);
};
