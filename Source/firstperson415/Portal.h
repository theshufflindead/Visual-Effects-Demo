// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Portal.generated.h"

class firstperson415Character;

UCLASS()
class FIRSTPERSON415_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Mesh for the portal
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

	//Captures scene to display on portal
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneCaptureComponent2D* sceneCapture;

	UPROPERTY(EditAnywhere)
		UArrowComponent* rootArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextureRenderTarget2D* renderTarget;

	UPROPERTY(EditAnywhere)
		UBoxComponent* boxComp;
	
	UPROPERTY(EditAnywhere)
		APortal* OtherPortal;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* mat;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SetBool(Afirstperson415Character* playerChar);

	UFUNCTION()
		void UpdatePortals();
};
