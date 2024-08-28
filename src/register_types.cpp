
#ifndef REGISTER_TYPES_SRC
#define REGISTER_TYPES_SRC
#include"../include/register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

void initialize_changeScene_module(ModuleInitializationLevel p_level){
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
    GDREGISTER_CLASS(slang_cpp::slang_SlangObject)
    GDREGISTER_CLASS(slang_cpp::slang_global)
    GDREGISTER_CLASS(slang_cpp::slang_NULL)
    GDREGISTER_CLASS(slang_cpp::slang_SIZE)
    GDREGISTER_CLASS(slang_cpp::slang_BOOL)
    GDREGISTER_CLASS(slang_cpp::slang_DOUBLE)
    GDREGISTER_CLASS(slang_cpp::slang_SlangRef)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IUnknown)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IGlobalSession)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_ISession)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IBlob)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_ICastable)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IFileSystem)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IFileSystemExt)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IMutableFileSystem)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_ISharedLibrary)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_ISharedLibraryLoader)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IComponentType)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_ITypeConformance)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IEntryPoint)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IModule)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IWriter)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_IProfiler)
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_ICompileRequest)
    GDREGISTER_CLASS(slang_cpp::slang_UUID)
    GDREGISTER_CLASS(slang_cpp::slang_CompilerOptionValue)
    GDREGISTER_CLASS(slang_cpp::slang_CompilerOptionEntry)
    GDREGISTER_CLASS(slang_cpp::slang_PreprocessorMacroDesc)
    GDREGISTER_CLASS(slang_cpp::slang_TargetDesc)
    GDREGISTER_CLASS(slang_cpp::slang_SessionDesc)
    GDREGISTER_CLASS(slang_cpp::slang_Modifier)
    GDREGISTER_CLASS(slang_cpp::slang_UserAttribute)
    GDREGISTER_CLASS(slang_cpp::slang_FunctionReflection)
    GDREGISTER_CLASS(slang_cpp::slang_DeclReflection)
    GDREGISTER_CLASS(slang_cpp::slang_GenericReflection)
    GDREGISTER_CLASS(slang_cpp::slang_VariableReflection)
    GDREGISTER_CLASS(slang_cpp::slang_VariableLayoutReflection)
    GDREGISTER_CLASS(slang_cpp::slang_TypeReflection)
    GDREGISTER_CLASS(slang_cpp::slang_SlangReflectionGeneric)
    GDREGISTER_CLASS(slang_cpp::slang_TypeLayoutReflection)
    GDREGISTER_CLASS(slang_cpp::slang_TypeParameterReflection)
    GDREGISTER_CLASS(slang_cpp::slang_EntryPointReflection)
    GDREGISTER_CLASS(slang_cpp::slang_ShaderReflection)
    GDREGISTER_CLASS(slang_cpp::slang_SpecializationArg)


    Engine::get_singleton()->register_singleton("slang_global",slang_cpp::slang_global::get_singleton());
}
void uninitialize_changeScene_module(ModuleInitializationLevel p_level){
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
    Engine::get_singleton()->unregister_singleton("slang_global");
}
extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT init_library(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {

	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_changeScene_module);
	init_obj.register_terminator(uninitialize_changeScene_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}

#endif //REGISTER_TYPES_SRC