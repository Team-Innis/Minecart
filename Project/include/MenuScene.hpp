#pragma once
#ifndef MenuScene_HPP
#define MenuScene_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Layer.hpp>

class MenuScene : public uth::Scene
{
private: // Just place everything else as private.
	uth::Shader m_shader;
	uth::GameObject title, startButton, helpButton, exitButton, sbText, hbText, exText, jumpText, background;
    std::unique_ptr<uth::Layer> main, instructions, bg;
    bool drawHelp;

public: // Every one of these public functions are required.
	MenuScene();
	~MenuScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();

	bool MouseOver(uth::GameObject&);
};

#endif //MenuScene_HPP