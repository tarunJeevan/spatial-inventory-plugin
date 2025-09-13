// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryGridWidget.h"

#include "CustomPlayerController.h"
#include "ItemObject.h"
#include "ItemWidget.h"
#include "SpatialInventory/Public/InventoryComponent.h"
#include "Components/Border.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UInventoryGridWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Bind custom mouse down event to grid border to block mouse events from passing through
	GridBorder->OnMouseButtonDownEvent.BindUFunction(this, "CustomOnMouseButtonDown");

	// Get InventoryComponent from owning player
	if (const APawn* Pawn = GetOwningPlayerPawn())
	{
		InventoryComponent = Pawn->FindComponentByClass<UInventoryComponent>();
	}
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryComponent not found in owning PlayerPawn."));
	}

	// Set rows, columns, and tile size
	Rows = InventoryComponent->Rows;
	Columns = InventoryComponent->Columns;
	TileSize = InventoryComponent->TileSize;

	// Set grid parameters
	const float NewWidth = InventoryComponent->Columns * InventoryComponent->TileSize;
	const float NewHeight = InventoryComponent->Rows * InventoryComponent->TileSize;

	// Set grid size
	UCanvasPanelSlot* BorderAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridBorder);
	BorderAsCanvasSlot->SetSize(FVector2D(NewWidth, NewHeight));

	// Draw grid lines
	CreateLineSegments();

	// Refresh inventory grid
	Refresh();

	// Bind to OnInventoryChanged delegate
	InventoryComponent->OnInventoryChanged.AddDynamic(this, &UInventoryGridWidget::Refresh);
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

bool UInventoryGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (IsRoomAvailableForPayload(GetPayload(InOperation)))
	{
		const FTile Tile = FTile(DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y);
		InventoryComponent->AddItemAt(GetPayload(InOperation), InventoryComponent->TileToIndex(Tile));
	}

	return true;
}

bool UInventoryGridWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	const FVector2D MousePosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	auto [Right, Down] = MousePositionInTile(MousePosition);
	int32 X, Y;

	// Calculate X based on mouse position in tile
	if (Right)
	{
		const int32 Value = GetPayload(InOperation)->GetDimensions().X - 1;
		X = FMath::Clamp(Value, 0, Value);
	}
	else
	{
		const int32 Value = GetPayload(InOperation)->GetDimensions().X - 0;
		X = FMath::Clamp(Value, 0, Value);
	}

	// Calculate Y based on mouse position in tile
	if (Down)
	{
		const int32 Value = GetPayload(InOperation)->GetDimensions().Y - 1;
		Y = FMath::Clamp(Value, 0, Value);
	}
	else
	{
		const int32 Value = GetPayload(InOperation)->GetDimensions().Y - 0;
		Y = FMath::Clamp(Value, 0, Value);
	}
	const FIntPoint CalcResult = FIntPoint(FMath::TruncToInt32(MousePosition.X / TileSize), FMath::TruncToInt32(MousePosition.Y / TileSize));

	DraggedItemTopLeftTile = FIntPoint(CalcResult - FIntPoint(X, Y) / 2); // TODO: Check if this is correct

	return true;
}

void UInventoryGridWidget::CreateLineSegments()
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

UItemObject* UInventoryGridWidget::GetPayload(const UDragDropOperation* DragDropOperation) const
{
	if (IsValid(DragDropOperation))
	{
		return Cast<UItemObject>(DragDropOperation->Payload);
	}
	// Return nullptr if drag and drop operation is invalid
	return nullptr;
}

bool UInventoryGridWidget::IsRoomAvailableForPayload(const UItemObject* Payload) const
{
	if (IsValid(Payload))
	{
		// Return true or false depending on if there is room available for payload in inventory
		const FTile Tile = FTile(DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y);
		return InventoryComponent->IsRoomAvailable(Payload, InventoryComponent->TileToIndex(Tile));
	}
	// Return false if payload is invalid
	return false;
}

TTuple<bool, bool> UInventoryGridWidget::MousePositionInTile(const FVector2D MousePosition) const
{
	bool Right = false;
	bool Down = false;

	// Determine if mouse is in right or left half of tile
	if (FMath::Fmod(MousePosition.X, TileSize) > TileSize / 2.f)
	{
		Right = true;
	}

	// Determine if mouse is in bottom or top half of tile
	if (FMath::Fmod(MousePosition.Y, TileSize) > TileSize / 2.f)
	{
		Down = true;
	}

	// Return tuple indicating right and down status of mouse position in tile
	return TTuple<bool, bool>(Right, Down);
}

void UInventoryGridWidget::OnItemRemoved(UItemObject* ItemObject)
{
	// Remove item from inventory component
	InventoryComponent->RemoveItem(ItemObject);
}

void UInventoryGridWidget::Refresh()
{
	GridCanvasPanel->ClearChildren();
	
	// Loop through inventory and create an item widget for every unique item
	for (const TPair<UItemObject*, FTile>& Pair: InventoryComponent->GetAllItems())
	{
		const TSubclassOf<UUserWidget> ItemWidgetClass = Cast<ACustomPlayerController>(GetOwningPlayer())->ItemWidgetClass;
		const FName ItemWidgetName = FName(*FString::Printf(TEXT("ItemWidget_%p"), Pair.Key));

		// Create and configure item widget
		if (UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass, ItemWidgetName))
		{
			ItemWidget->SetOwningPlayer(GetOwningPlayer());
			ItemWidget->Init(TileSize, Pair.Key);
			ItemWidget->Refresh();
			// Bind to OnRemoved delegate
			ItemWidget->OnRemoved.AddDynamic(this, &UInventoryGridWidget::OnItemRemoved);
			// Add item widget to grid canvas panel
			UCanvasPanelSlot* ItemWidgetPanelSlot = Cast<UCanvasPanelSlot>(GridCanvasPanel->AddChild(ItemWidget));
			// Set item widget size and position
			ItemWidgetPanelSlot->SetAutoSize(true);
			ItemWidgetPanelSlot->SetPosition(FVector2D(Pair.Value.X * TileSize, Pair.Value.Y * TileSize));
		}
	}
}

FEventReply UInventoryGridWidget::CustomOnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	return FEventReply(true);
}
