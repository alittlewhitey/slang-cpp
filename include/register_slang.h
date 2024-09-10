#pragma once
#ifndef REGISTER_SLANG_CPP_H
#define REGISTER_SLANG_CPP_H


#define HOT_RELOAD_ENABLED
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include "slang_cpp.h"

using namespace godot;
using namespace slang_cpp;


void initialize_slang_cpp_module(ModuleInitializationLevel p_level);
void uninitialize_slang_cpp_module(ModuleInitializationLevel p_level);

#endif // REGISTER_SLANG_CPP_H