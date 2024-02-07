
#include "PlaceableActor.h"
#include "CityTypes.h"
#include "PlaceableBoxComponent.h"
#include "BuilderSubsystem.h"

APlaceableActor::APlaceableActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

APlaceableActor::APlaceableActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	if (DefaultSceneComp)
	{
		SetRootComponent(DefaultSceneComp);
	}
	BoxCollision = CreateDefaultSubobject<UPlaceableBoxComponent>("BoxCollision");
	if (BoxCollision)
	{
		BoxCollision->SetCollisionProfileName("Building");
		BoxCollision->SetGenerateOverlapEvents(true);
		BoxCollision->bDynamicObstacle = true;
		BoxCollision->CanCharacterStepUpOn = ECB_No;
		BoxCollision->SetupAttachment(RootComponent);
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
	if (UBuilderSubsystem* Builder = GetGameInstance()->GetSubsystem<UBuilderSubsystem>())
	{
		if (Builder->IsPlacementModeEnabled())
		{
			return;
		}
	}
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
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 7.0f, FColor::Emerald, FString::Printf(TEXT("*** %s"), *OtherActor->GetName()));
	}
	Super::NotifyActorBeginOverlap(OtherActor);
}

void APlaceableActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (StaticMeshComp)
	{
		/* handle overlapping multiple actors at the same time */
		TArray<AActor*>outActors;
		StaticMeshComp->GetOverlappingActors(outActors);
		//const bool bNoOtherOverlaps = (StaticMeshComp->GetOverlapInfos().Num() == 0);
		if (outActors.Num() == 0 && BuildingState != EPlacementState::Placed)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 7.0f, FColor::Red, FString::Printf(TEXT("**END* %s"), *OtherActor->GetName()));

			BuildingState = EPlacementState::BeingPlacedValid;
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
	// set overlay as valid be default
	if (StaticMeshComp)
	{
		StaticMeshComp->SetOverlayMaterial(ValidPlacementMaterial);
	}
}
