#pragma once
#include "header.h"

class entity_data
{
public:
	char pad_0000[signatures::m_bDormant]; //0x0000
	bool dormant; //0x00ED
	char pad_00EE[6]; //0x00EE
	int32_t team; //0x00F4
	char pad_00F8[8]; //0x00F8
	int32_t health; //0x0100
	int32_t flags; //0x0104
	char pad_0108[48]; //0x0108
	vec3 origin; //0x0138
	char pad_0144[9572]; //0x0144
	uint32_t boneMatrix; //0x26A8
	char pad_26AC[2448]; //0x26AC
	vec3 aimpunch; //0x303C
	char pad_3048[8]; //0x3048
}; //Size: 0x3050

class entity
{
public:
	entity_data data;

	vec3 bone_pos{};
	//int shots_fired;

	//constructors
	entity(){};
	entity(uint32_t entity_address);

	//methods
	vec3 get_bone_pos(int bone = 8);
	bool is_valid();
};

class entity_list
{
public:
	std::vector<entity> entities { 0 };
	entity local_player;

	//constructors
	entity_list() 
	{
		entities.clear();
	}
	~entity_list() {}

	//methods
	void update();
	entity* get_closest(const vec3& local);
};