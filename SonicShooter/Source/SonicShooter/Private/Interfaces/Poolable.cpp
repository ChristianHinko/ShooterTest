// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Poolable.h"

// Add default functionality here for any IPoolable functions that are not pure virtual.
IPoolable::IPoolable()
{
	bDebugPooling = false;
}



void IPoolable::OnUnpooled()
{

}
void IPoolable::OnPooled()
{

}



void IPoolable::StartLogic()
{

}
void IPoolable::EndLogic()
{

}
