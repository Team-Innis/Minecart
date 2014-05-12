#pragma once
#ifndef Minimap_HPP
#define Minimap_HPP

#include <UtH/Renderer/RenderTexture.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Engine/GameObject.hpp>


namespace uth
{
    namespace TMX
    {
        class Map;
    }
}

class Minimap : public uth::GameObject
{
public:

    Minimap();

    bool Create(uth::TMX::Map* map, GameObject* playerObject);


private:

    virtual void update(float dt);

    virtual void draw(uth::RenderTarget& target);


    uth::TMX::Map* m_map;
    uth::SpriteBatch m_batch;
    uth::RenderTexture m_rtex;
    uth::GameObject m_rtexSprite;
    //uth::Camera m_camera;
    uth::GameObject* m_playerObject;

};

#endif