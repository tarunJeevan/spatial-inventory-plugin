// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemObject;
struct FTile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPATIALINVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	// Try to add item to inventory, returns true if successful
	bool TryAddItem(UItemObject* ItemObject);
	// Get all unique items in inventory with their top-left tile positions
	TMap<UItemObject*, FTile> GetAllItems() const;
	// Remove item from inventory
	void RemoveItem(const UItemObject* ItemObject);
	bool IsRoomAvailable(const UItemObject* ItemObject, const int32 TopLeftIndex) const;
	void AddItemAt(UItemObject* ItemObject, const int32 TopLeftIndex);
	int32 TileToIndex(const FTile Tile) const;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Constants", meta=(ExposeOnSpawn="true"))
	int32 Columns = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Constants", meta=(ExposeOnSpawn="true"))
	int32 Rows = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Constants", meta=(ExposeOnSpawn="true"))
	float TileSize = 25.f;

	UPROPERTY(BlueprintAssignable, Category="Inventory|Events")
	FOnInventoryChanged OnInventoryChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<UItemObject*> Items;

	bool bIsDirty;

private:
	UItemObject* GetItemAtIndex(const int32 Index) const;
	bool IsTileValid(const FTile Tile) const;
	FTile IndexToTile(const int32 Index) const;
};
