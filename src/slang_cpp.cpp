#ifndef SLANG_CPP_SRC
#define SLANG_CPP_SRC
#include "../include/slang_cpp.h"
namespace slang_cpp{
    slang_global* slang_global::single_ptr = nullptr;


    slang_ShaderReflection *slang_IComponentType::_getLayout(SlangInt targetIndex, slang_IBlob_PTR *blob) {
        return static_cast<slang_ShaderReflection *>(this->getLayout(targetIndex, reinterpret_cast<ISlangBlob **>(blob == nullptr? nullptr: &blob->value)));
    }

    SlangResult
    slang_IComponentType::_specialize(slang_SpecializationArg *specializationArgs, SlangInt specializationArgCount,
                                     slang_IComponentType_PTR*specializedOut, slang_IBlob_PTR *outDiagnostics) {
        return this->specialize(
                static_cast<slang::SpecializationArg *>(specializationArgs), specializationArgCount, reinterpret_cast<IComponentType **>(&specializedOut->value), reinterpret_cast<ISlangBlob **>(outDiagnostics == nullptr ? nullptr : &outDiagnostics->value));
    }

    SlangResult slang_IComponentType::_linkWithOptions(slang_IComponentType_PTR*outLinkedComponentType,
                                                      uint32_t compilerOptionEntryCount,
                                                      slang_CompilerOptionEntry *compilerOptionEntries,
                                                      slang_IBlob_PTR *outDiagnostics) {
        return this->linkWithOptions(reinterpret_cast<IComponentType **>(&outLinkedComponentType->value), compilerOptionEntryCount,
                                                     static_cast<slang::CompilerOptionEntry *>(compilerOptionEntries), reinterpret_cast<ISlangBlob **>(outDiagnostics == nullptr ? nullptr : &outDiagnostics->value));
    }


    slang_DeclReflection *slang_IModule::_getModuleReflection(slang_NULL*null) {
        return static_cast<slang_DeclReflection *>(this->getModuleReflection());
    }

    slang_IModule *slang_ISession::_loadModule(godot::String moduleName, slang_IBlob_PTR *outDiagnostics) {
        return static_cast<slang_IModule *>(this->loadModule(moduleName.utf8().get_data(),
                                                                              reinterpret_cast<slang::IBlob **>(&outDiagnostics->value)));
    }

    slang_IModule *slang_ISession::_loadModuleFromSource(godot::String moduleName, godot::String path, slang_IBlob *source,slang_IBlob_PTR *outDiagnostics) {
        return dynamic_cast<slang_IModule *>(this->loadModuleFromSource(moduleName.utf8().get_data(),
                                                                                         path.utf8().get_data(),
                                                                                         dynamic_cast<slang::IBlob *>(source),
                                                                                         reinterpret_cast<ISlangBlob **>(&outDiagnostics->value)));
    }

    slang_TypeReflection *
    slang_ISession::_specializeType(slang_TypeReflection *type_, slang_SpecializationArg *specializationArgs,
                                   SlangInt specializationArgCount, slang_IBlob_PTR*outDiagnostics) {
        return static_cast<slang_TypeReflection *>(this->specializeType(type_, specializationArgs,
                                                                                         specializationArgCount,
                                                                                         reinterpret_cast<slang::IBlob **>(&outDiagnostics->value)));
    }

    slang_TypeLayoutReflection *
    slang_ISession::_getTypeLayout(slang_TypeReflection *type_, SlangInt targetIndex, slang_LayoutRules rules,
                                  slang_IBlob_PTR*outDiagnostics) {
        return static_cast<slang_TypeLayoutReflection *>(this->getTypeLayout(type_, targetIndex,
                                                                                              static_cast<slang::LayoutRules>(rules),
                                                                                              reinterpret_cast<slang::IBlob **>(&outDiagnostics->value)));
    }

    slang_TypeReflection *
    slang_ISession::_getContainerType(slang_TypeReflection *elementType, slang_ContainerType containerType,
                                     slang_IBlob_PTR *outDiagnostics) {
        return static_cast<slang_TypeReflection *>(this->getContainerType(
                static_cast<slang::TypeReflection *>(elementType),
                static_cast<slang::ContainerType>(containerType), reinterpret_cast<slang::IBlob **>(&outDiagnostics->value)));
    }

    slang_TypeReflection *slang_ISession::_getDynamicType(slang_NULL*) {
        return static_cast<slang_TypeReflection *>(this->getDynamicType());
    }

    SlangResult slang_ISession::_getTypeRTTIMangledName(slang_TypeReflection *type, slang_IBlob_PTR *outNameBlob) {
        return this->getTypeRTTIMangledName(static_cast<slang::TypeReflection*>(type), reinterpret_cast<slang::IBlob**>(&outNameBlob->value));
    }

