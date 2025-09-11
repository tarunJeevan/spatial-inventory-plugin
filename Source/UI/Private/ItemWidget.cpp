// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemWidget.h"
#include "ItemObject.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

void UItemWidget::Refresh()
{
	const FIntPoint Dimensions = ItemObject->GetDimensions();
	Size = FVector2D(Dimensions.X * TileSize, Dimensions.Y * TileSize);

	// Set SizeBox dimensions based on item dimensions
	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);

	// Set Image dimensions based on item dimensions
	UCanvasPanelSlot* ImageAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemImage);
	ImageAsCanvasSlot->SetSize(Size);

	// Set item icon brush
	if (ItemObject && ItemImage)
	{
		const FSlateBrush IconBrush = UWidgetBlueprintLibrary::MakeBrushFromMaterial(ItemObject->GetIcon(), Size.X, Size.Y);
		ItemImage->SetBrush(IconBrush);
	}
}
