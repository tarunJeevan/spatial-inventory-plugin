// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryDataStructs.generated.h"

USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	FLine() {};
	FLine(const FVector2D Start, const FVector2D End): Start(Start), End(End) {};

	FVector2D Start;
	FVector2D End;
};

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	FTile() {};

	int32 X;
	int32 Y;
};

class SPATIALINVENTORY_API InventoryDataStructs
{
public:
	// 
};
