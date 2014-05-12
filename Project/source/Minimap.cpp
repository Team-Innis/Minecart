#include <Minimap.hpp>
#include <UtH/Engine/TMX/Map.hpp>
#include <UtH/Engine/UtHEngine.h>



Minimap::Minimap()
    : m_map(nullptr),
      m_batch(true),
      m_rtex(),
      //m_camera(),
      m_playerObject(nullptr)
{
    
}


bool Minimap::Create(uth::TMX::Map* map, GameObject* playerObject)
{
    //if (!playerObject)
    //    return false;

    m_batch.Clear();
    m_map = map;
    m_playerObject = playerObject;


    m_rtex.Initialize(uthEngine.GetWindow().GetSize(), false);
    m_rtex.GetCamera().SetSize(m_map->GetWidth() * m_map->GetTileWidth(), m_map->GetHeight() * m_map->GetTileHeight());
    //m_rtex.SetViewport(umath::rectangle(0.f, 0.f, m_rtex.GetSize().x, m_rtex.GetSize().y));

    uth::Sprite* sprite = new uth::Sprite(&m_rtex.GetTexture());
    m_rtexSprite.AddComponent(sprite);
    m_rtexSprite.transform.SetPosition((uthEngine.GetWindow().GetSize().x / 2.f) - (m_rtex.GetSize().x / 2.f), 0.f);


    return true;
}


void Minimap::update(float dt)
{
    //if (!m_playerObject)
    //    return;

    
}

void Minimap::draw(uth::RenderTarget& target)
{
    //if (!m_playerObject)
    //    return;

    m_rtex.Clear();

    //uth::Camera& camera = target.GetCamera();
    //uth::Camera tempCamera = camera;

    //camera.SetPosition(0.f, 0.f);
    //camera.SetSize(target.GetSize());

    m_map->Draw(m_rtex);

    m_rtexSprite.Draw(target);

    //target.GetCamera() = tempCamera;

    m_rtex.Update();
}