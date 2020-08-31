// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"





/**
 * We are not implementing this for this game but plan on it for future games. This will be our base target actor class.
 * An example of what to change would be to delete the Filter variable and let children target actors add it on their own so they can
 * decide which ability target data filter to use for their target actor.
 * 
 * IMPORTANT:
 * If we use this class as a base target actor class we also need to make our own AT_WaitTargetData base class that will use our base
 * target actor class instead of the engine's.
 * The comment in the engine's WaitTargetData_Task even tells you to make your own version of the task so this is appropriate
 */
