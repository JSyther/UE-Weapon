#include "RangeWeapon.h"

ARangeWeapon::ARangeWeapon()
{
    MaxAmmo = 30;
    CurrentAmmo = MaxAmmo;
    FireRate = 0.15f;
    Spread = 1.0f;
}

bool ARangeWeapon::HasAmmo() const
{
    return CurrentAmmo > 0;
}

void ARangeWeapon::ConsumeAmmo()
{
    if (CurrentAmmo > 0)
    {
        --CurrentAmmo;
    }
}

void ARangeWeapon::Reload()
{
    CurrentAmmo = MaxAmmo;
}

int32 ARangeWeapon::GetCurrentAmmo() const
{
    return CurrentAmmo;
}

int32 ARangeWeapon::GetMaxAmmo() const
{
    return MaxAmmo;
}

float ARangeWeapon::GetFireRate() const
{
    return FireRate;
}

float ARangeWeapon::GetSpread() const
{
    return Spread;
}
