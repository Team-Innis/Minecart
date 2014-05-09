#include "../include/GameScene.hpp"

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.
#include <UtH/Engine/Text.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>

// Main initialisation.
// Automatically called inside SceneManager.
bool GameScene::Init()
{
	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);



	return true;
}
// Main deinitialisation.
// Automatically called inside SceneManager.
bool GameScene::DeInit()
{
	return true;
}

// Update loop. Gone trought once per frame.
bool GameScene::Update(float dt)
{
    return true; // Update succeeded.
}
// Draw loop. All graphics are drawn during this loop.
bool GameScene::Draw()
{
	return true; // Drawing succeeded.
}

//Default constructor for initialising constant variables.
GameScene::GameScene()
{

}
//Default deconstrutor.
GameScene::~GameScene()
{

}

//bool GameScene::MouseOver(uth::GameObject& go)
//{
//	uth::AnimatedSprite* temp = dynamic_cast<uth::AnimatedSprite*>(go.GetComponent("AnimatedSprite"));
//
//	const umath::vector2 inputPos = umath::vector2(
//		uthInput.Common.Position().x - uthEngine.GetWindow().GetSize().x/2,
//		uthInput.Common.Position().y - uthEngine.GetWindow().GetSize().y/2);
//
//#if defined(UTH_SYSTEM_WINDOWS)
//	const umath::vector2 mousePos = umath::vector2(
//		uthInput.Mouse.Position().x - uthEngine.GetWindow().GetSize().x/2,
//		uthInput.Mouse.Position().y - uthEngine.GetWindow().GetSize().y/2);
//#endif
//
//	if( inputPos.x >= go.transform.GetPosition().x - go.transform.GetSize().x/2 &&
//		inputPos.x <= go.transform.GetPosition().x + go.transform.GetSize().x/2 &&
//		inputPos.y >= go.transform.GetPosition().y - go.transform.GetSize().y/2 &&
//		inputPos.y <= go.transform.GetPosition().y + go.transform.GetSize().y/2
//#if defined(UTH_SYSTEM_WINDOWS)
//	||  mousePos.x >= go.transform.GetPosition().x - go.transform.GetSize().x/2 &&
//		mousePos.x <= go.transform.GetPosition().x + go.transform.GetSize().x/2 &&
//		mousePos.y >= go.transform.GetPosition().y - go.transform.GetSize().y/2 &&
//		mousePos.y <= go.transform.GetPosition().y + go.transform.GetSize().y/2
//#endif
//		)
//	{
//		
//		temp->ChangeAnimation(1,1,1,0);
//
//		return true;
//	}
//	else
//	{
//		temp->ChangeAnimation(0,1,0,0);
//	}
//
//	return false;
//}