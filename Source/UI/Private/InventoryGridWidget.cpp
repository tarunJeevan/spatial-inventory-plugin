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
	Rows = InventoryComponent->Rows;
	Columns = InventoryComponent->Columns;
	TileSize = InventoryComponent->TileSize;
	
	const float NewWidth = Columns * TileSize;
	const float NewHeight = Rows * TileSize;
	LinesData = new FLines();

	// Set grid size
	UCanvasPanelSlot* BorderAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridBorder);
	BorderAsCanvasSlot->SetSize(FVector2D(NewWidth, NewHeight));

	// Draw grid lines
	CreateLineSegments();
}

void UInventoryGridWidget::NativeDestruct()
{
	delete LinesData;
	LinesData = nullptr;
	Super::NativeDestruct();
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                        const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	FPaintContext PaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	constexpr FLinearColor CustomColor(0.5f, 0.5f, 0.5f, 0.5f);
	const FVector2D TopLeftCorner = GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.f, 0.f));

	// Draw grid lines. TODO: Try modifying to fit Reid's version
	int32 k = 0;
	for (int32 i = 0; i < LinesData->XLines.Num(); i++)
	{
		for (int32 j = 0; j < LinesData->YLines.Num(); j++)
		{
			k = i;
		}
		const FVector2D PositionA = FVector2D(StartX[i], StartY[k]) + TopLeftCorner;
		const FVector2D PositionB = FVector2D(EndX[i], EndY[k]) + TopLeftCorner;
		UWidgetBlueprintLibrary::DrawLine(PaintContext, PositionA, PositionB, CustomColor);
	}

	// TODO: Second part
	
	return int32();
}

void UInventoryGridWidget::CreateLineSegments()
{
	// Compute coordinates for vertical lines
	for (int32 i = 0; i <= Columns; i++)
	{
		float X = i * TileSize;
		LinesData->XLines.Add(FVector2D(X, X));
		LinesData->YLines.Add(FVector2D(0.f, Rows * TileSize));
	}

	// Compute coordinates for horizontal lines
	for (int32 i = 0; i <= Rows; i++)
	{
		float Y = i * TileSize;
		LinesData->XLines.Add(FVector2D(0.f, Columns * TileSize));
		LinesData->YLines.Add(FVector2D(Y, Y));
	}

	// Populate Start and End arrays
	for (const FVector2D Line : LinesData->XLines)
	{
		StartX.Add(Line.X);
		EndX.Add(Line.Y);
	}
	for (const FVector2D Line : LinesData->YLines)
	{
		StartY.Add(Line.X);
		EndY.Add(Line.Y);
	}
}
