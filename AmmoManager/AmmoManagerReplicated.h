#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AmmoManagerReplicated.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, int32, CurrentAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReserveAmmoChanged, int32, CurrentReserveAmmo);

/**
 * UAmmoManagerReplicated
 * ----------------------
 * Multiplayer-ready ammo management system with replication support.
 * Tracks ammo in clip and reserve, handles reloads and consumption,
 * replicates ammo state from server to clients.
 */
UCLASS(Blueprintable)
class YOURPROJECT_API UAmmoManagerReplicated : public UObject
{
    GENERATED_BODY()

public:
    UAmmoManagerReplicated();

    /** Initialize ammo with max capacities */
    UFUNCTION(BlueprintCallable, Category = "Ammo")
    void Initialize(int32 MaxClip, int32 MaxReserve);

    /** Try consume one ammo from clip; returns true if successful */
    UFUNCTION(BlueprintCallable, Category = "Ammo")
    bool ConsumeAmmo();

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    bool HasAmmoInClip() const;

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    bool HasReserveAmmo() const;

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    bool CanReload() const;

    /** Reload clip from reserve; returns number of bullets reloaded */
    UFUNCTION(BlueprintCallable, Category = "Ammo")
    int32 ReloadClip();

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    int32 GetCurrentAmmo() const { return CurrentAmmo; }

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    int32 GetReserveAmmo() const { return ReserveAmmo; }

    /** Event triggered on clip ammo changes */
    UPROPERTY(BlueprintAssignable, Category = "Ammo")
    FOnAmmoChanged OnClipAmmoChanged;

    /** Event triggered on reserve ammo changes */
    UPROPERTY(BlueprintAssignable, Category = "Ammo")
    FOnReserveAmmoChanged OnReserveAmmoChanged;

protected:
    /** Current ammo in clip, replicated to clients */
    UPROPERTY(ReplicatedUsing = OnRep_CurrentAmmo, VisibleAnywhere, Category = "Ammo")
    int32 CurrentAmmo;

    /** Current reserve ammo, replicated to clients */
    UPROPERTY(ReplicatedUsing = OnRep_ReserveAmmo, VisibleAnywhere, Category = "Ammo")
    int32 ReserveAmmo;

    UPROPERTY(EditDefaultsOnly, Category = "Ammo")
    int32 MaxClipAmmo;

    UPROPERTY(EditDefaultsOnly, Category = "Ammo")
    int32 MaxReserveAmmo;

    /** Replication notification callbacks */
    UFUNCTION()
    void OnRep_CurrentAmmo();

    UFUNCTION()
    void OnRep_ReserveAmmo();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    void NotifyAmmoChanged();
    void NotifyReserveChanged();
};
