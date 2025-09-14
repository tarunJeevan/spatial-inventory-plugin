// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemObject;
class UUserWidget;
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

	/**
	 * @brief Try to add ItemObject to inventory
	 * 
	 * @param ItemObject	The ItemObject to add to the inventory
	 * @return				True if the item can be added to the inventory, false otherwise
	 */
	bool TryAddItem(UItemObject* ItemObject);


	/**
	 * @brief Get all unique items in inventory with their top-left tile positions
	 * 
	 * @return TMap<UItemObject*, FTile> of all items in inventory with their top-left tile position
	 */
	TMap<UItemObject*, FTile> GetAllItems() const;

	/**
	 * @brief Remove item from inventory
	 * 
	 * @param ItemObject ItemObject to remove from inventory
	 */
	void RemoveItem(const UItemObject* ItemObject);

	/**
	 * @brief Check if room is available in inventory for item
	 * 
	 * @param ItemObject ItemObject to check room in the inventory for
	 * @param TopLeftIndex Top left index of ItemObject to determine its place in the inventory
	 * @return True if there is room in the inventory for ItemObject, false otherwise
	 */
	bool IsRoomAvailable(const UItemObject* ItemObject, const int32 TopLeftIndex) const;

	/**
	 * @brief Add an item at a given location in the inventory
	 * @param ItemObject ItemObject to be added to inventory
	 * @param TopLeftIndex Top left index of ItemObject to determine its location in the inventory
	 */
	void AddItemAt(UItemObject* ItemObject, const int32 TopLeftIndex);

	/**
	 * @brief Convert an inventory tile to a mapped index
	 * 
	 * @param Tile FTile to convert to an index
	 * @return Integer index mapping to the given Tile
	 */
	int32 TileToIndex(const FTile Tile) const;

	/** The number of vertical columns in the inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Constants", meta=(ExposeOnSpawn="true"))
	int32 Columns = 1;

	/** The number of horizontal rows in the inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Constants", meta=(ExposeOnSpawn="true"))
	int32 Rows = 1;

	/** The size of each tile (intersection between row and column) in the inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Constants", meta=(ExposeOnSpawn="true"))
	float TileSize = 25.f;

	/** Widget class for items appearing in the inventory grid */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass = nullptr;

	/** Widget class for items appearing in the inventory grid */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|UI")
	TSubclassOf<UUserWidget> ItemWidgetClass = nullptr;

	/** Delegate to be broadcast when an item is added, moved, or removed */
	UPROPERTY(BlueprintAssignable, Category="Inventory|Events")
	FOnInventoryChanged OnInventoryChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Array containing all items in the inventory */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Inventory")
	TArray<UItemObject*> Items;

	/** Flag indicating that the inventory has changed and the UI must be updated */
	bool bIsDirty;

private:
	/**
	 * @brief Get the item at the given index
	 * 
	 * @param Index Index of an ItemObject in Items array
	 * @return ItemObject at the given index
	 */
	UItemObject* GetItemAtIndex(const int32 Index) const;

	/**
	 * @brief Check if a tile is valid
	 * 
	 * @param Tile FTile to validate
	 * @return True if Tile is within the bounds of the inventory, false otherwise
	 */
	bool IsTileValid(const FTile Tile) const;

	/**
	 * @brief Convert an index to its corresponding tile
	 * 
	 * @param Index Integer Index of an item in Items array
	 * @return Mapped FTile representing 2D location
	 */
	FTile IndexToTile(const int32 Index) const;
};
