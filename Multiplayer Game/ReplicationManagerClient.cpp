#include "Networks.h"
#include "ReplicationManagerClient.h"

void ReplicationManagerClient::Read(const InputMemoryStream& packet, ModuleNetworkingClient* client)
{
	int size;
	packet >> size;

	for (int i = 0; i < size; ++i)
	{
		uint32 networkId; packet >> networkId;
		if (networkId != -1)
		{

			ReplicationAction action; packet >> action;

			switch (action)
			{
			case ReplicationAction::None:
				break;
			case ReplicationAction::Create:
			{
				GameObject* newGo = Instantiate();

				if (newGo)
				{
					packet >> newGo->position.x;
					packet >> newGo->position.y;

					packet >> newGo->angle;

					packet >> newGo->order;

					packet >> newGo->pivot.x;
					packet >> newGo->pivot.y;

					packet >> newGo->size.x;
					packet >> newGo->size.y;

					packet >> newGo->color.r;
					packet >> newGo->color.g;
					packet >> newGo->color.b;
					packet >> newGo->color.a;

					packet >> newGo->textureType;

					switch (newGo->textureType)
					{
					case TextureType::Spacecraft1:
						newGo->texture = App->modResources->spacecraft1;
						break;
					case TextureType::Spacecraft2:
						newGo->texture = App->modResources->spacecraft2;
						break;
					case TextureType::Spacecraft3:
						newGo->texture = App->modResources->spacecraft3;
						break;
					case TextureType::Laser:
						newGo->texture = App->modResources->laser;
						break;
					default:
						break;
					}

					packet >> newGo->tag;

					App->modLinkingContext->registerNetworkGameObjectWithNetworkId(newGo, networkId);
				}
			}
			break;
			case ReplicationAction::Update:
			{
				GameObject* go = App->modLinkingContext->getNetworkGameObject(networkId);

				if (go)
				{
					packet >> go->position.x;
					packet >> go->position.y;

					packet >> go->angle;
				}
			}
			break;
			case ReplicationAction::Destroy:
			{
				GameObject* go = App->modLinkingContext->getNetworkGameObject(networkId);

				if (go)
				{
					App->modLinkingContext->unregisterNetworkGameObject(go);

					Destroy(go);
				}
			}
			break;
			case ReplicationAction::Notification:
			{
				uint32 data = 0u;
				packet >> data;

				client->SetInputDataFront(data);

			}
			break;
			default:
				break;
			}
		}
	}
}
