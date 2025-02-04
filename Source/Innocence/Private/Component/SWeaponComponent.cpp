// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SWeaponComponent.h"
#include "Item/Projectile/SProjectileBase.h"

// Sets default values for this component's properties
USWeaponComponent::USWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// 枪械网格体
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	WeaponMesh->SetSimulatePhysics(true);
	// 默认7发子弹
	BulletNumMax = 7;


}

// Called when the game starts
void USWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// 默认装满
	AddAll();

}

// 开火
TSubclassOf<AActor> USWeaponComponent::Fire()
{
	// 保证有子弹
	if (BulletInGun.Num() <= 0)
	{
		return nullptr;
	}

	return BulletInGun.Pop();
	//return BulletInGun[0];
}

// 装弹
void USWeaponComponent::AddBullet(TSubclassOf<AActor> ProjectileClass)
{
	// 不能超上限；
	if (BulletInGun.Num() >= BulletNumMax)
	{
		return;
	}

	if (!ProjectileClass) {
		BulletInGun.Add(DefaultBullet);
		return;
	}

	if (ProjectileClass)
	{
		BulletInGun.Add(ProjectileClass);
	}
}

// 装满
void USWeaponComponent::AddAll()
{
	// 不能超上限；
	int32 delta = BulletNumMax - BulletInGun.Num();
	if (delta <= 0)
	{
		return;
	}

	if (ensure(DefaultBullet))
	{
		//BulletInGun.Add(DefaultBullet);
		//BulletInGun.Init(DefaultBullet, delta);
		for (int i = 0; i < delta; i++)
		{
			BulletInGun.Add(DefaultBullet);
		}

	}
}





// Called every frame
void USWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

USWeaponComponent* USWeaponComponent::GetWeaponComp(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USWeaponComponent>(FromActor->GetComponentByClass(USWeaponComponent::StaticClass()));
	}

	return nullptr;
}