// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

UCLASS()
class SPATIALINVENTORY_API UItemObject : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	FIntPoint Dimensions;

public:
	FIntPoint GetDimensions() const { return Dimensions; }
};
