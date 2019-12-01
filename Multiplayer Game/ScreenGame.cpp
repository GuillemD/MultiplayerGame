#include "Networks.h"
#include "ModuleNetworkingServer.h"

GameObject *spaceTopLeft = nullptr;
GameObject *spaceTopRight = nullptr;
GameObject *spaceBottomLeft = nullptr;
GameObject *spaceBottomRight = nullptr;

//outer walls
GameObject *wall1 = nullptr;
GameObject *wall2 = nullptr;
GameObject *wall3 = nullptr;
GameObject *wall4 = nullptr;

//cover
GameObject *coverTopLeft = nullptr;
GameObject *coverTopRight = nullptr;
GameObject *coverBotLeft = nullptr;
GameObject *coverBotRight = nullptr;

GameObject *coverCenter1 = nullptr;


void ScreenGame::enable()
{
	if (isServer)
	{
		App->modNetServer->setListenPort(serverPort);
		App->modNetServer->setEnabled(true);
	}
	else
	{
		App->modNetClient->setServerAddress(serverAddress, serverPort);
		App->modNetClient->setPlayerInfo(playerName, spaceshipType);
		App->modNetClient->setEnabled(true);
	}

	spaceTopLeft = Instantiate();
	spaceTopLeft->texture = App->modResources->space;
	spaceTopLeft->order = -1;
	spaceTopRight = Instantiate();
	spaceTopRight->texture = App->modResources->space;
	spaceTopRight->order = -1;
	spaceBottomLeft = Instantiate();
	spaceBottomLeft->texture = App->modResources->space;
	spaceBottomLeft->order = -1;
	spaceBottomRight = Instantiate();
	spaceBottomRight->texture = App->modResources->space;
	spaceBottomRight->order = -1;

	//left wall
	wall1 = Instantiate();
	wall1->texture = App->modResources->wall;
	wall1->textureType = TextureType::Wall;
	wall1->collider = App->modCollision->addCollider(ColliderType::Wall, wall1);
	wall1->size = { 50,800 };
	wall1->position = { -760,0 };
	//top wall
	wall2 = Instantiate();
	wall2->texture = App->modResources->wall;
	wall2->textureType = TextureType::Wall;
	wall2->collider = App->modCollision->addCollider(ColliderType::Wall, wall2);
	wall2->size = { 50,1470 };
	wall2->position = { 0,-390 };
	wall2->angle = 90.0f;
	//right wall
	wall3 = Instantiate();
	wall3->texture = App->modResources->wall;
	wall3->textureType = TextureType::Wall;
	wall3->collider = App->modCollision->addCollider(ColliderType::Wall, wall3);
	wall3->size = { 50,800 };
	wall3->position = { 760,0 };
	//bottom wall
	wall4 = Instantiate();
	wall4->texture = App->modResources->wall;
	wall4->textureType = TextureType::Wall;
	wall4->collider = App->modCollision->addCollider(ColliderType::Wall, wall4);
	wall4->size = { 50,1470 };
	wall4->position = { 0,390 };
	wall4->angle = 90.0f;

	//top left cover
	coverTopLeft = Instantiate();
	coverTopLeft->texture = App->modResources->wall;
	coverTopLeft->textureType = TextureType::Wall;
	coverTopLeft->collider = App->modCollision->addCollider(ColliderType::Wall, coverTopLeft);
	coverTopLeft->size = { 20,110 };
	coverTopLeft->position = { -490,-180 };

	//top right cover
	coverTopRight = Instantiate();
	coverTopRight->texture = App->modResources->wall;
	coverTopRight->textureType = TextureType::Wall;
	coverTopRight->collider = App->modCollision->addCollider(ColliderType::Wall, coverTopRight);
	coverTopRight->size = { 20,110 };
	coverTopRight->position = { 490,-180 };

	//bot left cover
	coverBotLeft = Instantiate();
	coverBotLeft->texture = App->modResources->wall;
	coverBotLeft->textureType = TextureType::Wall;
	coverBotLeft->collider = App->modCollision->addCollider(ColliderType::Wall, coverBotLeft);
	coverBotLeft->size = { 20,110 };
	coverBotLeft->position = { -490, 180 };

	//bot right cover
	coverBotRight = Instantiate();
	coverBotRight->texture = App->modResources->wall;
	coverBotRight->textureType = TextureType::Wall;
	coverBotRight->collider = App->modCollision->addCollider(ColliderType::Wall, coverBotRight);
	coverBotRight->size = { 20,110 };
	coverBotRight->position = { 490,180 };

	//center
	coverCenter1 = Instantiate();
	coverCenter1->texture = App->modResources->wall;
	coverCenter1->textureType = TextureType::Wall;
	coverCenter1->collider = App->modCollision->addCollider(ColliderType::Wall, coverCenter1);
	coverCenter1->size = { 20,170 };
	coverCenter1->position = { 20,-20 };



}

void ScreenGame::update()
{
	if (!(App->modNetServer->isConnected() || App->modNetClient->isConnected()))
	{
		App->modScreen->swapScreensWithTransition(this, App->modScreen->screenMainMenu);
	}
	else
	{
		if (!isServer)
		{
			vec2 camPos = App->modRender->cameraPosition;
			vec2 bgSize = spaceTopLeft->texture->size;
			spaceTopLeft->position = bgSize * floor(camPos / bgSize);
			spaceTopRight->position = bgSize * (floor(camPos / bgSize) + vec2{ 1.0f, 0.0f });
			spaceBottomLeft->position = bgSize * (floor(camPos / bgSize) + vec2{ 0.0f, 1.0f });
			spaceBottomRight->position = bgSize * (floor(camPos / bgSize) + vec2{ 1.0f, 1.0f });;
		}
	}
}

void ScreenGame::gui()
{
}

void ScreenGame::disable()
{
	Destroy(spaceTopLeft);
	Destroy(spaceTopRight);
	Destroy(spaceBottomLeft);
	Destroy(spaceBottomRight);

	Destroy(wall1);
	Destroy(wall2);
	Destroy(wall3);
	Destroy(wall4);

	Destroy(coverTopLeft);
	Destroy(coverTopRight);
	Destroy(coverBotLeft);
	Destroy(coverBotRight);

	Destroy(coverCenter1);

}
