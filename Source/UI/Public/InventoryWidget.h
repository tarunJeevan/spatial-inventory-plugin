// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UBackgroundBlur;
class UBorder;
class UCanvasPanel;
class UInventoryGridWidget;

UCLASS()
class UI_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief Get a reference to the inventory grid
	 * 
	 * @return Reference to this inventory widget's grid widget
	 */
	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	UInventoryGridWidget* GetInventoryGridWidget() const { return InventoryGrid; }

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="InventoryWidget|UI")
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="InventoryWidget|UI")
	TObjectPtr<UBorder> BackgroundBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="InventoryWidget|UI")
	TObjectPtr<UBackgroundBlur> Blur;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="InventoryWidget|UI")
	TObjectPtr<UInventoryGridWidget> InventoryGrid;

	// Override function to initialize the widget (Called only once)
	virtual void NativeOnInitialized() override;

	// Override function to handle drop operations
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

private:
	// Function to bind to the widget's OnMouseButtonDown event
	UFUNCTION()
	FEventReply CustomOnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
};
