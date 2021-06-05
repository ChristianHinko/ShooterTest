// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/BlueprintFunctionLibraries/BFL_MathHelpers.h"



bool UBFL_MathHelpers::PointLiesOnSegment(const FVector& Start, const FVector& End, const FVector& Point)
{
    float SegmentDistance = FVector::Distance(Start, End);
    float StartToPointDistance = FVector::Distance(Start, Point);
    float PointToEndDistance = FVector::Distance(Point, End);

    if (FMath::IsNearlyEqual(StartToPointDistance + PointToEndDistance, SegmentDistance)) // if we are not a triangle
    {
        return true;
    }
    return false;
}
