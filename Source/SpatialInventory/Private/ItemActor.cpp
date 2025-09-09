// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemActor.h"
#include "InventoryComponent.h"
#include "InventoryInterface.h"
#include "ItemObject.h"
#include "Components/SphereComponent.h"

// Sets default values
AItemActor::AItemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the static mesh component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create sphere collision component
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	// Configure sphere collision
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECC_WorldDynamic);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	// Attach overlap event handler
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnSphereOverlap);

	// Set up component hierarchy
	StaticMesh->SetupAttachment(RootComponent);
	SphereCollision->SetupAttachment(StaticMesh);
}

// Called every frame
// void AItemActor::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// }

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	// Create a default item object if one doesn't already exist.
	if (!ItemObject)
	{
		ItemObject = CreateDefaultItemObject();
	}
}

void AItemActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
		{
			if (UInventoryComponent* InventoryComponent = IInventoryInterface::Execute_GetInventoryComponent(OtherActor))
			{
				// Add item to inventory via its item object
				if (InventoryComponent->TryAddItem(ItemObject))
				{
					// Destroy the item actor if added successfully
					Destroy();
				}
			}
		}
	}
}

UItemObject* AItemActor::CreateDefaultItemObject_Implementation()
{
	return UItemObject::StaticClass()->GetDefaultObject<UItemObject>();
}

