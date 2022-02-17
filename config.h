#pragma once
#include "header.h"
#include <fstream>

using json = nlohmann::json;

inline json config =
{
	{"aimbot_fov", 3.00f},
	{"aimbot_speed", 15.00f},
	{"aimbot_team", false},
	{"key_aim", 0x5},
	{"key_load", 0x75}
};

class config_t
{
public:
	config_t(){}

	void save()
	{
		std::ofstream o("config.json");
		o << std::setw(4) << config << std::endl;
		printf("created config\n");
	}

	void load()
	{
		std::ifstream in("config.json");

		const auto empty = [&]() -> bool {
			return in.peek() == std::ifstream::traits_type::eof();
		};

		if (in.good() && !empty()) {
			in >> config;
		}
		else {
			save();
		}

		printf("loaded config\n");
	}
};

inline config_t conf;
