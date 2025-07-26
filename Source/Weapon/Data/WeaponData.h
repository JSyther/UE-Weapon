#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponData.generated.h"

/** Weapon category: Melee or Ranged */
UENUM(BlueprintType)
enum class EWeaponCategory : uint8
{
    Melee   UMETA(DisplayName = "Melee"),
    Ranged  UMETA(DisplayName = "Ranged")
};

/** Fire mode for ranged weapons */
UENUM(BlueprintType)
enum class EFiringMode : uint8
{
    Single  UMETA(DisplayName = "Single Shot"),
    Burst   UMETA(DisplayName = "Burst Fire"),
    Auto    UMETA(DisplayName = "Automatic")
};

/** Weapon data struct for both melee and ranged */
USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
    GENERATED_BODY()

    // General
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|General")
    FName WeaponID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|General")
    FString WeaponName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|General")
    EWeaponCategory WeaponCategory;

    // Ranged specific
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ranged", meta=(EditCondition="WeaponCategory == EWeaponCategory::Ranged"))
    EFiringMode FiringMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ranged", meta=(EditCondition="WeaponCategory == EWeaponCategory::Ranged"))
    float BaseDamage = 25.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ranged", meta=(EditCondition="WeaponCategory == EWeaponCategory::Ranged"))
    float HeadshotMultiplier = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ranged", meta=(EditCondition="WeaponCategory == EWeaponCategory::Ranged"))
    float FireRate = 5.f; // rounds per second

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ranged", meta=(EditCondition="WeaponCategory == EWeaponCategory::Ranged"))
    float Accuracy = 0.8f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ranged", meta=(EditCondition="WeaponCategory == EWeaponCategory::Ranged"))
    int32 MagazineSize = 15;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ranged", meta=(EditCondition="WeaponCategory == EWeaponCategory::Ranged"))
    float ReloadTime = 2.f;

    // Melee specific
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee", meta=(EditCondition="WeaponCategory == EWeaponCategory::Melee"))
    float MeleeDamage = 40.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee", meta=(EditCondition="WeaponCategory == EWeaponCategory::Melee"))
    float AttackSpeed = 1.f; // attacks per second

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee", meta=(EditCondition="WeaponCategory == EWeaponCategory::Melee"))
    float Reach = 150.f; // melee range in cm

    // Common properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Common")
    float Recoil = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Common")
    float MovementSpeedModifier = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Common")
    bool bCanAimDownSights = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Common")
    float WeaponWeight = 5.f;

    // Visual & Audio (soft references)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Visual")
    TSoftObjectPtr<USkeletalMesh> WeaponMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Visual")
    TSoftObjectPtr<UParticleSystem> MuzzleFlashEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Audio")
    TSoftObjectPtr<USoundBase> FireSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Audio")
    TSoftObjectPtr<USoundBase> ReloadSound;

    // Constructor with defaults
    FWeaponData()
    {
        WeaponID = NAME_None;
        WeaponName = TEXT("DefaultWeapon");
        WeaponCategory = EWeaponCategory::Ranged;
        FiringMode = EFiringMode::Single;
        BaseDamage = 25.f;
        HeadshotMultiplier = 2.f;
        FireRate = 5.f;
        Accuracy = 0.8f;
        MagazineSize = 15;
        ReloadTime = 2.f;

        MeleeDamage = 40.f;
        AttackSpeed = 1.f;
        Reach = 150.f;

        Recoil = 1.f;
        MovementSpeedModifier = 1.f;
        bCanAimDownSights = true;
        WeaponWeight = 5.f;
    }
};
