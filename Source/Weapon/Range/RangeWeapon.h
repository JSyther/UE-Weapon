#pragma once

#include "CoreMinimal.h"
#include "WeaponModule.h"
#include "RangeWeapon.generated.h"

/**
 * Ranged weapon class with ammo, fire rate and projectile/spread control
 */
UCLASS()
class YOURGAME_API ARangeWeapon : public AWeaponModule
{
    GENERATED_BODY()

public:
    ARangeWeapon();

    /** Returns true if weapon has ammo */
    bool HasAmmo() const;

    /** Consumes one unit of ammo */
    void ConsumeAmmo();

    /** Reloads weapon to full capacity */
    void Reload();

    /** Getters */
    int32 GetCurrentAmmo() const;
    int32 GetMaxAmmo() const;
    float GetFireRate() const;
    float GetSpread() const;

protected:
    /** Current ammo count */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
    int32 CurrentAmmo;

    /** Max ammo per magazine */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
    int32 MaxAmmo;

    /** Time between shots */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    float FireRate;

    /** Bullet spread factor */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    float Spread;
};
