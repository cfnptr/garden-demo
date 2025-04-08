// Copyright 2024-2025 Nikita Fediuchin. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "garden/main.hpp"
#include "garden/system/log.hpp"
#include "garden/system/link.hpp"
#include "garden/system/thread.hpp"
#include "garden/system/camera.hpp"
#include "garden/system/spawner.hpp"
#include "garden/system/settings.hpp"
#include "garden/system/resource.hpp"
#include "garden/system/transform.hpp"
#include "garden/system/animation.hpp"
#include "garden/system/character.hpp"
#include "garden/system/fpv-controller.hpp"
#include "garden/system/render/oit.hpp"
#include "garden/system/render/csm.hpp"
#include "garden/system/render/mesh.hpp"
#include "garden/system/render/fxaa.hpp"
#include "garden/system/render/ssao.hpp"
#include "garden/system/render/bloom.hpp"
#include "garden/system/render/skybox.hpp"
#include "garden/system/render/deferred.hpp"
#include "garden/system/render/pbr-lighting.hpp"
#include "garden/system/render/tone-mapping.hpp"
#include "garden/system/render/auto-exposure.hpp"

#include "demo/app-defines.hpp"
#include "demo/system/main.hpp"

#if GARDEN_EDITOR
#include "garden/system/render/imgui.hpp"
#include "garden/editor/system/log.hpp"
#include "garden/editor/system/ecs.hpp"
#include "garden/editor/system/link.hpp"
#include "garden/editor/system/camera.hpp"
#include "garden/editor/system/spawner.hpp"
#include "garden/editor/system/physics.hpp"
#include "garden/editor/system/graphics.hpp"
#include "garden/editor/system/transform.hpp"
#include "garden/editor/system/hierarchy.hpp"
#include "garden/editor/system/animation.hpp"
#include "garden/editor/system/render/csm.hpp"
#include "garden/editor/system/render/fxaa.hpp"
#include "garden/editor/system/render/ssao.hpp"
#include "garden/editor/system/render/bloom.hpp"
#include "garden/editor/system/render/skybox.hpp"
#include "garden/editor/system/render/sprite.hpp"
#include "garden/editor/system/render/9-slice.hpp"
#include "garden/editor/system/render/deferred.hpp"
#include "garden/editor/system/render/pbr-lighting.hpp"
#include "garden/editor/system/render/tone-mapping.hpp"
#include "garden/editor/system/render/auto-exposure.hpp"
#include "garden/editor/system/render/mesh-gizmos.hpp"
#include "garden/editor/system/render/mesh-selector.hpp"
#include "garden/editor/system/render/gpu-resource.hpp"
#include "garden/editor/system/render/infinite-grid.hpp"
#endif

using namespace garden;
using namespace garden::demo;

static void entryPoint()
{
	auto manager = new Manager();
	createAppSystem(manager);
	manager->createSystem<MainSystem>();
	manager->createSystem<DoNotDestroySystem>();
	manager->createSystem<DoNotDuplicateSystem>();
	manager->createSystem<DoNotSerializeSystem>();
	manager->createSystem<StaticTransformSystem>();
	manager->createSystem<LogSystem>();
	manager->createSystem<SettingsSystem>();
	manager->createSystem<ResourceSystem>();
	manager->createSystem<LinkSystem>();
	manager->createSystem<CameraSystem>();
	manager->createSystem<TransformSystem>();
	manager->createSystem<InputSystem>();
	manager->createSystem<FpvControllerSystem>();
	manager->createSystem<SpawnerSystem>();
	manager->createSystem<AnimationSystem>();
	manager->createSystem<PhysicsSystem>();
	manager->createSystem<CharacterSystem>();
	#if GARDEN_DEBUG
	manager->createSystem<ImGuiRenderSystem>();
	#endif
	manager->createSystem<GraphicsSystem>();
	manager->createSystem<DeferredRenderSystem>(true, false);
	manager->createSystem<SkyboxRenderSystem>();
	manager->createSystem<MeshRenderSystem>();
	manager->createSystem<PbrLightingRenderSystem>(true, true);
	manager->createSystem<CsmRenderSystem>();
	manager->createSystem<SsaoRenderSystem>();
	manager->createSystem<OitRenderSystem>();
	manager->createSystem<BloomRenderSystem>();
	manager->createSystem<ToneMappingRenderSystem>();
	manager->createSystem<AutoExposureRenderSystem>();
	manager->createSystem<FxaaRenderSystem>();
	manager->createSystem<ThreadSystem>();

	#if GARDEN_EDITOR
	manager->createSystem<EditorRenderSystem>();
	manager->createSystem<HierarchyEditorSystem>();
	manager->createSystem<EcsEditorSystem>();
	manager->createSystem<LogEditorSystem>();
	manager->createSystem<LinkEditorSystem>();
	manager->createSystem<SpawnerEditorSystem>();
	manager->createSystem<CameraEditorSystem>();
	manager->createSystem<TransformEditorSystem>();
	manager->createSystem<AnimationEditorSystem>();
	manager->createSystem<PhysicsEditorSystem>();
	manager->createSystem<GraphicsEditorSystem>();
	manager->createSystem<GpuResourceEditorSystem>();
	manager->createSystem<InfiniteGridEditorSystem>();
	manager->createSystem<MeshSelectorEditorSystem>();
	manager->createSystem<MeshGizmosEditorSystem>();
	manager->createSystem<DeferredRenderEditorSystem>();
	manager->createSystem<SkyboxRenderEditorSystem>();
	manager->createSystem<SpriteRenderEditorSystem>();
	manager->createSystem<NineSliceRenderEditorSystem>();
	manager->createSystem<PbrLightingRenderEditorSystem>();
	manager->createSystem<CsmRenderEditorSystem>();
	manager->createSystem<SsaoRenderEditorSystem>();
	manager->createSystem<BloomRenderEditorSystem>();
	manager->createSystem<ToneMappingRenderEditorSystem>();
	manager->createSystem<AutoExposureRenderEditorSystem>();
	manager->createSystem<FxaaRenderEditorSystem>();
	#endif

	manager->initialize();
	InputSystem::startRenderThread();

	delete manager;
}

GARDEN_DECLARE_MAIN(entryPoint)