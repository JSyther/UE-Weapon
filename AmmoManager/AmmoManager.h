#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AmmoManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, int32, CurrentAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReserveAmmoChanged, int32, CurrentReserveAmmo);

/**
 * UAmmoManager
 * ------------
 * Handles ammo counts, clip reloads, and ammo events.
 * Designed to be embedded or composed inside weapon classes.
 */
UCLASS(Blueprintable)
class YOURPROJECT_API UAmmoManager : public UObject
{
    GENERATED_BODY()

public:
    UAmmoManager();

    /** Initializewait ammo counts */
    UFUNCTION(BlueprintCallable, Category="Ammo")
    void Initialize(int32 MaxClip, int32 MaxReserve);

    /** Attempt to consume one bullet from clip; returns true if successful */
    UFUNCTION(BlueprintCallable, Category="Ammo")
    bool ConsumeAmmo();

    /** Returns true if clip has ammo */
    UFUNCTION(BlueprintCallable, Category="Ammo")
    bool HasAmmoInClip() const;

    /** Returns true if reserve has ammo */
    UFUNCTION(BlueprintCallable, Category="Ammo")
    bool HasReserveAmmo() const;

    /** Returns true if reload possible */
    UFUNCTION(BlueprintCallable, Category="Ammo")
    bool CanReload() const;

    /** Reload clip from reserve; returns bullets reloaded */
    UFUNCTION(BlueprintCallable, Category="Ammo")
    int32 ReloadClip();

    /** Get current ammo in clip */
    UFUNCTION(BlueprintCallable, Category="Ammo")
    int32 GetCurrentAmmo() const { return CurrentAmmo; }

    /** Get current reserve ammo */
    UFUNCTION(BlueprintCallable, Category="Ammo")
    int32 GetReserveAmmo() const { return ReserveAmmo; }

    /** Events */
    UPROPERTY(BlueprintAssignable, Category="Ammo")
    FOnAmmoChanged OnClipAmmoChanged;

    UPROPERTY(BlueprintAssignable, Category="Ammo")
    FOnReserveAmmoChanged OnReserveAmmoChanged;

private:
    /** Current bullets in clip */
    UPROPERTY(VisibleAnywhere, Category="Ammo")
    int32 CurrentAmmo;

    /** Current bullets in reserve */
    UPROPERTY(VisibleAnywhere, Category="Ammo")
    int32 ReserveAmmo;

    /** Max bullets in clip */
    UPROPERTY(EditDefaultsOnly, Category="Ammo")
    int32 MaxClipAmmo;

    /** Max bullets in reserve */
    UPROPERTY(EditDefaultsOnly, Category="Ammo")
    int32 MaxReserveAmmo;

    void NotifyAmmoChanged();
    void NotifyReserveChanged();
};
