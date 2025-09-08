// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

class UItemObject;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ITEM_API AItemActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Create default item object (Override in Blueprint)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta=(DisplayName="Create Default Item Object", ReturnDisplayName="Item Object"))
	UItemObject* CreateDefaultItemObject();
	virtual UItemObject* CreateDefaultItemObject_Implementation();

	// Item properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USphereComponent> SphereCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	TObjectPtr<UItemObject> ItemObject = nullptr;
};
