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

#include "demo/system/main.hpp"
#include "garden/system/graphics.hpp"
#include "garden/system/render/skybox.hpp"
#include "garden/system/render/pbr-lighting.hpp"

using namespace garden::demo;

constexpr auto skyboxPath = "cubemaps/puresky";

MainSystem::MainSystem()
{
	ECSM_SUBSCRIBE_TO_EVENT("PostInit", MainSystem::postInit);
	ECSM_SUBSCRIBE_TO_EVENT("Update", MainSystem::update);
}
MainSystem::~MainSystem()
{
	if (Manager::Instance::get()->isRunning)
	{
		ECSM_UNSUBSCRIBE_FROM_EVENT("PostInit", MainSystem::postInit);
		ECSM_UNSUBSCRIBE_FROM_EVENT("Update", MainSystem::update);
	}

	unsetSingleton();
}

void MainSystem::postInit()
{
	auto manager = Manager::Instance::get();
	auto graphicsSystem = GraphicsSystem::Instance::get();
	auto pbrLightingView = manager->add<PbrLightingComponent>(graphicsSystem->camera);
	PbrLightingSystem::Instance::get()->loadCubemap(skyboxPath,
		pbrLightingView->cubemap, pbrLightingView->sh, pbrLightingView->specular);
	manager->add<SkyboxRenderComponent>(graphicsSystem->camera);
}
void MainSystem::update()
{
	auto graphicsSystem = GraphicsSystem::Instance::get();
	auto skyboxSystem = SkyboxRenderSystem::Instance::get();
	auto skyboxView = skyboxSystem->getComponent(graphicsSystem->camera);

	if (!skyboxView->descriptorSet)
	{
		auto skyboxPipeline = graphicsSystem->get(skyboxSystem->getPipeline());
		if (skyboxPipeline->isLoaded())
		{
			auto pbrLightngSystem = PbrLightingSystem::Instance::get();
			auto pbrLightingView = pbrLightngSystem->getComponent(graphicsSystem->camera);
			skyboxView->cubemap = pbrLightingView->cubemap;
			skyboxView->descriptorSet = skyboxSystem->createSharedDS(
				skyboxPath, ID<Image>(pbrLightingView->cubemap));
		}
	}
}