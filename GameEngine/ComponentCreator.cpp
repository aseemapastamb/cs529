#include "ComponentCreator.h"

ComponentCreator::ComponentCreator()
{
}

ComponentCreator::~ComponentCreator()
{
}

Body* ComponentCreator::CreateBody()
{
	return new Body();
}

Controller* ComponentCreator::CreateController()
{
	return new Controller();
}

Sprite* ComponentCreator::CreateSprite()
{
	return new Sprite();
}

Transform* ComponentCreator::CreateTransform()
{
	return new Transform();
}

UpDown* ComponentCreator::CreateUpDown()
{
	return new UpDown();
}

Health* ComponentCreator::CreateHealth()
{
	return new Health();
}

Ammo* ComponentCreator::CreateAmmo()
{
	return new Ammo();
}

Button* ComponentCreator::CreateButton()
{
	return new Button();
}

AI* ComponentCreator::CreateAI()
{
	return new AI();
}

Spawner* ComponentCreator::CreateSpawner()
{
	return new Spawner();
}