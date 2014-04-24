#pragma once
#ifndef HelloScene_HPP
#define HelloScene_HPP

#include <UtH/Engine/Scene.hpp>

class HelloScene : public uth::Scene
{
private: // Just place everything else as private.

public: // Every one of these public functions are required.
	HelloScene();
	~HelloScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();
};

#endif //HelloScene_HPP