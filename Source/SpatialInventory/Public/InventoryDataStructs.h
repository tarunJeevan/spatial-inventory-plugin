// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryDataStructs.generated.h"

USTRUCT(BlueprintType)
struct FLines
{
	GENERATED_BODY()

	FLines() {};

	TArray<FVector2D> XLines;
	TArray<FVector2D> YLines;
};

class SPATIALINVENTORY_API InventoryDataStructs
{
public:
	// 
};
