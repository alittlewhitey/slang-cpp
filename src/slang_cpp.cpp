#ifndef SLANG_CPP_SRC
#define SLANG_CPP_SRC
#include "../include/slang_cpp.h"
namespace slang_cpp{
    slang_global* slang_global::single_ptr = nullptr;

    slang_ShaderReflection *slang_IComponentType::getLayout(SlangInt targetIndex, slang_PTR<slang_IBlob *> *blob) {
        return static_cast<slang_ShaderReflection *>(this->IComponentType::getLayout(targetIndex, reinterpret_cast<ISlangBlob **>(blob == nullptr? nullptr: blob->get_value())));
    }

    SlangResult
    slang_IComponentType::specialize(slang_SpecializationArg *specializationArgs, SlangInt specializationArgCount,
                                     slang_PTR<slang_IComponentType *>*specializedOut, slang_PTR<slang_IBlob *> *outDiagnostics) {
        return this->IComponentType::specialize(
                static_cast<slang::SpecializationArg *>(specializationArgs), specializationArgCount, reinterpret_cast<IComponentType **>(specializedOut->get_value()), reinterpret_cast<ISlangBlob **>(outDiagnostics == nullptr ? nullptr : outDiagnostics->get_value()));
    }

    SlangResult slang_IComponentType::linkWithOptions(slang_PTR<slang_IComponentType *>*outLinkedComponentType,
                                                      uint32_t compilerOptionEntryCount,
                                                      slang_CompilerOptionEntry *compilerOptionEntries,
                                                      slang_PTR<slang_IBlob *> *outDiagnostics) {
        return this->IComponentType::linkWithOptions(reinterpret_cast<IComponentType **>(outLinkedComponentType->get_value()), compilerOptionEntryCount,
                                                     static_cast<slang::CompilerOptionEntry *>(compilerOptionEntries), reinterpret_cast<ISlangBlob **>(outDiagnostics == nullptr ? nullptr : outDiagnostics->get_value()));
    }


    slang_DeclReflection *slang_IModule::getModuleReflection(slang_NULL*null) {
        return static_cast<slang_DeclReflection *>(this->IModule::getModuleReflection());
    }

    slang_IModule *slang_ISession::loadModule(godot::String moduleName, slang_PTR<slang_IBlob *> *outDiagnostics) {
        return static_cast<slang_IModule *>(this->slang::ISession::loadModule(moduleName.utf8().get_data(),
                                                                              reinterpret_cast<slang::IBlob **>(outDiagnostics->get_value())));
    }

    slang_IModule *slang_ISession::loadModuleFromSource(godot::String moduleName, godot::String path, slang_IBlob *source,slang_PTR<slang_IBlob *> *outDiagnostics) {
        return dynamic_cast<slang_IModule *>(this->slang::ISession::loadModuleFromSource(moduleName.utf8().get_data(),
                                                                                         path.utf8().get_data(),
                                                                                         dynamic_cast<slang::IBlob *>(source),
                                                                                         reinterpret_cast<ISlangBlob **>(outDiagnostics->get_value())));
    }

    slang_TypeReflection *
    slang_ISession::specializeType(slang_TypeReflection *type_, slang_SpecializationArg *specializationArgs,
                                   SlangInt specializationArgCount, slang_PTR<slang_IBlob *> *outDiagnostics) {
        return static_cast<slang_TypeReflection *>(this->slang::ISession::specializeType(type_, specializationArgs,
                                                                                         specializationArgCount,
                                                                                         reinterpret_cast<slang::IBlob **>(outDiagnostics->get_value())));
    }

    slang_TypeLayoutReflection *
    slang_ISession::getTypeLayout(slang_TypeReflection *type_, SlangInt targetIndex, slang_LayoutRules rules,
                                  slang_PTR<slang_IBlob *> *outDiagnostics) {
        return static_cast<slang_TypeLayoutReflection *>(this->slang::ISession::getTypeLayout(type_, targetIndex,
                                                                                              static_cast<slang::LayoutRules>(rules),
                                                                                              reinterpret_cast<slang::IBlob **>(outDiagnostics->get_value())));
    }

    slang_TypeReflection *
    slang_ISession::getContainerType(slang_TypeReflection *elementType, slang_ContainerType containerType,
                                     slang_PTR<slang_IBlob *> *outDiagnostics) {
        return static_cast<slang_TypeReflection *>(this->slang::ISession::getContainerType(
                static_cast<slang::TypeReflection *>(elementType),
                static_cast<slang::ContainerType>(containerType), reinterpret_cast<slang::IBlob **>(outDiagnostics->get_value())));
    }

    slang_TypeReflection *slang_ISession::getDynamicType(slang_NULL*) {
        return static_cast<slang_TypeReflection *>(this->slang::ISession::getDynamicType());
    }

    SlangResult slang_ISession::getTypeRTTIMangledName(slang_TypeReflection *type, slang_PTR<slang_IBlob *> *outNameBlob) {
        return this->slang::ISession::getTypeRTTIMangledName(static_cast<slang::TypeReflection*>(type), reinterpret_cast<slang::IBlob**>(outNameBlob->get_value()));
    }

