#include "Networks.h"
#include "ModuleNetworkingServer.h"

GameObject *spaceTopLeft = nullptr;
GameObject *spaceTopRight = nullptr;
GameObject *spaceBottomLeft = nullptr;
GameObject *spaceBottomRight = nullptr;
GameObject *wall1 = nullptr;
GameObject *wall2 = nullptr;
GameObject *wall3 = nullptr;
GameObject *wall4 = nullptr;

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
	wall1 = App->modNetServer->spawnWalls();
	wall1->size = { 50,800 };
	wall1->position = { -760,0 };
	//top wall
	wall2 = App->modNetServer->spawnWalls();
	wall2->size = { 50,1470 };
	wall2->position = { 0,-390 };
	wall2->angle = 90.0f;
	//right wall
	wall3 = App->modNetServer->spawnWalls();
	wall3->size = { 50,800 };
	wall3->position = { 760,0 };
	//bottom wall
	wall4 = App->modNetServer->spawnWalls();
	wall4->size = { 50,1470 };
	wall4->position = { 0,390 };
	wall4->angle = 90.0f;
	
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
}
