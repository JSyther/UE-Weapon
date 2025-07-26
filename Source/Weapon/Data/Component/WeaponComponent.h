#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponModule.h"
#include "WeaponComponent.generated.h"

/**
 * Manages equipped weapon instances and general weapon state.
 * Responsible for holding references to weapon actors (range/melee).
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UWeaponComponent();

protected:
    virtual void BeginPlay() override;

public:
    /** Equip a weapon actor */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void EquipWeapon(AWeaponModule* NewWeapon);

    /** Unequip current weapon */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void UnequipWeapon();

    /** Get currently equipped weapon */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    AWeaponModule* GetCurrentWeapon() const;

    /** Check if a weapon is equipped */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    bool HasWeaponEquipped() const;

    /** Calculate damage based on weapon and hit info */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Helpers")
    float CalculateDamage(const FVector& HitLocation, const AActor* HitActor) const;


    /** Get the effective range of the weapon */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Helpers")
    float GetWeaponRange() const;

    /** Check if weapon has ammo available */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Helpers")
    bool IsAmmoAvailable() const;

    /** Get the weapon's fire rate */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Helpers")
    float GetFireRate() const;

    /** Check if the weapon is ready to fire (reload and cooldown completed) */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Helpers")
    bool IsWeaponReady() const;

    /** Get the weapon's weight */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Helpers")
    float GetWeaponWeight() const;

    /** Get current ammo percentage in magazine */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Helpers")
    float GetCurrentAmmoPercent() const;

    /** Check if weapon can aim down sights */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Helpers")
    bool CanAimDownSights() const;

    /** Get weapon damage type */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Helpers")
    FName GetDamageType() const;

protected:
    /** Currently equipped weapon actor */
    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    TWeakObjectPtr<AWeaponModule> CurrentWeapon;

    /** Owner reference for ranged weapon (nullable) */
    UPROPERTY()
    TWeakObjectPtr<AActor> RangeWeaponOwner = nullptr;

    /** Owner reference for melee weapon (nullable) */
    UPROPERTY()
    TWeakObjectPtr<AActor> MeleeWeaponOwner = nullptr;
};
