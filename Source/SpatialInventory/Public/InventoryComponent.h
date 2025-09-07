// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Constants", meta=(ExposeOnSpawn="true"))
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Constants", meta=(ExposeOnSpawn="true"))
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Constants", meta=(ExposeOnSpawn="true"))
	float TileSize;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
