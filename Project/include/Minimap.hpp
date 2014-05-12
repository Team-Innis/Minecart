#pragma once
#ifndef Minimap_HPP
#define Minimap_HPP

#include <UtH\Renderer\RenderTexture.hpp>
#include <UtH\Engine\SpriteBatch.hpp>


namespace uth
{
    namespace TMX
    {
        class Map;
    }
}

class Minimap
{

    Minimap(uth::TMX::Map& map);



private:

    uth::SpriteBatch m_batch;
    uth::RenderTexture m_rtex;
    uth::Camera m_camera;

};

#endif