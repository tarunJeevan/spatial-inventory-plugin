// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UBorder;
class UCanvasPanel;
class UImage;
class UItemObject;
class USizeBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoved, UItemObject*, ItemObject);

/**
 * 
 */
UCLASS()
class UI_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

	// Properties
	FVector2D Size;
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI")
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI")
	TObjectPtr<USizeBox> BackgroundSizeBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI")
	TObjectPtr<UBorder> BackgroundBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI")
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="ItemWidget|Private")
	float TileSize;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="ItemWidget|Private")
	TObjectPtr<UItemObject> ItemObject;

	// Delegate called when item is removed
	UPROPERTY(BlueprintAssignable, Category="ItemWidget|Delegates")
	FOnRemoved OnRemoved;

	// Refresh item widget
	UFUNCTION()
	void Refresh();
};
