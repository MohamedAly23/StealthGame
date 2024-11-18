// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGameInstance.h"


void UStealthGameInstance::SetScore(int32 NewScore)
{
    PlayerScore = NewScore;
}

int32 UStealthGameInstance::GetScore() 
{
    return PlayerScore;
}