#pragma once

enum class RepAction {
	None,
	Create,
	Update,
	Destroy,
};

struct RepCommand
{
	RepAction action;
	uint32 networkId;
};