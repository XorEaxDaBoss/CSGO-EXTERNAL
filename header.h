#pragma once

//windows
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <TlHelp32.h>
#include <cassert>
#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>
#include <cmath>

//3rd party
#include "json.hpp"

//ours
#include "memory.h"
#include "netvars.h"
#include "vector.h"
#include "math_class.h"
#include "Entity.h"
#include "config.h"

//modules
extern module_t engine, client;