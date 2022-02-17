#include "entity.h"

void entity_list::update()
{
	entities.clear();

	static constexpr auto max_players = 65;

	// local player
	const auto local_address = mem::read<uint32_t>(client.base + signatures::dwLocalPlayer);
	local_player = entity(local_address);

	for (auto i = 1; i < max_players; i++)
	{
		const auto entity_address = mem::read<uint32_t>(client.base + signatures::dwEntityList + 0x10 * i);

		if (!entity_address || entity_address == local_address)
			continue;

		entities.push_back(entity(entity_address));
	}
}

entity* entity_list::get_closest(const vec3& local)
{
	float best_dist = 4096.f;
	float best_fov = 180.f;
	entity* best_ent = nullptr;

	for (auto &ent : entities)
	{
		if (!ent.is_valid())
			continue;

		if (config["aimbot_team"].get<bool>() && local_player.data.team == ent.data.team)
			continue;

		const auto fov = get_fov(local, local_player.bone_pos, ent.bone_pos);

		if (fov > config["aimbot_fov"].get<float>())
		{
			continue; 
		}
			
		const auto distance = local_player.data.origin.DistTo(ent.data.origin);

		if (distance <= best_dist && fov <= best_fov)
		{
			best_fov = fov;
			best_dist = distance;
			best_ent = &ent;
		}
	}

	return best_ent;
}

entity::entity(uint32_t entity_address)
{
	this->data		= mem::read<entity_data>(entity_address);
	this->bone_pos	= get_bone_pos();
}

vec3 entity::get_bone_pos(int bone)
{
	Matrix3x4 boneMatrix = mem::read<Matrix3x4>(data.boneMatrix + (0x30 * bone));

	return vec3(boneMatrix.m[0][3], boneMatrix.m[1][3], boneMatrix.m[2][3]);
}

bool entity::is_valid()
{
	if (!this)
		return false;

	if (this->data.health <= 0)
		return false;

	if (this->data.dormant)
		return false;

	return true;
}
