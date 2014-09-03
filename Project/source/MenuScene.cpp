#include <MenuScene.hpp>

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.
#include <UtH/Engine/Text.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Core/Randomizer.hpp>
#include <vector>

// Main initialisation.
// Automatically called inside SceneManager.
bool MenuScene::Init()
{
    drawHelp = false;

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
    uth::Sprite *bgSprite = new uth::Sprite("title.tga");
    background.AddComponent(bgSprite);

    umath::vector2 res = uthEngine.GetWindow().GetSize();
    background.transform.SetScale(res.x / bgSprite->GetSize().x, res.y / bgSprite->GetSize().y);

	uth::Sprite *titleSprite= new uth::Sprite("titleText.tga");
	title.AddComponent(titleSprite);
    title.transform.SetScale(0.66f, 0.66f);

	uth::AnimatedSprite *animStart, *animHelp, *animExit;
	uth::Texture *buttonTexture = new uth::Texture("ButtonSheet.tga");
	animStart = new uth::AnimatedSprite(buttonTexture,2,1,2,0.f);
	animHelp = new uth::AnimatedSprite(buttonTexture,2,1,2,0.f);
	animExit = new uth::AnimatedSprite(buttonTexture,2,1,2,0.f);
	startButton.AddComponent(animStart);
	helpButton.AddComponent(animHelp);
    exitButton.AddComponent(animExit);

	uth::Text *startText, *helpText, *exitText, *bounceText;
	startText = new uth::Text("minecart.ttf",24);
	helpText = new uth::Text("minecart.ttf",24);
	exitText = new uth::Text("minecart.ttf",24);
	bounceText = new uth::Text("kenpixel.ttf",24);
	sbText.AddComponent(startText);
	hbText.AddComponent(helpText);
    exText.AddComponent(exitText);
    jumpText.AddComponent(bounceText);
	startText->AddText(L"START");
	helpText->AddText(L"HELP");
    exitText->AddText(L"EXIT");

    std::wstring strings[] =
    {
        L"Legal in Finland",
        L"Minecart!",
        L"wow such game",
        L"weeeeeeeeeeee",
        L"Shepard's favorite!",
        L"Under the Hood",
        L"100% more coal!",
        L"HL3 confirmed!",
        L"std::vector<UtH>",
        L"No annoying sounds!",
        L"Cage approved!",
        L"Technological superiority",
        L"TEAM-INNIS!"
    };

    uth::Randomizer::SetSeed();
    const int random = uth::Randomizer::GetInt(0, (sizeof(strings) / sizeof(std::wstring)) * 100);
    bounceText->AddText(strings[random % ((sizeof(strings) / sizeof(std::wstring)) - 1)], umath::vector4(1, 0.96f, 0.4, 1.f));

	//Creating layers
    bg.reset(new uth::Layer("Background", 0));
    main.reset(new uth::Layer("Main", 1));
    instructions.reset(new uth::Layer("Help", 2)); 

	//Placing objects to layers
    bg->AddGameObject(&background);
	main->AddGameObject(&title);
	main->AddGameObject(&startButton);
	main->AddGameObject(&helpButton);
    main->AddGameObject(&exitButton);
	main->AddGameObject(&sbText);
	main->AddGameObject(&hbText);
    main->AddGameObject(&exText);
    main->AddGameObject(&jumpText);
    
    const float left = -res.x / 2.f;
    const float x = left + 365.f;

	title.transform.SetPosition(x,-(uthEngine.GetWindow().GetSize().y/2.f)+125.f);

	startButton.transform.Move(x,-45.f);
	helpButton.transform.Move(x,45.f);
    exitButton.transform.Move(x, 135.f);
	sbText.transform.Move(x,-45.f);
	hbText.transform.Move(x,45.f);
    exText.transform.Move(x, 135.f);
    jumpText.transform.Move(title.transform.GetPosition().x + 250.f, title.transform.GetPosition().y + 25.f);
    jumpText.transform.Rotate(26.f);

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
    if (drawHelp)
    {
        if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Escape))
            drawHelp = false;
    }
    else
    {
        bool click = uthInput.Common.Event() == uth::InputEvent::CLICK;

        static float sine = 0.f;
        sine += 6.f * dt;
        float wave = 0.22f * std::sinf(sine);

        jumpText.transform.SetScale(0.9f + std::abs(wave));

        if (MouseOver(startButton) && click)
	    {
            uthSceneM.GoToScene(1);
	    }
	    else if (MouseOver(helpButton) && click)
	    {
            drawHelp = true;
	    }
        else if (MouseOver(exitButton) && click)
	    {
            return false;
	    }
    }

	return true; // Update succeeded.
}
// Draw loop. All graphics are drawn during this loop.
bool MenuScene::Draw()
{
    bg->Draw(uthEngine.GetWindow());

    if (drawHelp)
        instructions->Draw(uthEngine.GetWindow());
    else
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
	uth::AnimatedSprite* temp = go.GetComponent<uth::AnimatedSprite>("AnimatedSprite");

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