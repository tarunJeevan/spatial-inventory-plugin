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
	/** Width and height of the item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	FIntPoint Dimensions;

	/** Icon to be drawn on the item widget */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	TObjectPtr<UMaterialInterface> Icon = nullptr;

	/** Rotated icon to be drawn on the item widget */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	TObjectPtr<UMaterialInterface> IconRotated = nullptr;

	/** Class of the owning ItemActor */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	TSubclassOf<AItemActor> ItemClass = nullptr;

	/** Flag to indicate whether the item widget should be rotated or not */
	bool bIsRotated;

public:
	/**
	 * @brief Get the dimensions of the item
	 * 
	 * @return Dimensions of the item based on its rotation
	 */
	FIntPoint GetDimensions() const;

	/**
	 * @brief Get the icon to be displayed on the item widget
	 * 
	 * @return Icon to be drawn on the corresponding item widget
	 */
	TObjectPtr<UMaterialInterface> GetIcon() const { return bIsRotated ? IconRotated : Icon; }

	/**
	 * @brief Get the class of the ItemActor this ItemObject is attached to
	 * 
	 * @return Class of the owning ItemActor
	 */
	TSubclassOf<AItemActor> GetItemClass() const { return ItemClass; }

	/**
	 * @brief Rotate the item, flipping its dimensions
	 */
	void Rotate() { bIsRotated = !bIsRotated; }

	/**
	 * @return True if the item is currently rotated, false otherwise
	 */
	bool IsRotated() const { return bIsRotated; }
};
