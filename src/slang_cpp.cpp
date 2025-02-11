#ifndef SLANG_CPP_SRC
#define SLANG_CPP_SRC
#include "../include/slang_cpp.h"
namespace slang_cpp{

    MAKE_TEMPLATE_CLASS_SRC(SlangObject)
    MAKE_TEMPLATE_CLASS_SRC(NULL)
    MAKE_TEMPLATE_CLASS_SRC(INT)
    MAKE_TEMPLATE_CLASS_SRC(SIZE)
    MAKE_TEMPLATE_CLASS_SRC(BOOL)
    MAKE_TEMPLATE_CLASS_SRC(DOUBLE)
    MAKE_TEMPLATE_CLASS_SRC(SlangRef)
    MAKE_TEMPLATE_CLASS_SRC(IUnknown)
    MAKE_TEMPLATE_CLASS_SRC(IGlobalSession)
    MAKE_TEMPLATE_CLASS_SRC(ISession)
    MAKE_TEMPLATE_CLASS_SRC(IBlob)
    MAKE_TEMPLATE_CLASS_SRC(ICastable)
    MAKE_TEMPLATE_CLASS_SRC(IFileSystem)
    MAKE_TEMPLATE_CLASS_SRC(IFileSystemExt)
    MAKE_TEMPLATE_CLASS_SRC(IMutableFileSystem)
    MAKE_TEMPLATE_CLASS_SRC(ISharedLibrary)
    MAKE_TEMPLATE_CLASS_SRC(ISharedLibraryLoader)
    MAKE_TEMPLATE_CLASS_SRC(IComponentType)
    MAKE_TEMPLATE_CLASS_SRC(ITypeConformance)
    MAKE_TEMPLATE_CLASS_SRC(IEntryPoint)
    MAKE_TEMPLATE_CLASS_SRC(IModule)
    MAKE_TEMPLATE_CLASS_SRC(IWriter)
    // MAKE_TEMPLATE_CLASS_SRC(IProfiler)
    MAKE_TEMPLATE_CLASS_SRC(ICompileRequest)
    MAKE_TEMPLATE_CLASS_SRC(UUID)
    MAKE_TEMPLATE_CLASS_SRC(CompilerOptionValue)
    MAKE_TEMPLATE_CLASS_SRC(CompilerOptionEntry)
    MAKE_TEMPLATE_CLASS_SRC(PreprocessorMacroDesc)
    MAKE_TEMPLATE_CLASS_SRC(TargetDesc)
    MAKE_TEMPLATE_CLASS_SRC(SessionDesc)
    MAKE_TEMPLATE_CLASS_SRC(Modifier)
    MAKE_TEMPLATE_CLASS_SRC(UserAttribute)
    MAKE_TEMPLATE_CLASS_SRC(GenericReflection)
    MAKE_TEMPLATE_CLASS_SRC(VariableReflection)
    MAKE_TEMPLATE_CLASS_SRC(VariableLayoutReflection)
    MAKE_TEMPLATE_CLASS_SRC(FunctionReflection)
    MAKE_TEMPLATE_CLASS_SRC(DeclReflection)
    MAKE_TEMPLATE_CLASS_SRC(TypeReflection)
    MAKE_TEMPLATE_CLASS_SRC(SlangReflectionGeneric)
    MAKE_TEMPLATE_CLASS_SRC(TypeLayoutReflection)
    MAKE_TEMPLATE_CLASS_SRC(TypeParameterReflection)
    MAKE_TEMPLATE_CLASS_SRC(EntryPointReflection)
    MAKE_TEMPLATE_CLASS_SRC(ShaderReflection)
    MAKE_TEMPLATE_CLASS_SRC(SpecializationArg)

