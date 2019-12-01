#pragma once

enum class ClientMessage
{
	Hello,
	Input,
	Ping,
	Delivery
};

enum class ServerMessage
{
	Welcome,
	Unwelcome,
	Replication,
	Ping,
	Reply,
	Disconnect
};

enum class Disconnection
{
	Death,
	Input,
};