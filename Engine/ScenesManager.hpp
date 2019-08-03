#pragma once
#include <memory>
#include <vector>
#include <type_traits>
#include "Scene.hpp"

class SceneManager {
	using Scenes_t = std::vector<std::unique_ptr<Scene>>;

	Scenes_t scenes;
	size_t iCurScene = 0;
public:
	template<typename T, typename... Args>
	void addScene(Args... args) {
		static_assert(std::is_base_of_v<Scene, T>, "\"Scene\" class must be base of the given scene");
		scenes.push_back(std::make_unique<T>(args...));
	}

	void update(float dt, const Keyboard& kbd, const Mouse& mouse) {
		getCurScene().update(dt, kbd, mouse);
	}

	void draw(Graphics& gfx) const {
		getCurScene().draw(gfx);
	}

	Scene& getCurScene() {
		return *scenes[iCurScene];
	}
	const Scene& getCurScene() const {
		return *scenes[iCurScene];
	}

	void cycleScenes() {
		if (++iCurScene == scenes.size()) {
			iCurScene = 0;
		}
	}
};