    slang_ShaderReflection_HEAP_PTR *slang_IComponentType::_getLayout(SlangInt targetIndex, slang_IBlob *blob) const {
        auto* a = memnew(slang_ShaderReflection(value->getLayout(targetIndex, blob == nullptr? nullptr: &blob->value)));
        auto* ptr = memnew(slang_ShaderReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    SlangResult
    slang_IComponentType::_specialize(slang_SpecializationArg_VECTOR *specializationArgs, SlangInt specializationArgCount,
                                     slang_IComponentType*specializedOut, slang_IBlob *outDiagnostics) const {
        slang::SpecializationArg* args = new slang::SpecializationArg[specializationArgCount];
        for(int i = 0;i!=specializationArgCount;++i){
            args[i] = specializationArgs->at(i)->duplicate();
        }
        auto res = value->specialize(
                args, specializationArgCount, &specializedOut->value, outDiagnostics == nullptr ? nullptr : &outDiagnostics->value);
        delete[] args;
        return res;
    }

    SlangResult slang_IComponentType::_linkWithOptions(slang_IComponentType*outLinkedComponentType,
                                                      uint32_t compilerOptionEntryCount,
                                                      slang_CompilerOptionEntry *compilerOptionEntries,
                                                      slang_IBlob *outDiagnostics) const {
        auto a = compilerOptionEntries->duplicate();
        auto res = value->linkWithOptions(&outLinkedComponentType->value, compilerOptionEntryCount,
                                                     &a, outDiagnostics == nullptr ? nullptr : &outDiagnostics->value);
        return res;
    }

    slang_DeclReflection_HEAP_PTR *slang_IModule::_getModuleReflection() const {
        auto* a = memnew(slang_DeclReflection(value->getModuleReflection()));
        auto* ptr = memnew(slang_DeclReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_IModule_HEAP_PTR *slang_ISession::_loadModule(godot::String moduleName, slang_IBlob *outDiagnostics) const {
        moduleName = godot::ProjectSettings::get_singleton()->globalize_path(moduleName);
        auto* a = memnew(slang_IModule(value->loadModule(moduleName.utf8().get_data(),
                                                      &outDiagnostics->value)));
        auto* ptr = memnew(slang_IModule_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_IModule *slang_ISession::_loadModuleFromSource(godot::String moduleName, godot::String path, slang_IBlob *source,slang_IBlob *outDiagnostics) const {
        moduleName = godot::ProjectSettings::get_singleton()->globalize_path(moduleName);
        path = godot::ProjectSettings::get_singleton()->globalize_path(path);
        return dynamic_cast<slang_IModule *>(value->loadModuleFromSource(moduleName.utf8().get_data(),
                                                                                         path.utf8().get_data(),
                                                                                         dynamic_cast<slang::IBlob *>(source),
                                                                                         &outDiagnostics->value));
    }
    slang_TypeReflection_HEAP_PTR *slang_ISession::_specializeType(slang_TypeReflection *type_, slang_SpecializationArg_VECTOR *specializationArgs,
                                                                   SlangInt specializationArgCount, slang_IBlob*outDiagnostics) const {
        slang::SpecializationArg* args = new slang::SpecializationArg[specializationArgCount];
        for(int i = 0;i!= specializationArgCount;++i){
            args[i] = specializationArgs->at(i)->duplicate();
        }
        auto* a = memnew(slang_TypeReflection(value->specializeType(type_->value, args,
                                                                           specializationArgCount,
                                        &outDiagnostics->value)));
        auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        delete[] args;
        return ptr;
    }

    slang_TypeLayoutReflection_HEAP_PTR *
    slang_ISession::_getTypeLayout(slang_TypeReflection *type_, SlangInt targetIndex, slang_LayoutRules rules,
                                  slang_IBlob*outDiagnostics) const {
        auto* a = memnew(slang_TypeLayoutReflection(value->getTypeLayout(type_->value, targetIndex,
                                                                      static_cast<slang::LayoutRules>(rules),
                                                                 &outDiagnostics->value)));
        auto* ptr = memnew(slang_TypeLayoutReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_TypeReflection_HEAP_PTR *
    slang_ISession::_getContainerType(slang_TypeReflection *elementType, slang_ContainerType containerType,
                                     slang_IBlob *outDiagnostics) {
        auto* a = memnew(slang_TypeReflection(value->getContainerType(elementType->value,
                                                                   static_cast<slang::ContainerType>(containerType),
                                                                   &outDiagnostics->value)));
        auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_TypeReflection_HEAP_PTR *slang_ISession::_getDynamicType() {
        auto* a = memnew(slang_TypeReflection(value->getDynamicType()));
        auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    SlangResult slang_ISession::_getTypeRTTIMangledName(slang_TypeReflection *type, slang_IBlob *outNameBlob) {
        return value->getTypeRTTIMangledName(type->value, &outNameBlob->value);
    }

    SlangResult slang_ISession::_getTypeConformanceWitnessMangledName(slang_TypeReflection *type,
                                                                     slang_TypeReflection *interfaceType,
                                                                     slang_IBlob *outNameBlob) {
        return value->getTypeConformanceWitnessMangledName(type->value, interfaceType->value, &outNameBlob->value);
    }

    SlangResult slang_ISession::_getTypeConformanceWitnessSequentialID(slang_TypeReflection *type,
                                                                      slang_TypeReflection *interfaceType,
                                                                      slang_SIZE*outId) {
        uint32_t id;
        SlangResult res = value->getTypeConformanceWitnessSequentialID(type->value, interfaceType->value, &id);
        outId->set_value(id);
        return res;
    }

    SlangResult
    slang_ISession::_createTypeConformanceComponentType(slang_TypeReflection *type, slang_TypeReflection *interfaceType,
                                                       slang_ITypeConformance*outConformance,
                                                       SlangInt conformanceIdOverride, slang_IBlob *outDiagnostics) {
        return value->createTypeConformanceComponentType(
                type->value, interfaceType->value, &outConformance->value, conformanceIdOverride,
                &outDiagnostics->value);
    }

    slang_IModule *
    slang_ISession::_loadModuleFromIRBlob(godot::String moduleName, godot::String path, slang_IBlob *source,
                                         slang_IBlob *outDiagnostics) {
        moduleName = godot::ProjectSettings::get_singleton()->globalize_path(moduleName);
        path = godot::ProjectSettings::get_singleton()->globalize_path(path);
        return dynamic_cast<slang_IModule *>(value->loadModuleFromIRBlob(moduleName.utf8().get_data(),
                                                                                         path.utf8().get_data(),
                                                                                         source->value,
                                                                                         &outDiagnostics->value));
    }

    slang_IModule_HEAP_PTR *slang_ISession::_getLoadedModule(SlangInt index) {
        auto* a = memnew(slang_IModule(value->getLoadedModule(index)));
        auto* ptr= memnew(slang_IModule_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    bool slang_ISession::_isBinaryModuleUpToDate(godot::String modulePath, slang_IBlob *binaryModuleBlob) {
        modulePath = godot::ProjectSettings::get_singleton()->globalize_path(modulePath);
        return value->isBinaryModuleUpToDate(modulePath.utf8().get_data(),
                                                             binaryModuleBlob->value);
    }

    slang_IModule_HEAP_PTR *
    slang_ISession::_loadModuleFromSourceString(godot::String moduleName, godot::String path, godot::String string,
                                               slang_IBlob*outDiagnostics) {
        moduleName = godot::ProjectSettings::get_singleton()->globalize_path(moduleName);
        path = godot::ProjectSettings::get_singleton()->globalize_path(path);
        auto* a = memnew(slang_IModule(value->loadModuleFromSourceString(
                moduleName.utf8().get_data(), path.utf8().get_data(), string.utf8().get_data(),
                &outDiagnostics->value)));
        auto* ptr = memnew(slang_IModule_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }
    SlangResult slang_ISession::_createCompositeComponentType(slang_IComponentType_VECTOR* componentTypes,
                                                             slang_IComponentType *outCompositeComponentType,
                                                             slang_IBlob *outDiagnostics) {
        size_t size = componentTypes->size();
        slang::IComponentType** types = new slang::IComponentType*[size];
        for(int i = 0;i!= size;++i){
            types[i] =(*componentTypes)[i]->value;
        }
        auto res = value->createCompositeComponentType(
                types,
                size,
                &outCompositeComponentType->value,
                &outDiagnostics->value);
        delete[] types;
        return res;
    }

    SlangResult slang_ISession::_createCompileRequest(slang_ICompileRequest *outCompileRequest) {
        return value->createCompileRequest(
                &outCompileRequest->value);
    }

    slang_ISharedLibraryLoader *slang_IGlobalSession::_getSharedLibraryLoader(slang_NULL *) {
        return dynamic_cast<slang_ISharedLibraryLoader *>(value->getSharedLibraryLoader());
    }

    SlangResult slang_IGlobalSession::_parseCommandLineArguments(godot::TypedArray<godot::String> args,
                                                                slang_SessionDesc *outSessionDesc,
                                                                slang_IUnknown*outAuxAllocation) {
        auto size = args.size();
        const char** argv_ptr = new const char*[size];
        for(int i = 0; i < size; i++) {
            godot::String str = args[i];
            argv_ptr[i] = str.utf8().get_data();
        }
        auto res = value->parseCommandLineArguments(size,argv_ptr,
                                                                      dynamic_cast<slang::SessionDesc *>(outSessionDesc),
                                                                      &outAuxAllocation->value);
        delete[] argv_ptr;
        return res;
    }

    SlangResult slang_IGlobalSession::_getSessionDescDigest(slang_SessionDesc *sessionDesc, slang_IBlob*outBlob) {
        return value->getSessionDescDigest(dynamic_cast<slang::SessionDesc *>(sessionDesc),
                                                                 &outBlob->value);
    }

    SlangResult slang_IGlobalSession::_createSession(slang_SessionDesc *desc, slang_ISession *outSession) {
        return value->createSession(desc->duplicate(),
                                   &outSession->value);
    }

    SlangResult slang_IGlobalSession::_createCompileRequest(slang_ICompileRequest *outCompileRequest) {
        return value->createCompileRequest(
                &outCompileRequest->value);
    }

    void slang_IGlobalSession::_setSharedLibraryLoader(slang_ISharedLibraryLoader *loader) const {
        return value->setSharedLibraryLoader(
                loader->value);
    }

    void
    slang_IGlobalSession::_getDownstreamCompilerPrelude(slang_SlangPassThrough passThrough, slang_IBlob *outPrelude) {
        return value->getDownstreamCompilerPrelude((SlangPassThrough) passThrough,
                                                   &outPrelude->value);
    }

    void slang_IGlobalSession::_getLanguagePrelude(slang_SlangSourceLanguage sourceLanguage, slang_IBlob *outPrelude) {
        return value->getLanguagePrelude(
                static_cast<SlangSourceLanguage>(sourceLanguage),
                &outPrelude->value);
    }

    SlangResult slang_IGlobalSession::_saveStdLib(SlangArchiveType archiveType, slang_IBlob *outBlob) {
        return value->saveStdLib(archiveType, &outBlob->value);
    }

    slang_CompilerOptionValue_HEAP_PTR* slang_CompilerOptionEntry::get_value() {
        auto* ptr = memnew(slang_CompilerOptionValue_HEAP_PTR(new slang_CompilerOptionValue(value)));
        ptr->shouldFreeData = true;
        return ptr;
    }

    void slang_CompilerOptionEntry::set_value(slang_CompilerOptionValue* value) {
        this->value = value->duplicate();
    }

    slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR *slang_TargetDesc::get_compilerOptionEntries() {
        auto* a = memnew(slang_CompilerOptionEntry_VALUE_VECTOR());
        for(int i = 0;i!=value->compilerOptionEntryCount;++i){
            a->push_back(value->compilerOptionEntries[i]);
        }
        auto* ptr = memnew(slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    void slang_TargetDesc::set_compilerOptionEntries(slang_CompilerOptionEntry_VALUE_VECTOR *compilerOptionEntries) {
        this->value->compilerOptionEntries = compilerOptionEntries->data();
    }

    slang_TargetDesc_VALUE_VECTOR_HEAP_PTR* slang_SessionDesc::get_targets() {
        auto* vec = memnew(slang_TargetDesc_VALUE_VECTOR());
        vec->reserve(value->targetCount);
        for(int i = 0; i < value->targetCount; i++){
            (*vec)[i] = value->targets[i];
        }
        auto* ptr = memnew(slang_TargetDesc_VALUE_VECTOR_HEAP_PTR(vec));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    void slang_SessionDesc::set_targets(slang_TargetDesc_VALUE_VECTOR* targets) {
        this->value->targets = targets->data();
    }

    slang_IFileSystem *slang_SessionDesc::get_fileSystem() {
        return dynamic_cast<slang_IFileSystem *>(value->fileSystem);
    }

    void slang_SessionDesc::set_fileSystem(slang_IFileSystem *fileSystem) {
        this->value->fileSystem = fileSystem->value;
    }

    slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR *slang_SessionDesc::get_compilerOptionEntries() {
        auto*vec = memnew(slang_CompilerOptionEntry_VALUE_VECTOR());
        vec->reserve(value->compilerOptionEntryCount);
        for(int i = 0;i!= value->compilerOptionEntryCount;++i){
            (*vec)[i] = value->compilerOptionEntries[i];
        }
        auto* ptr = memnew(slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR(vec));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    void slang_SessionDesc::set_compilerOptionEntries(slang_CompilerOptionEntry_VALUE_VECTOR *compilerOptionEntries) {
        this->value->compilerOptionEntryCount = compilerOptionEntries->size();
        this->value->compilerOptionEntries = compilerOptionEntries->data();
    }

    slang_TypeReflection_HEAP_PTR *slang_UserAttribute::getArgumentType(uint32_t index) {
        auto* a = memnew(slang_TypeReflection(this->value->getArgumentType(index)));
        auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_TypeReflection_HEAP_PTR *slang_VariableReflection::getType() {
        auto* a = memnew(slang_TypeReflection(this->value->getType()));
        auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_TypeReflection_HEAP_PTR *slang_FunctionReflection::getReturnType() {
        auto* a = memnew(slang_TypeReflection(this->value->getReturnType()));
        auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_GenericReflection *slang_FunctionReflection::getGenericContainer() {
        return static_cast<slang_GenericReflection *>(this->value->getGenericContainer());
    }

    slang_TypeReflection_HEAP_PTR *slang_DeclReflection::getType() {
        auto* a = memnew(slang_TypeReflection(this->value->getType()));
        auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_GenericReflection *slang_DeclReflection::asGeneric() {
        return static_cast<slang_GenericReflection *>(this->value->asGeneric());
    }

    slang_TypeLayoutReflection_HEAP_PTR *slang_VariableLayoutReflection::getTypeLayout() {
        auto* a = memnew(slang_TypeLayoutReflection(this->value->getTypeLayout()));
        auto* ptr = memnew(slang_TypeLayoutReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_FunctionReflection_HEAP_PTR* slang_IEntryPoint::_getFunctionReflection() {
        auto* a = memnew(slang_FunctionReflection(value->getFunctionReflection()));
        auto* ptr = memnew(slang_FunctionReflection_HEAP_PTR(a));
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    godot::String slang_ICastable::_castAs(slang_UUID *uuid) {
        return (char*)(value->castAs(static_cast<SlangUUID>(*uuid)));
    }

    SlangResult slang_IUnknown::_query_interface(slang_UUID *guid, slang_VOID_PTR *outObj) {
        void *obj = nullptr;
        SlangResult res = value->queryInterface(guid->operator SlangUUID(), &obj);
        outObj->set_value(obj);
        return res;
    }

    SlangResult slang_IFileSystem::_loadFile(godot::String path, slang_IBlob *outBlob) {
        path = godot::ProjectSettings::get_singleton()->globalize_path(path);
        return value->loadFile(path.utf8().get_data(), &outBlob->value);
    }
}
#endif