// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/BlueprintFunctionLibraries/BFL_MaterialHelpers.h"

int32 UBFL_MaterialHelpers::GetMaterialIndexFromSectionIndex(const UStaticMeshComponent* StaticMeshComponent, const int32 SectionIndex)
{
    //adapted from GetMaterialFromCollisionFaceIndex
    const UStaticMesh* Mesh = StaticMeshComponent->GetStaticMesh();
    if (Mesh && Mesh->RenderData.IsValid() && SectionIndex >= 0)
    {
        const int32 LODIndex = Mesh->LODForCollision;
        const FStaticMeshRenderData* RenderData = Mesh->RenderData.Get();
        if (RenderData->LODResources.IsValidIndex(LODIndex))
        {
            const FStaticMeshLODResources& LODResource = RenderData->LODResources[LODIndex];
            if (SectionIndex < LODResource.Sections.Num())
            {
                return LODResource.Sections[SectionIndex].MaterialIndex;
            }
        }
    }

    return -1;
}
