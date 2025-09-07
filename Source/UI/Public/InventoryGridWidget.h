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

	TArray<FLine> Lines;

private:
	void CreateLineSegments(int32 Rows, int32 Columns, float TileSize);

protected:
	// Native function overrides
	virtual void NativeConstruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
		const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
};
