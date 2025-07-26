#include "WeaponComponent.h"
#include "Weapon/WeaponModule.h"

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrentWeapon = nullptr;
    RangeWeaponOwner = nullptr;
    MeleeWeaponOwner = nullptr;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UWeaponComponent::EquipWeapon(AWeaponModule* NewWeapon)
{
    if (!NewWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("EquipWeapon called with null weapon"));
        return;
    }

    CurrentWeapon = NewWeapon;

    // Set owner references based on weapon type (if needed)
    if (CurrentWeapon->IsA(ARangeWeapon::StaticClass()))
    {
        RangeWeaponOwner = GetOwner();
    }
    else if (CurrentWeapon->IsA(AMeleeWeapon::StaticClass()))
    {
        MeleeWeaponOwner = GetOwner();
    }
}

void UWeaponComponent::UnequipWeapon()
{
    CurrentWeapon = nullptr;
    RangeWeaponOwner = nullptr;
    MeleeWeaponOwner = nullptr;
}

AWeaponModule* UWeaponComponent::GetCurrentWeapon() const
{
    return CurrentWeapon.Get();
}

bool UWeaponComponent::HasWeaponEquipped() const
{
    return CurrentWeapon.IsValid();
}

float UWeaponComponent::CalculateDamage(const FVector& HitLocation, const AActor* HitActor) const
{
    if (!CurrentWeapon.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("CalculateDamage called but no weapon equipped"));
        return 0.f;
    }

    return CurrentWeapon->CalculateDamage(HitLocation, HitActor);
}

float UWeaponComponent::GetWeaponRange() const
{
    if (!CurrentWeapon.IsValid())
    {
        return 0.f;
    }

    return CurrentWeapon->GetWeaponData().Range;
}

bool UWeaponComponent::IsAmmoAvailable() const
{
    if (!CurrentWeapon.IsValid())
    {
        return false;
    }

    // Assuming weapon has a method or property to check ammo; if not, return true for melee or infinite ammo weapons
    if (ARangeWeapon* RangeWeapon = Cast<ARangeWeapon>(CurrentWeapon.Get()))
    {
        return RangeWeapon->CurrentAmmo > 0;
    }

    // For melee or other weapons, assume ammo is available
    return true;
}

float UWeaponComponent::GetFireRate() const
{
    if (!CurrentWeapon.IsValid())
    {
        return 0.f;
    }

    return CurrentWeapon->GetWeaponData().FireRate;
}

bool UWeaponComponent::IsWeaponReady() const
{
    if (!CurrentWeapon.IsValid())
    {
        return false;
    }

    // Simplified: You can extend with reload or cooldown flags on weapon class
    return true;
}

float UWeaponComponent::GetWeaponWeight() const
{
    if (!CurrentWeapon.IsValid())
    {
        return 0.f;
    }

    return CurrentWeapon->GetWeaponData().Weight;
}

float UWeaponComponent::GetCurrentAmmoPercent() const
{
    if (!CurrentWeapon.IsValid())
    {
        return 0.f;
    }

    if (ARangeWeapon* RangeWeapon = Cast<ARangeWeapon>(CurrentWeapon.Get()))
    {
        if (RangeWeapon->CurrentAmmo <= 0 || RangeWeapon->GetWeaponData().MagazineSize <= 0)
        {
            return 0.f;
        }

        return static_cast<float>(RangeWeapon->CurrentAmmo) / RangeWeapon->GetWeaponData().MagazineSize;
    }

    return 1.f; // Melee or non-ammo weapons always full
}

bool UWeaponComponent::CanAimDownSights() const
{
    if (!CurrentWeapon.IsValid())
    {
        return false;
    }

    return CurrentWeapon->GetWeaponData().bCanAimDownSights;
}

FName UWeaponComponent::GetDamageType() const
{
    if (!CurrentWeapon.IsValid())
    {
        return NAME_None;
    }

    return CurrentWeapon->GetWeaponData().DamageType;
}
