#pragma once

enum class RepAction {
	None,
	Create,
	Update,
	Destroy,
	NewClient
};

struct RepCommand
{
	RepAction action;
	uint32 networkId;
};