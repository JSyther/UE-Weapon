#include "WeaponModule.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h" // veya CapsuleComponent, ihtiyaca göre

AWeaponModule::AWeaponModule()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create and attach weapon mesh
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;

    // Create and attach collision component
    WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
    WeaponCollision->SetupAttachment(WeaponMesh);
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    WeaponCollision->SetCollisionObjectType(ECC_WorldDynamic);
    WeaponCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    WeaponCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}
