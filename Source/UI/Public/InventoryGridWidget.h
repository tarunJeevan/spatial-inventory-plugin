// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryDataStructs.h"
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

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|GridWidgets")
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|GridWidgets")
	TObjectPtr<UBorder> GridBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="UI|GridWidgets")
	TObjectPtr<UCanvasPanel> GridCanvasPanel;

	UPROPERTY(BlueprintReadOnly, Category="UI|InventoryGrid")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	// Local variables
	int32 Rows;
	int32 Columns;
	float TileSize;

	TArray<float> StartX;
	TArray<float> EndX;
	TArray<float> StartY;
	TArray<float> EndY;

	FLines* LinesData = nullptr; // TODO: Try changing FLines to simple (X,Y) and create array of Flines

private:
	void CreateLineSegments();

protected:
	// Native function overrides
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
		const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

};
