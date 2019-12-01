#pragma once

struct Behaviour
{
	GameObject *gameObject = nullptr;

	virtual void start() { }

	virtual void update() { }

	virtual void onInput(const InputController &input) { }

	virtual void onCollisionTriggered(Collider &c1, Collider &c2) { }
};

struct Spaceship : public Behaviour
{
	bool asteroid_hit = false;
	void start() override
	{
		gameObject->tag = (uint32)(Random.next() * UINT_MAX);
	}
	void update() override
	{
		if (asteroid_hit)
		{
			gameObject->hp -= 75;

			asteroid_hit = false;
			if (gameObject->hp <= 0)
				App->modNetServer->DisconectClient(gameObject);
		

		}
		
		
	}
	void onInput(const InputController &input) override
	{
		if (input.horizontalAxis != 0.0f)
		{
			const float rotateSpeed = 180.0f;
			gameObject->angle += input.horizontalAxis * rotateSpeed * Time.deltaTime;
			NetworkUpdate(gameObject);
		}

		if (input.actionDown == ButtonState::Pressed)
		{
			const float advanceSpeed = 200.0f;
			gameObject->position += vec2FromDegrees(gameObject->angle) * advanceSpeed * Time.deltaTime;
			NetworkUpdate(gameObject);
		}

		if (input.actionLeft == ButtonState::Press)
		{
			GameObject * laser = App->modNetServer->spawnBullet(gameObject);
			laser->tag = gameObject->tag;
		}
	}

	void onCollisionTriggered(Collider &c1, Collider &c2) override
	{
		if (c2.type == ColliderType::Laser && c2.gameObject->tag != gameObject->tag)
		{
			NetworkDestroy(c2.gameObject); // Destroy the laser

			// NOTE(jesus): spaceship was collided by a laser
			// Be careful, if you do NetworkDestroy(gameObject) directly,
			// the client proxy will poing to an invalid gameObject...
			// instead, make the gameObject invisible or disconnect the client.

			// Destroy other player
			gameObject->hp = gameObject->hp - 25;
			if(gameObject->hp <= 0)
				App->modNetServer->DisconectClient(c1.gameObject);


		}
		if (c2.type == ColliderType::Asteroid)
		{
			asteroid_hit = true;
			NetworkDestroy(c2.gameObject);
		}
		if (c2.type == ColliderType::Wall)
		{
			gameObject->position -= gameObject->position / 100;
		}
	}
};

struct Laser : public Behaviour
{
	float secondsSinceCreation = 0.0f;

	void update() override
	{
		const float pixelsPerSecond = 1000.0f;
		gameObject->position += vec2FromDegrees(gameObject->angle) * pixelsPerSecond * Time.deltaTime;

		secondsSinceCreation += Time.deltaTime;

		NetworkUpdate(gameObject);

		const float lifetimeSeconds = 2.0f;
		if (secondsSinceCreation > lifetimeSeconds) NetworkDestroy(gameObject);
	}

	void onCollisionTriggered(Collider &c1, Collider &c2) override
	{
		if (c2.type == ColliderType::Wall || c2.type == ColliderType::Cover)
		{
			NetworkDestroy(gameObject);
		}
		if (c2.type == ColliderType::Asteroid)
		{
			NetworkDestroy(c2.gameObject);
			NetworkDestroy(gameObject);
		}
	}
};

struct Asteroid : public Behaviour
{
	float secondsSinceCreation = 0.0f;

	
	void update() override
	{
		const float speed = 200.0f;
		gameObject->position += vec2FromDegrees(gameObject->angle) * speed * Time.deltaTime;

		secondsSinceCreation += Time.deltaTime;

		NetworkUpdate(gameObject);

		const float lifetimeSeconds = 10.0f;
		if (secondsSinceCreation > lifetimeSeconds) NetworkDestroy(gameObject);
	}

};
