#pragma once

#include "CoreMinimal.h"
#include "WeaponModule.h"
#include "MeleeWeapon.generated.h"

/**
 * Melee weapon class for close combat weapons (swords, knives, etc.)
 */
UCLASS()
class YOURGAME_API AMeleeWeapon : public AWeaponModule
{
    GENERATED_BODY()

public:
    AMeleeWeapon();

    /** Get Melee attack radius */
    UFUNCTION(BlueprintCallable, Category = "Melee")
    float GetAttackRadius() const;

    /** Set Melee attack radius */
    UFUNCTION(BlueprintCallable, Category = "Melee")
    void SetAttackRadius(float Radius);

    /** Get attack cooldown */
    UFUNCTION(BlueprintCallable, Category = "Melee")
    float GetAttackCooldown() const;

    /** Set attack cooldown */
    UFUNCTION(BlueprintCallable, Category = "Melee")
    void SetAttackCooldown(float Cooldown);

    /** Check if weapon can attack based on cooldown */
    UFUNCTION(BlueprintCallable, Category = "Melee")
    bool CanAttack() const;

    /** Perform melee attack logic */
    UFUNCTION(BlueprintCallable, Category = "Melee")
    void PerformMeleeAttack();

    /** Get base damage amount */
    UFUNCTION(BlueprintCallable, Category = "Melee")
    float GetBaseDamage() const;

protected:
    /** Radius of melee attack (can be used for hit detection sphere) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
    float AttackRadius;

    /** Time in seconds between attacks */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
    float AttackCooldown;

private:
    /** Timestamp of last performed attack */
    float LastAttackTime;
};
