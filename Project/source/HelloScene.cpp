#include "../include/HelloScene.hpp"

#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.

// Main initialisation.
// Automatically called inside SceneManager.
bool HelloScene::Init()
{

	return true;
}
// Main deinitialisation.
// Automatically called inside SceneManager.
bool HelloScene::DeInit()
{
	
	return true;
}

// Update loop. Gone trought once per frame.
bool HelloScene::Update(float dt)
{
	
	return true; // Update succeeded.
}
// Draw loop. All graphics are drawn during this loop.
bool HelloScene::Draw()
{
	
	return true; // Drawing succeeded.
}

//Default constructor for initialising constant variables.
HelloScene::HelloScene()
{

}
//Default deconstrutor.
HelloScene::~HelloScene()
{

}