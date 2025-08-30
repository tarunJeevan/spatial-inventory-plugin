// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"

// #include "Components/Border.h"
// #include "Components/CanvasPanel.h"
// #include "Components/CanvasPanelSlot.h"
// #include "InventoryDataStructs.h"

void UInventoryGridWidget::InitializeGrid(UInventoryComponent* InventoryComponentRef, const float CustomTileSize)
{
	InventoryComponent = InventoryComponentRef;
	TileSize = CustomTileSize;
}
