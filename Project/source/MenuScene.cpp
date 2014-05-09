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
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	// Creates new component and gives it to gameobject.
	// Deleting component is done automatically.
	//uth::Text *titletext;
	//titletext = new uth::Text("bigbottom.ttf",48);
	//titletext->AddText(L"MINECART");
	//title.AddComponent(titletext);
	uth::Sprite *titleSprite= new uth::Sprite("Minecartlogo2.tga");
	title.AddComponent(titleSprite);

	uth::AnimatedSprite *animStart, *animHelp, *animExit;
	uth::Texture *buttonTexture = new uth::Texture("ButtonSheet.tga");
	animStart = new uth::AnimatedSprite(buttonTexture,2,1,2,0.f);
	animHelp = new uth::AnimatedSprite(buttonTexture,2,1,2,0.f);
	animExit = new uth::AnimatedSprite(buttonTexture,2,1,2,0.f);
	startButton.AddComponent(animStart);
	helpButton.AddComponent(animHelp);
    exitButton.AddComponent(animExit);

	uth::Text *startText, *helpText, *exitText;
	startText = new uth::Text("minecart.ttf",24);
	helpText = new uth::Text("minecart.ttf",24);
	exitText = new uth::Text("minecart.ttf",24);
	sbText.AddComponent(startText);
	hbText.AddComponent(helpText);
    exText.AddComponent(exitText);
	startText->AddText(L"START");
	helpText->AddText(L"HELP");
    exitText->AddText(L"EXIT");

	//Creating layers
    bg.reset(new uth::Layer("Background", 0));
    main.reset(new uth::Layer("Main", 1));
    instructions.reset(new uth::Layer("Help", 2)); 

	//Placing objects to layers
	main->AddGameObject(&title);
	main->AddGameObject(&startButton);
	main->AddGameObject(&helpButton);
    main->AddGameObject(&exitButton);
	main->AddGameObject(&sbText);
	main->AddGameObject(&hbText);
    main->AddGameObject(&exText);

	title.transform.SetPosition(0,-(uthEngine.GetWindow().GetSize().y/2.f)+125.f);
	startButton.transform.Move(0,-45.f);
	helpButton.transform.Move(0,45.f);
    exitButton.transform.Move(0, 135.f);
	sbText.transform.Move(0,-45.f);
	hbText.transform.Move(0,45.f);
    exText.transform.Move(0, 135.f);

	return true;
}
// Main deinitialisation.
// Automatically called inside SceneManager.
bool MenuScene::DeInit()
{
	return true;
}

// Update loop. Gone trought once per frame.
bool MenuScene::Update(float dt)
{
    if (MouseOver(startButton) && uthInput.Common.Event() == uth::InputEvent::CLICK)
	{
        uthSceneM.GoToScene(1);
	}
	else if (MouseOver(helpButton))
	{

	}
    else if (MouseOver(exitButton) && uthInput.Common.Event() == uth::InputEvent::CLICK)
	{
        return false;
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