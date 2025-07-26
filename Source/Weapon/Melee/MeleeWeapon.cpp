#include "MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AMeleeWeapon::AMeleeWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    AttackRadius = 150.0f;   // Default melee attack radius
    AttackCooldown = 1.0f;   // Default cooldown between attacks
    LastAttackTime = -AttackCooldown;  // So attack can be performed immediately after spawn
}

float AMeleeWeapon::GetAttackRadius() const
{
    return AttackRadius;
}

void AMeleeWeapon::SetAttackRadius(float Radius)
{
    AttackRadius = Radius;
}

float AMeleeWeapon::GetAttackCooldown() const
{
    return AttackCooldown;
}

void AMeleeWeapon::SetAttackCooldown(float Cooldown)
{
    AttackCooldown = Cooldown;
}

bool AMeleeWeapon::CanAttack() const
{
    if (!GetWorld())
    {
        return false;
    }

    float CurrentTime = GetWorld()->GetTimeSeconds();
    return (CurrentTime - LastAttackTime) >= AttackCooldown;
}

void AMeleeWeapon::PerformMeleeAttack()
{
    if (!CanAttack())
    {
        return;
    }

    // Perform a sphere overlap around the weapon to detect hit actors
    FVector SweepCenter = GetActorLocation();
    TArray<FOverlapResult> Overlaps;

    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(AttackRadius);
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);      // Ignore self
    QueryParams.AddIgnoredActor(GetOwner()); // Ignore owner (e.g. character holding weapon)

    bool bHasHit = GetWorld()->OverlapMultiByChannel(
        Overlaps,
        SweepCenter,
        FQuat::Identity,
        ECC_Pawn, // Assuming pawns are damageable actors
        CollisionShape,
        QueryParams
    );

    if (bHasHit)
    {
        for (const FOverlapResult& Result : Overlaps)
        {
            AActor* HitActor = Result.GetActor();
            if (HitActor && HitActor != GetOwner())
            {
                UGameplayStatics::ApplyDamage(HitActor, GetBaseDamage(), GetInstigatorController(), this, nullptr);
            }
        }
    }

    LastAttackTime = GetWorld()->GetTimeSeconds();
}

float AMeleeWeapon::GetBaseDamage() const
{
    return 25.f; // Default damage; this can be expanded to use WeaponData or attributes
}
