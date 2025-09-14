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

UCLASS()
class UI_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="ItemWidget|UI")
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="ItemWidget|UI")
	TObjectPtr<USizeBox> BackgroundSizeBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="ItemWidget|UI")
	TObjectPtr<UBorder> BackgroundBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="ItemWidget|UI")
	TObjectPtr<UImage> ItemImage;

	/** Tile size set in the inventory component */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="ItemWidget|Private")
	float TileSize;

	/** ItemObject representing the item that was added to the inventory */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="ItemWidget|Private")
	TObjectPtr<UItemObject> ItemObject;

	/** The size of the item widget based on the item's dimensions */
	FVector2D Size;

public:
	/** Default item widget background color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemWidget|UI")
	FLinearColor DefaultBackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.5f);
	
	/** Item widget background color when mouse is hovering over it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemWidget|UI")
	FLinearColor HoverBackgroundColor = FLinearColor(0.5f, 0.5f, 0.5f, 0.2f);
	
	/** Delegate to be broadcast when the item is dropped */
	UPROPERTY(BlueprintAssignable, Category="ItemWidget|Delegates")
	FOnRemoved OnRemoved;

	/**
	 * @brief Initialize a newly constructed instance with the necessary data
	 * 
	 * @param InTileSize Tile size set in the inventory component
	 * @param InItemObject ItemObject representing the item that was picked up
	 */
	void Init(const float InTileSize, UItemObject* InItemObject);

	/**
	 * @brief Refresh the item widget's UI based on the ItemObject
	 */
	UFUNCTION()
	void Refresh();

protected:
	// Override function to draw a highlight color when mouse is hovering over the item widget
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// Override function to draw normal color when mouse stops hovering over the item widget
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	// Override function to start a drag and drop operation
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// Override function to handle drag and drop operation
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	                                  UDragDropOperation*& OutOperation) override;
};
