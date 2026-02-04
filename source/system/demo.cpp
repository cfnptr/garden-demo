// Copyright 2024-2026 Nikita Fediuchin. All rights reserved.
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

#include "demo/system/main.hpp"
#include "garden/system/graphics.hpp"
#include "garden/system/transform.hpp"
#include "garden/system/render/pbr-lighting.hpp"

using namespace garden::demo;

MainSystem::MainSystem()
{
	auto manager = Manager::Instance::get();
	ECSM_SUBSCRIBE_TO_EVENT("PostInit", MainSystem::postInit);
}
MainSystem::~MainSystem()
{
	if (Manager::Instance::get()->isRunning)
	{
		auto manager = Manager::Instance::get();
		ECSM_UNSUBSCRIBE_FROM_EVENT("PostInit", MainSystem::postInit);
	}

	unsetSingleton();
}

void MainSystem::postInit()
{
	auto manager = Manager::Instance::get();
	auto graphicsSystem = GraphicsSystem::Instance::get();
	auto pbrLightingView = manager->add<PbrLightingComponent>(graphicsSystem->camera);
	pbrLightingView->setCubemapMode(PbrCubemapMode::Dynamic);

	auto directionalLight = manager->createEntity();
	manager->reserveComponents(directionalLight, 4);

	auto transformView = manager->add<TransformComponent>(directionalLight);
	transformView->setRotation(lookAtQuat(normalize3(-f32x4(1.0f, 6.0f, 2.0f))));
	#if GARDEN_DEBUG || GARDEN_EDITOR
	transformView->debugName = "Directional Light";
	manager->add<DoNotDestroyComponent>(directionalLight);
	manager->add<DoNotSerializeComponent>(directionalLight);
	#endif
	graphicsSystem->directionalLight = directionalLight;
}