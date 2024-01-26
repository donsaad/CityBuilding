
#include "PlaceableActor.h"
#include "CityTypes.h"
#include "PlaceableStaticMeshComp.h"
#include "PlaceableBoxComponent.h"

APlaceableActor::APlaceableActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

APlaceableActor::APlaceableActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BoxCollision = CreateDefaultSubobject<UPlaceableBoxComponent>("BoxCollision");
	if (BoxCollision)
	{
		BoxCollision->SetCollisionProfileName("Building");
		BoxCollision->SetGenerateOverlapEvents(true);
		BoxCollision->bDynamicObstacle = true;
		BoxCollision->CanCharacterStepUpOn = ECB_No;
		RootComponent = BoxCollision;
	}
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	if (StaticMeshComp)
	{
		StaticMeshComp->Mobility = EComponentMobility::Movable;
		StaticMeshComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		StaticMeshComp->CanCharacterStepUpOn = ECB_No;
		StaticMeshComp->SetupAttachment(RootComponent);
	}

	BuildingState = EPlacementState::Created;

}

void APlaceableActor::NotifyActorOnClicked(FKey ButtonPressed /*= EKeys::LeftMouseButton*/)
{
	if (StaticMeshComp && BuildingState == EPlacementState::Placed)
	{
		UMaterialInterface* MeshMat = StaticMeshComp->GetMaterial(0);
		if (UMaterialInstanceDynamic* MatIns = Cast<UMaterialInstanceDynamic>(MeshMat))
		{
			MatIns->SetVectorParameterValue("BaseColor", FLinearColor({ FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f) ,FMath::FRandRange(0.0f, 1.0f) ,FMath::FRandRange(0.0f, 1.0f) }));
		}
		else
		{
			UMaterialInstanceDynamic* NewMatIns = UMaterialInstanceDynamic::Create(MeshMat, this);
			StaticMeshComp->SetMaterial(0, NewMatIns);
			NewMatIns->SetVectorParameterValue("BaseColor", FLinearColor({ FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f) ,FMath::FRandRange(0.0f, 1.0f) ,FMath::FRandRange(0.0f, 1.0f) }));
		}
	}

	Super::NotifyActorOnClicked(ButtonPressed);
}

void APlaceableActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (BuildingState != EPlacementState::Placed)
	{
		BuildingState = EPlacementState::BeingPlacedInvalid;
		if (StaticMeshComp)
		{
			StaticMeshComp->SetOverlayMaterial(InvalidPlacementMaterial);
		}
	}
	Super::NotifyActorBeginOverlap(OtherActor);
}

void APlaceableActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (BuildingState != EPlacementState::Placed)
	{
		BuildingState = EPlacementState::BeingPlacedValid;
		if (StaticMeshComp)
		{
			StaticMeshComp->SetOverlayMaterial(ValidPlacementMaterial);
		}
	}
	Super::NotifyActorEndOverlap(OtherActor);
}

bool APlaceableActor::CanBePlaced() const
{
	return BuildingState == EPlacementState::BeingPlacedValid;
}

void APlaceableActor::PlaceBuilding()
{
	BuildingState = EPlacementState::Placed;
	if (BoxCollision)
	{
		BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	}
	if (StaticMeshComp)
	{
		StaticMeshComp->SetOverlayMaterial(nullptr);
	}
	//if (PlaceableStaticMesh)
	//{
		// TODO: change material opacity visuals
	//}
}

void APlaceableActor::MarkAsBeingPlaced()
{
	BuildingState = EPlacementState::BeingPlacedValid;
}

bool APlaceableActor::IsPlaced() const
{
	return BuildingState == EPlacementState::Placed;
}

void APlaceableActor::BeginPlay()
{
	Super::BeginPlay();

}
