#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct ITEM_API FItemData
{
	GENERATED_BODY()

	FItemData() {};
	FItemData(const int32 InRows, const int32 InColumns) : Rows(InRows), Columns(InColumns) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Columns;
};