    SlangResult slang_ISession::_getTypeConformanceWitnessMangledName(slang_TypeReflection *type,
                                                                     slang_TypeReflection *interfaceType,
                                                                     slang_IBlob_PTR *outNameBlob) {
        return this->getTypeConformanceWitnessMangledName(static_cast<slang::TypeReflection*>(type), static_cast<slang::TypeReflection*>(interfaceType), reinterpret_cast<slang::IBlob**>(outNameBlob->get_value()));
    }

    SlangResult slang_ISession::_getTypeConformanceWitnessSequentialID(slang_TypeReflection *type,
                                                                      slang_TypeReflection *interfaceType,
                                                                      slang_SIZE*outId) {
        uint32_t id;
        SlangResult res = this->getTypeConformanceWitnessSequentialID(static_cast<slang::TypeReflection*>(type), static_cast<slang::TypeReflection*>(interfaceType), &id);
        outId->set_value(id);
        return res;
    }

    SlangResult
    slang_ISession::_createTypeConformanceComponentType(slang_TypeReflection *type, slang_TypeReflection *interfaceType,
                                                       slang_ITypeConformance_PTR*outConformance,
                                                       SlangInt conformanceIdOverride, slang_IBlob_PTR *outDiagnostics) {
        return this->createTypeConformanceComponentType(
                static_cast<slang::TypeReflection *>(type), interfaceType, reinterpret_cast<slang::ITypeConformance **>(&outConformance->value), conformanceIdOverride,
                reinterpret_cast<slang::IBlob **>(&outDiagnostics->value));
    }

    slang_IModule *
    slang_ISession::_loadModuleFromIRBlob(godot::String moduleName, godot::String path, slang_IBlob *source,
                                         slang_IBlob_PTR *outDiagnostics) {
        return dynamic_cast<slang_IModule *>(this->loadModuleFromIRBlob(moduleName.utf8().get_data(),
                                                                                         path.utf8().get_data(),
                                                                                         static_cast<slang::IBlob *>(source),
                                                                                         reinterpret_cast<slang::IBlob **>(&outDiagnostics->value)));
    }

    slang_IModule *slang_ISession::_getLoadedModule(SlangInt index, slang_NULL *) {
        return static_cast<slang_IModule *>(this->getLoadedModule(index));
    }

    bool slang_ISession::_isBinaryModuleUpToDate(godot::String modulePath, slang_IBlob *binaryModuleBlob) {
        return this->isBinaryModuleUpToDate(modulePath.utf8().get_data(),
                                                             static_cast<slang::IBlob *>(binaryModuleBlob));
    }

    slang_IModule *
    slang_ISession::_loadModuleFromSourceString(godot::String moduleName, godot::String path, godot::String string,
                                               slang_IBlob_PTR*outDiagnostics) {
        return static_cast<slang_IModule *>(this->loadModuleFromSourceString(
                moduleName.utf8().get_data(), path.utf8().get_data(), string.utf8().get_data(),
                reinterpret_cast<slang::IBlob **>(&outDiagnostics->value)));
    }
    SlangResult slang_ISession::_createCompositeComponentType(slang_IComponentType_VECTOR* componentTypes,
                                                             slang_IComponentType_PTR *outCompositeComponentType,
                                                             slang_IBlob_PTR *outDiagnostics) {
        auto size = componentTypes->size();
        slang::IComponentType* ptrs[size];
        for(int i = 0;i!= size;i++){
            ptrs[i] = (*componentTypes)[i];
        }
        return this->createCompositeComponentType(
                const_cast<slang::IComponentType *const *>(ptrs), size,
                reinterpret_cast<slang::IComponentType **>(outCompositeComponentType->get_value()),
                reinterpret_cast<slang::IBlob **>(outDiagnostics->get_value()));
    }

    slang_ISharedLibraryLoader *slang_IGlobalSession::_getSharedLibraryLoader(slang_NULL *) {
        return dynamic_cast<slang_ISharedLibraryLoader *>(this->getSharedLibraryLoader());
    }

    SlangResult slang_IGlobalSession::_parseCommandLineArguments(godot::TypedArray<godot::String> args,
                                                                slang_SessionDesc *outSessionDesc,
                                                                slang_IUnknown_PTR*outAuxAllocation) {
        auto size = args.size();
        const char* argv_ptr[size];
        for(int i = 0; i < size; i++) {
            godot::String str = args[i];
            argv_ptr[i] = str.utf8().get_data();
        }
        return this->parseCommandLineArguments(size,argv_ptr,
                                                                      dynamic_cast<slang::SessionDesc *>(outSessionDesc),
                                                                      reinterpret_cast<ISlangUnknown **>(&outAuxAllocation->value));
    }

