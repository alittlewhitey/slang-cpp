#ifndef SLANG_CPP_SRC
#define SLANG_CPP_SRC
#include "../include/slang_cpp.h"
namespace slang_cpp{
    slang_global* slang_global::single_ptr = nullptr;


    slang_ShaderReflection_HEAP_PTR *slang_IComponentType::_getLayout(SlangInt targetIndex, slang_IBlob_PTR *blob) {
        auto* a = new slang_ShaderReflection(this->getLayout(targetIndex, reinterpret_cast<ISlangBlob **>(blob == nullptr? nullptr: &blob->value)));
        auto* ptr = new slang_ShaderReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    SlangResult
    slang_IComponentType::_specialize(slang_SpecializationArg_VECTOR *specializationArgs, SlangInt specializationArgCount,
                                     slang_IComponentType_PTR*specializedOut, slang_IBlob_PTR *outDiagnostics) {
        slang::SpecializationArg args[specializationArgCount];
        for(int i = 0;i!=specializationArgCount;++i){
            args[i] = specializationArgs->at(i)->duplicate();
        }
        return this->specialize(
                args, specializationArgCount, reinterpret_cast<IComponentType **>(&specializedOut->value), reinterpret_cast<ISlangBlob **>(outDiagnostics == nullptr ? nullptr : &outDiagnostics->value));
    }

    SlangResult slang_IComponentType::_linkWithOptions(slang_IComponentType_PTR*outLinkedComponentType,
                                                      uint32_t compilerOptionEntryCount,
                                                      slang_CompilerOptionEntry *compilerOptionEntries,
                                                      slang_IBlob_PTR *outDiagnostics) {
        auto a = compilerOptionEntries->duplicate();
        auto res = this->linkWithOptions(reinterpret_cast<IComponentType **>(&outLinkedComponentType->value), compilerOptionEntryCount,
                                                     &a, reinterpret_cast<ISlangBlob **>(outDiagnostics == nullptr ? nullptr : &outDiagnostics->value));
        return res;
    }

    slang_ShaderReflection* slang_IComponentType::a(SlangInt targetIndex, slang_IBlob_PTR *blob) {
        return new slang_ShaderReflection(this->getLayout(targetIndex, reinterpret_cast<ISlangBlob **>(blob == nullptr? nullptr: &blob->value)));
    }


    slang_DeclReflection_HEAP_PTR *slang_IModule::_getModuleReflection() {
        auto* a = new slang_DeclReflection(this->getModuleReflection());
        auto* ptr = new slang_DeclReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
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
    slang_TypeReflection_HEAP_PTR *slang_ISession::_specializeType(slang_TypeReflection *type_, slang_SpecializationArg_VECTOR *specializationArgs,
                                                                   SlangInt specializationArgCount, slang_IBlob_PTR*outDiagnostics) {
        slang::SpecializationArg args[specializationArgCount];
        for(int i = 0;i!= specializationArgCount;++i){
            args[i] = specializationArgs->at(i)->duplicate();
        }
        auto* a = new slang_TypeReflection(this->specializeType(type_->value, args,
                                                                           specializationArgCount,
                                        reinterpret_cast<slang::IBlob **>(&outDiagnostics->value)));
        auto* ptr = new slang_TypeReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_TypeLayoutReflection_HEAP_PTR *
    slang_ISession::_getTypeLayout(slang_TypeReflection *type_, SlangInt targetIndex, slang_LayoutRules rules,
                                  slang_IBlob_PTR*outDiagnostics) {
        auto* a = new slang_TypeLayoutReflection(this->getTypeLayout(type_->value, targetIndex,
                                                                      static_cast<slang::LayoutRules>(rules),
                                                                 reinterpret_cast<slang::IBlob **>(&outDiagnostics->value)));
        auto* ptr = new slang_TypeLayoutReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_TypeReflection_HEAP_PTR *
    slang_ISession::_getContainerType(slang_TypeReflection *elementType, slang_ContainerType containerType,
                                     slang_IBlob_PTR *outDiagnostics) {
        auto* a = new slang_TypeReflection(this->getContainerType(elementType->value,
                                                                   static_cast<slang::ContainerType>(containerType),
                                                                   reinterpret_cast<slang::IBlob **>(&outDiagnostics->value)));
        auto* ptr = new slang_TypeReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_TypeReflection_HEAP_PTR *slang_ISession::_getDynamicType() {
        auto* a = new slang_TypeReflection(this->getDynamicType());
        auto* ptr = new slang_TypeReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    SlangResult slang_ISession::_getTypeRTTIMangledName(slang_TypeReflection *type, slang_IBlob_PTR *outNameBlob) {
        return this->getTypeRTTIMangledName(type->value, reinterpret_cast<slang::IBlob**>(&outNameBlob->value));
    }

    SlangResult slang_ISession::_getTypeConformanceWitnessMangledName(slang_TypeReflection *type,
                                                                     slang_TypeReflection *interfaceType,
                                                                     slang_IBlob_PTR *outNameBlob) {
        return this->getTypeConformanceWitnessMangledName(type->value, interfaceType->value, reinterpret_cast<slang::IBlob**>(outNameBlob->get_value()));
    }

    SlangResult slang_ISession::_getTypeConformanceWitnessSequentialID(slang_TypeReflection *type,
                                                                      slang_TypeReflection *interfaceType,
                                                                      slang_SIZE*outId) {
        uint32_t id;
        SlangResult res = this->getTypeConformanceWitnessSequentialID(type->value, interfaceType->value, &id);
        outId->set_value(id);
        return res;
    }

    SlangResult
    slang_ISession::_createTypeConformanceComponentType(slang_TypeReflection *type, slang_TypeReflection *interfaceType,
                                                       slang_ITypeConformance_PTR*outConformance,
                                                       SlangInt conformanceIdOverride, slang_IBlob_PTR *outDiagnostics) {
        return this->createTypeConformanceComponentType(
                type->value, interfaceType->value, reinterpret_cast<slang::ITypeConformance **>(&outConformance->value), conformanceIdOverride,
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

    slang_IModule *slang_ISession::_getLoadedModule(SlangInt index) {
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
        return this->createCompositeComponentType(
                reinterpret_cast<slang::IComponentType *const *>(componentTypes->data()),
                componentTypes->size(),
                reinterpret_cast<slang::IComponentType **>(&outCompositeComponentType->value),
                reinterpret_cast<slang::IBlob **>(&outDiagnostics->value));
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

    SlangResult slang_IGlobalSession::_createSession(slang_SessionDesc *desc, slang_ISession_PTR *outSession) {
        return this->createSession(desc->duplicate(),
                                   reinterpret_cast<slang::ISession **>(&outSession->value));
    }

    slang_CompilerOptionValue_HEAP_PTR* slang_CompilerOptionEntry::get_value() {
        auto* ptr = new slang_CompilerOptionValue_HEAP_PTR(new slang_CompilerOptionValue(value));
        ptr->shouldFreeData = true;
        return ptr;
    }

    void slang_CompilerOptionEntry::set_value(slang_CompilerOptionValue* value) {
        this->value = value->duplicate();
    }

    slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR *slang_TargetDesc::get_compilerOptionEntries() {
        auto* a = new slang_CompilerOptionEntry_VALUE_VECTOR();
        for(int i = 0;i!=value->compilerOptionEntryCount;++i){
            a->push_back(value->compilerOptionEntries[i]);
        }
        auto* ptr = new slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    void slang_TargetDesc::set_compilerOptionEntries(slang_CompilerOptionEntry_VALUE_VECTOR *compilerOptionEntries) {
        this->value->compilerOptionEntries = compilerOptionEntries->data();
    }

    slang_TargetDesc_VALUE_VECTOR_HEAP_PTR* slang_SessionDesc::get_targets() {
        auto* vec = new slang_TargetDesc_VALUE_VECTOR();
        vec->reserve(value->targetCount);
        for(int i = 0; i < value->targetCount; i++){
            (*vec)[i] = value->targets[i];
        }
        auto* ptr = new slang_TargetDesc_VALUE_VECTOR_HEAP_PTR(vec);
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
        this->value->fileSystem = fileSystem;
    }

    slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR *slang_SessionDesc::get_compilerOptionEntries() {
        auto*vec = new slang_CompilerOptionEntry_VALUE_VECTOR();
        vec->reserve(value->compilerOptionEntryCount);
        for(int i = 0;i!= value->compilerOptionEntryCount;++i){
            (*vec)[i] = value->compilerOptionEntries[i];
        }
        auto* ptr = new slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR(vec);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    void slang_SessionDesc::set_compilerOptionEntries(slang_CompilerOptionEntry_VALUE_VECTOR *compilerOptionEntries) {
        this->value->compilerOptionEntryCount = compilerOptionEntries->size();
        this->value->compilerOptionEntries = compilerOptionEntries->data();
    }

    slang_TypeReflection_HEAP_PTR *slang_UserAttribute::getArgumentType(uint32_t index) {
        auto* a = new slang_TypeReflection(this->value->getArgumentType(index));
        auto* ptr = new slang_TypeReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_TypeReflection_HEAP_PTR *slang_VariableReflection::getType() {
        auto* a = new slang_TypeReflection(this->value->getType());
        auto* ptr = new slang_TypeReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_TypeReflection_HEAP_PTR *slang_FunctionReflection::getReturnType() {
        auto* a = new slang_TypeReflection(this->value->getReturnType());
        auto* ptr = new slang_TypeReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_GenericReflection *slang_FunctionReflection::getGenericContainer() {
        return static_cast<slang_GenericReflection *>(this->value->getGenericContainer());
    }

    slang_TypeReflection_HEAP_PTR *slang_DeclReflection::getType() {
        auto* a = new slang_TypeReflection(this->value->getType());
        auto* ptr = new slang_TypeReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_GenericReflection *slang_DeclReflection::asGeneric() {
        return static_cast<slang_GenericReflection *>(this->value->asGeneric());
    }

    slang_TypeLayoutReflection_HEAP_PTR *slang_VariableLayoutReflection::getTypeLayout() {
        auto* a = new slang_TypeLayoutReflection(this->value->getTypeLayout());
        auto* ptr = new slang_TypeLayoutReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    slang_FunctionReflection_HEAP_PTR* slang_IEntryPoint::_getFunctionReflection() {
        auto* a = new slang_FunctionReflection(this->getFunctionReflection());
        auto* ptr = new slang_FunctionReflection_HEAP_PTR(a);
        ptr->set_shouldFreeData(true);
        return ptr;
    }

    godot::String slang_ICastable::_castAs(slang_UUID *uuid) {
        return (char*)(this->castAs(static_cast<SlangUUID>(*uuid)));
    }

    SlangResult slang_IUnknown::_query_interface(slang_UUID *guid, slang_VOID_PTR *outObj) {
        void *obj = nullptr;
        SlangResult res = this->queryInterface(guid->operator SlangUUID(), &obj);
        outObj->set_value(obj);
        return res;
    }
}
#endif