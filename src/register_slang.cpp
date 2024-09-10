
#ifndef REGISTER_SLANG_CPP_SRC
#define REGISTER_SLANG_CPP_SRC
#include"../include/register_slang.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#define SLANG_BIND_CLASS(class)\
    GDREGISTER_CLASS(slang_cpp::slang_##class)        \
    GDREGISTER_CLASS(slang_cpp::slang_##class##_PTR)\
    GDREGISTER_CLASS(slang_cpp::slang_##class##_VECTOR)
#define SLANG_BIND_ABSTRACT_CLASS(class)\
    GDREGISTER_ABSTRACT_CLASS(slang_cpp::slang_##class)        \
    GDREGISTER_CLASS(slang_cpp::slang_##class##_PTR)\
    GDREGISTER_CLASS(slang_cpp::slang_##class##_VECTOR)

void initialize_slang_cpp_module(ModuleInitializationLevel p_level){
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
    SLANG_BIND_CLASS(SlangObject)
    SLANG_BIND_CLASS(NULL)
    SLANG_BIND_CLASS(INT)
    SLANG_BIND_CLASS(SIZE)
    SLANG_BIND_CLASS(BOOL)
    SLANG_BIND_CLASS(DOUBLE)
    SLANG_BIND_CLASS(SlangRef)
    GDREGISTER_CLASS(slang_cpp::slang_global)
    GDREGISTER_CLASS(slang_cpp::slang_VOID_PTR)
    SLANG_BIND_ABSTRACT_CLASS(IUnknown)
    SLANG_BIND_ABSTRACT_CLASS(IGlobalSession)
    SLANG_BIND_ABSTRACT_CLASS(ISession)
    SLANG_BIND_ABSTRACT_CLASS(IBlob)
    SLANG_BIND_ABSTRACT_CLASS(ICastable)
    SLANG_BIND_ABSTRACT_CLASS(IFileSystem)
    SLANG_BIND_ABSTRACT_CLASS(IFileSystemExt)
    SLANG_BIND_ABSTRACT_CLASS(IMutableFileSystem)
    SLANG_BIND_ABSTRACT_CLASS(ISharedLibrary)
    SLANG_BIND_ABSTRACT_CLASS(ISharedLibraryLoader)
    SLANG_BIND_ABSTRACT_CLASS(IComponentType)
    SLANG_BIND_ABSTRACT_CLASS(ITypeConformance)
    SLANG_BIND_ABSTRACT_CLASS(IEntryPoint)
    SLANG_BIND_ABSTRACT_CLASS(IModule)
    SLANG_BIND_ABSTRACT_CLASS(IWriter)
    SLANG_BIND_ABSTRACT_CLASS(IProfiler)
    SLANG_BIND_ABSTRACT_CLASS(ICompileRequest)
    SLANG_BIND_CLASS(UUID)
    SLANG_BIND_CLASS(CompilerOptionValue)
    SLANG_BIND_CLASS(CompilerOptionEntry)
    SLANG_BIND_CLASS(PreprocessorMacroDesc)
    SLANG_BIND_CLASS(TargetDesc)
    SLANG_BIND_CLASS(SessionDesc)
    SLANG_BIND_CLASS(Modifier)
    SLANG_BIND_CLASS(UserAttribute)
    SLANG_BIND_CLASS(FunctionReflection)
    SLANG_BIND_CLASS(DeclReflection)
    SLANG_BIND_CLASS(GenericReflection)
    SLANG_BIND_CLASS(VariableReflection)
    SLANG_BIND_CLASS(VariableLayoutReflection)
    SLANG_BIND_CLASS(TypeReflection)
    SLANG_BIND_CLASS(SlangReflectionGeneric)
    SLANG_BIND_CLASS(TypeLayoutReflection)
    SLANG_BIND_CLASS(TypeParameterReflection)
    SLANG_BIND_CLASS(EntryPointReflection)
    SLANG_BIND_CLASS(ShaderReflection)
    SLANG_BIND_CLASS(SpecializationArg)


    Engine::get_singleton()->register_singleton("slang_global",slang_cpp::slang_global::get_singleton());
}
void uninitialize_slang_cpp_module(ModuleInitializationLevel p_level){
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
    Engine::get_singleton()->unregister_singleton("slang_global");
}
//extern "C" {
//// Initialization.
//GDExtensionBool GDE_EXPORT init_library(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
//
//	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
//
//	init_obj.register_initializer(initialize_changeScene_module);
//	init_obj.register_terminator(uninitialize_changeScene_module);
//	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
//
//	return init_obj.init();
//}
//}

#endif //REGISTER_SLANG_CPP_SRC