    SlangResult slang_ISession::getTypeConformanceWitnessMangledName(slang_TypeReflection *type,
                                                                     slang_TypeReflection *interfaceType,
                                                                     slang_PTR<slang_IBlob *> *outNameBlob) {
        return this->slang::ISession::getTypeConformanceWitnessMangledName(static_cast<slang::TypeReflection*>(type), static_cast<slang::TypeReflection*>(interfaceType), reinterpret_cast<slang::IBlob**>(outNameBlob->get_value()));
    }

    SlangResult slang_ISession::getTypeConformanceWitnessSequentialID(slang_TypeReflection *type,
                                                                      slang_TypeReflection *interfaceType,
                                                                      slang_INT<uint32_t> *outId) {
        uint32_t id;
        SlangResult res = this->slang::ISession::getTypeConformanceWitnessSequentialID(static_cast<slang::TypeReflection*>(type), static_cast<slang::TypeReflection*>(interfaceType), &id);
        outId->set_value(id);
        return res;
    }

    SlangResult
    slang_ISession::createTypeConformanceComponentType(slang_TypeReflection *type, slang_TypeReflection *interfaceType,
                                                       slang_PTR<slang_ITypeConformance *>*outConformance,
                                                       SlangInt conformanceIdOverride, slang_PTR<slang_IBlob*> *outDiagnostics) {
        return this->slang::ISession::createTypeConformanceComponentType(
                static_cast<slang::TypeReflection *>(type), interfaceType, reinterpret_cast<slang::ITypeConformance **>(outConformance->get_value()), conformanceIdOverride,
                reinterpret_cast<slang::IBlob **>(outDiagnostics->get_value()));
    }

    slang_IModule *
    slang_ISession::loadModuleFromIRBlob(godot::String moduleName, godot::String path, slang_IBlob *source,
                                         slang_PTR<slang_IBlob*> *outDiagnostics) {
        return dynamic_cast<slang_IModule *>(this->slang::ISession::loadModuleFromIRBlob(moduleName.utf8().get_data(),
                                                                                         path.utf8().get_data(),
                                                                                         static_cast<slang::IBlob *>(source),
                                                                                         reinterpret_cast<slang::IBlob **>(outDiagnostics->get_value())));
    }

    slang_IModule *slang_ISession::getLoadedModule(SlangInt index, slang_NULL *) {
        return static_cast<slang_IModule *>(this->slang::ISession::getLoadedModule(index));
    }

    bool slang_ISession::isBinaryModuleUpToDate(godot::String modulePath, slang_IBlob *binaryModuleBlob) {
        return this->slang::ISession::isBinaryModuleUpToDate(modulePath.utf8().get_data(),
                                                             static_cast<slang::IBlob *>(binaryModuleBlob));
    }

    slang_IModule *
    slang_ISession::loadModuleFromSourceString(godot::String moduleName, godot::String path, godot::String string,
                                               slang_PTR<slang_IBlob*> *outDiagnostics) {
        return static_cast<slang_IModule *>(this->slang::ISession::loadModuleFromSourceString(
                moduleName.utf8().get_data(), path.utf8().get_data(), string.utf8().get_data(),
                reinterpret_cast<slang::IBlob **>(outDiagnostics->get_value())));
    }

    slang_ISharedLibraryLoader *slang_IGlobalSession::getSharedLibraryLoader(slang_NULL *) {
        return dynamic_cast<slang_ISharedLibraryLoader *>(this->slang::IGlobalSession::getSharedLibraryLoader());
    }

    SlangResult slang_IGlobalSession::parseCommandLineArguments(int argc, godot::TypedArray<godot::String> argv,
                                                                slang_SessionDesc *outSessionDesc,
                                                                slang_PTR<slang_IUnknown *>*outAuxAllocation) {
        const char* argv_ptr[argc];
        for(int i = 0; i < argc; i++) {
            godot::String str = argv[i];
            argv_ptr[i] = str.utf8().get_data();
        }
        return this->slang::IGlobalSession::parseCommandLineArguments(argc,argv_ptr,
                                                                      dynamic_cast<slang::SessionDesc *>(outSessionDesc),
                                                                      reinterpret_cast<ISlangUnknown **>(outAuxAllocation->get_value()));
    }

    SlangResult slang_IGlobalSession::getSessionDescDigest(slang_SessionDesc *sessionDesc, slang_PTR<slang_IBlob*>*outBlob) {
        return this->slang::IGlobalSession::getSessionDescDigest(dynamic_cast<slang::SessionDesc *>(sessionDesc),
                                                                 reinterpret_cast<ISlangBlob **>(outBlob->get_value()));
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

    slang_TargetDesc *slang_SessionDesc::get_targets() {
        return const_cast<slang_TargetDesc *>(static_cast<const slang_TargetDesc *>(targets));
    }

    void slang_SessionDesc::set_targets(const slang_TargetDesc *targets) {
        this->targets = targets;
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

    slang_FunctionReflection *slang_IEntryPoint::getFunctionReflection(slang_NULL *) {
        return static_cast<slang_FunctionReflection *>(this->IEntryPoint::getFunctionReflection());
    }
}
#endif