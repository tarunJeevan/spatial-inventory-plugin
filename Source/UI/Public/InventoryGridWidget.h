// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryDataStructs.h"
#include "ItemWidget.h"
#include "InventoryGridWidget.generated.h"

class UBackgroundBlur;
class UBorder;
class UCanvasPanel;
class UInventoryComponent;

UCLASS()
class UI_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Item widget background color when drop location is allowed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventoryGridWidget|UI")
	FLinearColor ValidDropBackgroundColor = FLinearColor(0.f, 1.f, 0.f, 0.25f);
	
	/** Item widget background color when drop location is not allowed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventoryGridWidget|UI")
	FLinearColor InvalidDropBackgroundColor = FLinearColor(1.f, 0.f, 0.f, 0.25f);
	
	/**
	 * @brief Get the player's inventory component
	 * 
	 * @return InventoryComponent owned by the owning player pawn
	 */
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|GridWidgets")
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|GridWidgets")
	TObjectPtr<UBorder> GridBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|GridWidgets")
	TObjectPtr<UCanvasPanel> GridCanvasPanel;

	/** Inventory component owned by the owning player pawn */
	UPROPERTY(BlueprintReadOnly, Category="UI|InventoryGrid")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	/** Array of grid lines to be drawn */
	TArray<FLine> Lines;
	int32 Rows;
	int32 Columns;
	float TileSize;
	/** Top left tile of the item being dragged */
	FIntPoint DraggedItemTopLeftTile;
	/** Flag to determine whether to draw the expected drop location of the dragged item */
	bool bDrawDropLocation;

private:
	/**
	 * @brief Compute the coordinates of the inventory grid's vertical and horizontal lines
	 */
	void CreateLineSegments();

	/**
	 * @brief Helper function to get the ItemObject being dragged
	 * @param DragDropOperation DragDropOperation to get the payload from
	 * @return Payload cast as an ItemObject
	 */
	UItemObject* GetPayload(const UDragDropOperation* DragDropOperation) const;

	/**
	 * @brief Check if there is room in the inventory for the ItemObject being dragged
	 * 
	 * @param Payload ItemObject to check room in the inventory for
	 * @return True if there is room in the inventory, false otherwise
	 */
	bool IsRoomAvailableForPayload(const UItemObject* Payload) const;

	/**
	 * @brief Get the relative position of the mouse in a tile to determine where to draw the drop location
	 * 
	 * @param MousePosition The current mouse position within a tile
	 * @return Tuple of booleans indicating whether the mouse is within the top/bottom half and right/left half of the tile
	 */
	TTuple<bool, bool> MousePositionInTile(const FVector2D MousePosition) const;

	/**
	 * @brief Function to bind to an item widget's OnRemoved delegate
	 * 
	 * @param ItemObject ItemObject to remove from inventory
	 */
	UFUNCTION()
	void OnItemRemoved(UItemObject* ItemObject);

	/**
	 * @brief Function to bind to the inventory component's OnInventoryChanged delegate
	 */
	UFUNCTION()
	void Refresh();

	/**
	 * @brief Function to bind to the GridBorder's OnMouseButtonDown event to block mouse events
	 * 
	 * @param MyGeometry Default param from the OnMouseButtonDown event
	 * @param MouseEvent Default param from the OnMouseButtonDown event
	 * @return Reply stating that the event has been handled
	 */
	UFUNCTION()
	FEventReply CustomOnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

protected:
	// Override function to initialize the inventory grid widget (called only once)
	virtual void NativeOnInitialized() override;

	// Override function to draw item widgets and other things
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
		const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	// Override function to handle drag operations in the inventory grid
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	// Override function to handle drag operations in the inventory grid
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// Override function to handle drag operations in the inventory grid
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                              UDragDropOperation* InOperation) override;

	// Override function to handle drop operations in the inventory grid 
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	// Override function to handle item widget rotation in the inventory grid
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
