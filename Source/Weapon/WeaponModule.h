#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Component/WeaponComponent.h"
#include "WeaponModule.generated.h"

// Forward declarations
class USkeletalMeshComponent;
class UShapeComponent;
class UWeaponComponent;

/**
 * Base weapon actor class with mesh, collision, and weapon logic component.
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

    /** Get the internal weapon logic component */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

protected:
    /** Skeletal mesh component representing the weapon */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;

    /** Collision component for weapon interactions */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    UShapeComponent* WeaponCollision;

    /** Weapon logic and state component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    UWeaponComponent* WeaponComponent;
};
