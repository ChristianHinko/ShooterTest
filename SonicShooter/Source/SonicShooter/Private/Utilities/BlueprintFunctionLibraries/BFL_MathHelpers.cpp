// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/BlueprintFunctionLibraries/BFL_MathHelpers.h"



bool UBFL_MathHelpers::PointLinesOnSegment(const FVector& Start, const FVector& End, const FVector& Point)
{
    //FVector::CrossProduct()




    float SegmentDistance = FVector::Distance(Start, End);
    float StartToPointDistance = FVector::Distance(Start, Point);
    float PointToEndDistance = FVector::Distance(Point, End);

    if (FMath::IsNearlyEqual(StartToPointDistance + PointToEndDistance, SegmentDistance)) // if we are not a triangle
    {
        return true;
    }





    //crossproduct = (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y)

    //    # compare versus epsilon for floating point values, or != 0 if using integers
    //    if abs(crossproduct) > epsilon:
    //return False

    //    dotproduct = (c.x - a.x) * (b.x - a.x) + (c.y - a.y) * (b.y - a.y)
    //    if dotproduct < 0 :
    //        return False

    //        squaredlengthba = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)
    //        if dotproduct > squaredlengthba:
    //return False

    //    return True
    return false;
}
