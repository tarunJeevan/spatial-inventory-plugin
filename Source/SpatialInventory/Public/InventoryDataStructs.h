// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryDataStructs.generated.h"

/**
 * @brief A struct to hold the start and end coordinates of a line to draw inventory grid lines
 */
USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	FLine() {};
	FLine(const FVector2D InStart, const FVector2D InEnd): Start(InStart), End(InEnd) {};

	FVector2D Start;
	FVector2D End;
};

/**
 * @brief Location of an item in the 2D inventory grid
 */
USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	FTile() {};
	FTile(const int32 InX, const int32 InY): X(InX), Y(InY) {};

	int32 X;
	int32 Y;
};
