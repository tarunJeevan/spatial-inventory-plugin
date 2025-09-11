// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

class AItemActor;

UCLASS(BlueprintType, Blueprintable)
class SPATIALINVENTORY_API UItemObject : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	FIntPoint Dimensions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	TObjectPtr<UMaterialInterface> Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	TObjectPtr<UMaterialInterface> IconRotated = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	TSubclassOf<AItemActor> ItemClass = nullptr;

	bool bIsRotated;

public:
	FIntPoint GetDimensions() const { return Dimensions; }
	TObjectPtr<UMaterialInterface> GetIcon() const { return bIsRotated ? IconRotated : Icon; }
};
