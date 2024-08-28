#pragma once
#ifndef REGISTER_TYPES_H
#define REGISTER_TYPES_H


#define HOT_RELOAD_ENABLED
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include "slang_cpp.h"

using namespace godot;
using namespace slang_cpp;


void initialize_example_module(ModuleInitializationLevel p_level);
void uninitialize_example_module(ModuleInitializationLevel p_level);

#endif // REGISTER_TYPES_H