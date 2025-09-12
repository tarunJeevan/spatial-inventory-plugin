// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryUtils.h"

#include "ItemActor.h"
#include "ItemObject.h"

void UInventoryUtils::SpawnItemFromActor(UItemObject* ItemObject, AActor* Actor, bool bGroundClamp)
{
	// Calculate spawn location
	FVector SpawnLocation = Actor->GetActorLocation() + Actor->GetActorForwardVector() * 150.f;
	// Do a line trace to find ground if bGroundClamp is true
	if (bGroundClamp)
	{
		// Line trace params
		FHitResult Hit;
		FVector TraceStart = SpawnLocation;
		FVector TraceEnd = SpawnLocation - FVector(0.f, 0.f, 1000.f);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(Actor);

		// Perform line trace
		if (Actor->GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
		{
			SpawnLocation = Hit.Location;
		}
	}

	// Spawn item
	AItemActor* SpawnedItem = Actor->GetWorld()->SpawnActorDeferred<AItemActor>(ItemObject->GetItemClass(), FTransform(SpawnLocation));
	SpawnedItem->SetItemObject(ItemObject);
	SpawnedItem->FinishSpawning(FTransform(SpawnLocation));
}
