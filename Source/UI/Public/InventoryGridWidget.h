// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

class UBackgroundBlur;
class UBorder;
class UCanvasPanel;
class UInventoryComponent;

/**
 * 
 */
UCLASS()
class UI_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|InventoryGrid")
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|InventoryGrid")
	TObjectPtr<UBorder> GridBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|InventoryGrid")
	TObjectPtr<UCanvasPanel> GridCanvasPanel;

protected:
	UPROPERTY(BlueprintReadOnly, Category="UI|InventoryGrid")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(BlueprintReadOnly, Category="UI|InventoryGrid")
	float TileSize;

public:
	UFUNCTION(BlueprintCallable, Category="UI|InventoryGrid")
	void InitializeGrid(UInventoryComponent* InventoryComponentRef, const float CustomTileSize);
};
