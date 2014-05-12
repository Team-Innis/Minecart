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
	
	touchPos = umath::vector2(player->transform.GetPosition().x, 0);
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