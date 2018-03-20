#include "cmp_sprite.h"
#include "SystemRenderer.h"

//void SpriteComponent::Update(const double dt) {
//	_sprite->setPosition(_parent->getPosition());
//}

void ShapeComponent::Update(const double dt) {
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::Render() {
	Renderer::queue(_shape.get());
}

sf::Shape& ShapeComponent::getShape() const {
	return *_shape;
}

ShapeComponent::ShapeComponent(Entity* p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}