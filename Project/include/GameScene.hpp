#pragma once
#ifndef GameScene_HPP
#define GameScene_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Layer.hpp>
#include <UtH/Engine/TMX/Map.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <Minimap.hpp>

#include <array>
#include <utility>

class GameScene : public uth::Scene
{
private: // Just place everything else as private.
	uth::Shader m_shader;

	uth::TMX::Map gameMap;
	uth::Camera* mainCamera;
	uth::GameObject *player, *cart;
	std::array<umath::rectangle,7> switches;
	std::array<uth::TMX::Object*,7> tmxSwitches;
	std::array<umath::rectangle,8> rails;
	std::array<uth::TMX::Object*,8> tmxRails;

	int offsetY;
	float speed;
	int line;
	bool switchlane;
	std::string direction;

    Minimap m_minimap;

	const std::pair<bool, umath::vector2> pressFunc(const umath::rectangle &rect);

public: // Every one of these public functions are required.
	GameScene();
	~GameScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();
};

#endif //GameScene_HPP