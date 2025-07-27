#include "RecoilSystem.h"
#include "Math/UnrealMathUtility.h"

URecoilSystem::URecoilSystem()
    : VerticalRecoilMin(1.0f)
    , VerticalRecoilMax(3.0f)
    , HorizontalRecoilMin(-1.0f)
    , HorizontalRecoilMax(1.0f)
    , RecoverySpeed(5.0f)
    , MaxRecoilOffset(FVector2D(10.0f, 10.0f))
    , CurrentRecoilOffset(FVector2D::ZeroVector)
{
}

FVector2D URecoilSystem::ApplyRecoil()
{
    // Calculate vertical recoil within range
    const float VerticalRecoil = FMath::RandRange(VerticalRecoilMin, VerticalRecoilMax);

    // Calculate horizontal recoil with random sign within range
    const float HorizontalRecoil = FMath::RandRange(HorizontalRecoilMin, HorizontalRecoilMax);

    // Add recoil delta to current offset
    CurrentRecoilOffset.X += VerticalRecoil;
    CurrentRecoilOffset.Y += HorizontalRecoil;

    // Clamp recoil offset to max limits
    CurrentRecoilOffset.X = FMath::Clamp(CurrentRecoilOffset.X, 0.f, MaxRecoilOffset.X);
    CurrentRecoilOffset.Y = FMath::Clamp(CurrentRecoilOffset.Y, -MaxRecoilOffset.Y, MaxRecoilOffset.Y);

    // Notify listeners (e.g. to adjust camera)
    OnRecoilApplied.Broadcast(CurrentRecoilOffset);

    // Return recoil delta (pitch, yaw)
    return FVector2D(VerticalRecoil, HorizontalRecoil);
}

void URecoilSystem::UpdateRecovery(float DeltaTime)
{
    if (CurrentRecoilOffset.IsNearlyZero())
        return;

    // Smoothly interpolate recoil offset back to zero
    const float RecoveryStep = RecoverySpeed * DeltaTime;

    // Recover vertical recoil (pitch)
    CurrentRecoilOffset.X = FMath::FInterpTo(CurrentRecoilOffset.X, 0.f, DeltaTime, RecoverySpeed);

    // Recover horizontal recoil (yaw)
    CurrentRecoilOffset.Y = FMath::FInterpTo(CurrentRecoilOffset.Y, 0.f, DeltaTime, RecoverySpeed);

    // Clamp to zero if close enough
    if (FMath::Abs(CurrentRecoilOffset.X) < KINDA_SMALL_NUMBER)
    {
        CurrentRecoilOffset.X = 0.f;
    }
    if (FMath::Abs(CurrentRecoilOffset.Y) < KINDA_SMALL_NUMBER)
    {
        CurrentRecoilOffset.Y = 0.f;
    }
}

void URecoilSystem::ResetRecoil()
{
    CurrentRecoilOffset = FVector2D::ZeroVector;
    OnRecoilApplied.Broadcast(CurrentRecoilOffset);
}
