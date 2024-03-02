// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory\Item\Fragments\STItemFragment_BulletSpread.h"


#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "Inventory/Item/Gun/STAttributeSet_Gun.h"
#include "GameFramework/CharacterMovementComponent.h"

USTItemFragment_BulletSpread::USTItemFragment_BulletSpread()
{

}



USTItemFragment_BulletSpreadInstanced::USTItemFragment_BulletSpreadInstanced()
    : CurrentBulletSpread(this, TEXT("CurrentBulletSpread"), 0.f)
{

}

void USTItemFragment_BulletSpreadInstanced::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);


    FDoRepLifetimeParams Params;
    Params.Condition = COND_None;
    Params.RepNotifyCondition = REPNOTIFY_OnChanged;
    Params.bIsPushBased = true;

    DOREPLIFETIME_WITH_PARAMS_FAST(USTItemFragment_BulletSpreadInstanced, CurrentBulletSpread, Params);

}

void USTItemFragment_BulletSpreadInstanced::SetAbilitySystemComponent(const UAbilitySystemComponent* NewASC)
{
    // Set the ASC
    OwnerASC = NewASC;

    if (const UAbilitySystemComponent* ASC = OwnerASC.Get())
    {
        // Refresh attribute values
        MinBulletSpread = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetMinBulletSpreadAttribute());
        MovingBulletSpread = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetMovingBulletSpreadAttribute());
        BulletSpreadIncRate = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetBulletSpreadIncRateAttribute());
        FireBulletSpread = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetFireBulletSpreadAttribute());
        BulletSpreadDecSpeed = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetBulletSpreadDecSpeedAttribute());

        // Set our CMC
        if (const FGameplayAbilityActorInfo* ActorInfo = ASC->AbilityActorInfo.Get())
        {
            CMC = Cast<UCharacterMovementComponent>(ActorInfo->MovementComponent.Get());
        }
    }
    else
    {
        MinBulletSpread = 0.f;
        MovingBulletSpread = 0.f;
        BulletSpreadIncRate = 0.f;
        FireBulletSpread = 0.f;
        BulletSpreadDecSpeed = 0.f;

        CMC = nullptr;
    }

    CurrentBulletSpread = FMath::Clamp<float>(CurrentBulletSpread, MinBulletSpread, MovingBulletSpread);
}


float USTItemFragment_BulletSpreadInstanced::GetRestBulletSpread() const
{
    float RetVal = MinBulletSpread;
    if (IsMovingToIncBulletSpread())
    {
        RetVal = MovingBulletSpread;
    }

    return RetVal;
}

void USTItemFragment_BulletSpreadInstanced::ApplyFireBulletSpread()
{
    CurrentBulletSpread = CurrentBulletSpread + FireBulletSpread;
}

void USTItemFragment_BulletSpreadInstanced::ResetBulletSpread()
{
    CurrentBulletSpread = MinBulletSpread;
}

bool USTItemFragment_BulletSpreadInstanced::IsMovingToIncBulletSpread() const
{
    if (BulletSpreadIncRate <= 0)
    {
        return false;
    }
    if (!CMC)
    {
        return false;
    }
    if (CMC->IsMovingOnGround() && CMC->GetCurrentAcceleration().SizeSquared() > KINDA_SMALL_NUMBER)
    {
        return true;
    }
    if (CMC->IsFalling())
    {
        return true;
    }

    return false;
}

void USTItemFragment_BulletSpreadInstanced::Tick(float DeltaTime)
{
    //UKismetSystemLibrary::PrintString(this, "USTAttributeSet_Gun::Tick()", true, false);
    if (IsMovingToIncBulletSpread())
    {
        if (CurrentBulletSpread < MovingBulletSpread)
        {
            CurrentBulletSpread = CurrentBulletSpread + (BulletSpreadIncRate * DeltaTime);
            if (CurrentBulletSpread > MovingBulletSpread)
            {
                CurrentBulletSpread = MovingBulletSpread;
            }
            return;
        }
    }

    float InterptedBulletSpread = FMath::FInterpTo(CurrentBulletSpread, GetRestBulletSpread(), DeltaTime, BulletSpreadDecSpeed);
    CurrentBulletSpread = InterptedBulletSpread;
    if (CurrentBulletSpread < GetRestBulletSpread())
    {
        CurrentBulletSpread = GetRestBulletSpread();
    }
}
bool USTItemFragment_BulletSpreadInstanced::IsTickable() const
{
    // Refresh attribute values
    if (const UAbilitySystemComponent* ASC = OwnerASC.Get())
    {
        // NOTE: this sets up the members for Tick() as well
        MinBulletSpread = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetMinBulletSpreadAttribute());
        MovingBulletSpread = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetMovingBulletSpreadAttribute());
        BulletSpreadIncRate = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetBulletSpreadIncRateAttribute());
        FireBulletSpread = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetFireBulletSpreadAttribute());
        BulletSpreadDecSpeed = ASC->GetNumericAttribute(USTAttributeSet_Gun::GetBulletSpreadDecSpeedAttribute());
    }

    if (CurrentBulletSpread < MinBulletSpread)
    {
        // NOTE: this sets up the member for Tick() as well
        CurrentBulletSpread = MinBulletSpread;
    }


    if (IsMovingToIncBulletSpread()/* && CurrentBulletSpread < GetMovingBulletSpread()*/)
    {
        return true;
    }

    // We are above our rest state, return true
    if (CurrentBulletSpread > GetRestBulletSpread())
    {
        return true;
    }

    return false;
}
