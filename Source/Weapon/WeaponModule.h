#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponModule.generated.h"

/**
 * Base weapon actor class with mesh and collision components.
 */
UCLASS(Abstract)
class YOURGAME_API AWeaponModule : public AActor
{
    GENERATED_BODY()

public:
    AWeaponModule();

public:
    /** Get the weapon mesh component */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

    /** Set the weapon mesh component */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void SetWeaponMesh(USkeletalMeshComponent* NewMesh) { WeaponMesh = NewMesh; }

    /** Get the weapon collision component */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    UShapeComponent* GetWeaponCollision() const { return WeaponCollision; }

    /** Set the weapon collision component */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void SetWeaponCollision(UShapeComponent* NewCollision) { WeaponCollision = NewCollision; }

protected:
    /** Skeletal mesh component representing the weapon */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;

    /** Collision component for weapon interactions */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    UShapeComponent* WeaponCollision;
};
