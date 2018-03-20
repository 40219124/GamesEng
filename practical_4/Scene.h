#pragma once
#include "Entity.h"

class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;
	virtual void Update(const double dt) { _ents.Update(dt); }
	virtual void Render() { _ents.Render(); }
	virtual void Load() = 0;
	std::vector<std::shared_ptr<Entity>> &getEnts() { return _ents.list; }

protected:
	EntityManager _ents;
};