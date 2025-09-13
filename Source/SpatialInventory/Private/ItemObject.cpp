// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemObject.h"

FIntPoint UItemObject::GetDimensions() const
{
	if (bIsRotated)
	{
		return FIntPoint(Dimensions.Y, Dimensions.X);
	}
	return Dimensions;
}
