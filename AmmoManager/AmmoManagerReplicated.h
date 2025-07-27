#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AmmoManagerReplicated.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, int32, CurrentAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReserveAmmoChanged, int32, CurrentReserveAmmo);

/**
 * UAmmoManagerReplicated
 * ----------------------
 * Multiplayer-ready ammo manager with replication and server RPCs that include validation.
 * Handles ammo counts, consumption, reloads, and notifies clients of changes.
 */
UCLASS(Blueprintable)
class YOURPROJECT_API UAmmoManagerReplicated : public UObject
{
    GENERATED_BODY()

public:
    UAmmoManagerReplicated();

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    void Initialize(int32 MaxClip, int32 MaxReserve);

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    bool ConsumeAmmo();

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    bool HasAmmoInClip() const;

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    bool HasReserveAmmo() const;

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    bool CanReload() const;

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    int32 ReloadClip();

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    int32 GetCurrentAmmo() const { return CurrentAmmo; }

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    int32 GetReserveAmmo() const { return ReserveAmmo; }

    UPROPERTY(BlueprintAssignable, Category = "Ammo")
    FOnAmmoChanged OnClipAmmoChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ammo")
    FOnReserveAmmoChanged OnReserveAmmoChanged;

protected:
    UPROPERTY(ReplicatedUsing=OnRep_CurrentAmmo, VisibleAnywhere, Category = "Ammo")
    int32 CurrentAmmo;

    UPROPERTY(ReplicatedUsing=OnRep_ReserveAmmo, VisibleAnywhere, Category = "Ammo")
    int32 ReserveAmmo;

    UPROPERTY(EditDefaultsOnly, Category = "Ammo")
    int32 MaxClipAmmo;

    UPROPERTY(EditDefaultsOnly, Category = "Ammo")
    int32 MaxReserveAmmo;

    UFUNCTION()
    void OnRep_CurrentAmmo();

    UFUNCTION()
    void OnRep_ReserveAmmo();

    /** Server RPCs with validation */
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerConsumeAmmo();

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerReloadClip();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    void NotifyAmmoChanged();
    void NotifyReserveChanged();
};
