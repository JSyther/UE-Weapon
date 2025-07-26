#include "WeaponModule.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Component/WeaponComponent.h"

AWeaponModule::AWeaponModule()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create and attach weapon mesh (root)
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;
    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponMesh->SetGenerateOverlapEvents(false);

    // Create and attach collision component (for melee hits, pickup detection, etc.)
    WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
    WeaponCollision->SetupAttachment(WeaponMesh);
    WeaponCollision->SetBoxExtent(FVector(32.f)); // Default size, customize as needed
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    WeaponCollision->SetCollisionObjectType(ECC_WorldDynamic);
    WeaponCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    WeaponCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    WeaponCollision->SetGenerateOverlapEvents(true);

    // Optional: Create internal weapon logic handler (UWeaponComponent)
    WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
}
