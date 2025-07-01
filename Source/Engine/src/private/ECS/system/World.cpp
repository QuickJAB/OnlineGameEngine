#include "ECS/system/World.h"

#include <print>

using namespace std;

const uint32_t World::createEntity()
{
    // Get the next unique id from the world and return it then increment the counter
    const uint32_t id = m_nextEntityId;
    ++m_nextEntityId;
    return id;
}

void World::update(float in_dt)
{
    if (m_transformComps.getSize() <= 0) return;

    const std::vector<TransformComp*>* transforms = m_transformComps.getComponents();
    for (auto it = transforms->begin(); it != transforms->end(); ++it)
    {
        TransformComp* transformComp = *it;
        
        // Process transform data here
    }
}
