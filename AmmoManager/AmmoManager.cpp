#include "AmmoManager.h"

UAmmoManager::UAmmoManager()
    : CurrentAmmo(0)
    , ReserveAmmo(0)
    , MaxClipAmmo(30)
    , MaxReserveAmmo(90)
{
    // Constructor: Initializes ammo counts to defaults.
    // CurrentAmmo and ReserveAmmo start at zero to ensure explicit initialization.
}

void UAmmoManager::Initialize(int32 MaxClip, int32 MaxReserve)
{
    // Initialize max capacities ensuring sensible minimums.
    MaxClipAmmo = FMath::Max(1, MaxClip);
    MaxReserveAmmo = FMath::Max(0, MaxReserve);

    // Set current ammo counts to their maximum values.
    CurrentAmmo = MaxClipAmmo;
    ReserveAmmo = MaxReserveAmmo;

    // Notify listeners of initial ammo states.
    NotifyAmmoChanged();
    NotifyReserveChanged();
}

bool UAmmoManager::ConsumeAmmo()
{
    // Attempt to consume one bullet from the clip.

    if (CurrentAmmo <= 0)
    {
        // No ammo available in clip to consume.
        return false;
    }

    // Reduce ammo count by one.
    --CurrentAmmo;

    // Broadcast change event.
    NotifyAmmoChanged();

    return true;
}

bool UAmmoManager::HasAmmoInClip() const
{
    // Returns whether there is any ammo left in the clip.
    return CurrentAmmo > 0;
}

bool UAmmoManager::HasReserveAmmo() const
{
    // Returns whether there is any ammo left in reserve.
    return ReserveAmmo > 0;
}

bool UAmmoManager::CanReload() const
{
    // Reload is possible only if reserve ammo exists and clip is not full.
    return (ReserveAmmo > 0) && (CurrentAmmo < MaxClipAmmo);
}

int32 UAmmoManager::ReloadClip()
{
    // Reload ammo from reserve into clip, returning amount reloaded.

    if (!CanReload())
    {
        // Reload not possible, return zero.
        return 0;
    }

    // Calculate ammo needed to fill clip to max.
    const int32 AmmoNeeded = MaxClipAmmo - CurrentAmmo;

    // Determine how much ammo can be transferred from reserve.
    const int32 AmmoToReload = FMath::Min(AmmoNeeded, ReserveAmmo);

    // Update ammo counts.
    CurrentAmmo += AmmoToReload;
    ReserveAmmo -= AmmoToReload;

    // Notify listeners of changes.
    NotifyAmmoChanged();
    NotifyReserveChanged();

    return AmmoToReload;
}

void UAmmoManager::NotifyAmmoChanged()
{
    // Broadcast the current clip ammo count to any listeners.
    OnClipAmmoChanged.Broadcast(CurrentAmmo);
}

void UAmmoManager::NotifyReserveChanged()
{
    // Broadcast the current reserve ammo count to any listeners.
    OnReserveAmmoChanged.Broadcast(ReserveAmmo);
}
