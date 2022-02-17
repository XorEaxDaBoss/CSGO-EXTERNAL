#include "header.h"

void aimbot_thread()
{
	entity_list entlist;
	
	while (true)
	{
		auto pViewMatrix	= mem::read<Matrix4x4>(client.base + signatures::dwViewMatrix);
		auto client_state	= mem::read<uintptr_t>(engine.base + signatures::dwClientState);
		auto local_view		= mem::read<vec3>(client_state + signatures::dwClientState_ViewAngles);

		entlist.update();

		local_view += entlist.local_player.data.aimpunch * 2;
		auto target = entlist.get_closest(local_view);

		const int aim_key = config["key_aim"].get<int>(), load_key = config["key_load"].get<int>();

		if (GetAsyncKeyState(aim_key) & 0x8000 && target->is_valid())
		{
#ifdef rpm_only
			vec3 screen {0,0,0};
			if (!WorldToScreen(target->bone_pos, screen, &pViewMatrix))
				continue;

			screen.x /= config["aimbot_speed"].get<float>();
			screen.y /= config["aimbot_speed"].get<float>();

			INPUT in { 0 };
			in.type = INPUT_MOUSE;
			in.mi.dx = screen.x;
			in.mi.dy = screen.y;
			in.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
			SendInput(1, &in, sizeof(INPUT));
#else
			vec3 dir = entlist.local_player.bone_pos - target->bone_pos;
			vector_normalize(dir);

			vec3 aim_angle;
			vector_angles(dir, aim_angle);

			smooth_angle(local_view, aim_angle, config["aimbot_speed"].get<float>());
			clamp_angle(aim_angle);

			aim_angle -= entlist.local_player.data.aimpunch * 2;
			mem::write<vec3>(client_state + signatures::dwClientState_ViewAngles, aim_angle);
#endif
		}

		if (GetAsyncKeyState(load_key) & 0x1)
		{
			entlist.entities.clear();
			conf.load();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}
