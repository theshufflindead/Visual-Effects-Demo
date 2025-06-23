// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");
	ProcMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();

	CreateVertices();
	CreateTriangles();
	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true);
	ProcMesh->SetMaterial(0, Mat);
	
}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Alters the perlin procedural mesh based on the impact point of the projectile
void APerlinProcTerrain::AlterMesh(FVector ImpactPoint)
{
	for (int i = 0; i < Vertices.Num(); i++)
	{
		FVector tempVector = ImpactPoint - this->GetActorLocation();

		if (FVector(Vertices[i] - tempVector).Size() < radius)
		{
			Vertices[i] = Vertices[i] - Depth;
			ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

//Creates the vertices for the procedural mesh based on various values
void APerlinProcTerrain::CreateVertices()
{
	for (int X = 0; X <= XSize; X++) 
	{
		for (int Y = 0; Y <= YSize; Y++)
		{
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), Z));
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}

//Draws the triangles using the procedurally generated vertices
void APerlinProcTerrain::CreateTriangles()
{
	int Vertex = 0;

	for (int X = 0; X < XSize; X++)
	{
		for (int Y = 0; Y < YSize; Y++)
		{
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);

			Vertex++;
		}

		Vertex++;
	}
}

