#include <GameScene.hpp>

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.
#include <UtH/Engine/Text.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>


bool GameScene::Init()
{
	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);
    
	gameMap.LoadFromFile("map.tmx");
	const int mapOffX = (gameMap.GetTileWidth()*gameMap.GetWidth())
			- (gameMap.GetTileWidth()/2)- (gameMap.GetTileWidth()*2);
	const int mapOffY = (gameMap.GetTileHeight()*gameMap.GetHeight())
		- (gameMap.GetTileWidth()/2) /*- (uthEngine.GetWindowResolution().y/2)*/;
	offsetY = mapOffY;
	mainCamera = new uth::Camera(umath::vector2(mapOffX,mapOffY),uthEngine.GetWindowResolution());
	uthEngine.GetWindow().SetCamera(mainCamera);

	speed = 100.f;
	line = 3;

	player = new uth::GameObject();
	cart = new uth::GameObject();
	cart->AddComponent(new uth::AnimatedSprite(new uth::Texture("minecartAnim.tga"),4,4,1));
	player->AddComponent(new uth::Sprite("player.tga"));
	player->transform.SetScale(0.5f);
	cart->transform.SetScale(0.5f);

	for(int i = 0; i < gameMap.objectGroups.at(0)->GetObjectsByType("switch")->size(); ++i)
	{
		switches.at(i) = (gameMap.objectGroups.at(0)->GetObjectsByType("switch")->at(i)->GetRectangle());
		tmxObjects.at(i) = (gameMap.objectGroups.at(0)->GetObjectsByType("switch")->at(i));
	}

	return true;
}

bool GameScene::DeInit()
{
	delete mainCamera;
	delete player;
	delete cart;

	return true;
}


bool GameScene::Update(float dt)
{
	speed += dt;
	mainCamera->Scroll(0,-dt*speed);

	player->transform.SetPosition(line*gameMap.GetTileWidth(),mainCamera->GetPosition().y);
	cart->transform.SetPosition(player->transform.GetPosition());

	for(int i = 0; i < switches.size(); ++i)
	{
		if(pressFunc(switches.at(i)).first)
		{
			WriteLog("Touched %s should move to lane %s\n",
				tmxObjects.at(i)->GetName().c_str(), tmxObjects.at(i)->GetProperty("lane").c_str());
		}
	}

    return true;
}

bool GameScene::Draw()
{
	gameMap.Draw(uthEngine.GetWindow());
	cart->Draw(uthEngine.GetWindow());
	player->Draw(uthEngine.GetWindow());


	return true;
}


GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

const std::pair<bool, umath::vector2> GameScene::pressFunc(const umath::rectangle &rect)
{
	if(uthInput.Common.Event() == uth::InputEvent::CLICK)
	{
		umath::vector2 pos = umath::vector2();
		pos.x = uthInput.Common.Position().x;
		pos.y = uthInput.Common.Position().y + mainCamera->transform.position.y
			- uthEngine.GetWindowResolution().y/2 + gameMap.GetTileHeight()/2;

		if(pos.x > rect.x && pos.y > rect.y &&
			pos.x < rect.x+rect.width && pos.y < rect.y+rect.height)
		{
			return std::pair<bool, umath::vector2>(true, pos);
		}

	}

	return std::pair<bool, umath::vector2>(false, umath::vector2());
}