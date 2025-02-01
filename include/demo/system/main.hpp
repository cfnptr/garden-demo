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

#pragma once
#include "ecsm.hpp"

namespace garden::demo
{

using namespace ecsm;

class MainSystem final : public System, public Singleton<MainSystem>
{
	MainSystem();
	~MainSystem() final;

	void postInit();
	void update();

	friend class ecsm::Manager;
};

} // namespace garden::demo