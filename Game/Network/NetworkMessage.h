#pragma once

enum MSGID
{
	WELCOME = 0,
	GAME,
	ENTITY
};

struct WelcomeMessage
{
	int msgID;
	unsigned int seed;
};

struct GameMessage
{
	int msgID;
	int totalEntities;
};

struct EntityMessage
{
	short id;
	char entityType;
	bool isAlive;
	Vector2f position;
	Vector2f orientation;
	float rotation;
	Vector2f velocity;
	//Vector2f totalForce;
};