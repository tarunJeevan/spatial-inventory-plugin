// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

class UItemObject;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class SPATIALINVENTORY_API AItemActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemActor();
	void SetItemObject(UItemObject* NewItemObject);

protected:
	// Item properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USphereComponent> SphereCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category="Item")
	TObjectPtr<UItemObject> ItemObject = nullptr;

	// Native function overrides
	virtual void BeginPlay() override;

	// On sphere collision overlap handler
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                     const FHitResult& SweepResult);
	
	// Create default item object (Override in Blueprint)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta=(DisplayName="Create Default Item Object", ReturnDisplayName="Item Object"))
	UItemObject* CreateDefaultItemObject();
	virtual UItemObject* CreateDefaultItemObject_Implementation();
};
