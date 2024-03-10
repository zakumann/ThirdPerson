// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputForward;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputBackward;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputRight;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputLeft;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputLook;
};
