// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "Components/Border.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Bind custom mouse down event to grid border to block mouse events from passing through
	BackgroundBorder->OnMouseButtonDownEvent.BindUFunction(this, "CustomOnMouseButtonDown");
}

FEventReply UInventoryWidget::CustomOnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	return FEventReply(true);
}
