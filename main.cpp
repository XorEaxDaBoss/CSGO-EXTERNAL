#include "header.h"

module_t engine{}, client{};

extern void aimbot_thread();

int main()
{
	mem::proc_handle = mem::get_process("csgo.exe");

	if (mem::proc_handle)
	{
		printf("found process: %i\n", mem::proc_id);

		engine = mem::get_module("engine.dll");
		client = mem::get_module("client.dll");

		printf("engine: %x\nclient: %x\n", engine.base, client.base);

		conf.load();

		std::thread aimbot(aimbot_thread);
		aimbot.join();
	}
	else {
		printf("failed to find csgo\n");
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));
}