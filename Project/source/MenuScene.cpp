#include "../include/MenuScene.hpp"

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.
#include <UtH/Engine/Text.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>

// Main initialisation.
// Automatically called inside SceneManager.
bool MenuScene::Init()
{
	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/vertexshader.vert", "Shaders/fragmentshader.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	// Creates new component and gives it to gameobject.
	// Deleting component is done automatically.
	uth::Text *titletext;
	titletext = new uth::Text("bigbottom.ttf",48);
	titletext->AddText(L"MINECART");
	title.AddComponent(titletext);

	uth::AnimatedSprite *animStart, *animHelp;
	uth::Texture *buttonTexture = new uth::Texture("ButtonSheet.tga");
	animStart = new uth::AnimatedSprite(buttonTexture,2,1,2,0.f);
	animHelp = new uth::AnimatedSprite(buttonTexture,2,1,2,0.f);
	startButton.AddComponent(animStart);
	helpButton.AddComponent(animHelp);

	uth::Text *startText, *helpText;
	startText = new uth::Text("bigbottom.ttf",24);
	helpText = new uth::Text("bigbottom.ttf",24);
	startText->AddText(L"START");
	helpText->AddText(L"HELP");
	sbText.AddComponent(startText);
	hbText.AddComponent(helpText);

	//Creating layers
	bg = new uth::Layer("Background", 0);
	main = new uth::Layer("Main", 1);
	instructions = new uth::Layer("Help", 2); 

	//Placing objects to layers
	main->AddGameObject(&title);
	main->AddGameObject(&startButton);
	main->AddGameObject(&helpButton);
	main->AddGameObject(&sbText);
	main->AddGameObject(&hbText);

	title.transform.SetPosition(-192.f,-(uthEngine.GetWindow().GetSize().y/2.f)+72.f);
	startButton.transform.Move(0,-45.f);
	helpButton.transform.Move(0,45.f);
	sbText.transform.Move(-24*2.5f,-45.f);
	hbText.transform.Move(-24*2,45.f);

	return true;
}
// Main deinitialisation.
// Automatically called inside SceneManager.
bool MenuScene::DeInit()
{
	delete main, instructions, bg;
	return true;
}

// Update loop. Gone trought once per frame.
bool MenuScene::Update(float dt)
{
	if(MouseOver(startButton))
	{
			
	}
	else if(MouseOver(helpButton))
	{

	}

	return true; // Update succeeded.
}
// Draw loop. All graphics are drawn during this loop.
bool MenuScene::Draw()
{
	main->Draw(uthEngine.GetWindow());

	return true; // Drawing succeeded.
}

//Default constructor for initialising constant variables.
MenuScene::MenuScene()
{

}
//Default deconstrutor.
MenuScene::~MenuScene()
{

}

bool MenuScene::MouseOver(uth::GameObject& go)
{
	uth::AnimatedSprite* temp = dynamic_cast<uth::AnimatedSprite*>(go.GetComponent("AnimatedSprite"));

	const umath::vector2 inputPos = umath::vector2(
		uthInput.Common.Position().x - uthEngine.GetWindow().GetSize().x/2,
		uthInput.Common.Position().y - uthEngine.GetWindow().GetSize().y/2);

#if defined(UTH_SYSTEM_WINDOWS)
	const umath::vector2 mousePos = umath::vector2(
		uthInput.Mouse.Position().x - uthEngine.GetWindow().GetSize().x/2,
		uthInput.Mouse.Position().y - uthEngine.GetWindow().GetSize().y/2);
#endif

	if( inputPos.x >= go.transform.GetPosition().x - go.transform.GetSize().x/2 &&
		inputPos.x <= go.transform.GetPosition().x + go.transform.GetSize().x/2 &&
		inputPos.y >= go.transform.GetPosition().y - go.transform.GetSize().y/2 &&
		inputPos.y <= go.transform.GetPosition().y + go.transform.GetSize().y/2
#if defined(UTH_SYSTEM_WINDOWS)
	||  mousePos.x >= go.transform.GetPosition().x - go.transform.GetSize().x/2 &&
		mousePos.x <= go.transform.GetPosition().x + go.transform.GetSize().x/2 &&
		mousePos.y >= go.transform.GetPosition().y - go.transform.GetSize().y/2 &&
		mousePos.y <= go.transform.GetPosition().y + go.transform.GetSize().y/2
#endif
		)
	{
		
		temp->ChangeAnimation(1,1,1,0);

		return true;
	}
	else
	{
		temp->ChangeAnimation(0,1,0,0);
	}

	return false;
}