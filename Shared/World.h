#pragma once

// TODO: Go and actually make these. The IDE is throwing a piss fit regardless.
class LuaEngine;
class Item;

class Entity;	// If it walks and talks like an X...
class NPC : public Entity;
class Player : public Entity;

template<class T> class Registry;	// For O(1) lookups of hashed reference ID strings.
class ItemRegistry : public Registry<Item>;
class NPCRegistry : public Registry<NPC>;


/* 
	The core implementation of in-game logic.
	Clients running a local server will have their own World instance.
	Clients connecting to a remote host will send requests and recieve replies.
*/
class World
{
private:
	LuaEngine LuaInstance;
	ItemRegistry ItemDatabase;
	NPCRegistry NPCDatabase;
public:
};