    SlangResult slang_IGlobalSession::_getSessionDescDigest(slang_SessionDesc *sessionDesc, slang_IBlob_PTR*outBlob) {
        return this->getSessionDescDigest(dynamic_cast<slang::SessionDesc *>(sessionDesc),
                                                                 reinterpret_cast<ISlangBlob **>(&outBlob->value));
    }

    slang_CompilerOptionValue* slang_CompilerOptionEntry::get_value() {
        return static_cast<slang_CompilerOptionValue*>(&value);
    }

    void slang_CompilerOptionEntry::set_value(slang_CompilerOptionValue* value) {
        this->value = *value;
    }

    slang_CompilerOptionEntry *slang_TargetDesc::get_compilerOptionEntries() {
        return static_cast<slang_CompilerOptionEntry*>(compilerOptionEntries);
    }

    void slang_TargetDesc::set_compilerOptionEntries(slang_CompilerOptionEntry *compilerOptionEntries) {
        this->compilerOptionEntries = compilerOptionEntries;
    }

    godot::Array slang_SessionDesc::get_targets() {
        godot::Array a;
        for(int i = 0; i < targetCount; i++){
            a[i] = static_cast<slang_TargetDesc*>(const_cast<slang::TargetDesc*>(&targets[i]));
        }

        return a;
    }

    void slang_SessionDesc::set_targets(godot::Array targets) {
        delete[] this->targets;
        int size = targets.size();
        this->targets = new slang::TargetDesc[size];
        for(int i = 0;i!=size;++i){
            *const_cast<slang::TargetDesc*>(&this->targets[i]) = *dynamic_cast<slang::TargetDesc*>(targets[i].operator Object *());
        }
    }

    slang_PreprocessorMacroDesc *slang_SessionDesc::get_preprocessorMacros() {
        return const_cast<slang_PreprocessorMacroDesc *>(static_cast<const slang_PreprocessorMacroDesc *>(preprocessorMacros));
    }

    void slang_SessionDesc::set_preprocessorMacros(const slang_PreprocessorMacroDesc *preprocessorMacros) {
        this->preprocessorMacros = preprocessorMacros;
    }

    slang_IFileSystem *slang_SessionDesc::get_fileSystem() {
        return dynamic_cast<slang_IFileSystem *>(fileSystem);
    }

    void slang_SessionDesc::set_fileSystem(slang_IFileSystem *fileSystem) {
        this->fileSystem = fileSystem;
    }

    slang_CompilerOptionEntry *slang_SessionDesc::get_compilerOptionEntries() {
        return static_cast<slang_CompilerOptionEntry *>(compilerOptionEntries);
    }

    void slang_SessionDesc::set_compilerOptionEntries(slang_CompilerOptionEntry *compilerOptionEntries) {
        this->compilerOptionEntries = compilerOptionEntries;
    }

    slang_TypeReflection *slang_UserAttribute::getArgumentType(uint32_t index) {
        return static_cast<slang_TypeReflection *>(this->slang::UserAttribute::getArgumentType(index));
    }

    slang_TypeReflection *slang_VariableReflection::getType(slang_NULL *) {
        return static_cast<slang_TypeReflection *>(this->slang::VariableReflection::getType());
    }

    slang_TypeReflection *slang_FunctionReflection::getReturnType() {
        return static_cast<slang_TypeReflection *>(this->slang::FunctionReflection::getReturnType());
    }

    slang_GenericReflection *slang_FunctionReflection::getGenericContainer() {
        return static_cast<slang_GenericReflection *>(this->slang::FunctionReflection::getGenericContainer());
    }

    slang_TypeReflection *slang_DeclReflection::getType() {
        return static_cast<slang_TypeReflection *>(this->slang::DeclReflection::getType());
    }

    slang_GenericReflection *slang_DeclReflection::asGeneric() {
        return static_cast<slang_GenericReflection *>(this->slang::DeclReflection::asGeneric());
    }

    slang_TypeLayoutReflection *slang_VariableLayoutReflection::getTypeLayout() {
        return static_cast<slang_TypeLayoutReflection *>(this->slang::VariableLayoutReflection::getTypeLayout());
    }

    slang_FunctionReflection *slang_IEntryPoint::_getFunctionReflection(slang_NULL *) {
        return static_cast<slang_FunctionReflection *>(this->getFunctionReflection());
    }

    godot::String slang_ICastable::_castAs(slang_UUID *uuid, slang_NULL *null) {
        return (char*)(this->castAs(static_cast<SlangUUID>(*uuid)));
    }
}
#endif