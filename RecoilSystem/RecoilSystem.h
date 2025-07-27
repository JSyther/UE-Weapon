#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RecoilSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecoilApplied, FVector2D, RecoilDelta);

/**
 * URecoilSystem
 * -------------
 * Modular recoil handler to simulate weapon kick and aim offset.
 * 
 * Supports:
 * - Vertical and horizontal recoil with randomness
 * - Smooth recoil recovery over time
 * - Blueprint events on recoil application
 */
UCLASS(Blueprintable)
class YOURPROJECT_API URecoilSystem : public UObject
{
    GENERATED_BODY()

public:
    URecoilSystem();

    /** Apply recoil impulse; returns recoil delta to apply */
    UFUNCTION(BlueprintCallable, Category = "Recoil")
    FVector2D ApplyRecoil();

    /** Update recoil recovery over DeltaTime */
    UFUNCTION(BlueprintCallable, Category = "Recoil")
    void UpdateRecovery(float DeltaTime);

    /** Get current recoil offset (pitch, yaw) */
    UFUNCTION(BlueprintCallable, Category = "Recoil")
    FVector2D GetCurrentRecoilOffset() const { return CurrentRecoilOffset; }

    /** Reset recoil instantly */
    UFUNCTION(BlueprintCallable, Category = "Recoil")
    void ResetRecoil();

    /** Max vertical recoil per shot */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
    float VerticalRecoilMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
    float VerticalRecoilMax;

    /** Horizontal recoil range (random between min and max, can be negative for left or right) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
    float HorizontalRecoilMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
    float HorizontalRecoilMax;

    /** Speed at which recoil recovers per second */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
    float RecoverySpeed;

    /** Clamp max recoil offset */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
    FVector2D MaxRecoilOffset;

    /** Event called after recoil is applied */
    UPROPERTY(BlueprintAssignable, Category = "Recoil")
    FOnRecoilApplied OnRecoilApplied;

private:
    /** Current accumulated recoil offset (pitch, yaw) */
    FVector2D CurrentRecoilOffset;
};
