// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "ItemObject.h"

void UItemWidget::Init(const float InTileSize, UItemObject* InItemObject)
{
	TileSize = InTileSize;
	ItemObject = InItemObject;
}

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

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	// Set item widget background border color to semi-transparent gray
	BackgroundBorder->SetBrushColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.2f));
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	// Reset item widget background border color to original color
	BackgroundBorder->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.5f));
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// Set widget to detect drag if left mouse button is pressed
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                       UDragDropOperation*& OutOperation)
{
	// Create drag and drop operation
	UDragDropOperation* Operation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());

	if (Operation)
	{
		// Configure drag and drop operation
		Operation->Payload = ItemObject;
		Operation->DefaultDragVisual = this;
		Operation->Pivot = EDragPivot::CenterCenter;
	}

	// Remove item from inventory
	OnRemoved.Broadcast(ItemObject);
	// Remove item widget from parent
	RemoveFromParent();
	
	// Set output operation
	OutOperation = Operation;
}
