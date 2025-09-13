// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "InventoryDataStructs.h"
#include "ItemObject.h"

#pragma region Public
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
										FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsDirty)
	{
		bIsDirty = false;
		OnInventoryChanged.Broadcast();
	}
}

bool UInventoryComponent::TryAddItem(UItemObject* ItemObject)
{
	if (IsValid(ItemObject))
	{
		// Try to add item in every possible position in inventory
		for (int32 i = 0; i < Items.Num(); i++)
		{
			// Check for available room in inventory and add item if found
			if (IsRoomAvailable(ItemObject, i))
			{
				AddItemAt(ItemObject, i);
				return true;
			}
		}
		
		// Rotate item and try again
		ItemObject->Rotate();
		for (int32 i = 0; i < Items.Num(); i++)
		{
			// Check for available room in inventory and add item if found
			if (IsRoomAvailable(ItemObject, i))
			{
				AddItemAt(ItemObject, i);
				return true;
			}
		}
		// Rotate item back to original orientation
		ItemObject->Rotate();
		
		// No room was found so return false
		return false;
	}
	// If ItemObject is invalid, return false
	return false;
}

TMap<UItemObject*, FTile> UInventoryComponent::GetAllItems() const
{
	// Initialize map to be returned
	TMap<UItemObject*, FTile> AllItems;

	// Iterate through inventory array
	for (int32 i = 0; i < Items.Num(); i++)
	{
		// If item is valid and not already in map, add it with its top-left tile position
		if (IsValid(Items[i]))
		{
			if (!AllItems.Contains(Items[i]))
			{
				AllItems.Add(Items[i], IndexToTile(i));
			}
		}
	}
	return AllItems;
}

void UInventoryComponent::RemoveItem(const UItemObject* ItemObject)
{
	if (IsValid(ItemObject))
	{
		for (UItemObject*& Item: Items)
		{
			// Remove all instances of the item from the inventory
			if (Item == ItemObject)
			{
				Item = nullptr;
				bIsDirty = true;
			}
		}
	}
}

bool UInventoryComponent::IsRoomAvailable(const UItemObject* ItemObject, const int32 TopLeftIndex) const
{
	const FTile Tile = IndexToTile(TopLeftIndex);
	const FIntPoint Dimensions = ItemObject->GetDimensions();

	// Check if item fits within inventory bounds
	for (int32 i = Tile.X; i <= Tile.X + Dimensions.X - 1; i++)
	{
		for (int32 j = Tile.Y; j <= Tile.Y + Dimensions.Y - 1; j++)
		{
			// Check if the tile is valid. If not, return false
			if (IsTileValid(FTile(i, j)))
			{
				// If tile is already occupied by another item, return false
				if (const UItemObject* ItemAtIndex = GetItemAtIndex(TileToIndex(FTile(i, j))))
				{
					// If the index is invalid, return false
					if (ItemAtIndex == nullptr)
					{
						return false;
					}
					// If there is a valid item in the slot, return false
					if (IsValid(ItemAtIndex))
					{
						return false;
					}
				} 
			}
			else
			{
				return false;
			}
		}
	}
	// If all checks passed, return true
	return true;
}

void UInventoryComponent::AddItemAt(UItemObject* ItemObject, const int32 TopLeftIndex)
{
	const FTile Tile = IndexToTile(TopLeftIndex);
	const FIntPoint Dimensions = ItemObject->GetDimensions();

	// Check if item fits within inventory bounds
	for (int32 i = Tile.X; i <= Tile.X + Dimensions.X - 1; i++)
	{
		for (int32 j = Tile.Y; j <= Tile.Y + Dimensions.Y - 1; j++)
		{
			Items[TileToIndex(FTile(i, j))] = ItemObject;
		}
	}
	// Set flag to update inventory state
	bIsDirty = true;
}

int32 UInventoryComponent::TileToIndex(const FTile Tile) const
{
	return Tile.X + Tile.Y * Columns;
}
#pragma endregion

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize inventory array size based on rows and columns
	Items.SetNum(Rows * Columns);
}

#pragma region Private
UItemObject* UInventoryComponent::GetItemAtIndex(const int32 Index) const
{
	if (Items.IsValidIndex(Index))
	{
		return Items[Index]; 
	}
	return nullptr;
}

bool UInventoryComponent::IsTileValid(const FTile Tile) const
{
	if (Tile.X >= 0 && Tile.Y >= 0 && Tile.X < Columns && Tile.Y < Rows)
	{
		return true;
	}
	return false;
}

FTile UInventoryComponent::IndexToTile(const int32 Index) const
{
	return FTile(Index % Columns, Index / Columns);
}
#pragma endregion 
