#include <GameScene.hpp>

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.
#include <UtH/Engine/Text.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Core/Randomizer.hpp>


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
		tmxSwitches.at(i) = (gameMap.objectGroups.at(0)->GetObjectsByType("switch")->at(i));
	}
	for(int i = 0; i < gameMap.objectGroups.at(1)->GetObjectsByType("railarea")->size(); ++i)
	{
		rails.at(i) = (gameMap.objectGroups.at(1)->GetObjectsByType("railarea")->at(i)->GetRectangle());
		tmxRails.at(i) = (gameMap.objectGroups.at(1)->GetObjectsByType("railarea")->at(i));
	}

    m_minimap.Create(&gameMap, player);
	switchlane = false;

	uth::ParticleTemplate pTemplate;
	pTemplate.SetTexture(new uth::Texture("partikkeli.tga"));
	pTemplate.SetLifetime(0.25f);
	pTemplate.SetSpeed(100, 400);
	pTemplate.SetInitFunction([](uth::Particle &particle, uth::ParticleTemplate &particleTemplate)
	{
		umath::vector2 vec = particle.transform.GetPosition();

		umath::vector2 vec2(uthInput.Common.Position().x + uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindowResolution().x/2, 
			uthInput.Common.Position().y + uthEngine.GetWindow().GetCamera().GetPosition().y - uthEngine.GetWindowResolution().y/2);

		vec = (vec2 - vec);
		vec = vec / vec.getLength();

		particle.direction = (vec * uth::Randomizer::GetFloat(particleTemplate.minSpeed, particleTemplate.maxSpeed));
		particle.direction.RotateDegrees(uth::Randomizer::GetFloat(-35, 35));

		particle.transform.Rotate(particle.direction.getDegrees());

		particle.transform.SetSize(1.5f, uth::Randomizer::GetFloat(4, 16));

		particle.transform.SetPosition(vec2);
		
		float color = uth::Randomizer::GetFloat(0.8f, 1.0f);
		particle.color = umath::vector4(color, color, color, 1.0f);
	});
	
	uth::Affector* affector = new uth::Affector();
	affector->SetUpdateFunc([](uth::Particle &particle, uth::ParticleTemplate &particleTemplate, float dt)
	{
		particle.transform.Move(particle.direction * dt);
	});
	pSystem.transform.SetPosition(mainCamera->GetPosition());
	pSystem.SetTemplate(pTemplate);
	pSystem.AddAffector(affector);


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
	pSystem.transform = player->transform;

	for(int i = 0; i < switches.size(); ++i)
	{
		if(pressFunc(switches.at(i)).first)
		{
			pSystem.Emit(15);
			switchlane = true;
			break;
		}
	}

	if(switchlane)
	{
		umath::rectangle playerRect(player->transform.position.x,player->transform.position.y,
			player->transform.size.x*player->transform.GetScale().x,
			player->transform.size.y*player->transform.GetScale().y);

		for(int i = 0; i < rails.size(); ++i)
		{
			if(rails.at(i).Intersects(playerRect))
			{
				WriteLog("Player touched %s\n", tmxRails.at(i)->GetName().c_str());
				direction = tmxRails.at(i)->GetProperty("direction");
				switchlane = false;
				break;
			}
		}
	}

	if(direction != "")
	{
		if(direction == "right")
		{
			line++;
			direction = "";
		}

		else if(direction == "left")
		{
			line--;
			direction = "";
		}
	}

	pSystem.Update(dt);
    m_minimap.Update(dt);

    return true;
}

bool GameScene::Draw()
{
	gameMap.Draw(uthEngine.GetWindow());
	cart->Draw(uthEngine.GetWindow());
	player->Draw(uthEngine.GetWindow());
	pSystem.Draw(uthEngine.GetWindow());
    m_minimap.Draw(uthEngine.GetWindow());

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