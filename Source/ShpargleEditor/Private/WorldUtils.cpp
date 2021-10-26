// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldUtils.h"
#include "Editor.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"


UStaticMeshComponent* UWorldUtils::AddStaticMeshComponentToActor(class AActor* TargetActor, FString Name, class UStaticMesh* Mesh, const FTransform& RelativeTransform)
{
	UStaticMeshComponent* Component = NewObject<UStaticMeshComponent>(TargetActor, *Name);
	Component->ClearFlags(RF_DefaultSubObject);

	Component->SetStaticMesh(Mesh);
	Component->SetRelativeTransform_Direct(RelativeTransform);

	Component->SetupAttachment(TargetActor->GetRootComponent());
	Component->UpdateComponentToWorld();
	Component->RegisterComponent();
	Component->OnComponentCreated();

	TargetActor->AddInstanceComponent(Component);
	TargetActor->RerunConstructionScripts();

	return Component;
}
