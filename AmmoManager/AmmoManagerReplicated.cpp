#include "AmmoManagerReplicated.h"
#include "Net/UnrealNetwork.h"

UAmmoManagerReplicated::UAmmoManagerReplicated()
    : CurrentAmmo(0)
    , ReserveAmmo(0)
    , MaxClipAmmo(30)
    , MaxReserveAmmo(90)
{
    SetIsReplicatedByDefault(true);
}

void UAmmoManagerReplicated::Initialize(int32 MaxClip, int32 MaxReserve)
{
    MaxClipAmmo = MaxClip;
    MaxReserveAmmo = MaxReserve;

    if (GetOwner() && GetOwner()->HasAuthority())
    {
        CurrentAmmo = MaxClipAmmo;
        ReserveAmmo = MaxReserveAmmo;
        NotifyAmmoChanged();
        NotifyReserveChanged();
    }
}

bool UAmmoManagerReplicated::ConsumeAmmo()
{
    if (GetOwner() && GetOwner()->HasAuthority())
    {
        if (CurrentAmmo <= 0)
            return false;

        CurrentAmmo--;
        NotifyAmmoChanged();
        return true;
    }

    if (GetOwner() && !GetOwner()->HasAuthority())
    {
        ServerConsumeAmmo();
    }
    return false;
}

bool UAmmoManagerReplicated::HasAmmoInClip() const
{
    return CurrentAmmo > 0;
}

bool UAmmoManagerReplicated::HasReserveAmmo() const
{
    return ReserveAmmo > 0;
}

bool UAmmoManagerReplicated::CanReload() const
{
    return CurrentAmmo < MaxClipAmmo && ReserveAmmo > 0;
}

int32 UAmmoManagerReplicated::ReloadClip()
{
    if (GetOwner() && GetOwner()->HasAuthority())
    {
        if (!CanReload())
            return 0;

        int32 AmmoNeeded = MaxClipAmmo - CurrentAmmo;
        int32 AmmoToReload = FMath::Min(AmmoNeeded, ReserveAmmo);

        CurrentAmmo += AmmoToReload;
        ReserveAmmo -= AmmoToReload;

        NotifyAmmoChanged();
        NotifyReserveChanged();

        return AmmoToReload;
    }

    if (GetOwner() && !GetOwner()->HasAuthority())
    {
        ServerReloadClip();
    }
    return 0;
}

void UAmmoManagerReplicated::OnRep_CurrentAmmo()
{
    NotifyAmmoChanged();
}

void UAmmoManagerReplicated::OnRep_ReserveAmmo()
{
    NotifyReserveChanged();
}

void UAmmoManagerReplicated::NotifyAmmoChanged()
{
    OnClipAmmoChanged.Broadcast(CurrentAmmo);
}

void UAmmoManagerReplicated::NotifyReserveChanged()
{
    OnReserveAmmoChanged.Broadcast(ReserveAmmo);
}

void UAmmoManagerReplicated::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UAmmoManagerReplicated, CurrentAmmo);
    DOREPLIFETIME(UAmmoManagerReplicated, ReserveAmmo);
}

bool UAmmoManagerReplicated::ServerConsumeAmmo_Validate()
{
    return true; // Add validation logic if needed
}

void UAmmoManagerReplicated::ServerConsumeAmmo_Implementation()
{
    if (CurrentAmmo > 0)
    {
        CurrentAmmo--;
        NotifyAmmoChanged();
    }
}

bool UAmmoManagerReplicated::ServerReloadClip_Validate()
{
    return true; // Add validation logic if needed
}

void UAmmoManagerReplicated::ServerReloadClip_Implementation()
{
    if (CurrentAmmo < MaxClipAmmo && ReserveAmmo > 0)
    {
        int32 AmmoNeeded = MaxClipAmmo - CurrentAmmo;
        int32 AmmoToReload = FMath::Min(AmmoNeeded, ReserveAmmo);

        CurrentAmmo += AmmoToReload;
        ReserveAmmo -= AmmoToReload;

        NotifyAmmoChanged();
        NotifyReserveChanged();
    }
}
