// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryGridWidget.h"
#include "SpatialInventory/Public/InventoryComponent.h"
#include "Components/Border.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Get InventoryComponent from owning player
	if (const APawn* Pawn = GetOwningPlayerPawn())
	{
		InventoryComponent = Pawn->FindComponentByClass<UInventoryComponent>();
	}
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryComponent not found in owning PlayerPawn."));
	}

	// Set grid parameters
	const float NewWidth = InventoryComponent->Columns * InventoryComponent->TileSize;
	const float NewHeight = InventoryComponent->Rows * InventoryComponent->TileSize;

	// Set grid size
	UCanvasPanelSlot* BorderAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridBorder);
	BorderAsCanvasSlot->SetSize(FVector2D(NewWidth, NewHeight));

	// Draw grid lines
	CreateLineSegments(InventoryComponent->Rows, InventoryComponent->Columns, InventoryComponent->TileSize);
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                        const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	// Create the necessary parameters
	FPaintContext PaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	constexpr FLinearColor CustomColor(0.5f, 0.5f, 0.5f, 0.5f);
	const FVector2D TopLeftCorner = GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.f, 0.f));

	// Draw lines
	for (const FLine Line: Lines)
	{
		
		const FVector2D PositionA = Line.Start + TopLeftCorner;
		const FVector2D PositionB = Line.End + TopLeftCorner;
		UWidgetBlueprintLibrary::DrawLine(PaintContext, PositionA, PositionB, CustomColor); 
	}

	// TODO: Second part
	
	return int32();
}

void UInventoryGridWidget::CreateLineSegments(const int32 Rows, const int32 Columns, const float TileSize)
{
	// Compute coordinates for vertical lines
	for (int32 i = 0; i <= Columns; i++)
	{
		const float X = i * TileSize;
		Lines.Add(FLine(FVector2D(X, 0.f), FVector2D(X, Rows * TileSize)));
	}

	// Compute coordinates for horizontal lines
	for (int32 i = 0; i <= Rows; i++)
	{
		const float Y = i * TileSize;
		Lines.Add(FLine(FVector2D(0.f, Y), FVector2D(Columns * TileSize, Y)));
	}
}
