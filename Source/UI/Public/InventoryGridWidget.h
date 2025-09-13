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

/**
 * 
 */
UCLASS()
class UI_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|GridWidgets")
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|GridWidgets")
	TObjectPtr<UBorder> GridBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|GridWidgets")
	TObjectPtr<UCanvasPanel> GridCanvasPanel;

	UPROPERTY(BlueprintReadOnly, Category="UI|InventoryGrid")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	TArray<FLine> Lines;
	int32 Rows;
	int32 Columns;
	float TileSize;

	FIntPoint DraggedItemTopLeftTile;
	bool bDrawDropLocation;

private:
	void CreateLineSegments();
	UItemObject* GetPayload(const UDragDropOperation* DragDropOperation) const;
	bool IsRoomAvailableForPayload(const UItemObject* Payload) const;
	TTuple<bool, bool> MousePositionInTile(const FVector2D MousePosition) const;

	UFUNCTION()
	void OnItemRemoved(UItemObject* ItemObject);

	UFUNCTION()
	void Refresh();

	UFUNCTION()
	FEventReply CustomOnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

protected:
	// Native function overrides
	virtual void NativeOnInitialized() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
		const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                              UDragDropOperation* InOperation) override;
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
