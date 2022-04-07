// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/PoolableInterface.h"

// Add default functionality here for any IPoolableInterface functions that are not pure virtual.
IPoolableInterface::IPoolableInterface()
{
	bIsCurentlyInPool = false;
}



void IPoolableInterface::OnUnpooled()
{
	bIsCurentlyInPool = false;
}
void IPoolableInterface::OnPooled()
{
	bIsCurentlyInPool = true;
}



void IPoolableInterface::StartLogic()
{

}
void IPoolableInterface::EndLogic()
{

}
