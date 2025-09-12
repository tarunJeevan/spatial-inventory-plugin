// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "InventoryComponent.h"
#include "InventoryGridWidget.h"
#include "Components/Border.h"
#include "InventoryUtils.h"
#include "ItemObject.h"
#include "Blueprint/DragDropOperation.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Bind custom mouse down event to grid border to block mouse events from passing through
	BackgroundBorder->OnMouseButtonDownEvent.BindUFunction(this, "CustomOnMouseButtonDown");
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	// Spawn payload into the world
	UInventoryUtils::SpawnItemFromActor(Cast<UItemObject>(InOperation->Payload), InventoryGrid->GetInventoryComponent()->GetOwner(), true);

	return true;
}

FEventReply UInventoryWidget::CustomOnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	return FEventReply(true);
}
