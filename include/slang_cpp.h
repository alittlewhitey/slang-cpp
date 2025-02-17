#ifndef SLANG_CPP
#define SLANG_CPP
#include <vector>
#include <functional>
#include <slang/include/slang.h>
#include <slang/source/core/slang-common.h>
#include <slang/source/core/slang-file-system.h>
#include <slang/source/core/slang-shared-library.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include "slang_enums.h"
namespace Slang{
    typedef ISlangFileSystem IFileSystem;
    typedef ISlangFileSystemExt IFileSystemExt;
    typedef ISlangMutableFileSystem IMutableFileSystem;
    typedef ISlangSharedLibrary ISharedLibrary;
}
using godot::memdelete;

#define MAKE_TEMPLATE_CLASS(ClassName)                                                                                                                  \
                                                                                                                                                      \
class slang_##ClassName##_HEAP_PTR : public slang_SlangObject{                                                                                    \
    GDCLASS(slang_##ClassName##_HEAP_PTR, slang_SlangObject)                                                                                      \
public:                                                                                                                                                 \
    bool shouldFreeData = 0;                                                                                                                            \
    bool isArr = 0;                                                                                                                                 \
    slang_##ClassName *value = nullptr;                                                                                                                     \
    void set_shouldFreeData(bool v){                                                                                                                    \
        this->shouldFreeData = v;                                                                                                                       \
    }                                                                                                                                                   \
    bool get_shouldFreeData(){                                                                                                                          \
        return this->shouldFreeData;                                                                                                                    \
    }                                                                                                                                                   \
    slang_##ClassName##_HEAP_PTR(slang_##ClassName* v): value(v){}                                                                    \
    slang_##ClassName##_HEAP_PTR(){}                                                                                                                    \
    operator slang_##ClassName *() const{                                                                                                               \
        return this->value;                                                                                                                             \
    }                                                                                                                                                   \
    void set_value(slang_##ClassName *v) {                                                                                                              \
        value = v;                                                                                                                                      \
    }                                                                                                                                                   \
    slang_##ClassName *get_value() const {                                                                                                                                                \
        return value;                                                                                                                                   \
    }                                                                                                                                                   \
    void free_self();                                                                                                                                                   \
private:                                                                                                                                                \
    static void _bind_methods() {                                                                                                                       \
        godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_##ClassName##_HEAP_PTR::set_value);                                   \
        godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_##ClassName##_HEAP_PTR::get_value);                                            \
        if constexpr(std::is_pointer_v<slang_##ClassName>)                                                                                              \
            godot::ClassDB::add_property("slang_" #ClassName "_HEAP_PTR", godot::PropertyInfo(godot::Variant::OBJECT, "value"),                         \
                                     "set_value", "get_value");                                                                                         \
        godot::ClassDB::bind_method(godot::D_METHOD("free_self"),&slang_##ClassName##_HEAP_PTR::free_self);                                             \
        godot::ClassDB::bind_method(godot::D_METHOD("set_shouldFreeData", "shouldFreeData"), &slang_##ClassName##_HEAP_PTR::set_shouldFreeData);        \
        godot::ClassDB::bind_method(godot::D_METHOD("get_shouldFreeData"), &slang_##ClassName##_HEAP_PTR::get_shouldFreeData);                          \
        godot::ClassDB::add_property("slang_" #ClassName "_HEAP_PTR", godot::PropertyInfo(godot::Variant::BOOL, "shouldFreeData"),                      \
                                     "set_shouldFreeData", "get_shouldFreeData");                                                                       \
    }                                                                                                                                                   \
};                                                                                                                                                      \
class slang_##ClassName##_VECTOR: public slang_SlangObject{                                                     \
GDCLASS(slang_##ClassName##_VECTOR, slang_SlangObject)                                                                                                  \
    static void _bind_methods() {                                                                                                                       \
        godot::ClassDB::bind_method(godot::D_METHOD("push_back", "t"), &slang_##ClassName##_VECTOR::push_back);                                         \
        godot::ClassDB::bind_method(godot::D_METHOD("pop_back"), &slang_##ClassName##_VECTOR::pop_back);                                                \
        godot::ClassDB::bind_method(godot::D_METHOD("size"), &slang_##ClassName##_VECTOR::size);                                                        \
        godot::ClassDB::bind_method(godot::D_METHOD("resize", "size"), &slang_##ClassName##_VECTOR::resize);                                            \
        godot::ClassDB::bind_method(godot::D_METHOD("clear"), &slang_##ClassName##_VECTOR::clear);                                                      \
        godot::ClassDB::bind_method(godot::D_METHOD("swap", "other"), &slang_##ClassName##_VECTOR::swap);                                               \
        godot::ClassDB::bind_method(godot::D_METHOD("set", "index", "t"), &slang_##ClassName##_VECTOR::set);                                            \
        godot::ClassDB::bind_method(godot::D_METHOD("at", "index"), &slang_##ClassName##_VECTOR::at);                                                   \
    }                                                                                                                                                   \
    std::vector<slang_##ClassName*> value;                                                                                                          \
public:                                                                                                                                                 \
    slang_##ClassName##_VECTOR():value(){}                                                                                    \
    slang_##ClassName##_VECTOR(int size):value(std::vector<slang_##ClassName*>(size)){}                                                                        \
    void push_back(slang_##ClassName* t){                                                                                                                                                 \
        value.push_back(t);                                                                                            \
    }                                                                                                                                                   \
    void pop_back(){                                                                                                                                    \
        value.pop_back();                                                                                              \
    }                                                                                                                                                   \
    int size(){                                                                                                                                         \
        return value.size();                                                                                           \
    }                                                                                                                                                   \
    void resize(int size){                                                                                                                              \
        value.resize(size);                                                                                            \
    }                                                                                                                                                   \
    void clear(){                                                                                                                                       \
        value.clear();                                                                                                 \
    }                                                                                                                                                   \
    void swap(slang_##ClassName##_VECTOR* other){                                                                                                       \
        value.swap(other->value);                                                                                            \
    }                                                                                                                                                   \
    slang_##ClassName*& operator[](int i){                                                                                                              \
        return value[i];                                                                                    \
    }                                                                                                                                                  \
    void set(int index,slang_##ClassName* t) {                                                                                                          \
        if (index >= value.size())                                                                                     \
            return;                                                                                                                                     \
        value[index] = t;                                                                                                                             \
    }                                                                                                                                                   \
    slang_##ClassName* at(int index) {                                                                                                                  \
        if (index >= value.size())                                                                                     \
            throw std::out_of_range("index out of range");                                                                                              \
        return value[index];                                                                                                                          \
    }                                                                                                                                                   \
};
#define MAKE_TEMPLATE_CLASS_SRC(ClassName) \
    void slang_##ClassName##_HEAP_PTR::free_self(){                                                                                                                                   \
        if(shouldFreeData){                                                                                                                             \
            if(isArr)                                                                                                                                   \
                delete[] this->value;                                                                                                                   \
            else                                                                                                                                        \
                godot::memdelete(this->value);                                                                                                                     \
            this->value = nullptr;                                                                                                                      \
        }                                                                                                                                               \
        godot::memdelete(this);                                                                                                                                    \
    }


#define MAKE_VALUE_TEMPLATE(ClassName)                                                                                                                  \
class slang_##ClassName##_VALUE : public slang_SlangObject{                                                                                             \
    GDCLASS(slang_##ClassName##_VALUE,slang_SlangObject)                                                                                                \
private:                                                                                                                                                \
    static void _bind_methods() {                                                                                                                       \
        godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_##ClassName##_VALUE::set_value);                                        \
    }                                                                                                                                                   \
public:                                                                                                                                                 \
    decltype(slang_##ClassName().duplicate()) value;                                                                                                    \
    slang_##ClassName##_VALUE(slang_##ClassName *v) : value(v->duplicate()) {}                                                                                      \
    void set_value(slang_##ClassName *v) {                                                                                                              \
        value = v->duplicate();                                                                                                                         \
    }                                                                                                                                                   \
};                                                                                                                                                      \
class slang_##ClassName##_VALUE_VECTOR: public slang_SlangObject,public std::vector<decltype(slang_##ClassName().duplicate())> {                        \
GDCLASS(slang_##ClassName##_VALUE_VECTOR, slang_SlangObject)                                                                                            \
    static void _bind_methods() {                                                                                                                       \
        godot::ClassDB::bind_method(godot::D_METHOD("push_back", "t"), &slang_##ClassName##_VALUE_VECTOR::push_back_p);                                   \
        godot::ClassDB::bind_method(godot::D_METHOD("pop_back"), &slang_##ClassName##_VALUE_VECTOR::pop_back);                                          \
        godot::ClassDB::bind_method(godot::D_METHOD("size"), &slang_##ClassName##_VALUE_VECTOR::size);                                                  \
        godot::ClassDB::bind_method(godot::D_METHOD("resize", "size"), &slang_##ClassName##_VALUE_VECTOR::resize);                                      \
        godot::ClassDB::bind_method(godot::D_METHOD("clear"), &slang_##ClassName##_VALUE_VECTOR::clear);                                                \
        godot::ClassDB::bind_method(godot::D_METHOD("swap", "other"), &slang_##ClassName##_VALUE_VECTOR::swap);                                         \
        godot::ClassDB::bind_method(godot::D_METHOD("set", "index", "t"), &slang_##ClassName##_VALUE_VECTOR::set);                                      \
    }                                                                                                                                                   \
public:                                                                                                                                                 \
    slang_##ClassName##_VALUE_VECTOR():std::vector<decltype(slang_##ClassName().duplicate())>(){}                                                       \
    slang_##ClassName##_VALUE_VECTOR(int size):std::vector<decltype(slang_##ClassName().duplicate())>(size){}                                           \
    void push_back_p(slang_##ClassName* t){                                                                                                               \
        this->std::vector<decltype(slang_##ClassName().duplicate())>::push_back(t->duplicate());                                                        \
    }void push_back(slang_##ClassName t){                                                                                                               \
        this->std::vector<decltype(slang_##ClassName().duplicate())>::push_back(t.duplicate());                                                         \
    }                                                                                                                                                   \
    void pop_back(){                                                                                                                                    \
        this->std::vector<decltype(slang_##ClassName().duplicate())>::pop_back();                                                                       \
    }                                                                                                                                                   \
    int size(){                                                                                                                                         \
        return this->std::vector<decltype(slang_##ClassName().duplicate())>::size();                                                                    \
    }                                                                                                                                                   \
    void resize(int size){                                                                                                                              \
        this->std::vector<decltype(slang_##ClassName().duplicate())>::resize(size);                                                                     \
    }                                                                                                                                                   \
    void clear(){                                                                                                                                       \
        this->std::vector<decltype(slang_##ClassName().duplicate())>::clear();                                                                          \
    }                                                                                                                                                   \
    void swap(slang_##ClassName##_VALUE_VECTOR* other){                                                                                                 \
        this->std::vector<decltype(slang_##ClassName().duplicate())>::swap(*other);                                                                     \
    }                                                                                                                                                   \
    decltype(slang_##ClassName().duplicate())& operator[](int i){                                                                                       \
        return this->std::vector<decltype(slang_##ClassName().duplicate())>::operator[](i);                                                             \
    }                                                                                                                                                   \
    void set(int index,slang_##ClassName* t) {                                                                                                          \
        if (index >= this->std::vector<decltype(slang_##ClassName().duplicate())>::size())                                                              \
            return;                                                                                                                                     \
        (*this)[index] = t->duplicate();                                                                                                                \
    }                                                                                                                                                   \
};                                                                                                                                                      \
class slang_##ClassName##_VALUE_VECTOR_PTR : public slang_SlangObject{                                                                                               \
    GDCLASS(slang_##ClassName##_VALUE_VECTOR_PTR,slang_SlangObject)                                                                                                  \
private:                                                                                                                                                \
    static void _bind_methods() {                                                                                                                       \
        godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_##ClassName##_VALUE_VECTOR_PTR::set_value);                                        \
        godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_##ClassName##_VALUE_VECTOR_PTR::get_value);                                                 \
        if constexpr(std::is_pointer_v<slang_##ClassName##_VALUE_VECTOR>)                                                                                              \
            godot::ClassDB::add_property("slang_" #ClassName "_VALUE_VECTOR_PTR", godot::PropertyInfo(godot::Variant::OBJECT, "value"),                              \
                                     "set_value", "get_value");                                                                                         \
    }                                                                                                                                                   \
public:                                                                                                                                                 \
    slang_##ClassName##_VALUE_VECTOR *value = nullptr;                                                                                                                 \
    slang_##ClassName##_VALUE_VECTOR_PTR(slang_##ClassName##_VALUE_VECTOR *v = nullptr) : value(v) {}                                                                               \
    operator slang_##ClassName##_VALUE_VECTOR *() const {                                                                                                              \
        return value;                                                                                                                                   \
    }                                                                                                                                                   \
    void set_value(slang_##ClassName##_VALUE_VECTOR *v) {                                                                                                              \
        value = v;                                                                                                                                      \
    }                                                                                                                                                   \
    slang_##ClassName##_VALUE_VECTOR *get_value() const {                                                                                                              \
        return value;                                                                                                                                   \
    }                                                                                                                                                   \
};                                                                                                                                                      \
class slang_##ClassName##_VALUE_VECTOR_HEAP_PTR : public slang_##ClassName##_VALUE_VECTOR_PTR{                                                                                    \
    GDCLASS(slang_##ClassName##_VALUE_VECTOR_HEAP_PTR, slang_##ClassName##_VALUE_VECTOR_PTR)                                                                                      \
public:                                                                                                                                                 \
    bool shouldFreeData = 0;                                                                                                                            \
    bool isArr = 0;                                                                                                                                     \
    void set_shouldFreeData(bool v){                                                                                                                    \
        this->shouldFreeData = v;                                                                                                                       \
    }                                                                                                                                                   \
    bool get_shouldFreeData(){                                                                                                                          \
        return this->shouldFreeData;                                                                                                                    \
    }                                                                                                                                                   \
    slang_##ClassName##_VALUE_VECTOR_HEAP_PTR(slang_##ClassName##_VALUE_VECTOR* v = nullptr): slang_##ClassName##_VALUE_VECTOR_PTR(v){}                                                          \
    operator slang_##ClassName##_VALUE_VECTOR *() const{                                                                                                               \
        return this->value;                                                                                                                             \
    }                                                                                                                                                   \
    void free_self(){                                                                                                                                   \
        if(shouldFreeData){                                                                                                                             \
            if(isArr)                                                                                                                                   \
                delete[] this->value;                                                                                                                   \
            else                                                                                                                                        \
                godot::memdelete(this->value);                                                                                                                     \
            this->value = nullptr;                                                                                                                      \
        }                                                                                                                                               \
        godot::memdelete(this);                                                                                                                                    \
    }                                                                                                                                                   \
private:                                                                                                                                                \
    static void _bind_methods() {                                                                                                                       \
        godot::ClassDB::bind_method(godot::D_METHOD("free_self"),&slang_##ClassName##_VALUE_VECTOR_HEAP_PTR::free_self);                                             \
        godot::ClassDB::bind_method(godot::D_METHOD("set_shouldFreeData", "shouldFreeData"), &slang_##ClassName##_VALUE_VECTOR_HEAP_PTR::set_shouldFreeData);        \
        godot::ClassDB::bind_method(godot::D_METHOD("get_shouldFreeData"), &slang_##ClassName##_VALUE_VECTOR_HEAP_PTR::get_shouldFreeData);                          \
        godot::ClassDB::add_property("slang_" #ClassName "_VALUE_VECTOR_HEAP_PTR", godot::PropertyInfo(godot::Variant::BOOL, "shouldFreeData"),                      \
                                     "set_shouldFreeData", "get_shouldFreeData");                                                                       \
    }                                                                                                                                                   \
};



namespace slang_cpp {

    class slang_SlangObject : public godot::Object {
    GDCLASS(slang_SlangObject, godot::Object)
    public:
        static void _bind_methods() {}
    };
    MAKE_TEMPLATE_CLASS(SlangObject)

    class slang_NULL;

    MAKE_TEMPLATE_CLASS(NULL)

    class slang_INT;

    MAKE_TEMPLATE_CLASS(INT)

    class slang_SIZE;

    MAKE_TEMPLATE_CLASS(SIZE)

    class slang_BOOL;

    MAKE_TEMPLATE_CLASS(BOOL)

    class slang_DOUBLE;

    MAKE_TEMPLATE_CLASS(DOUBLE)

    class slang_SlangRef;

    MAKE_TEMPLATE_CLASS(SlangRef)

    class slang_IUnknown;

    MAKE_TEMPLATE_CLASS(IUnknown)

    class slang_IGlobalSession;

    MAKE_TEMPLATE_CLASS(IGlobalSession)

    class slang_ISession;

    MAKE_TEMPLATE_CLASS(ISession)

    class slang_IBlob;

    MAKE_TEMPLATE_CLASS(IBlob)

    class slang_ICastable;

    MAKE_TEMPLATE_CLASS(ICastable)

    class slang_IFileSystem;

    MAKE_TEMPLATE_CLASS(IFileSystem)

    class slang_IFileSystemExt;

    MAKE_TEMPLATE_CLASS(IFileSystemExt)

    class slang_IMutableFileSystem;

    MAKE_TEMPLATE_CLASS(IMutableFileSystem)

    class slang_ISharedLibrary;

    MAKE_TEMPLATE_CLASS(ISharedLibrary)

    class slang_ISharedLibraryLoader;

    MAKE_TEMPLATE_CLASS(ISharedLibraryLoader)

    class slang_IComponentType;

    MAKE_TEMPLATE_CLASS(IComponentType)

    class slang_ITypeConformance;

    MAKE_TEMPLATE_CLASS(ITypeConformance)

    class slang_IEntryPoint;

    MAKE_TEMPLATE_CLASS(IEntryPoint)

    class slang_IModule;

    MAKE_TEMPLATE_CLASS(IModule)

    class slang_IWriter;

    MAKE_TEMPLATE_CLASS(IWriter)

    class slang_IProfiler;

    MAKE_TEMPLATE_CLASS(IProfiler)

    class slang_ICompileRequest;

    MAKE_TEMPLATE_CLASS(ICompileRequest)

    class slang_UUID;

    MAKE_TEMPLATE_CLASS(UUID)

    class slang_CompilerOptionValue;

    MAKE_TEMPLATE_CLASS(CompilerOptionValue)

    class slang_CompilerOptionEntry;

    MAKE_TEMPLATE_CLASS(CompilerOptionEntry)

    class slang_PreprocessorMacroDesc;

    MAKE_TEMPLATE_CLASS(PreprocessorMacroDesc)

    class slang_TargetDesc;

    MAKE_TEMPLATE_CLASS(TargetDesc)

    class slang_SessionDesc;

    MAKE_TEMPLATE_CLASS(SessionDesc)

    class slang_Modifier;

    MAKE_TEMPLATE_CLASS(Modifier)

    class slang_UserAttribute;

    MAKE_TEMPLATE_CLASS(UserAttribute)

    class slang_FunctionReflection;

    MAKE_TEMPLATE_CLASS(FunctionReflection)

    class slang_DeclReflection;

    MAKE_TEMPLATE_CLASS(DeclReflection)

    class slang_GenericReflection;

    MAKE_TEMPLATE_CLASS(GenericReflection)

    class slang_VariableReflection;

    MAKE_TEMPLATE_CLASS(VariableReflection)

    class slang_VariableLayoutReflection;

    MAKE_TEMPLATE_CLASS(VariableLayoutReflection)

    class slang_TypeReflection;

    MAKE_TEMPLATE_CLASS(TypeReflection)

    class slang_SlangReflectionGeneric;

    MAKE_TEMPLATE_CLASS(SlangReflectionGeneric)

    class slang_TypeLayoutReflection;

    MAKE_TEMPLATE_CLASS(TypeLayoutReflection)

    class slang_TypeParameterReflection;

    MAKE_TEMPLATE_CLASS(TypeParameterReflection)

    class slang_EntryPointReflection;

    MAKE_TEMPLATE_CLASS(EntryPointReflection)

    class slang_ShaderReflection;

    MAKE_TEMPLATE_CLASS(ShaderReflection)

    typedef slang_ShaderReflection slang_ProgramLayout;

    class slang_SpecializationArg;

    MAKE_TEMPLATE_CLASS(SpecializationArg)

    class slang_global;

    class slang_NULL : public slang_SlangObject {
    GDCLASS(slang_NULL, slang_SlangObject)
        static void _bind_methods() {}
    };



    class slang_VOID_PTR: public slang_SlangObject{
    GDCLASS(slang_VOID_PTR, slang_SlangObject)
    protected:
        void* value = nullptr;

    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value_s", "value"), &slang_VOID_PTR::set_value_s);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value_s"), &slang_VOID_PTR::get_value_s);
            godot::ClassDB::add_property("slang_VOID_PTR", godot::PropertyInfo(godot::Variant::OBJECT, "value"),
                                         "set_value_s", "get_value_s");
        }

    public:
        slang_VOID_PTR(void *v = nullptr) : value(v) {}

        operator void *() const {
            return value;
        }

        void set_value(void *v) {
            value = v;
        }
        void *get_value() const {
            return value;
        }

        void set_value_s(godot::String v) {
            value = (void*)v.utf8().get_data();
        }
        godot::String get_value_s() const {
            if(value == nullptr)
                return "";
            return godot::String::utf8((char*)value);
        }
    };

    class slang_INT : public slang_SlangObject {
    GDCLASS(slang_INT, slang_SlangObject)

        int64_t value = 0;

        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_INT::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_INT::get_value);
            godot::ClassDB::add_property("slang_INT", godot::PropertyInfo(godot::Variant::INT, "value"),
                                         "set_value", "get_value");
        }

    public:
        slang_INT(int64_t v = 0) : value(v) {}

        operator int64_t() const {
            return value;
        }

        void set_value(int64_t v) {
            value = v;
        }

        [[nodiscard]] int64_t get_value() const {
            return value;
        }
    };



    class slang_BOOL : public slang_SlangObject {
    GDCLASS(slang_BOOL, slang_SlangObject)

        bool value : 1 = false;

        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_BOOL::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_BOOL::get_value);
            godot::ClassDB::add_property("slang_BOOL", godot::PropertyInfo(godot::Variant::BOOL, "value"),
                                         "set_value", "get_value");
        }

    public:
        slang_BOOL(bool v = false) : value(v) {}

        operator bool() const {
            return value;
        }

        void set_value(bool v) {
            value = v;
        }

        [[nodiscard]] bool get_value() const {
            return value;
        }
    };



    class slang_DOUBLE : public slang_SlangObject {
    GDCLASS(slang_DOUBLE, slang_SlangObject)

        double value = 0;

        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_DOUBLE::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_DOUBLE::get_value);
            godot::ClassDB::add_property("slang_DOUBLE", godot::PropertyInfo(godot::Variant::FLOAT, "value"),
                                         "set_value", "get_value");
        }

    public:
        slang_DOUBLE(double v = 0) : value(v) {}

        operator double() const {
            return value;
        }

        void set_value(double v) {
            value = v;
        }

        double get_value() const {
            return value;
        }
    };


    class slang_SIZE : public slang_SlangObject {
    GDCLASS(slang_SIZE, slang_SlangObject)

        size_t value = 0;

        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_SIZE::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_SIZE::get_value);
            godot::ClassDB::add_property("slang_SIZE", godot::PropertyInfo(godot::Variant::INT, "value"),
                                         "set_value", "get_value");
        }

    public:
        slang_SIZE(size_t v = 0) : value(v) {}

        operator size_t() const {
            return value;
        }

        void set_value(size_t v) {
            value = v;
        }

        size_t get_value() const {
            return value;
        }
    };



    template<typename Type>
    class slang_ENUM : public slang_SlangObject {
    GDCLASS(slang_ENUM<Type>, slang_SlangObject)
        Type value = 0;
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_ENUM<Type>::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_ENUM<Type>::get_value);
            godot::ClassDB::add_property("slang_ENUM", godot::PropertyInfo(godot::Variant::INT, "value"),
                                         "set_value", "get_value");
        }
    public:
        slang_ENUM(Type v = 0) : value(v) {}

        operator Type() const {
            return value;
        }
        void set_value(Type v) {
            value = v;
        }
        Type get_value() const {
            return value;
        }
    };
    template<typename _Signature>
    class slang_Callable;
    template<typename _Res, typename... _ArgTypes>
    class slang_Callable<_Res(_ArgTypes...)> : public slang_SlangObject{
        GDCLASS(slang_Callable<_Res(_ArgTypes...)> , slang_SlangObject)
        std::function<_Res(_ArgTypes...)> func;
    public:
        slang_Callable(){
            func = nullptr;
        }
        slang_Callable(std::function<_Res(_ArgTypes...)> f) : func(f) {}
        static void _bind_methods(){}
        _Res operator()(_ArgTypes... args) const {
            return func(args...);
        }
        void set_func(std::function<_Res(_ArgTypes...)> f) {
            func = f;
        }
        std::function<_Res(_ArgTypes...)> get_func() const {
            return func;
        }
    };
    class slang_SlangRef : public godot::Object {
    GDCLASS(slang_SlangRef, godot::Object)
    public:
        static void _bind_methods() {}
    };

    class slang_IUnknown : public slang_SlangRef{
    GDCLASS(slang_IUnknown, slang_SlangRef)
    public:
        ISlangUnknown* value = nullptr;
        ISlangUnknown* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IUnknown() = default;
        slang_IUnknown(ISlangUnknown* ival):value(ival){}
        void operator=(ISlangUnknown* ival){
            value = ival;
        }
        operator ISlangUnknown*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IUnknown::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("query_interface", "guid", "outObj"),
                                        &slang_IUnknown::_query_interface);
            godot::ClassDB::bind_method(godot::D_METHOD("add_ref"), &slang_IUnknown::_add_ref);
            godot::ClassDB::bind_method(godot::D_METHOD("release"), &slang_IUnknown::_release);
        }

        SlangResult _query_interface(slang_UUID *guid, slang_VOID_PTR *outObj);

        uint32_t _add_ref() {
            return value->addRef();
        }

        uint32_t _release() {
            return value->release();
        }
    };

    class slang_IGlobalSession : public slang_SlangRef{
    GDCLASS(slang_IGlobalSession, slang_SlangRef)
    public:
        slang::IGlobalSession* value = nullptr;
        slang::IGlobalSession* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IGlobalSession() = default;
        slang_IGlobalSession(slang::IGlobalSession* ival):value(ival){}
        void operator=(slang::IGlobalSession* ival){
            value = ival;
        }
        operator slang::IGlobalSession*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IGlobalSession::has_value);
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_NONE)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_FXC)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_DXC)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_GLSLANG)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_SPIRV_DIS)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_CLANG)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_VISUAL_STUDIO)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_GCC)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_GENERIC_C_CPP)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_NVRTC)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_LLVM)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_SPIRV_OPT)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_METAL)
            BIND_ENUM_CONSTANT(slang_SlangPassThrough::SLANG_PASS_THROUGH_COUNT_OF)

            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_UNKNOWN)
            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_SLANG)
            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_HLSL)
            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_GLSL)
            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_C)
            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_CPP)
            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_CUDA)
            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_SPIRV)
            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_METAL)
            BIND_ENUM_CONSTANT(slang_SlangSourceLanguage::SLANG_SOURCE_LANGUAGE_COUNT_OF)
            godot::ClassDB::bind_method(godot::D_METHOD("createSession", "desc", "outSession"),
                                        &slang_IGlobalSession::_createSession);
            godot::ClassDB::bind_method(godot::D_METHOD("findProfile", "name"), &slang_IGlobalSession::_findProfile);
            godot::ClassDB::bind_method(godot::D_METHOD("setDownstreamCompilerPath", "passThrough", "path"),
                                        &slang_IGlobalSession::_setDownstreamCompilerPath);
            godot::ClassDB::bind_method(godot::D_METHOD("setDownstreamCompilerPrelude", "passThrough", "preludeText"),
                                        &slang_IGlobalSession::_setDownstreamCompilerPrelude);
            godot::ClassDB::bind_method(godot::D_METHOD("getDownstreamCompilerPrelude", "passThrough", "outPrelude"),
                                        &slang_IGlobalSession::_getDownstreamCompilerPrelude);
            godot::ClassDB::bind_method(godot::D_METHOD("getBuildTagString"), &slang_IGlobalSession::_getBuildTagString);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("setDefaultDownstreamCompiler", "sourceLanguage", "defaultCompiler"),
                    &slang_IGlobalSession::_setDefaultDownstreamCompiler);
            godot::ClassDB::bind_method(godot::D_METHOD("getDefaultDownstreamCompiler", "sourceLanguage"),
                                        &slang_IGlobalSession::_getDefaultDownstreamCompiler);
            godot::ClassDB::bind_method(godot::D_METHOD("setLanguagePrelude", "sourceLanguage", "preludeText"),
                                        &slang_IGlobalSession::_setLanguagePrelude);
            godot::ClassDB::bind_method(godot::D_METHOD("getLanguagePrelude", "sourceLanguage", "outPrelude"),
                                        &slang_IGlobalSession::_getLanguagePrelude);
            godot::ClassDB::bind_method(godot::D_METHOD("createCompileRequest", "outCompileRequest"),
                                        &slang_IGlobalSession::_createCompileRequest);
            godot::ClassDB::bind_method(godot::D_METHOD("addBuiltins", "sourcePath", "sourceString"),
                                        &slang_IGlobalSession::_addBuiltins);
            godot::ClassDB::bind_method(godot::D_METHOD("setSharedLibraryLoader", "loader"),
                                        &slang_IGlobalSession::_setSharedLibraryLoader);
            godot::ClassDB::bind_method(godot::D_METHOD("getSharedLibraryLoader"),
                                        &slang_IGlobalSession::_getSharedLibraryLoader);
            godot::ClassDB::bind_method(godot::D_METHOD("checkCompileTargetSupport", "target"),
                                        &slang_IGlobalSession::_checkCompileTargetSupport);
            godot::ClassDB::bind_method(godot::D_METHOD("checkPassThroughSupport", "passThrough"),
                                        &slang_IGlobalSession::_checkPassThroughSupport);
            godot::ClassDB::bind_method(godot::D_METHOD("compileStdLib", "flags"),
                                        &slang_IGlobalSession::_compileStdLib);
            godot::ClassDB::bind_method(godot::D_METHOD("loadStdLib", "stdLib","stdLibSizeInBytes"),
                                        &slang_IGlobalSession::_loadStdLib);
            BIND_ENUM_CONSTANT(slang_SlangCapabilityID::SLANG_CAPABILITY_UNKNOWN)
            godot::ClassDB::bind_method(godot::D_METHOD("findCapability", "name"),
                                        &slang_IGlobalSession::_findCapability);
            godot::ClassDB::bind_method(godot::D_METHOD("setDownstreamCompilerForTransition", "source", "tartget"),
                                        &slang_IGlobalSession::_setDownstreamCompilerForTransition);
            godot::ClassDB::bind_method(godot::D_METHOD("getDownstreamCompilerForTransition", "source", "target"),
                                        &slang_IGlobalSession::_getDownstreamCompilerForTransition);
            godot::ClassDB::bind_method(godot::D_METHOD("getCompilerElapsedTime", "outTotalTime", "outDownstreamTime"),
                                        &slang_IGlobalSession::_getCompilerElapsedTime);
            godot::ClassDB::bind_method(godot::D_METHOD("setSPIRVCoreGrammar", "jsonPath"),
                                        &slang_IGlobalSession::_setSPIRVCoreGrammar);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("parseCommandLineArguments", "args", "outSessionDesc", "outAuxAllocation"),
                    &slang_IGlobalSession::_parseCommandLineArguments);
            godot::ClassDB::bind_method(godot::D_METHOD("getSessionDescDigest", "sessionDesc", "outBlob"),
                                        &slang_IGlobalSession::_getSessionDescDigest);
        }

    public:
        SlangResult _createSession(slang_SessionDesc *desc, slang_ISession* outSession);

        slang_SlangProfileID _findProfile(godot::String name) noexcept {
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            return static_cast<slang_SlangProfileID>(value->findProfile(name.utf8().get_data()));
        }

        void _setDownstreamCompilerPath(slang_SlangPassThrough passThrough, godot::String path) {
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->setDownstreamCompilerPath((SlangPassThrough) passThrough,
                                                                          path.utf8().get_data());
        }

        void _setDownstreamCompilerPrelude(slang_SlangPassThrough passThrough, godot::String preludeText) {
            return value->setDownstreamCompilerPrelude((SlangPassThrough) passThrough,
                                                                             preludeText.utf8().get_data());
        }

        void _getDownstreamCompilerPrelude(slang_SlangPassThrough passThrough, slang_IBlob*outPrelude);

        godot::String _getBuildTagString() {
            auto a = value->getBuildTagString();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }

        SlangResult _setDefaultDownstreamCompiler(slang_SlangSourceLanguage sourceLanguage, slang_SlangPassThrough defaultCompiler) {
            return value->setDefaultDownstreamCompiler(
                    static_cast<SlangSourceLanguage>(sourceLanguage), static_cast<SlangPassThrough>(defaultCompiler));
        }

        int _getDefaultDownstreamCompiler(slang_SlangSourceLanguage sourceLanguage) {
            return value->getDefaultDownstreamCompiler(
                    static_cast<SlangSourceLanguage>(sourceLanguage));
        }

        void _setLanguagePrelude(slang_SlangSourceLanguage sourceLanguage, godot::String preludeText) {
            return value->setLanguagePrelude(
                    static_cast<SlangSourceLanguage>(sourceLanguage), preludeText.utf8().get_data());
        }

        void _getLanguagePrelude(slang_SlangSourceLanguage sourceLanguage, slang_IBlob*outPrelude);

        SlangResult _createCompileRequest(slang_ICompileRequest*outCompileRequest);

        void _addBuiltins(godot::String sourcePath, godot::String sourceString) {
            sourcePath = godot::ProjectSettings::get_singleton()->globalize_path(sourcePath);
            return value->addBuiltins(sourcePath.utf8().get_data(),
                                                            sourceString.utf8().get_data());
        }

        void _setSharedLibraryLoader(slang_ISharedLibraryLoader *loader) const;

        slang_ISharedLibraryLoader *_getSharedLibraryLoader(slang_NULL *null);

        SlangResult _checkCompileTargetSupport(slang_SlangCompileTarget target) {
            return value->checkCompileTargetSupport(static_cast<SlangCompileTarget>(target));
        }

        SlangResult _checkPassThroughSupport(slang_SlangPassThrough passThrough) {
            return value->checkPassThroughSupport(static_cast<SlangPassThrough>(passThrough));
        }

        SlangResult _compileStdLib(slang::CompileStdLibFlags flags) {
            return value->compileStdLib(flags);
        }

        SlangResult _loadStdLib(slang_VOID_PTR* stdLib, size_t stdLibSizeInBytes) {
            return value->loadStdLib(stdLib->get_value(), stdLibSizeInBytes);
        }

        SlangResult _saveStdLib(SlangArchiveType archiveType,slang_IBlob*outBlob);

        slang_SlangCapabilityID _findCapability(godot::String name) {
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            return static_cast<slang_SlangCapabilityID>(value->findCapability(
                    name.utf8().get_data()));
        }

        void _setDownstreamCompilerForTransition(slang_SlangCompileTarget source, slang_SlangCompileTarget target,
                                                slang_SlangPassThrough passThrough) {
            return value->setDownstreamCompilerForTransition(
                    static_cast<SlangCompileTarget>(source),
                    static_cast<SlangCompileTarget>(target),
                    static_cast<SlangPassThrough>(passThrough));
        }

        slang_SlangPassThrough
        _getDownstreamCompilerForTransition(slang_SlangCompileTarget source, slang_SlangCompileTarget target) {
            return static_cast<slang_SlangPassThrough>(value->getDownstreamCompilerForTransition(
                    static_cast<SlangCompileTarget>(source), static_cast<SlangCompileTarget>(target)));
        }

        void _getCompilerElapsedTime(slang_DOUBLE *outTotalTime, slang_DOUBLE *outDownstreamTime) {
            double totalTime, downstreamTime;
            value->getCompilerElapsedTime(&totalTime, &downstreamTime);
            outTotalTime->set_value(totalTime);
            outDownstreamTime->set_value(downstreamTime);
        }

        SlangResult _setSPIRVCoreGrammar(godot::String jsonPath) {
            jsonPath = godot::ProjectSettings::get_singleton()->globalize_path(jsonPath);
            return value->setSPIRVCoreGrammar(jsonPath.utf8().get_data());
        }

        SlangResult
        _parseCommandLineArguments(godot::TypedArray<godot::String> args, slang_SessionDesc *outSessionDesc,
                                  slang_IUnknown*outAuxAllocation);

        SlangResult _getSessionDescDigest(slang_SessionDesc *sessionDesc, slang_IBlob*outBlob);
    };

    class slang_ISession : public slang_SlangRef{
    GDCLASS(slang_ISession, slang_SlangRef)
    public:
        slang::ISession* value = nullptr;
        slang::ISession* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_ISession() = default;
        slang_ISession(slang::ISession* ival):value(ival){}
        void operator=(slang::ISession* ival){
            value = ival;
        }
        operator slang::ISession*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_ISession::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("loadModule", "moduleName", "outDiagnostics"),
                                        &slang_ISession::_loadModule);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("loadModuleFromSource", "moduleName", "path", "source", "outDiagnostics"),
                    &slang_ISession::_loadModuleFromSource);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("createCompositeComponentType", "componentTypes",
                                    "outCompositeComponentType", "outDiagnostics"),
                    &slang_ISession::_createCompositeComponentType);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("specializeType", "type_", "specializationArgs", "specializationArgCount",
                                    "outDiagnostics"), &slang_ISession::_specializeType);
            BIND_ENUM_CONSTANT(slang_LayoutRules::Default)
            BIND_ENUM_CONSTANT(slang_LayoutRules::MetalArgumentBufferTier2)
            godot::ClassDB::bind_method(
                    godot::D_METHOD("getTypeLayout", "type_", "targetIndex", "rules", "outDiagnostics"),
                    &slang_ISession::_getTypeLayout);
            BIND_ENUM_CONSTANT(slang_ContainerType::None)
            BIND_ENUM_CONSTANT(slang_ContainerType::UnsizedArray)
            BIND_ENUM_CONSTANT(slang_ContainerType::StructuredBuffer)
            BIND_ENUM_CONSTANT(slang_ContainerType::ConstantBuffer)
            BIND_ENUM_CONSTANT(slang_ContainerType::ParameterBlock)
            godot::ClassDB::bind_method(godot::D_METHOD("getContainerType","elementType","containerType","outDiagnostics"),&slang_ISession::_getContainerType);
            godot::ClassDB::bind_method(godot::D_METHOD("getDynamicType"), &slang_ISession::_getDynamicType);
            godot::ClassDB::bind_method(godot::D_METHOD("getTypeRTTIMangledName", "type_", "outNameBlob"),
                                        &slang_ISession::_getTypeRTTIMangledName);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("getTypeConformanceWitnessMangledName", "type_", "interfaceType", "outNameBlob"),
                    &slang_ISession::_getTypeConformanceWitnessMangledName);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("getTypeConformanceWitnessSequentialID", "type_", "interfaceType", "outId"),
                    &slang_ISession::_getTypeConformanceWitnessSequentialID);
            godot::ClassDB::bind_method(godot::D_METHOD("createCompileRequest", "outCompileRequest"),
                                        &slang_ISession::_createCompileRequest);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("createTypeConformanceComponentType", "type_", "interfaceType", "outConformance",
                                    "conformanceIdOverride", "outDiagnostics"),
                    &slang_ISession::_createTypeConformanceComponentType);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("loadModuleFromIRBlob", "moduleName", "path", "source", "outDiagnostics"),
                    &slang_ISession::_loadModuleFromIRBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("getLoadedModuleCount"), &slang_ISession::_getLoadedModuleCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getLoadedModule"), &slang_ISession::_getLoadedModule);
            godot::ClassDB::bind_method(godot::D_METHOD("isBinaryModuleUpToDate", "modulePath", "binaryModuleBlob"),
                                        &slang_ISession::_isBinaryModuleUpToDate);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("loadModuleFromSourceString", "moduleName", "path", "string", "outDiagnostics"),
                    &slang_ISession::_loadModuleFromSourceString);
        }

    public:
        slang_IModule_HEAP_PTR *_loadModule(godot::String moduleName, slang_IBlob *outDiagnostics) const;

        slang_IModule *_loadModuleFromSource(godot::String moduleName, godot::String path, slang_IBlob *source,
                                            slang_IBlob*outDiagnostics) const;
        SlangResult _createCompositeComponentType(slang_IComponentType_VECTOR* componentTypes,
                                                                  slang_IComponentType *outCompositeComponentType,
                                                                  slang_IBlob *outDiagnostics);
        slang_TypeReflection_HEAP_PTR* _specializeType(slang_TypeReflection* type_, slang_SpecializationArg_VECTOR* specializationArgs, SlangInt specializationArgCount, slang_IBlob* outDiagnostics) const;
        slang_TypeLayoutReflection_HEAP_PTR* _getTypeLayout(slang_TypeReflection* type_, SlangInt targetIndex, slang_LayoutRules rules, slang_IBlob* outDiagnostics) const;
        slang_TypeReflection_HEAP_PTR* _getContainerType(slang_TypeReflection* elementType, slang_ContainerType containerType, slang_IBlob* outDiagnostics);
        slang_TypeReflection_HEAP_PTR* _getDynamicType();
        SlangResult _getTypeRTTIMangledName(slang_TypeReflection* type, slang_IBlob* outNameBlob);
        SlangResult _getTypeConformanceWitnessMangledName(slang_TypeReflection* type, slang_TypeReflection* interfaceType, slang_IBlob* outNameBlob);
        SlangResult _getTypeConformanceWitnessSequentialID(slang_TypeReflection* type, slang_TypeReflection* interfaceType, slang_SIZE* outId);
        SlangResult _createCompileRequest(slang_ICompileRequest*outCompileRequest);
        SlangResult _createTypeConformanceComponentType(slang_TypeReflection* type, slang_TypeReflection* interfaceType, slang_ITypeConformance* outConformance, SlangInt conformanceIdOverride, slang_IBlob* outDiagnostics);
        slang_IModule *_loadModuleFromIRBlob(godot::String moduleName, godot::String path, slang_IBlob *source, slang_IBlob *outDiagnostics);
        SlangInt _getLoadedModuleCount() {
            return value->getLoadedModuleCount();
        }
        slang_IModule_HEAP_PTR *_getLoadedModule(SlangInt index);
        bool _isBinaryModuleUpToDate(godot::String modulePath, slang_IBlob *binaryModuleBlob);
        slang_IModule_HEAP_PTR *_loadModuleFromSourceString(godot::String moduleName, godot::String path, godot::String string, slang_IBlob *outDiagnostics);
    };

    class slang_IBlob : public slang_SlangRef{
    GDCLASS(slang_IBlob, slang_SlangRef)
    public:
        slang::IBlob* value = nullptr;
        slang::IBlob* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IBlob() = default;
        slang_IBlob(slang::IBlob* ival): value(ival){}
        void operator=(slang::IBlob* ival){
            value = ival;
        }
        operator slang::IBlob*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IBlob::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("getBufferPointer"), &slang_IBlob::_getBufferPointer);
            godot::ClassDB::bind_method(godot::D_METHOD("getBufferSize"), &slang_IBlob::_getBufferSize);
        }
    public:
        godot::String _getBufferPointer(){
            auto a = (char*)(value->getBufferPointer());
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        size_t _getBufferSize(){
            return value->getBufferSize();
        }
    };

    class slang_ICastable : public slang_SlangRef{
    GDCLASS(slang_ICastable, slang_SlangRef)
    public:
        Slang::ICastable* value;
        Slang::ICastable* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_ICastable() = default;
        slang_ICastable(Slang::ICastable* ival): value(ival){}
        void operator=(Slang::ICastable* ival){
            value = ival;
        }
        operator Slang::ICastable*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_ICastable::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("castAs", "uuid"), &slang_ICastable::_castAs);
        }
    public:
        godot::String _castAs(slang_UUID* uuid);
    };

    class slang_IFileSystem : public slang_SlangRef{
    GDCLASS(slang_IFileSystem, slang_SlangRef)
    public:
        Slang::IFileSystem* value = nullptr;
        Slang::IFileSystem* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IFileSystem() = default;
        slang_IFileSystem(Slang::IFileSystem* ival):value(ival){}
        void operator=(Slang::IFileSystem* ival){
            value = ival;
        }
        operator Slang::IFileSystem*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IFileSystem::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("loadFile", "path", "outBlob"), &slang_IFileSystem::_loadFile);
        }
    public:
        SlangResult _loadFile(godot::String path, slang_IBlob* outBlob);
    };

    class slang_IFileSystemExt : public  slang_SlangRef{
    GDCLASS(slang_IFileSystemExt, slang_SlangRef)
    public:
        Slang::IFileSystemExt* value = nullptr;
        Slang::IFileSystemExt* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IFileSystemExt() = default;
        slang_IFileSystemExt(Slang::IFileSystemExt* ival):value(ival){}
        void operator=(Slang::IFileSystemExt* ival){
            value = ival;
        }
        operator Slang::IFileSystemExt*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IFileSystemExt::has_value);
            BIND_ENUM_CONSTANT(slang_SlangPathType::SLANG_PATH_TYPE_DIRECTORY)
            BIND_ENUM_CONSTANT(slang_SlangPathType::SLANG_PATH_TYPE_FILE)
            BIND_ENUM_CONSTANT(slang_PathKind::Simplified)
            BIND_ENUM_CONSTANT(slang_PathKind::Canonical)
            BIND_ENUM_CONSTANT(slang_PathKind::Display)
            BIND_ENUM_CONSTANT(slang_PathKind::OperatingSystem)
            BIND_ENUM_CONSTANT(slang_PathKind::CountOf_)

            BIND_ENUM_CONSTANT(slang_OSPathKind::None_)
            BIND_ENUM_CONSTANT(slang_OSPathKind::Direct)
            BIND_ENUM_CONSTANT(slang_OSPathKind::OperatingSystem_)

            godot::ClassDB::bind_method(godot::D_METHOD("getFileUniqueIdentity", "path", "outBlob"), &slang_IFileSystemExt::_getFileUniqueIdentity);
            godot::ClassDB::bind_method(godot::D_METHOD("calcCombinedPath", "pathType", "fromPath", "path", "pathOut"), &slang_IFileSystemExt::_calcCombinedPath);
            godot::ClassDB::bind_method(godot::D_METHOD("getPathType", "path", "pathTypeOut"), &slang_IFileSystemExt::_getPathType);
            godot::ClassDB::bind_method(godot::D_METHOD("getPath", "kind", "path", "pathOut"), &slang_IFileSystemExt::_getPath);
            godot::ClassDB::bind_method(godot::D_METHOD("getOSPathKind"), &slang_IFileSystemExt::_getOSPathKind);
        }
    public:
        SlangResult _getFileUniqueIdentity(godot::String path, slang_IBlob* outBlob){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->getFileUniqueIdentity(path.utf8().get_data(), &outBlob->value);
        }
        SlangResult _calcCombinedPath(slang_SlangPathType pathType, godot::String fromPath, godot::String path, slang_IBlob* pathOut){
            fromPath = godot::ProjectSettings::get_singleton()->globalize_path(fromPath);
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->calcCombinedPath(static_cast<SlangPathType>(pathType), fromPath.utf8().get_data(), path.utf8().get_data(), &pathOut->value);
        }
        SlangResult _getPathType(godot::String path, slang_ENUM<slang_SlangPathType>* pathTypeOut){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            SlangPathType pathType;
            SlangResult res = value->getPathType(path.utf8().get_data(), &pathType);
            pathTypeOut->set_value(static_cast<slang_SlangPathType>(pathType));
            return res;
        }
        SlangResult _getPath(slang_PathKind kind, godot::String path, slang_IBlob* pathOut){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->getPath(static_cast<PathKind>(kind), path.utf8().get_data(), &pathOut->value);
        }
        SlangResult _enumeratePathContents(godot::String path,void(*callback)(SlangPathType pathType, const char* name, void* userData) , slang_VOID_PTR userData){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->enumeratePathContents(path.utf8().get_data(), callback, userData);
        }
        slang_OSPathKind _getOSPathKind(){
            return static_cast<slang_OSPathKind>(value->getOSPathKind());
        }
    };

    class slang_IMutableFileSystem : public  slang_SlangRef{
    GDCLASS(slang_IMutableFileSystem, slang_SlangRef)
    public:
        Slang::IMutableFileSystem* value = nullptr;
        Slang::IMutableFileSystem* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IMutableFileSystem() = default;
        slang_IMutableFileSystem(Slang::IMutableFileSystem* ival): value(ival){}
        void operator=(Slang::IMutableFileSystem* ival){
            value = ival;
        }
        operator Slang::IMutableFileSystem*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IMutableFileSystem::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("saveFile", "path", "data", "size"), &slang_IMutableFileSystem::_saveFile);
            godot::ClassDB::bind_method(godot::D_METHOD("saveFileBlob", "path", "blob"), &slang_IMutableFileSystem::_saveFileBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("remove", "path"), &slang_IMutableFileSystem::_remove);
            godot::ClassDB::bind_method(godot::D_METHOD("createDirectory", "path"), &slang_IMutableFileSystem::_createDirectory);
        }

    public:
        SlangResult _saveFile(godot::String path, slang_VOID_PTR* data, size_t size){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->saveFile(path.utf8().get_data(), data->get_value(), size);
        }
        SlangResult _saveFileBlob(godot::String path, slang_IBlob* blob){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->saveFileBlob(path.utf8().get_data(), blob->value);
        }
        SlangResult _remove(godot::String path){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->remove(path.utf8().get_data());
        }
        SlangResult _createDirectory(godot::String path) {
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->createDirectory(path.utf8().get_data());
        }
    };

    class slang_ISharedLibrary : public slang_SlangRef{
    GDCLASS(slang_ISharedLibrary, slang_SlangRef)
    public:
        Slang::ISharedLibrary* value = nullptr;
        Slang::ISharedLibrary* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_ISharedLibrary() = default;
        slang_ISharedLibrary(Slang::ISharedLibrary* ival):value(ival){}
        void operator=(Slang::ISharedLibrary* ival){
            value = ival;
        }
        operator Slang::ISharedLibrary*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_ISharedLibrary::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("findSymbolAddressByName", "name"), &slang_ISharedLibrary::_findSymbolAddressByName);
        }
    public:
        SlangFuncPtr _findFuncByName(godot::String name){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            return value->findFuncByName(name.utf8().get_data());
        }
        godot::String _findSymbolAddressByName(godot::String name){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto a = static_cast<char *>(const_cast<void *>(value->findSymbolAddressByName(name.utf8().get_data())));
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
    };

    class slang_ISharedLibraryLoader : public slang_SlangRef{
    GDCLASS(slang_ISharedLibraryLoader, slang_SlangRef)
    public:
        ISlangSharedLibraryLoader* value = nullptr;
        ISlangSharedLibraryLoader* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_ISharedLibraryLoader() = default;
        slang_ISharedLibraryLoader(ISlangSharedLibraryLoader* ival):value(ival){}
        void operator=(ISlangSharedLibraryLoader* ival){
            value = ival;
        }
        operator ISlangSharedLibraryLoader*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_ISharedLibraryLoader::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("loadSharedLibrary", "path", "sharedLibraryOut"),
                                        &slang_ISharedLibraryLoader::_loadSharedLibrary);
        }

    public:
        SlangResult _loadSharedLibrary(godot::String path, slang_ISharedLibrary*sharedLibraryOut) {
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->loadSharedLibrary(path.utf8().get_data(),
                                                                      &sharedLibraryOut->value);
        }
    };
    class slang_IComponentType : public slang_SlangRef{
    GDCLASS(slang_IComponentType, slang_SlangRef)
    public:
        slang::IComponentType* value = nullptr;
        slang::IComponentType* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IComponentType() = default;
        slang_IComponentType(slang::IComponentType* ival): value(ival){}
        void operator=(slang::IComponentType* ival){
            value = ival;
        }
        operator slang::IComponentType*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IComponentType::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("getSession"), &slang_IComponentType::_getSession);
            godot::ClassDB::bind_method(godot::D_METHOD("getLayout", "targetIndex", "blob"), &slang_IComponentType::_getLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("getSpecializationParamCount"), &slang_IComponentType::_getSpecializationParamCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointCode", "entryPointIndex", "targetIndex", "outCode", "outDiagnostics"), &slang_IComponentType::_getEntryPointCode);
            godot::ClassDB::bind_method(godot::D_METHOD("getResultAsFileSystem", "entryPointIndex", "targetIndex", "outFileSystem"), &slang_IComponentType::_getResultAsFileSystem);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointHash", "entryPointIndex", "targetIndex", "outHash"), &slang_IComponentType::_getEntryPointHash);
            godot::ClassDB::bind_method(godot::D_METHOD("specialize", "specializationArgs", "specializationArgCount", "specializedOut", "outDiagnostics"), &slang_IComponentType::_specialize);
            godot::ClassDB::bind_method(godot::D_METHOD("link", "module", "outDiagnostics"), &slang_IComponentType::_link);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointHostCallable", "entryPointIndex", "targetIndex", "outSharedLibrary", "outDiagnostics"), &slang_IComponentType::_getEntryPointHostCallable);
            godot::ClassDB::bind_method(godot::D_METHOD("linkWithOptions", "outLinkedComponentType", "compilerOptionEntryCount", "compilerOptionEntries", "outDiagnostics"), &slang_IComponentType::_linkWithOptions);
            godot::ClassDB::bind_method(godot::D_METHOD("getTargetCode", "targetIndex", "outCode", "outDiagnostics"), &slang_IComponentType::_getTargetCode);
        }
    public:
        slang_ISession *_getSession() {
            return dynamic_cast<slang_ISession *>(value->getSession());
        }

        slang_ShaderReflection_HEAP_PTR* _getLayout(SlangInt targetIndex = 0,slang_IBlob* blob = nullptr) const;
        SlangInt _getSpecializationParamCount(){
            return value->getSpecializationParamCount();
        }
        SlangResult _getEntryPointCode(SlangInt entryPointIndex,SlangInt targetIndex,slang_IBlob* outCode,slang_IBlob* outDiagnostics = nullptr){
            return value->getEntryPointCode(entryPointIndex,targetIndex,&outCode->value,outDiagnostics==nullptr?nullptr:&outDiagnostics->value);
        }
        SlangResult _getResultAsFileSystem(SlangInt entryPointIndex,SlangInt targetIndex,slang_IMutableFileSystem* outFileSystem){
            return value->getResultAsFileSystem(entryPointIndex,targetIndex,&outFileSystem->value);
        }
        void _getEntryPointHash(SlangInt entryPointIndex,SlangInt targetIndex,slang_IBlob* outHash){
            return value->getEntryPointHash(entryPointIndex,targetIndex,&outHash->value);
        }
        SlangResult _specialize(slang_SpecializationArg_VECTOR* specializationArgs,SlangInt specializationArgCount,slang_IComponentType* specializedOut,slang_IBlob* outDiagnostics = nullptr) const;
        SlangResult _link(slang_IComponentType* module,slang_IBlob* outDiagnostics = nullptr){
            return value->link(&module->value,outDiagnostics==nullptr?nullptr:&outDiagnostics->value);
        }
        SlangResult _getEntryPointHostCallable(int entryPointIndex,int targetIndex,slang_ISharedLibrary* outSharedLibrary, slang_IBlob* outDiagnostics = nullptr){
            return value->getEntryPointHostCallable(entryPointIndex,targetIndex,&outSharedLibrary->value,outDiagnostics==nullptr?nullptr:&outDiagnostics->value);
        }
        SlangResult _linkWithOptions(slang_IComponentType* outLinkedComponentType,uint32_t compilerOptionEntryCount,slang_CompilerOptionEntry* compilerOptionEntries,slang_IBlob* outDiagnostics = nullptr) const;
        SlangResult _getTargetCode(SlangInt targetIndex,slang_IBlob* outCode,slang_IBlob* outDiagnostics = nullptr){
            return value->getTargetCode(targetIndex,&outCode->value,outDiagnostics==nullptr?nullptr:&outDiagnostics->value);
        }
    };
    class slang_ITypeConformance : public slang_SlangRef{
    GDCLASS(slang_ITypeConformance, slang_SlangRef)
    public:
        slang::ITypeConformance* value = nullptr;
        slang::ITypeConformance* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_ITypeConformance() = default;
        slang_ITypeConformance(slang::ITypeConformance* ival){}
        void operator=(slang::ITypeConformance* ival){
            value = ival;
        }
        operator slang::ITypeConformance*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_ITypeConformance::has_value);

        }
    };
    class slang_IEntryPoint : public slang_SlangRef{
    GDCLASS(slang_IEntryPoint, slang_SlangRef)
    public:
        slang::IEntryPoint* value = nullptr;
        slang::IEntryPoint* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IEntryPoint() = default;
        slang_IEntryPoint(slang::IEntryPoint* ival):value(ival){}
        void operator=(slang::IEntryPoint* ival){
            value = ival;
        }
        operator slang::IEntryPoint*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IEntryPoint::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("getFunctionReflection"), &slang_IEntryPoint::_getFunctionReflection);
        }
        slang_FunctionReflection_HEAP_PTR* _getFunctionReflection();
    };
    class slang_IModule : public slang_SlangRef{
    GDCLASS(slang_IModule, slang_SlangRef)
    public:
        slang::IModule* value = nullptr;
        slang::IModule* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IModule() = default;
        slang_IModule(slang::IModule* ival):value(ival){}
        void operator=(slang::IModule* ival){
            value = ival;
        }
        operator slang::IModule*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IModule::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("findEntryPointByName", "name", "outEntryPoint"), &slang_IModule::_findEntryPointByName);
            godot::ClassDB::bind_method(godot::D_METHOD("getDefinedEntryPointCount"), &slang_IModule::_getDefinedEntryPointCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getDefinedEntryPoint", "index", "outEntryPoint"), &slang_IModule::_getDefinedEntryPoint);
            godot::ClassDB::bind_method(godot::D_METHOD("serialize", "outBlob"), &slang_IModule::_serialize);
            godot::ClassDB::bind_method(godot::D_METHOD("writeToFile", "fileName"), &slang_IModule::_writeToFile);
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_IModule::_getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getFilePath"), &slang_IModule::_getFilePath);
            godot::ClassDB::bind_method(godot::D_METHOD("getUniqueIdentity"), &slang_IModule::_getUniqueIdentity);
            godot::ClassDB::bind_method(godot::D_METHOD("findAndCheckEntryPoint", "name", "stage", "outEntryPoint", "outDiagnostics"), &slang_IModule::_findAndCheckEntryPoint);
            godot::ClassDB::bind_method(godot::D_METHOD("getDependencyFileCount"), &slang_IModule::_getDependencyFileCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getDependencyFilePath", "index"), &slang_IModule::_getDependencyFilePath);
            godot::ClassDB::bind_method(godot::D_METHOD("getModuleReflection"), &slang_IModule::_getModuleReflection);
            godot::ClassDB::bind_method(godot::D_METHOD("precompileForTarget", "target", "outDiagnostics"), &slang_IModule::_precompileForTarget);
        }
    public:
        SlangResult _findEntryPointByName(godot::String name, slang_IEntryPoint* outEntryPoint){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            return value->findEntryPointByName(name.utf8().get_data(),&outEntryPoint->value);
        }
        SlangInt32 _getDefinedEntryPointCount(){
            return value->getDefinedEntryPointCount();
        }
        SlangResult _getDefinedEntryPoint(SlangInt32 index, slang_IEntryPoint* outEntryPoint){
            return value->getDefinedEntryPoint(index,&outEntryPoint->value);
        }
        SlangResult _serialize(slang_IBlob* outBlob){
            return value->serialize(&outBlob->value);
        }
        SlangResult _writeToFile(godot::String fileName){
            fileName = godot::ProjectSettings::get_singleton()->globalize_path(fileName);
            return value->writeToFile(fileName.utf8().get_data());
        }
        godot::String _getName(){
            auto a = value->getName();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        godot::String _getFilePath(){
            auto a = value->getFilePath();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        godot::String _getUniqueIdentity(){
            auto a = value->getUniqueIdentity();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        SlangResult _findAndCheckEntryPoint(godot::String name,slang_SlangStage stage,slang_IEntryPoint* outEntryPoint,slang_IBlob* outDiagnostics){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            return value->findAndCheckEntryPoint(name.utf8().get_data(),static_cast<SlangStage>(stage),&outEntryPoint->value,&outDiagnostics->value);
        }
        SlangInt32 _getDependencyFileCount(){
            return value->getDependencyFileCount();
        }
        godot::String _getDependencyFilePath(SlangInt32 index){
            auto a = value->getDependencyFilePath(index);
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        slang_DeclReflection_HEAP_PTR* _getModuleReflection() const;
        SlangResult _precompileForTarget(slang_SlangCompileTarget target,slang_IBlob* outDiagnostics){
            return value->precompileForTarget(static_cast<SlangCompileTarget>(target),&outDiagnostics->value);
        }
    };

    class slang_IWriter : public slang_SlangRef{
    GDCLASS(slang_IWriter, slang_SlangRef)
    public:
        ISlangWriter* value = nullptr;
        ISlangWriter* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IWriter() = default;
        slang_IWriter(ISlangWriter* ival):value(ival){}
        void operator=(ISlangWriter* ival){
            value = ival;
        }
        operator ISlangWriter*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_IWriter::has_value);
            BIND_ENUM_CONSTANT(slang_SlangWriterMode::SLANG_WRITER_MODE_TEXT)
            BIND_ENUM_CONSTANT(slang_SlangWriterMode::SLANG_WRITER_MODE_BINARY)

            godot::ClassDB::bind_method(godot::D_METHOD("beginAppendBuffer", "maxNumChars"), &slang_IWriter::_beginAppendBuffer);
            godot::ClassDB::bind_method(godot::D_METHOD("endAppendBuffer", "buffer", "numChars"), &slang_IWriter::_endAppendBuffer);
            godot::ClassDB::bind_method(godot::D_METHOD("write", "chars", "numChars"), &slang_IWriter::_write);
            godot::ClassDB::bind_method(godot::D_METHOD("flush"), &slang_IWriter::_flush);
            godot::ClassDB::bind_method(godot::D_METHOD("isConsole"), &slang_IWriter::_isConsole);
            godot::ClassDB::bind_method(godot::D_METHOD("setMode", "mode"), &slang_IWriter::_setMode);
        }
    public:
        godot::String _beginAppendBuffer(size_t maxNumChars){
            auto a = value->beginAppendBuffer(maxNumChars);
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        SlangResult _endAppendBuffer(godot::String buffer,size_t numChars){
            return value->endAppendBuffer(const_cast<char *>(buffer.utf8().get_data()), numChars);
        }
        SlangResult _write(godot::String chars, size_t numChars){
            return value->write(const_cast<char *>(chars.utf8().get_data()), numChars);
        }
        void _flush(){
            return value->flush();
        }
        bool _isConsole(){
            return value->isConsole();
        }
        SlangResult _setMode(slang_SlangWriterMode mode){
            return value->setMode(static_cast<SlangWriterMode>(mode));
        }
    };
    class slang_IProfiler : public slang_SlangRef{
    GDCLASS(slang_IProfiler, slang_SlangRef)
    public:
        ISlangProfiler* value = nullptr;
        ISlangProfiler* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_IProfiler() = default;
        slang_IProfiler(ISlangProfiler* ival):value(ival){}
        void operator=(ISlangProfiler* ival){
            value = ival;
        }
        operator ISlangProfiler*(){
            return value;
        }
    private:
        static void _bind_methods(){
            // godot::ClassDB::bind_method(godot::D_METHOD("getEntryCount"), &slang_IProfiler::_getEntryCount);
            // godot::ClassDB::bind_method(godot::D_METHOD("getEntryName", "index"), &slang_IProfiler::_getEntryName);
            // godot::ClassDB::bind_method(godot::D_METHOD("getEntryTimeMS", "index"), &slang_IProfiler::_getEntryTimeMS);
            // godot::ClassDB::bind_method(godot::D_METHOD("getEntryInvocationTimes", "index"), &slang_IProfiler::_getEntryInvocationTimes);
        }
    public:
        size_t _getEntryCount(){
            return value->getEntryCount();
        }
        godot::String _getEntryName(uint32_t index){
            auto a =  value->getEntryName(index);
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        long _getEntryTimeMS(uint32_t index){
            return value->getEntryTimeMS(index);
        }
        uint32_t _getEntryInvocationTimes(uint32_t index){
            return value->getEntryInvocationTimes(index);
        }
    };
    class slang_ICompileRequest : public slang_SlangRef{
    GDCLASS(slang_ICompileRequest, slang_SlangRef)
    public:
        slang::ICompileRequest* value = nullptr;
        slang::ICompileRequest* shift(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang_ICompileRequest() = default;
        slang_ICompileRequest(slang::ICompileRequest* ival):value(ival){}
        void operator=(slang::ICompileRequest* ival){
            value = ival;
        }
        operator slang::ICompileRequest*(){
            return value;
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_ICompileRequest::has_value);
            BIND_ENUM_CONSTANT(slang_SlangCompileFlags::SLANG_COMPILE_FLAG_NO_MANGLING)
            BIND_ENUM_CONSTANT(slang_SlangCompileFlags::SLANG_COMPILE_FLAG_NO_CODEGEN)
            BIND_ENUM_CONSTANT(slang_SlangCompileFlags::SLANG_COMPILE_FLAG_OBFUSCATE)
            BIND_ENUM_CONSTANT(slang_SlangCompileFlags::SLANG_COMPILE_FLAG_NO_CHECKING)
            BIND_ENUM_CONSTANT(slang_SlangCompileFlags::SLANG_COMPILE_FLAG_SPLIT_MIXED_TYPES)

            BIND_ENUM_CONSTANT(slang_SlangTargetFlags::SLANG_TARGET_FLAG_PARAMETER_BLOCKS_USE_REGISTER_SPACES)
            BIND_ENUM_CONSTANT(slang_SlangTargetFlags::SLANG_TARGET_FLAG_GENERATE_WHOLE_PROGRAM)
            BIND_ENUM_CONSTANT(slang_SlangTargetFlags::SLANG_TARGET_FLAG_DUMP_IR)
            BIND_ENUM_CONSTANT(slang_SlangTargetFlags::SLANG_TARGET_FLAG_GENERATE_SPIRV_DIRECTLY)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoLevel::SLANG_DEBUG_INFO_LEVEL_NONE)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoLevel::SLANG_DEBUG_INFO_LEVEL_MINIMAL)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoLevel::SLANG_DEBUG_INFO_LEVEL_STANDARD)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoLevel::SLANG_DEBUG_INFO_LEVEL_MAXIMAL)

            BIND_ENUM_CONSTANT(slang_SlangOptimizationLevel::SLANG_OPTIMIZATION_LEVEL_NONE)
            BIND_ENUM_CONSTANT(slang_SlangOptimizationLevel::SLANG_OPTIMIZATION_LEVEL_DEFAULT)
            BIND_ENUM_CONSTANT(slang_SlangOptimizationLevel::SLANG_OPTIMIZATION_LEVEL_HIGH)
            BIND_ENUM_CONSTANT(slang_SlangOptimizationLevel::SLANG_OPTIMIZATION_LEVEL_MAXIMAL)

            BIND_ENUM_CONSTANT(slang_SlangContainerFormat::SLANG_CONTAINER_FORMAT_NONE)
            BIND_ENUM_CONSTANT(slang_SlangContainerFormat::SLANG_CONTAINER_FORMAT_SLANG_MODULE)

            BIND_ENUM_CONSTANT(slang_SlangWriterChannel::SLANG_WRITER_CHANNEL_DIAGNOSTIC)
            BIND_ENUM_CONSTANT(slang_SlangWriterChannel::SLANG_WRITER_CHANNEL_STD_OUTPUT)
            BIND_ENUM_CONSTANT(slang_SlangWriterChannel::SLANG_WRITER_CHANNEL_STD_ERROR)
            BIND_ENUM_CONSTANT(slang_SlangWriterChannel::SLANG_WRITER_CHANNEL_COUNT_OF)

            BIND_ENUM_CONSTANT(slang_SlangSeverity::SLANG_SEVERITY_DISABLED)
            BIND_ENUM_CONSTANT(slang_SlangSeverity::SLANG_SEVERITY_NOTE)
            BIND_ENUM_CONSTANT(slang_SlangSeverity::SLANG_SEVERITY_WARNING)
            BIND_ENUM_CONSTANT(slang_SlangSeverity::SLANG_SEVERITY_ERROR)
            BIND_ENUM_CONSTANT(slang_SlangSeverity::SLANG_SEVERITY_FATAL)
            BIND_ENUM_CONSTANT(slang_SlangSeverity::SLANG_SEVERITY_INTERNAL)

            BIND_ENUM_CONSTANT(slang_SlangDebugInfoFormat::SLANG_DEBUG_INFO_FORMAT_DEFAULT)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoFormat::SLANG_DEBUG_INFO_FORMAT_C7)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoFormat::SLANG_DEBUG_INFO_FORMAT_PDB)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoFormat::SLANG_DEBUG_INFO_FORMAT_STABS)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoFormat::SLANG_DEBUG_INFO_FORMAT_COFF)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoFormat::SLANG_DEBUG_INFO_FORMAT_DWARF)
            BIND_ENUM_CONSTANT(slang_SlangDebugInfoFormat::SLANG_DEBUG_INFO_FORMAT_COUNT_OF)

            godot::ClassDB::bind_method(godot::D_METHOD("setFileSystem", "fileSystem"), &slang_ICompileRequest::_setFileSystem);
            godot::ClassDB::bind_method(godot::D_METHOD("setCompileFlags", "compileFlags"), &slang_ICompileRequest::_setCompileFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("getCompileFlags"), &slang_ICompileRequest::_getCompileFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("setDumpIntermediates", "enable"), &slang_ICompileRequest::_setDumpIntermediates);
            godot::ClassDB::bind_method(godot::D_METHOD("setDumpIntermediatePrefix", "prefix"), &slang_ICompileRequest::_setDumpIntermediatePrefix);
            godot::ClassDB::bind_method(godot::D_METHOD("setLineDirectiveMode", "mode"), &slang_ICompileRequest::_setLineDirectiveMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setCodeGenTarget", "target"), &slang_ICompileRequest::_setCodeGenTarget);
            godot::ClassDB::bind_method(godot::D_METHOD("addCodeGenTarget", "target"), &slang_ICompileRequest::_addCodeGenTarget);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetProfile", "targetIndex", "profile"), &slang_ICompileRequest::_setTargetProfile);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetFlags", "targetIndex", "flags"), &slang_ICompileRequest::_setTargetFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetFloatingPointMode", "targetIndex", "mode"), &slang_ICompileRequest::_setTargetFloatingPointMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetMatrixLayoutMode", "targetIndex", "mode"), &slang_ICompileRequest::_setTargetMatrixLayoutMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setMatrixLayoutMode", "mode"), &slang_ICompileRequest::_setMatrixLayoutMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setDebugInfoLevel", "level"), &slang_ICompileRequest::_setDebugInfoLevel);
            godot::ClassDB::bind_method(godot::D_METHOD("setOptimizationLevel", "level"), &slang_ICompileRequest::_setOptimizationLevel);
            godot::ClassDB::bind_method(godot::D_METHOD("setOutputContainerFormat", "format"), &slang_ICompileRequest::_setOutputContainerFormat);
            godot::ClassDB::bind_method(godot::D_METHOD("setPassThrough", "passThrough"), &slang_ICompileRequest::_setPassThrough);
            godot::ClassDB::bind_method(godot::D_METHOD("setWriter", "channel", "writer"), &slang_ICompileRequest::_setWriter);
            godot::ClassDB::bind_method(godot::D_METHOD("getWriter", "channel"), &slang_ICompileRequest::_getWriter);
            godot::ClassDB::bind_method(godot::D_METHOD("addSearchPath", "path"), &slang_ICompileRequest::_addSearchPath);
            godot::ClassDB::bind_method(godot::D_METHOD("addPreprocessorDefine", "key", "value"), &slang_ICompileRequest::_addPreprocessorDefine);
            godot::ClassDB::bind_method(godot::D_METHOD("processCommandLineArguments", "args", "argCount"), &slang_ICompileRequest::_processCommandLineArguments);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnit", "language", "name"), &slang_ICompileRequest::_addTranslationUnit);
            godot::ClassDB::bind_method(godot::D_METHOD("setDefaultModuleName", "defaultModuleName"), &slang_ICompileRequest::_setDefaultModuleName);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitPreprocessorDefine", "translationUnitIndex", "key", "value"), &slang_ICompileRequest::_addTranslationUnitPreprocessorDefine);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitSourceFile", "translationUnitIndex", "path"), &slang_ICompileRequest::_addTranslationUnitSourceFile);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitSourceString", "translationUnitIndex", "path", "source"), &slang_ICompileRequest::_addTranslationUnitSourceString);
            godot::ClassDB::bind_method(godot::D_METHOD("addLibraryReference", "path", "libData", "libDataSize"), &slang_ICompileRequest::_addLibraryReference);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitSourceStringSpan", "translationUnitIndex", "path", "sourceBegin", "sourceEnd"), &slang_ICompileRequest::_addTranslationUnitSourceStringSpan);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitSourceBlob", "translationUnitIndex", "path", "sourceBlob"), &slang_ICompileRequest::_addTranslationUnitSourceBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("addEntryPoint", "translationUnitIndex", "name", "stage"), &slang_ICompileRequest::_addEntryPoint);
            godot::ClassDB::bind_method(godot::D_METHOD("addEntryPointEx", "translationUnitIndex", "name", "stage", "genericArgCount", "genericArgs"), &slang_ICompileRequest::_addEntryPointEx);
            godot::ClassDB::bind_method(godot::D_METHOD("setGlobalGenericArgs", "genericArgCount", "genericArgs"), &slang_ICompileRequest::_setGlobalGenericArgs);
            godot::ClassDB::bind_method(godot::D_METHOD("setTypeNameForGlobalExistentialTypeParam","slotIndex","typeName"),&slang_ICompileRequest::_setTypeNameForGlobalExistentialTypeParam);
            godot::ClassDB::bind_method(godot::D_METHOD("setTypeNameForEntryPointExistentialTypeParam","entryPointIndex","slotIndex","typeName"),&slang_ICompileRequest::_setTypeNameForEntryPointExistentialTypeParam);
            godot::ClassDB::bind_method(godot::D_METHOD("setAllowGLSLInput","bool"),&slang_ICompileRequest::_setAllowGLSLInput);
            godot::ClassDB::bind_method(godot::D_METHOD("compile"), &slang_ICompileRequest::_compile);
            godot::ClassDB::bind_method(godot::D_METHOD("getDiagnosticOutput"), &slang_ICompileRequest::_getDiagnosticOutput);
            godot::ClassDB::bind_method(godot::D_METHOD("getDiagnosticOutputBlob","outBlob"), &slang_ICompileRequest::_getDiagnosticOutputBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("getDependencyFileCount"),&slang_ICompileRequest::_getDependencyFileCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getDependencyFilePath","index"),&slang_ICompileRequest::_getDependencyFilePath);
            godot::ClassDB::bind_method(godot::D_METHOD("getTranslationUnitCount"),&slang_ICompileRequest::_getTranslationUnitCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointSource","entryPointIndex"),&slang_ICompileRequest::_getEntryPointSource);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointCode","entryPointIndex","outSize"),&slang_ICompileRequest::_getEntryPointCode);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointCodeBlob", "entryPointIndex","targetIndex","outBlob"), &slang_ICompileRequest::_getEntryPointCodeBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointHostCallable","entryPointIndex","targetIndex","outCallable"), &slang_ICompileRequest::_getEntryPointHostCallable);
            godot::ClassDB::bind_method(godot::D_METHOD("getTargetCodeBlob","targetIndex","outBlob"), &slang_ICompileRequest::_getTargetCodeBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("getTargetHostCallable","targetIndex","outSharedLibrary"), &slang_ICompileRequest::_getTargetHostCallable);
            godot::ClassDB::bind_method(godot::D_METHOD("getCompileRequestResultAsFileSystem"),&slang_ICompileRequest::_getCompileRequestResultAsFileSystem);
            godot::ClassDB::bind_method(godot::D_METHOD("getContainerCode","outBlob"), &slang_ICompileRequest::_getContainerCode);
            godot::ClassDB::bind_method(godot::D_METHOD("loadRepro","fileSystem","data","size"), &slang_ICompileRequest::_loadRepro);
            godot::ClassDB::bind_method(godot::D_METHOD("saveRepro","outBlob"), &slang_ICompileRequest::_saveRepro);
            godot::ClassDB::bind_method(godot::D_METHOD("enableReproCapture"), &slang_ICompileRequest::_enableReproCapture);
            godot::ClassDB::bind_method(godot::D_METHOD("getProgram","outProgram"), &slang_ICompileRequest::_getProgram);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPoint", "entryPointIndex","outEntryPoint"), &slang_ICompileRequest::_getEntryPoint);
            godot::ClassDB::bind_method(godot::D_METHOD("getModule","translationUnitIndex","outModule"),&slang_ICompileRequest::_getModule);
            godot::ClassDB::bind_method(godot::D_METHOD("getSession","outSession"),&slang_ICompileRequest::_getSession);
            godot::ClassDB::bind_method(godot::D_METHOD("getReflection"),&slang_ICompileRequest::_getReflection);
            godot::ClassDB::bind_method(godot::D_METHOD("setCommandLineCompilerMode"),&slang_ICompileRequest::_setCommandLineCompilerMode);
            godot::ClassDB::bind_method(godot::D_METHOD("addTargetCapability","targetIndex","capability"),&slang_ICompileRequest::_addTargetCapability);
            godot::ClassDB::bind_method(godot::D_METHOD("getProgramWithEntryPoints","outProgram"),&slang_ICompileRequest::_getProgramWithEntryPoints);
            godot::ClassDB::bind_method(godot::D_METHOD("isParameterLocationUsed","entryPointIndex","targetIndex","category","spaceIndex","registerIndex","outUsed"),&slang_ICompileRequest::_isParameterLocationUsed);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetLineDirectiveMode","targetIndex","mode"),&slang_ICompileRequest::_setTargetLineDirectiveMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetForceGLSLScalarBufferLayout","targetIndex","forceScalarLayout"),&slang_ICompileRequest::_setTargetForceGLSLScalarBufferLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("overrideDiagnosticSeverity","messageID","overrideSeverity"),&slang_ICompileRequest::_overrideDiagnosticSeverity);
            godot::ClassDB::bind_method(godot::D_METHOD("getDiagnosticFlags"),&slang_ICompileRequest::_getDiagnosticFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("setDiagnosticFlags","flags"),&slang_ICompileRequest::_setDiagnosticFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("setDebugInfoFormat","format"),&slang_ICompileRequest::_setDebugInfoFormat);
            godot::ClassDB::bind_method(godot::D_METHOD("setEnableEffectAnnotations","value"),&slang_ICompileRequest::_setEnableEffectAnnotations);
            godot::ClassDB::bind_method(godot::D_METHOD("setReportDownstreamTime","value"),&slang_ICompileRequest::_setReportDownstreamTime);
            godot::ClassDB::bind_method(godot::D_METHOD("setReportPerfBenchmark","value"),&slang_ICompileRequest::_setReportPerfBenchmark);
            godot::ClassDB::bind_method(godot::D_METHOD("setSkipSPIRVValidation","value"),&slang_ICompileRequest::_setSkipSPIRVValidation);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetUseMinimumSlangOptimization","targetIndex","value"),&slang_ICompileRequest::_setTargetUseMinimumSlangOptimization);
            godot::ClassDB::bind_method(godot::D_METHOD("setIgnoreCapabilityCheck","value"),&slang_ICompileRequest::_setIgnoreCapabilityCheck);
            // godot::ClassDB::bind_method(godot::D_METHOD("getCompileTimeProfile","compileTimeProfile","shouldClear"),&slang_ICompileRequest::_getCompileTimeProfile, &slang_ICompileRequest::getCompileTimeProfile);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetGenerateWholeProgram","targetIndex","value"),&slang_ICompileRequest::_setTargetGenerateWholeProgram);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetEmbedDXIL","targetIndex","value"),&slang_ICompileRequest::_setTargetEmbedDXIL);
        }
    public:
        void _setFileSystem(slang_IFileSystem* fileSystem){
            return value->setFileSystem(fileSystem->value);
        }
        void _setCompileFlags(slang_SlangCompileFlags compileFlags){
            return value->setCompileFlags(static_cast<SlangCompileFlags>(compileFlags));
        }
        SlangCompileFlags _getCompileFlags(){
            return value->getCompileFlags();
        }
        void _setDumpIntermediates(int enable){
            return value->setDumpIntermediates(enable);
        }
        void _setDumpIntermediatePrefix(godot::String prefix){
            return value->setDumpIntermediatePrefix(prefix.utf8().get_data());
        }
        void _setLineDirectiveMode(slang_SlangLineDirectiveMode mode){
            return value->setLineDirectiveMode(static_cast<SlangLineDirectiveMode>(mode));
        }
        void _setCodeGenTarget(slang_SlangCompileTarget target){
            return value->setCodeGenTarget(static_cast<SlangCompileTarget>(target));
        }
        int _addCodeGenTarget(slang_SlangCompileTarget target){
            return value->addCodeGenTarget(static_cast<SlangCompileTarget>(target));
        }
        void _setTargetProfile(int targetIndex,slang_SlangProfileID profile){
            return value->setTargetProfile(targetIndex,static_cast<SlangProfileID>(profile));
        }
        void _setTargetFlags(int targetIndex,slang_SlangTargetFlags flags){
            return value->setTargetFlags(targetIndex,static_cast<SlangTargetFlags>(flags));
        }
        void _setTargetFloatingPointMode(int targetIndex,slang_SlangFloatingPointMode mode){
            return value->setTargetFloatingPointMode(targetIndex,static_cast<SlangFloatingPointMode>(mode));
        }
        void _setTargetMatrixLayoutMode(int targetIndex,slang_SlangMatrixLayoutMode mode){
            return value->setTargetMatrixLayoutMode(targetIndex,static_cast<SlangMatrixLayoutMode>(mode));
        }
        void _setMatrixLayoutMode(slang_SlangMatrixLayoutMode mode){
            return value->setMatrixLayoutMode(static_cast<SlangMatrixLayoutMode>(mode));
        }
        void _setDebugInfoLevel(slang_SlangDebugInfoLevel level){
            return value->setDebugInfoLevel(static_cast<SlangDebugInfoLevel>(level));
        }
        void _setOptimizationLevel(slang_SlangOptimizationLevel level){
            return value->setOptimizationLevel(static_cast<SlangOptimizationLevel>(level));
        }
        void _setOutputContainerFormat(slang_SlangContainerFormat format){
            return value->setOutputContainerFormat(static_cast<SlangContainerFormat>(format));
        }
        void _setPassThrough(slang_SlangPassThrough passThrough){
            return value->setPassThrough(static_cast<SlangPassThrough>(passThrough));
        }
        void _setDiagnosticCallback(SlangDiagnosticCallback callback, slang_VOID_PTR* userData){
            return value->setDiagnosticCallback(callback,userData);
        }
        void _setWriter(slang_SlangWriterChannel channel, slang_IWriter* writer){
            return value->setWriter(static_cast<SlangWriterChannel>(channel),writer->value);
        }
        slang_IWriter_HEAP_PTR* _getWriter(slang_SlangWriterChannel channel) {
            auto* a = memnew(slang_IWriter(value->getWriter(
                    static_cast<SlangWriterChannel>(channel))));
            auto* ptr = memnew(slang_IWriter_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        void _addSearchPath(godot::String path){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->addSearchPath(path.utf8().get_data());
        }
        void _addPreprocessorDefine(godot::String key, godot::String value){
            return this->value->addPreprocessorDefine(key.utf8().get_data(),value.utf8().get_data());
        }
        SlangResult _processCommandLineArguments(godot::TypedArray<godot::String> args, int argCount){
            const char** argv = new const char*[argCount];
            for(int i = 0; i < argCount; i++){
                argv[i] = args[i].operator godot::String().utf8().get_data();
            }
            auto res = value->processCommandLineArguments(argv,argCount);
            delete[] argv;
            return res;
        }
        int _addTranslationUnit(slang_SlangSourceLanguage language,godot::String name){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            return value->addTranslationUnit(static_cast<SlangSourceLanguage>(language), name.utf8().get_data());
        }
        void _setDefaultModuleName(godot::String defaultModuleName){
            return value->setDefaultModuleName(defaultModuleName.utf8().get_data());
        }
        void _addTranslationUnitPreprocessorDefine(int translationUnitIndex,godot::String key, godot::String value){
            return this->value->addTranslationUnitPreprocessorDefine(translationUnitIndex,key.utf8().get_data(),value.utf8().get_data());
        }
        void _addTranslationUnitSourceFile(int translationUnitIndex,godot::String path){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->addTranslationUnitSourceFile(translationUnitIndex,path.utf8().get_data());
        }
        void _addTranslationUnitSourceString(int translationUnitIndex,godot::String path,godot::String source){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->addTranslationUnitSourceString(translationUnitIndex,path.utf8().get_data(),source.utf8().get_data());
        }
        SlangResult _addLibraryReference(godot::String path, slang_VOID_PTR* libData,size_t libDataSize){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->addLibraryReference(path.utf8().get_data(),libData->get_value(),libDataSize);
        }
        void _addTranslationUnitSourceStringSpan(int translationUnitIndex,godot::String path,godot::String sourceBegin,godot::String sourceEnd){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->addTranslationUnitSourceStringSpan(translationUnitIndex,path.utf8().get_data(),sourceBegin.utf8().get_data(),sourceEnd.utf8().get_data());
        }
        void _addTranslationUnitSourceBlob(int translationUnitIndex,godot::String path,slang_IBlob* sourceBlob){
            path = godot::ProjectSettings::get_singleton()->globalize_path(path);
            return value->addTranslationUnitSourceBlob(translationUnitIndex,path.utf8().get_data(),sourceBlob->value);
        }
        int _addEntryPoint(int translationUnitIndex,godot::String name,slang_SlangStage stage){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            return value->addEntryPoint(translationUnitIndex,name.utf8().get_data(),static_cast<SlangStage>(stage));
        }
        int _addEntryPointEx(int translationUnitIndex,godot::String name,slang_SlangStage stage,int genericArgCount,godot::TypedArray<godot::String>genericArgs){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            const char** args = new const char*[genericArgCount];
            for(int i = 0; i < genericArgCount; i++) {
                args[i] = genericArgs[i].operator godot::String().utf8().get_data();
            }
            auto res = value->addEntryPointEx(translationUnitIndex,name.utf8().get_data(),static_cast<SlangStage>(stage),genericArgCount,args);
            delete[] args;
            return res;
        }
        SlangResult _setGlobalGenericArgs(int genericArgCount,godot::TypedArray<godot::String>genericArgs){
            const char** args = new const char*[genericArgCount];
            for(int i = 0; i < genericArgCount; i++) {
                args[i] = genericArgs[i].operator godot::String().utf8().get_data();
            }
            auto res = value->setGlobalGenericArgs(genericArgCount,args);
            delete[] args;
            return res;
        }
        SlangResult _setTypeNameForGlobalExistentialTypeParam(int typeParamIndex,godot::String typeName){
            return value->setTypeNameForGlobalExistentialTypeParam(typeParamIndex,typeName.utf8().get_data());
        }
        SlangResult _setTypeNameForEntryPointExistentialTypeParam(int entryPointIndex,int slotIndex,godot::String typeName){
            return value->setTypeNameForEntryPointExistentialTypeParam(entryPointIndex,slotIndex,typeName.utf8().get_data());
        }
        void _setAllowGLSLInput(bool value){
            return this->value->setAllowGLSLInput(value);
        }
        SlangResult _compile(){
            return value->compile();
        }
        godot::String _getDiagnosticOutput(slang_NULL* null){
            auto a = value->getDiagnosticOutput();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        SlangResult _getDiagnosticOutputBlob(slang_IBlob* outBlob){
            return value->getDiagnosticOutputBlob(&outBlob->value);
        }
        int SLANG_MCALL _getDependencyFileCount(){
            return value->getDependencyFileCount();
        }
        godot::String _getDependencyFilePath(int index,slang_NULL*null){
            auto a = value->getDependencyFilePath(index);
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        int _getTranslationUnitCount(){
            return value->getTranslationUnitCount();
        }
        godot::String _getEntryPointSource(int entryPointIndex){
            auto a = value->getEntryPointSource(entryPointIndex);
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        godot::String _getEntryPointCode(int entryPointIndex,slang_SIZE* outSize){
            size_t size = 0;
            auto res = value->getEntryPointCode(entryPointIndex, &size);
            outSize->set_value(size);
            if(res == 0)
                return "";
            return (char*)res;
        }
        SlangResult _getEntryPointCodeBlob(int entryPointIndex,int targetIndex,slang_IBlob* outBlob){
            return value->getEntryPointCodeBlob(entryPointIndex,targetIndex,&outBlob->value);
        }
        SlangResult _getEntryPointHostCallable(int entryPointIndex,int targetIndex,slang_ISharedLibrary* outCallable){
            return value->getEntryPointHostCallable(entryPointIndex,targetIndex,&outCallable->value);
        }
        SlangResult _getTargetCodeBlob(int targetIndex,slang_IBlob* outBlob){
            return value->getTargetCodeBlob(targetIndex,&outBlob->value);
        }
        SlangResult _getTargetHostCallable(int targetIndex,slang_ISharedLibrary* outCallable){
            return value->getTargetHostCallable(targetIndex,&outCallable->value);
        }
        const void* _getCompileRequestCode(slang_SIZE* outSize){
            size_t size = 0;
            auto res = value->getCompileRequestCode(&size);
            outSize->set_value(size);
            return res;
        }
        slang_IMutableFileSystem_HEAP_PTR* _getCompileRequestResultAsFileSystem(){
            auto* a= memnew(slang_IMutableFileSystem(value->getCompileRequestResultAsFileSystem()));
            auto* ptr = memnew(slang_IMutableFileSystem_HEAP_PTR(a));
            ptr -> set_shouldFreeData(true);
            return ptr;
        }
        SlangResult _getContainerCode(slang_IBlob* outBlob){
            return value->getContainerCode(&outBlob->value);
        }
        SlangResult _loadRepro(slang_IFileSystem* fileSystem,slang_VOID_PTR* data,size_t size){
            return value->loadRepro(fileSystem->value,data->get_value(),size);
        }
        SlangResult _saveRepro(slang_IBlob* blob){
            return value->saveRepro(&blob->value);
        }
        SlangResult _enableReproCapture(){
            return value->enableReproCapture();
        }
        SlangResult _getProgram(slang_IComponentType* outProgram){
            return value->getProgram(&outProgram->value);
        }
        SlangResult _getEntryPoint(SlangInt entryPointIndex, slang_IComponentType* outEntryPoint){
            return value->getEntryPoint(entryPointIndex, &outEntryPoint->value);
        }
        SlangResult _getModule(SlangInt translationUnitIndex, slang_IModule* outModule){
            return value->getModule(translationUnitIndex, &outModule->value);
        }
        SlangResult _getSession(slang_ISession* outSession){
            return value->getSession(&outSession->value);
        }
        slang_ProgramLayout* _getReflection(slang_NULL* null){
            value->getReflection();
            return nullptr;
        }
        void _setCommandLineCompilerMode(){
            return value->setCommandLineCompilerMode();
        }
        SlangResult _addTargetCapability(SlangInt capability,slang_SlangCapabilityID capabilityID){
            return value->addTargetCapability(capability,static_cast<SlangCapabilityID>(capabilityID));
        }
        SlangResult _getProgramWithEntryPoints(slang_IComponentType* outProgram){
            return value->getProgramWithEntryPoints(&outProgram->value);
        }
        SlangResult _isParameterLocationUsed(SlangInt entryPointIndex, SlangInt targetIndex, slang_SlangParameterCategory category,SlangUInt spaceIndex, SlangUInt registerIndex, slang_BOOL* outUsed){
            bool used = 0;
            auto res = value->isParameterLocationUsed(entryPointIndex, targetIndex, static_cast<SlangParameterCategory>(category), spaceIndex, registerIndex, used);
            outUsed->set_value(used);
            return res;
        }
        void _setTargetLineDirectiveMode(SlangInt targetIndex, slang_SlangLineDirectiveMode mode){
            return value->setTargetLineDirectiveMode(targetIndex, static_cast<SlangLineDirectiveMode>(mode));
        }
        void _setTargetForceGLSLScalarBufferLayout(int targetIndex, bool forceScalarLayout){
            return value->setTargetForceGLSLScalarBufferLayout(targetIndex, forceScalarLayout);
        }
        void _overrideDiagnosticSeverity(SlangInt messageID, slang_SlangSeverity overrideSeverity){
            return value->overrideDiagnosticSeverity(messageID, static_cast<SlangSeverity>(overrideSeverity));
        }
        int _getDiagnosticFlags(){
            return value->getDiagnosticFlags();
        }
        void _setDiagnosticFlags(int flags){
            return value->setDiagnosticFlags(flags);
        }
        void _setDebugInfoFormat(slang_SlangDebugInfoFormat debugFormat){
            return value->setDebugInfoFormat(static_cast<SlangDebugInfoFormat>(debugFormat));
        }
        void _setEnableEffectAnnotations(bool value){
            return this->value->setEnableEffectAnnotations(value);
        }
        void _setReportDownstreamTime(bool value){
            return this->value->setReportDownstreamTime(value);
        }
        void _setReportPerfBenchmark(bool value){
            return this->value->setReportPerfBenchmark(value);
        }
        void _setSkipSPIRVValidation(bool value){
            return this->value->setSkipSPIRVValidation(value);
        }
        void _setTargetUseMinimumSlangOptimization(int targetIndex, bool value){
            return this->value->setTargetUseMinimumSlangOptimization(targetIndex, value);
        }
        void _setIgnoreCapabilityCheck(bool value){
            return this->value->setIgnoreCapabilityCheck(value);
        }
        SlangResult _getCompileTimeProfile(slang_IProfiler* outProfile,bool shouldClear){
            return value->getCompileTimeProfile(&outProfile->value, shouldClear);
        }
        void _setTargetGenerateWholeProgram(int targetIndex, bool value){
            return this->value->setTargetGenerateWholeProgram(targetIndex, value);
        }
        void _setTargetEmbedDXIL(int targetIndex, bool value){
            return this->value->setTargetEmbedDXIL(targetIndex, value);
        }
    };

    class slang_UUID : public slang_SlangObject {
    GDCLASS(slang_UUID, slang_SlangObject)
    public:
        SlangUUID duplicate(){
            return *this;
        }
    private:
        uint32_t data1 = 0;
        uint16_t data2 = 0;
        uint16_t data3 = 0;
        uint8_t data4_0 = 0;
        uint8_t data4_1 = 0;
        uint8_t data4_2 = 0;
        uint8_t data4_3 = 0;
        uint8_t data4_4 = 0;
        uint8_t data4_5 = 0;
        uint8_t data4_6 = 0;
        uint8_t data4_7 = 0;

        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_data1", "value"), &slang_UUID::set_data1);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data1"), &slang_UUID::get_data1);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data2", "value"), &slang_UUID::set_data2);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data2"), &slang_UUID::get_data2);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data3", "value"), &slang_UUID::set_data3);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data3"), &slang_UUID::get_data3);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data4_0", "value"), &slang_UUID::set_data4_0);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data4_0"), &slang_UUID::get_data4_0);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data4_1", "value"), &slang_UUID::set_data4_1);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data4_1"), &slang_UUID::get_data4_1);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data4_2", "value"), &slang_UUID::set_data4_2);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data4_2"), &slang_UUID::get_data4_2);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data4_3", "value"), &slang_UUID::set_data4_3);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data4_3"), &slang_UUID::get_data4_3);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data4_4", "value"), &slang_UUID::set_data4_4);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data4_4"), &slang_UUID::get_data4_4);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data4_5", "value"), &slang_UUID::set_data4_5);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data4_5"), &slang_UUID::get_data4_5);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data4_6", "value"), &slang_UUID::set_data4_6);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data4_6"), &slang_UUID::get_data4_6);
            godot::ClassDB::bind_method(godot::D_METHOD("set_data4_7", "value"), &slang_UUID::set_data4_7);
            godot::ClassDB::bind_method(godot::D_METHOD("get_data4_7"), &slang_UUID::get_data4_7);
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data1"), "set_data1",
                                         "get_data1");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data2"), "set_data2",
                                         "get_data2");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data3"), "set_data3",
                                         "get_data3");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data4_0"),
                                         "set_data4_0", "get_data4_0");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data4_1"),
                                         "set_data4_1", "get_data4_1");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data4_2"),
                                         "set_data4_2", "get_data4_2");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data4_3"),
                                         "set_data4_3", "get_data4_3");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data4_4"),
                                         "set_data4_4", "get_data4_4");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data4_5"),
                                         "set_data4_5", "get_data4_5");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data4_6"),
                                         "set_data4_6", "get_data4_6");
            godot::ClassDB::add_property("slang_UUID", godot::PropertyInfo(godot::Variant::INT, "data4_7"),
                                         "set_data4_7", "get_data4_7");
        }

    public:
        operator SlangUUID(){
            SlangUUID id;
            id.data1 = data1;
            id.data2 = data2;
            id.data3 = data3;
            id.data4[0] = data4_0;
            id.data4[1] = data4_1;
            id.data4[2] = data4_2;
            id.data4[3] = data4_3;
            id.data4[4] = data4_4;
            id.data4[5] = data4_5;
            id.data4[6] = data4_6;
            id.data4[7] = data4_7;
            return id;
        }
        void set_data1(uint32_t value) {
            data1 = value;
        }

        uint32_t get_data1() {
            return data1;
        }

        void set_data2(uint16_t value) {
            data2 = value;
        }

        uint16_t get_data2() {
            return data2;
        }

        void set_data3(uint16_t value) {
            data3 = value;
        }

        uint16_t get_data3() {
            return data3;
        }

        void set_data4_0(uint8_t value) {
            data4_0 = value;
        }

        uint8_t get_data4_0() {
            return data4_0;
        }

        void set_data4_1(uint8_t value) {
            data4_1 = value;
        }

        uint8_t get_data4_1() {
            return data4_1;
        }

        void set_data4_2(uint8_t value) {
            data4_2 = value;
        }

        uint8_t get_data4_2() {
            return data4_2;
        }

        void set_data4_3(uint8_t value) {
            data4_3 = value;
        }

        uint8_t get_data4_3() {
            return data4_3;
        }

        void set_data4_4(uint8_t value) {
            data4_4 = value;
        }

        uint8_t get_data4_4() {
            return data4_4;
        }

        void set_data4_5(uint8_t value) {
            data4_5 = value;
        }

        uint8_t get_data4_5() {
            return data4_5;
        }

        void set_data4_6(uint8_t value) {
            data4_6 = value;
        }

        uint8_t get_data4_6() {
            return data4_6;
        }

        void set_data4_7(uint8_t value) {
            data4_7 = value;
        }

        uint8_t get_data4_7() {
            return data4_7;
        }
    };

    MAKE_VALUE_TEMPLATE(UUID)



    class slang_CompilerOptionValue :public slang_SlangObject{
    GDCLASS(slang_CompilerOptionValue, slang_SlangObject)
        slang_CompilerOptionValueKind kind = slang_CompilerOptionValueKind::Int;
        int32_t intValue0 = 0;
        int32_t intValue1 = 0;
        const char* stringValue0 = "";
        const char* stringValue1 = "";
    public:
        slang::CompilerOptionValue duplicate(){
            return *this;
        }
        slang_CompilerOptionValue(){}
        slang_CompilerOptionValue(slang::CompilerOptionValue value){
            this->kind = (slang_CompilerOptionValueKind)value.kind;
            this->intValue0 = value.intValue0;
            this->intValue1 = value.intValue1;
            this->stringValue0 = value.stringValue0;
            this->stringValue1 = value.stringValue1;
        }
        void operator=(slang::CompilerOptionValue value){
            this->kind = (slang_CompilerOptionValueKind)value.kind;
            this->intValue0 = value.intValue0;
            this->intValue1 = value.intValue1;
            this->stringValue0 = value.stringValue0;
            this->stringValue1 = value.stringValue1;
        }
        operator slang::CompilerOptionValue(){
            slang::CompilerOptionValue value;
            value.kind = (slang::CompilerOptionValueKind)kind;
            value.intValue0 = intValue0;
            value.intValue1 = intValue1;
            value.stringValue0 = stringValue0;
            value.stringValue1 = stringValue1;
            return value;
        }

    private:
        static void _bind_methods() {
            BIND_ENUM_CONSTANT(slang_CompilerOptionValueKind::Int)
            BIND_ENUM_CONSTANT(slang_CompilerOptionValueKind::String)
            godot::ClassDB::bind_method(godot::D_METHOD("set_kind", "kind"), &slang_CompilerOptionValue::set_kind);
            godot::ClassDB::bind_method(godot::D_METHOD("get_kind"), &slang_CompilerOptionValue::get_kind);
            godot::ClassDB::add_property("slang_CompilerOptionValue",
                                         godot::PropertyInfo(godot::Variant::INT, "kind", godot::PROPERTY_HINT_ENUM,
                                                             "Int,String"), "set_kind", "get_kind");

            godot::ClassDB::bind_method(godot::D_METHOD("set_intValue0", "intValue0"),
                                        &slang_CompilerOptionValue::set_intValue0);
            godot::ClassDB::bind_method(godot::D_METHOD("get_intValue0"), &slang_CompilerOptionValue::get_intValue0);
            godot::ClassDB::add_property("slang_CompilerOptionValue",
                                         godot::PropertyInfo(godot::Variant::INT, "intValue0"), "set_intValue0",
                                         "get_intValue0");

            godot::ClassDB::bind_method(godot::D_METHOD("set_intValue1", "intValue1"),
                                        &slang_CompilerOptionValue::set_intValue1);
            godot::ClassDB::bind_method(godot::D_METHOD("get_intValue1"), &slang_CompilerOptionValue::get_intValue1);
            godot::ClassDB::add_property("slang_CompilerOptionValue",
                                         godot::PropertyInfo(godot::Variant::INT, "intValue1"), "set_intValue1",
                                         "get_intValue1");

            godot::ClassDB::bind_method(godot::D_METHOD("set_stringValue0", "stringValue0"),
                                        &slang_CompilerOptionValue::set_stringValue0);
            godot::ClassDB::bind_method(godot::D_METHOD("get_stringValue0"),
                                        &slang_CompilerOptionValue::get_stringValue0);
            godot::ClassDB::add_property("slang_CompilerOptionValue",
                                         godot::PropertyInfo(godot::Variant::STRING, "stringValue0"),
                                         "set_stringValue0", "get_stringValue0");

            godot::ClassDB::bind_method(godot::D_METHOD("set_stringValue1", "stringValue1"),
                                        &slang_CompilerOptionValue::set_stringValue1);
            godot::ClassDB::bind_method(godot::D_METHOD("get_stringValue1"),
                                        &slang_CompilerOptionValue::get_stringValue1);
            godot::ClassDB::add_property("slang_CompilerOptionValue",
                                         godot::PropertyInfo(godot::Variant::STRING, "stringValue1"),
                                         "set_stringValue1", "get_stringValue1");

        }

    public:
        slang_CompilerOptionValueKind get_kind() {
            return (slang_CompilerOptionValueKind) kind;
        }

        void set_kind(slang_CompilerOptionValueKind kind) {
            this->kind = kind;
        }

        int get_intValue0() {
            return intValue0;
        }

        void set_intValue0(int intValue0) {
            this->intValue0 = intValue0;
        }

        int get_intValue1() {
            return intValue1;
        }

        void set_intValue1(int intValue1) {
            this->intValue1 = intValue1;
        }

        godot::String get_stringValue0() {
            auto a = stringValue0;
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }

        void set_stringValue0(godot::String str) {
            this->stringValue0 = str.utf8().get_data();
        }

        godot::String get_stringValue1() {
            auto a = stringValue1;
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }

        void set_stringValue1(godot::String str) {
            this->stringValue1 = str.utf8().get_data();
        }
    };

    MAKE_VALUE_TEMPLATE(CompilerOptionValue)

    class slang_CompilerOptionEntry : public slang_SlangObject{
    GDCLASS(slang_CompilerOptionEntry, slang_SlangObject)
        slang_CompilerOptionName name;
        slang_CompilerOptionValue value;
    public:
        slang_CompilerOptionEntry(){}
        slang_CompilerOptionEntry(slang::CompilerOptionEntry entry){
            this->name = slang_CompilerOptionName(entry.name);
            this->value = entry.value;
        }
        void operator= (slang::CompilerOptionEntry entry){
            this->name = slang_CompilerOptionName(entry.name);
            this->value = entry.value;
        }
        slang::CompilerOptionEntry duplicate(){
            return *this;
        }
        operator slang::CompilerOptionEntry(){
            slang::CompilerOptionEntry entry;
            entry.name = static_cast<slang::CompilerOptionName>(name);
            entry.value = value;
            return entry;
        }
    private:
        static void _bind_methods() {
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::MacroDefine)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DepFile)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::EntryPointName)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Specialize)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Help)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::HelpStyle)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Include)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Language)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::MatrixLayoutColumn)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::MatrixLayoutRow)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ZeroInitialize)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::IgnoreCapabilities)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::RestrictiveCapabilityCheck)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ModuleName)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Output)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Profile)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Stage)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Target)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Version)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::WarningsAsErrors)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DisableWarnings)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::EnableWarning)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DisableWarning)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DumpWarningDiagnostics)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::InputFilesRemain)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::EmitIr)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ReportDownstreamTime)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ReportPerfBenchmark)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::SkipSPIRVValidation)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::SourceEmbedStyle)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::SourceEmbedName)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::SourceEmbedLanguage)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DisableShortCircuit)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::MinimumSlangOptimization)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DisableNonEssentialValidations)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DisableSourceMap)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::UnscopedEnum)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::PreserveParameters)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Capability)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DefaultImageFormatUnknown)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DisableDynamicDispatch)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DisableSpecialization)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::FloatingPointMode)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DebugInformation)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::LineDirectiveMode)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Optimization)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Obfuscate)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VulkanBindShift)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VulkanBindGlobals)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VulkanInvertY)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VulkanUseDxPositionW)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VulkanUseEntryPointName)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VulkanUseGLLayout)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VulkanEmitReflection)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::GLSLForceScalarLayout)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::EnableEffectAnnotations)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::EmitSpirvViaGLSL)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::EmitSpirvDirectly)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::SPIRVCoreGrammarJSON)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::IncompleteLibrary)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::CompilerPath)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DefaultDownstreamCompiler)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DownstreamArgs)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::PassThrough)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DumpRepro)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DumpReproOnError)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ExtractRepro)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::LoadRepro)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::LoadReproDirectory)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ReproFallbackDirectory)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DumpAst)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DumpIntermediatePrefix)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DumpIntermediates)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DumpIr)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DumpIrIds)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::PreprocessorOutput)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::OutputIncludes)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ReproFileSystem)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::SerialIr)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::SkipCodeGen)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ValidateIr)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VerbosePaths)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VerifyDebugSerialIr)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::NoCodeGen)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::FileSystem)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Heterogeneous)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::NoMangle)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::NoHLSLBinding)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::NoHLSLPackConstantBufferElements)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ValidateUniformity)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::AllowGLSL)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::EnableExperimentalPasses)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ArchiveType)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::CompileStdLib)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::Doc)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::IrCompression)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::LoadStdLib)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ReferenceModule)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::SaveStdLib)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::SaveStdLibBinSource)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::TrackLiveness)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::LoopInversion)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::ParameterBlocksUseRegisterSpaces)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::CountOfParsableOptions)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::DebugInformationFormat)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::VulkanBindShiftAll)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::GenerateWholeProgram)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::UseUpToDateBinaryModule)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::EmbedDXIL)
            BIND_ENUM_CONSTANT(slang_CompilerOptionName::CountOf)
            godot::ClassDB::bind_method(godot::D_METHOD("set_name", "name"), &slang_CompilerOptionEntry::set_name);
            godot::ClassDB::bind_method(godot::D_METHOD("get_name"), &slang_CompilerOptionEntry::get_name);
            godot::ClassDB::add_property("slang_CompilerOptionEntry",
                                         godot::PropertyInfo(godot::Variant::INT, "name", godot::PROPERTY_HINT_ENUM,
                                                             "MacroDefine,DepFile,EntryPointName,Specialize,Help,HelpStyle,Include,Language,"
                                                             "MatrixLayoutColumn,MatrixLayoutRow,ZeroInitialize,IgnoreCapabilities,RestrictiveCapabilityCheck,"
                                                             "ModuleName,Output,Profile,Stage,Target,Version,WarningsAsErrors,DisableWarnings,"
                                                             "EnableWarning,DisableWarning,DumpWarningDiagnostics,InputFilesRemain,EmitIr,ReportDownstreamTime,"
                                                             "ReportPerfBenchmark,SkipSPIRVValidation,SourceEmbedStyle,SourceEmbedName,SourceEmbedLanguage,"
                                                             "DisableShortCircuit,MinimumSlangOptimization,DisableNonEssentialValidations,DisableSourceMap,"
                                                             "UnscopedEnum,PreserveParameters,Capability,DefaultImageFormatUnknown,DisableDynamicDispatch,"
                                                             "DisableSpecialization,FloatingPointMode,DebugInformation,LineDirectiveMode,Optimization,Obfuscate,"
                                                             "VulkanBindShift,VulkanBindGlobals,VulkanInvertY,VulkanUseDxPositionW,VulkanUseEntryPointName,"
                                                             "VulkanUseGLLayout,VulkanEmitReflection,GLSLForceScalarLayout,EnableEffectAnnotations,EmitSpirvViaGLSL,"
                                                             "EmitSpirvDirectly,SPIRVCoreGrammarJSON,IncompleteLibrary,CompilerPath,DefaultDownstreamCompiler,"
                                                             "DownstreamArgs,PassThrough,DumpRepro,DumpReproOnError,ExtractRepro,LoadRepro,LoadReproDirectory,"
                                                             "ReproFallbackDirectory,DumpAst,DumpIntermediatePrefix,DumpIntermediates,DumpIr,DumpIrIds,"
                                                             "PreprocessorOutput,OutputIncludes,ReproFileSystem,SerialIr,SkipCodeGen,ValidateIr,"
                                                             "VerbosePaths,VerifyDebugSerialIr,NoCodeGen,FileSystem,Heterogeneous,NoMangle,NoHLSLBinding,"
                                                             "NoHLSLPackConstantBufferElements,ValidateUniformity,AllowGLSL,EnableExperimentalPasses,"
                                                             "ArchiveType,CompileStdLib,Doc,IrCompression,LoadStdLib,ReferenceModule,SaveStdLib,SaveStdLibBinSource,"
                                                             "TrackLiveness,LoopInversion,ParameterBlocksUseRegisterSpaces,CountOfParsableOptions,"
                                                             "DebugInformationFormat,VulkanBindShiftAll,GenerateWholeProgram,UseUpToDateBinaryModule,"
                                                             "EmbedDXIL,CountOf"
                                         ), "set_name", "get_name");

            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_CompilerOptionEntry::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_CompilerOptionEntry::get_value);
        }

    public:
        slang_CompilerOptionName get_name() {
            return name;
        }

        void set_name(slang_CompilerOptionName name) {
            this->name = name;
        }

        slang_CompilerOptionValue_HEAP_PTR *get_value();

        void set_value(slang_CompilerOptionValue *value);

    };

    MAKE_VALUE_TEMPLATE(CompilerOptionEntry)

    class slang_PreprocessorMacroDesc : public  slang_SlangObject{
    GDCLASS(slang_PreprocessorMacroDesc, slang_SlangObject)
        const char* name = "";
        const char* value = "";
    public:
        slang::PreprocessorMacroDesc duplicate(){
            return *this;
        }
        slang_PreprocessorMacroDesc(){
            this->name = "";
            this->value = "";
        }
        slang_PreprocessorMacroDesc(slang::PreprocessorMacroDesc desc){
            this->name = desc.name;
            this->value = desc.name;
        }
        operator slang::PreprocessorMacroDesc(){
            slang::PreprocessorMacroDesc desc;
            desc.name = this->name;
            desc.value = this->value;
            return desc;
        }

    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_name", "name"), &slang_PreprocessorMacroDesc::set_name);
            godot::ClassDB::bind_method(godot::D_METHOD("get_name"), &slang_PreprocessorMacroDesc::get_name);
            godot::ClassDB::add_property("slang_PreprocessorMacroDesc",
                                         godot::PropertyInfo(godot::Variant::STRING, "name"), "set_name", "get_name");

            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_PreprocessorMacroDesc::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_PreprocessorMacroDesc::get_value);
            godot::ClassDB::add_property("slang_PreprocessorMacroDesc",
                                         godot::PropertyInfo(godot::Variant::STRING, "value"), "set_value",
                                         "get_value");
        }

    public:
        godot::String get_name() const{
            if(name == 0)
                return "";
            return name;
        }

        void set_name(godot::String name) {
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            this->name = name.utf8().get_data();
        }

        godot::String get_value() const{
            if(value==0)
                return "";
            return godot::String::utf8(value);
        }

        void set_value(godot::String value) {
            this->value = value.utf8().get_data();
        }
    };


    MAKE_VALUE_TEMPLATE(PreprocessorMacroDesc)

    class slang_TargetDesc : public  slang_SlangObject{
    GDCLASS(slang_TargetDesc, slang_SlangObject)
    public:
        slang::TargetDesc* value;
        bool heap = 1;
        slang::TargetDesc duplicate(){
            return *value;
        }
        bool has_value(){
            return value;
        }
        slang_TargetDesc():value(memnew(slang::TargetDesc())) {}
        slang_TargetDesc(slang::TargetDesc* desc):value(desc),heap(0){}
        void operator=(slang::TargetDesc* desc){
            if(heap){
                godot::memdelete(value);
                heap = 0;
            }
            value = desc;
        }
        operator slang::TargetDesc*(){
            return value;
        }
        ~slang_TargetDesc(){
            if(heap){
                memdelete(value);
                heap = 0;
            }
        }

    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_TargetDesc::has_value);

            godot::ClassDB::bind_method(godot::D_METHOD("set_structureSize", "structureSize"),
                                        &slang_TargetDesc::set_structureSize);
            godot::ClassDB::bind_method(godot::D_METHOD("get_structureSize"), &slang_TargetDesc::get_structureSize);
//            godot::ClassDB::add_property("slang_TargetDesc", godot::PropertyInfo(godot::Variant::INT, "structureSize"),
//                                         "set_structureSize", "get_structureSize");

            BIND_ENUM_CONSTANT(SLANG_TARGET_UNKNOWN)
            BIND_ENUM_CONSTANT(SLANG_TARGET_NONE)
            BIND_ENUM_CONSTANT(SLANG_GLSL)
            BIND_ENUM_CONSTANT(SLANG_GLSL_VULKAN_DEPRECATED)
            BIND_ENUM_CONSTANT(SLANG_GLSL_VULKAN_ONE_DESC_DEPRECATED)
            BIND_ENUM_CONSTANT(SLANG_HLSL)
            BIND_ENUM_CONSTANT(SLANG_SPIRV)
            BIND_ENUM_CONSTANT(SLANG_SPIRV_ASM)
            BIND_ENUM_CONSTANT(SLANG_DXBC)
            BIND_ENUM_CONSTANT(SLANG_DXBC_ASM)
            BIND_ENUM_CONSTANT(SLANG_DXIL)
            BIND_ENUM_CONSTANT(SLANG_DXIL_ASM)
            BIND_ENUM_CONSTANT(SLANG_C_SOURCE)
            BIND_ENUM_CONSTANT(SLANG_CPP_SOURCE)
            BIND_ENUM_CONSTANT(SLANG_HOST_EXECUTABLE)
            BIND_ENUM_CONSTANT(SLANG_SHADER_SHARED_LIBRARY)
            BIND_ENUM_CONSTANT(SLANG_SHADER_HOST_CALLABLE)
            BIND_ENUM_CONSTANT(SLANG_CUDA_SOURCE)
            BIND_ENUM_CONSTANT(SLANG_PTX)
            BIND_ENUM_CONSTANT(SLANG_CUDA_OBJECT_CODE)
            BIND_ENUM_CONSTANT(SLANG_OBJECT_CODE)
            BIND_ENUM_CONSTANT(SLANG_HOST_CPP_SOURCE)
            BIND_ENUM_CONSTANT(SLANG_HOST_HOST_CALLABLE)
            BIND_ENUM_CONSTANT(SLANG_CPP_PYTORCH_BINDING)
            BIND_ENUM_CONSTANT(SLANG_METAL)
            BIND_ENUM_CONSTANT(SLANG_METAL_LIB)
            BIND_ENUM_CONSTANT(SLANG_METAL_LIB_ASM)
            BIND_ENUM_CONSTANT(SLANG_HOST_SHARED_LIBRARY)
            BIND_ENUM_CONSTANT(SLANG_TARGET_COUNT_OF)

            godot::ClassDB::bind_method(godot::D_METHOD("set_format", "format"), &slang_TargetDesc::set_format);
            godot::ClassDB::bind_method(godot::D_METHOD("get_format"), &slang_TargetDesc::get_format);
//            godot::ClassDB::add_property("slang_TargetDesc",
//                                         godot::PropertyInfo(godot::Variant::INT, "format", godot::PROPERTY_HINT_ENUM,
//                                                             "SLANG_TARGET_UNKNOWN,SLANG_TARGET_NONE,SLANG_GLSL,SLANG_GLSL_VULKAN_DEPRECATED,"
//                                                             "SLANG_GLSL_VULKAN_ONE_DESC_DEPRECATED,SLANG_HLSL,SLANG_SPIRV,SLANG_SPIRV_ASM,"
//                                                             "SLANG_DXBC,SLANG_DXBC_ASM,SLANG_DXIL,SLANG_DXIL_ASM,SLANG_C_SOURCE,SLANG_CPP_SOURCE,"
//                                                             "SLANG_HOST_EXECUTABLE,SLANG_SHADER_SHARED_LIBRARY,SLANG_SHADER_HOST_CALLABLE,"
//                                                             "SLANG_CUDA_SOURCE,SLANG_PTX,SLANG_CUDA_OBJECT_CODE,SLANG_OBJECT_CODE,"
//                                                             "SLANG_HOST_CPP_SOURCE,SLANG_HOST_HOST_CALLABLE,SLANG_CPP_PYTORCH_BINDING,"
//                                                             "SLANG_METAL,SLANG_METAL_LIB,SLANG_METAL_LIB_ASM,SLANG_HOST_SHARED_LIBRARY,"
//                                                             "SLANG_TARGET_COUNT_OF"
//                                         ), "set_format", "get_format");

            BIND_ENUM_CONSTANT(slang_SlangProfileID::SLANG_PROFILE_UNKNOWN)

            godot::ClassDB::bind_method(godot::D_METHOD("set_profile", "profile"), &slang_TargetDesc::set_profile);
            godot::ClassDB::bind_method(godot::D_METHOD("get_profile"), &slang_TargetDesc::get_profile);
//            godot::ClassDB::add_property("slang_TargetDesc",
//                                         godot::PropertyInfo(godot::Variant::INT, "profile", godot::PROPERTY_HINT_ENUM,
//                                                             "SLANG_PROFILE_UNKNOWN"
//                                         ), "set_profile", "get_profile");

            godot::ClassDB::bind_method(godot::D_METHOD("set_flags", "flags"), &slang_TargetDesc::set_flags);
            godot::ClassDB::bind_method(godot::D_METHOD("get_flags"), &slang_TargetDesc::get_flags);
//            godot::ClassDB::add_property("slang_TargetDesc", godot::PropertyInfo(godot::Variant::INT, "flags"),
//                                         "set_flags", "get_flags");

            BIND_ENUM_CONSTANT(slang_SlangFloatingPointMode::SLANG_FLOATING_POINT_MODE_DEFAULT)
            BIND_ENUM_CONSTANT(slang_SlangFloatingPointMode::SLANG_FLOATING_POINT_MODE_FAST)
            BIND_ENUM_CONSTANT(slang_SlangFloatingPointMode::SLANG_FLOATING_POINT_MODE_PRECISE)

            godot::ClassDB::bind_method(godot::D_METHOD("set_floatingPointMode", "floatingPointMode"),
                                        &slang_TargetDesc::set_floatingPointMode);
            godot::ClassDB::bind_method(godot::D_METHOD("get_floatingPointMode"),
                                        &slang_TargetDesc::get_floatingPointMode);
//            godot::ClassDB::add_property("slang_TargetDesc",
//                                         godot::PropertyInfo(godot::Variant::INT, "floatingPointMode",
//                                                             godot::PROPERTY_HINT_ENUM,
//                                                             "SLANG_FLOATING_POINT_MODE_DEFAULT,SLANG_FLOATING_POINT_MODE_FAST,SLANG_FLOATING_POINT_MODE_PRECISE"
//                                         ), "set_floatingPointMode", "get_floatingPointMode");

            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_DEFAULT)
            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_NONE)
            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_STANDARD)
            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_GLSL)
            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_SOURCE_MAP)

            godot::ClassDB::bind_method(godot::D_METHOD("set_lineDirectiveMode", "lineDirectiveMode"),
                                        &slang_TargetDesc::set_lineDirectiveMode);
            godot::ClassDB::bind_method(godot::D_METHOD("get_lineDirectiveMode"),
                                        &slang_TargetDesc::get_lineDirectiveMode);
//            godot::ClassDB::add_property("slang_TargetDesc",
//                                         godot::PropertyInfo(godot::Variant::INT, "lineDirectiveMode",
//                                                             godot::PROPERTY_HINT_ENUM,
//                                                             "SLANG_LINE_DIRECTIVE_MODE_DEFAULT,SLANG_LINE_DIRECTIVE_MODE_NONE,SLANG_LINE_DIRECTIVE_MODE_STANDARD,"
//                                                             "SLANG_LINE_DIRECTIVE_MODE_GLSL,SLANG_LINE_DIRECTIVE_MODE_SOURCE_MAP"
//                                         ), "set_lineDirectiveMode", "get_lineDirectiveMode");

            godot::ClassDB::bind_method(
                    godot::D_METHOD("set_forceGLSLScalarBufferLayout", "forceGLSLScalarBufferLayout"),
                    &slang_TargetDesc::set_forceGLSLScalarBufferLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("get_forceGLSLScalarBufferLayout"),
                                        &slang_TargetDesc::get_forceGLSLScalarBufferLayout);
//            godot::ClassDB::add_property("slang_TargetDesc",
//                                         godot::PropertyInfo(godot::Variant::BOOL, "forceGLSLScalarBufferLayout"),
//                                         "set_forceGLSLScalarBufferLayout", "get_forceGLSLScalarBufferLayout");

            godot::ClassDB::bind_method(godot::D_METHOD("set_compilerOptionEntries", "compilerOptionEntries"),
                                        &slang_TargetDesc::set_compilerOptionEntries);
            godot::ClassDB::bind_method(godot::D_METHOD("get_compilerOptionEntries"),
                                        &slang_TargetDesc::get_compilerOptionEntries);

            godot::ClassDB::bind_method(godot::D_METHOD("set_compilerOptionEntryCount", "compilerOptionEntryCount"),
                                        &slang_TargetDesc::set_compilerOptionEntryCount);
            godot::ClassDB::bind_method(godot::D_METHOD("get_compilerOptionEntryCount"),
                                        &slang_TargetDesc::get_compilerOptionEntryCount);
//            godot::ClassDB::add_property("slang_TargetDesc",
//                                         godot::PropertyInfo(godot::Variant::INT, "compilerOptionEntryCount"),
//                                         "set_compilerOptionEntryCount", "get_compilerOptionEntryCount");

        }

    public:
        size_t get_structureSize() const {
            return value->structureSize;
        }

        void set_structureSize(size_t size) {
            this->value->structureSize = size;
        }

        slang_SlangCompileTarget get_format() const {
            return (slang_SlangCompileTarget) value->format;
        }

        void set_format(slang_SlangCompileTarget format) {
            this->value->format = static_cast<SlangCompileTarget>(format);
        }

        slang_SlangProfileID get_profile() const {
            return (slang_SlangProfileID) value->profile;
        }

        void set_profile(slang_SlangProfileID profile) {
            this->value->profile = static_cast<SlangProfileID>(profile);
        }

        unsigned int get_flags() const {
            return value->flags;
        }

        void set_flags(unsigned int flags) {
            this->value->flags = flags;
        }

        int get_floatingPointMode() const {
            return (int) value->floatingPointMode;
        }

        void set_floatingPointMode(int floatingPointMode) {
            this->value->floatingPointMode = static_cast<SlangFloatingPointMode>(floatingPointMode);
        }

        slang_SlangLineDirectiveMode get_lineDirectiveMode() const {
            return (slang_SlangLineDirectiveMode) value->lineDirectiveMode;
        }

        void set_lineDirectiveMode(slang_SlangLineDirectiveMode lineDirectiveMode) {
            this->value->lineDirectiveMode = static_cast<SlangLineDirectiveMode>(lineDirectiveMode);
        }

        bool get_forceGLSLScalarBufferLayout() const {
            return value->forceGLSLScalarBufferLayout;
        }

        void set_forceGLSLScalarBufferLayout(bool forceGLSLScalarBufferLayout) {
            this->value->forceGLSLScalarBufferLayout = forceGLSLScalarBufferLayout;
        }

        slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR *get_compilerOptionEntries();

        void set_compilerOptionEntries(slang_CompilerOptionEntry_VALUE_VECTOR *compilerOptionEntries);

        uint32_t get_compilerOptionEntryCount() const {
            return value->compilerOptionEntryCount;
        }

        void set_compilerOptionEntryCount(uint32_t compilerOptionEntryCount) {
            this->value->compilerOptionEntryCount = compilerOptionEntryCount;
        }
    };



    MAKE_VALUE_TEMPLATE(TargetDesc)

    class slang_SessionDesc : public slang_SlangObject{
    GDCLASS(slang_SessionDesc, slang_SlangObject)
    public:
        slang::SessionDesc* value;
        bool heap = 1;
        slang_SessionDesc():value(memnew(slang::SessionDesc())){}
        slang_SessionDesc(slang::SessionDesc* desc):value(desc),heap(0){}
        slang::SessionDesc duplicate(){
            return *value;
        }
        bool has_value(){
            return value;
        }
        void operator=(slang::SessionDesc* desc){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = desc;
        }
        operator slang::SessionDesc*(){
            return value;
        }
        ~slang_SessionDesc(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_SessionDesc::has_value);

            godot::ClassDB::bind_method(godot::D_METHOD("set_structureSize", "structureSize"),
                                        &slang_SessionDesc::set_structureSize);
            godot::ClassDB::bind_method(godot::D_METHOD("get_structureSize"), &slang_SessionDesc::get_structureSize);
//            godot::ClassDB::add_property("slang_SessionDesc", godot::PropertyInfo(godot::Variant::INT, "structureSize"),
//                                         "set_structureSize", "get_structureSize");

            godot::ClassDB::bind_method(godot::D_METHOD("set_targets", "targets"), &slang_SessionDesc::set_targets);
            godot::ClassDB::bind_method(godot::D_METHOD("get_targets"), &slang_SessionDesc::get_targets);

            godot::ClassDB::bind_method(godot::D_METHOD("set_targetCount", "targetCount"),
                                        &slang_SessionDesc::set_targetCount);
            godot::ClassDB::bind_method(godot::D_METHOD("get_targetCount"), &slang_SessionDesc::get_targetCount);
//            godot::ClassDB::add_property("slang_SessionDesc", godot::PropertyInfo(godot::Variant::INT, "targetCount"),
//                                         "set_targetCount", "get_targetCount");

            godot::ClassDB::bind_method(godot::D_METHOD("set_flags", "flags"), &slang_SessionDesc::set_flags);
            godot::ClassDB::bind_method(godot::D_METHOD("get_flags"), &slang_SessionDesc::get_flags);
//            godot::ClassDB::add_property("slang_SessionDesc", godot::PropertyInfo(godot::Variant::INT, "flags"),
//                                         "set_flags", "get_flags");

            BIND_ENUM_CONSTANT(slang_SlangMatrixLayoutMode::SLANG_MATRIX_LAYOUT_MODE_UNKNOWN)
            BIND_ENUM_CONSTANT(slang_SlangMatrixLayoutMode::SLANG_MATRIX_LAYOUT_ROW_MAJOR)
            BIND_ENUM_CONSTANT(slang_SlangMatrixLayoutMode::SLANG_MATRIX_LAYOUT_COLUMN_MAJOR)


            godot::ClassDB::bind_method(godot::D_METHOD("set_defaultMatrixLayoutMode", "defaultMatrixLayoutMode"),
                                        &slang_SessionDesc::set_defaultMatrixLayoutMode);
            godot::ClassDB::bind_method(godot::D_METHOD("get_defaultMatrixLayoutMode"),
                                        &slang_SessionDesc::get_defaultMatrixLayoutMode);
//            godot::ClassDB::add_property("slang_SessionDesc",
//                                         godot::PropertyInfo(godot::Variant::INT, "defaultMatrixLayoutMode",
//                                                             godot::PROPERTY_HINT_ENUM,
//                                                             "SLANG_MATRIX_LAYOUT_MODE_UNKNOWN,SLANG_MATRIX_LAYOUT_ROW_MAJOR,SLANG_MATRIX_LAYOUT_COLUMN_MAJOR"
//                                         ), "set_defaultMatrixLayoutMode", "get_defaultMatrixLayoutMode");

            godot::ClassDB::bind_method(godot::D_METHOD("set_preprocessorMacroCount", "preprocessorMacroCount"),
                                        &slang_SessionDesc::set_preprocessorMacroCount);
            godot::ClassDB::bind_method(godot::D_METHOD("get_preprocessorMacroCount"),
                                        &slang_SessionDesc::get_preprocessorMacroCount);
//            godot::ClassDB::add_property("slang_SessionDesc",
//                                         godot::PropertyInfo(godot::Variant::INT, "preprocessorMacroCount"),
//                                         "set_preprocessorMacroCount", "get_preprocessorMacroCount");

            godot::ClassDB::bind_method(godot::D_METHOD("set_fileSystem", "fileSystem"),
                                        &slang_SessionDesc::set_fileSystem);
            godot::ClassDB::bind_method(godot::D_METHOD("get_fileSystem"), &slang_SessionDesc::get_fileSystem);

            godot::ClassDB::bind_method(godot::D_METHOD("set_enableEffectAnnotations", "enableEffectAnnotations"),
                                        &slang_SessionDesc::set_enableEffectAnnotations);
            godot::ClassDB::bind_method(godot::D_METHOD("get_enableEffectAnnotations"),
                                        &slang_SessionDesc::get_enableEffectAnnotations);
//            godot::ClassDB::add_property("slang_SessionDesc",
//                                         godot::PropertyInfo(godot::Variant::BOOL, "enableEffectAnnotations"),
//                                         "set_enableEffectAnnotations", "get_enableEffectAnnotations");

            godot::ClassDB::bind_method(godot::D_METHOD("set_allowGLSLSyntax", "allowGLSLSyntax"),
                                        &slang_SessionDesc::set_allowGLSLSyntax);
            godot::ClassDB::bind_method(godot::D_METHOD("get_allowGLSLSyntax"),
                                        &slang_SessionDesc::get_allowGLSLSyntax);
//            godot::ClassDB::add_property("slang_SessionDesc",
//                                         godot::PropertyInfo(godot::Variant::BOOL, "allowGLSLSyntax"),
//                                         "set_allowGLSLSyntax", "get_allowGLSLSyntax");

            godot::ClassDB::bind_method(godot::D_METHOD("set_compilerOptionEntries", "compilerOptionEntries"),
                                        &slang_SessionDesc::set_compilerOptionEntries);
            godot::ClassDB::bind_method(godot::D_METHOD("get_compilerOptionEntries"),
                                        &slang_SessionDesc::get_compilerOptionEntries);
        }

    public:
        size_t get_structureSize() {
            return value->structureSize;
        }

        void set_structureSize(size_t size) {
            this->value->structureSize = size;
        }

        slang_TargetDesc_VALUE_VECTOR_HEAP_PTR* get_targets();

        void set_targets(slang_TargetDesc_VALUE_VECTOR* targets);

        int64_t get_targetCount() {
            return value->targetCount;
        }

        void set_targetCount(int64_t targetCount) {
            this->value->targetCount = targetCount;
        }

        uint32_t get_flags() {
            return value->flags;
        }

        void set_flags(uint32_t flags) {
            this->value->flags = flags;
        }

        slang_SlangMatrixLayoutMode get_defaultMatrixLayoutMode() {
            return (slang_SlangMatrixLayoutMode) value->defaultMatrixLayoutMode;
        }

        void set_defaultMatrixLayoutMode(slang_SlangMatrixLayoutMode defaultMatrixLayoutMode) {
            this->value->defaultMatrixLayoutMode = (SlangMatrixLayoutMode) defaultMatrixLayoutMode;
        }

        const char *const *get_searchPaths() {
            return value->searchPaths;
        }

        void set_searchPaths(const char *const *searchPaths) {
            this->value->searchPaths = searchPaths;
        }

        int64_t get_searchPathCount() {
            return value->searchPathCount;
        }

        void set_searchPathCount(int64_t searchPathCount) {
            this->value->searchPathCount = searchPathCount;
        }

        int64_t get_preprocessorMacroCount() {
            return value->preprocessorMacroCount;
        }

        void set_preprocessorMacroCount(int64_t preprocessorMacroCount) {
            this->value->preprocessorMacroCount = preprocessorMacroCount;
        }

        slang_IFileSystem *get_fileSystem();

        void set_fileSystem(slang_IFileSystem *fileSystem);

        bool get_enableEffectAnnotations() {
            return value->enableEffectAnnotations;
        }

        void set_enableEffectAnnotations(bool enableEffectAnnotations) {
            this->value->enableEffectAnnotations = enableEffectAnnotations;
        }

        bool get_allowGLSLSyntax() {
            return value->allowGLSLSyntax;
        }

        void set_allowGLSLSyntax(bool allowGLSLSyntax) {
            this->value->allowGLSLSyntax = allowGLSLSyntax;
        }

        slang_CompilerOptionEntry_VALUE_VECTOR_HEAP_PTR *get_compilerOptionEntries();

        void set_compilerOptionEntries(slang_CompilerOptionEntry_VALUE_VECTOR *compilerOptionEntries);

        uint32_t get_compilerOptionEntryCount() {
            return value->compilerOptionEntryCount;
        }

        void set_compilerOptionEntryCount(uint32_t compilerOptionEntryCount) {
            this->value->compilerOptionEntryCount = compilerOptionEntryCount;
        }
    };


    MAKE_VALUE_TEMPLATE(SessionDesc)

    class slang_Modifier : public slang_SlangObject{
    GDCLASS(slang_Modifier, slang_SlangObject)
    public:
        slang::Modifier* value;
        bool heap = 1;
        slang::Modifier duplicate(){
            return *value;
        }
        bool has_value(){
            return value;
        }
        slang_Modifier():value(memnew(slang::Modifier())) {}
        slang_Modifier(slang::Modifier* modi):value(modi),heap(0){}
        void operator= (slang::Modifier* modi){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = modi;
        }
        operator slang::Modifier*(){
            return value;
        }
        ~slang_Modifier(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_Modifier::has_value);
            BIND_ENUM_CONSTANT(slang::Modifier::ID::NoDiff)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::Static)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::Shared)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::Const)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::Export)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::Extern)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::Differentiable)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::Mutating)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::In)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::Out)
            BIND_ENUM_CONSTANT(slang::Modifier::ID::InOut)
        }
    };


    MAKE_VALUE_TEMPLATE(Modifier)
}
VARIANT_ENUM_CAST(slang::Modifier::ID)
namespace slang_cpp {
    class slang_UserAttribute : public  slang_SlangObject{
    GDCLASS(slang_UserAttribute, slang_SlangObject)
    public:
        slang::UserAttribute* value = nullptr;
        bool heap = 1;
        slang_UserAttribute():value(memnew(slang::UserAttribute())){}
        slang_UserAttribute(slang::UserAttribute* attr):value(attr),heap(0){}
        void operator=(slang::UserAttribute* attr){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = attr;
        }
        bool has_value(){
            return value;
        }
        operator slang::UserAttribute*(){
            return value;
        }
        slang::UserAttribute duplicate(){
            return *value;
        }
        ~slang_UserAttribute(){
            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_UserAttribute::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_UserAttribute::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentCount"), &slang_UserAttribute::getArgumentCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentType", "index"), &slang_UserAttribute::getArgumentType);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentValueInt", "index", "outValue"), &slang_UserAttribute::getArgumentValueInt);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentValueFloat", "index", "outValue"), &slang_UserAttribute::getArgumentValueFloat);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentValueString", "index", "outSize"), &slang_UserAttribute::getArgumentValueString);
        }
    public:
        godot::String getName() {
            auto a = this->value->getName();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        uint32_t getArgumentCount() {
            return this->value->getArgumentCount();
        }
        slang_TypeReflection_HEAP_PTR* getArgumentType(uint32_t index);
        SlangResult getArgumentValueInt(uint32_t index, slang_INT* outValue){
            int v = 0;
            SlangResult res = this->value->getArgumentValueInt(index, &v);
            outValue->set_value(v);
            return res;
        }
        SlangResult getArgumentValueFloat(uint32_t index, slang_DOUBLE* outValue){
            float v = 0;
            SlangResult res = this->value->getArgumentValueFloat(index, &v);
            outValue->set_value(v);
            return res;
        }
        godot::String getArgumentValueString(uint32_t index,slang_SIZE* outSize){
            size_t size = 0;
            const char* v = this->value->getArgumentValueString(index, &size);
            if(v == 0)
                return "";
            return godot::String::utf8(v);
        }
    };


    MAKE_VALUE_TEMPLATE(UserAttribute)


    class slang_VariableReflection : public  slang_SlangObject{
    GDCLASS(slang_VariableReflection, slang_SlangObject)
    public:
        slang::VariableReflection* value = nullptr;
        bool heap = 1;
        slang_VariableReflection():value(memnew(slang::VariableReflection())){}
        slang_VariableReflection(slang::VariableReflection* var):value(var),heap(0){}
        void operator=(slang::VariableReflection* var){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = var;
        }
        operator slang::VariableReflection*(){
            return value;
        }
        slang::VariableReflection duplicate(){
            return *value;
        }
        bool has_value(){
            return value;
        }
        ~slang_VariableReflection(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_VariableReflection::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_VariableReflection::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getType"), &slang_VariableReflection::getType);
            godot::ClassDB::bind_method(godot::D_METHOD("findModifier", "id"), &slang_VariableReflection::findModifier);
            godot::ClassDB::bind_method(godot::D_METHOD("getUserAttributeCount"), &slang_VariableReflection::getUserAttributeCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getUserAttributeByIndex", "index"), &slang_VariableReflection::getUserAttributeByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("findUserAttributeByName", "session", "name"), &slang_VariableReflection::findUserAttributeByName);
            godot::ClassDB::bind_method(godot::D_METHOD("hasDefaultValue"), &slang_VariableReflection::hasDefaultValue);
        }

    public:
        godot::String getName() {
            auto a = this->value->getName();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        slang_TypeReflection_HEAP_PTR * getType();
        slang_Modifier_HEAP_PTR* findModifier(slang::Modifier::ID id){
            auto* a = memnew(slang_Modifier(this->value->findModifier(id)));
            auto* ptr = memnew(slang_Modifier_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        unsigned int getUserAttributeCount(){
            return this->value->getUserAttributeCount();
        }
        slang_UserAttribute_HEAP_PTR* getUserAttributeByIndex(unsigned int index) {
            auto* ptr = memnew(slang_UserAttribute_HEAP_PTR(memnew(slang_UserAttribute(this->value->getUserAttributeByIndex(index)))));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_UserAttribute_HEAP_PTR* findUserAttributeByName(slang_IGlobalSession* session,godot::String name) {
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto* ptr = memnew(slang_UserAttribute_HEAP_PTR(memnew(slang_UserAttribute(this->value->findUserAttributeByName(session->value,name.utf8().get_data())))));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        bool hasDefaultValue(){
            return this->value->hasDefaultValue();
        }

    };


    MAKE_VALUE_TEMPLATE(VariableReflection)


    class slang_VariableLayoutReflection : public slang_SlangObject{
    GDCLASS(slang_VariableLayoutReflection, slang_SlangObject)
    public:
        slang::VariableLayoutReflection* value = nullptr;
        bool heap = 1;
        slang_VariableLayoutReflection():value(memnew(slang::VariableLayoutReflection())){}
        slang_VariableLayoutReflection(slang::VariableLayoutReflection* refl):value(refl),heap(0){}
        void operator=(slang::VariableLayoutReflection* refl){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = refl;
        }
        operator slang::VariableLayoutReflection*(){
            return value;
        }
        slang::VariableLayoutReflection duplicate(){
            return *value;
        }
        bool has_value(){
            return value;
        }
        ~slang_VariableLayoutReflection(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_VariableLayoutReflection::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("getVariable"), &slang_VariableLayoutReflection::getVariable);
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_VariableLayoutReflection::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("findModifier", "id"), &slang_VariableLayoutReflection::findModifier);
            godot::ClassDB::bind_method(godot::D_METHOD("getTypeLayout"), &slang_VariableLayoutReflection::getTypeLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("getCategory"), &slang_VariableLayoutReflection::getCategory);
            godot::ClassDB::bind_method(godot::D_METHOD("getCategoryCount"), &slang_VariableLayoutReflection::getCategoryCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getCategoryByIndex"), &slang_VariableLayoutReflection::getCategoryByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("getOffset","category"), &slang_VariableLayoutReflection::getOffset);
            godot::ClassDB::bind_method(godot::D_METHOD("getBindingIndex"), &slang_VariableLayoutReflection::getBindingIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("getBindingSpace"), &slang_VariableLayoutReflection::getBindingSpace);
            godot::ClassDB::bind_method(godot::D_METHOD("getSemanticName"), &slang_VariableLayoutReflection::getSemanticName);
            godot::ClassDB::bind_method(godot::D_METHOD("getSemanticIndex"), &slang_VariableLayoutReflection::getSemanticIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("getStage"), &slang_VariableLayoutReflection::getStage);
        }

    public:
        slang_VariableReflection_HEAP_PTR* getVariable() {
            auto* a = memnew(slang_VariableReflection(this->value->getVariable()));
            auto* ptr = memnew(slang_VariableReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        godot::String getName(){
            auto a = this->value->getName();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        slang_Modifier_HEAP_PTR* findModifier(slang::Modifier::ID id){
            auto* a = memnew(slang_Modifier(this->value->findModifier(id)));
            auto* ptr = memnew(slang_Modifier_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_TypeLayoutReflection_HEAP_PTR* getTypeLayout();
        slang_SlangParameterCategory getCategory() {
            return (slang_SlangParameterCategory) this->value->getCategory();
        }
        unsigned int getCategoryCount(){
            return this->value->getCategoryCount();
        }
        slang_SlangParameterCategory getCategoryByIndex(unsigned int index){
            return (slang_SlangParameterCategory)this->value->getCategoryByIndex(index);
        }
        size_t getOffset(slang_SlangParameterCategory category = SLANG_PARAMETER_CATEGORY_UNIFORM){
            return this->value->getOffset((SlangParameterCategory)category);
        }
        unsigned getBindingIndex(){
            return this->value->getBindingIndex();
        }
//        unsigned getBindingSpace(){
//            return this->value.getBindingSpace();
//        }
        size_t getBindingSpace(slang_SlangParameterCategory category){
            return this->value->getBindingSpace((SlangParameterCategory)category);
        }
        godot::String getSemanticName(){
            auto a = this->value->getSemanticName();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        size_t getSemanticIndex(){
            return this->value->getSemanticIndex();
        }
        slang_SlangStage getStage(){
            return (slang_SlangStage)this->value->getStage();
        }
    };


    MAKE_VALUE_TEMPLATE(VariableLayoutReflection)


    class slang_FunctionReflection : public slang_SlangObject{
    GDCLASS(slang_FunctionReflection, slang_SlangObject)
    public:
        slang::FunctionReflection* value = nullptr;
        bool heap = 1;
        slang_FunctionReflection():value(memnew(slang::FunctionReflection())){}
        slang_FunctionReflection(slang::FunctionReflection* refl): value(refl),heap(0){}
        void operator=(slang::FunctionReflection* refl){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = refl;
        }
        operator slang::FunctionReflection*(){
            return value;
        }
        slang::FunctionReflection duplicate(){
            return *value;
        }
        bool has_value(){
            return value;
        }
        ~slang_FunctionReflection(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_FunctionReflection::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_FunctionReflection::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getReturnType"), &slang_FunctionReflection::getReturnType);
            godot::ClassDB::bind_method(godot::D_METHOD("getParameterCount"), &slang_FunctionReflection::getParameterCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getParameterByIndex", "index"), &slang_FunctionReflection::getParameterByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("getUserAttributeCount"), &slang_FunctionReflection::getUserAttributeCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getUserAttributeByIndex", "index"), &slang_FunctionReflection::getUserAttributeByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("findUserAttributeByName", "session", "name"), &slang_FunctionReflection::findUserAttributeByName);
            godot::ClassDB::bind_method(godot::D_METHOD("findModifier", "id"), &slang_FunctionReflection::findModifier);
            godot::ClassDB::bind_method(godot::D_METHOD("getGenericContainer"), &slang_FunctionReflection::getGenericContainer);
        }

    public:
        godot::String getName() {
            auto a = this->value->getName();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        slang_TypeReflection_HEAP_PTR * getReturnType();
        unsigned int getParameterCount() {
            return this->value->getParameterCount();
        }
        slang_VariableReflection_HEAP_PTR* getParameterByIndex(unsigned int index) {
            auto* a = memnew(slang_VariableReflection(this->value->getParameterByIndex(index)));
            auto* ptr = memnew(slang_VariableReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        unsigned int getUserAttributeCount() {
            return this->value->getUserAttributeCount();
        }
        slang_UserAttribute_HEAP_PTR* getUserAttributeByIndex(unsigned int index) {
            auto* a = memnew(slang_UserAttribute(this->value->getUserAttributeByIndex(index)));
            auto* ptr = memnew(slang_UserAttribute_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_UserAttribute_HEAP_PTR* findUserAttributeByName(slang_IGlobalSession* session,godot::String name) {
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto* a = memnew(slang_UserAttribute(this->value->findUserAttributeByName(session->value,name.utf8().get_data())));
            auto* ptr = memnew(slang_UserAttribute_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_Modifier_HEAP_PTR* findModifier(slang::Modifier::ID id){
            auto* a = memnew(slang_Modifier(this->value->findModifier(id)));
            auto* ptr = memnew(slang_Modifier_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_GenericReflection* getGenericContainer();
    };


    MAKE_VALUE_TEMPLATE(FunctionReflection)


    class slang_DeclReflection : public slang_SlangObject{
    GDCLASS(slang_DeclReflection, slang_SlangObject)
    public:
        slang::DeclReflection* value;
        bool heap = 1;
        slang_DeclReflection():value(memnew(slang::DeclReflection())){}
        slang_DeclReflection(slang::DeclReflection* ref): value(ref),heap(0){}
        void operator=(slang::DeclReflection* ref){
            value = ref;
        }
        operator slang::DeclReflection*(){
            return value;
        }
        slang::DeclReflection duplicate(){
            return *value;
        }
        bool has_value(){
            return value;
        }
        ~slang_DeclReflection(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    public:
        enum Kind
        {
            Unsupported = SLANG_DECL_KIND_UNSUPPORTED_FOR_REFLECTION,
            Struct = SLANG_DECL_KIND_STRUCT,
            Func = SLANG_DECL_KIND_FUNC,
            Module = SLANG_DECL_KIND_MODULE,
            Generic = SLANG_DECL_KIND_GENERIC,
            Variable = SLANG_DECL_KIND_VARIABLE,
        };
    private:
        static void _bind_methods(){
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_DeclReflection::has_value);
            BIND_ENUM_CONSTANT(slang_DeclReflection::Kind::Unsupported)
            BIND_ENUM_CONSTANT(slang_DeclReflection::Kind::Struct)
            BIND_ENUM_CONSTANT(slang_DeclReflection::Kind::Func)
            BIND_ENUM_CONSTANT(slang_DeclReflection::Kind::Module)
            BIND_ENUM_CONSTANT(slang_DeclReflection::Kind::Generic)
            BIND_ENUM_CONSTANT(slang_DeclReflection::Kind::Variable)

            godot::ClassDB::bind_method(godot::D_METHOD("getKind"), &slang_DeclReflection::getKind);
            godot::ClassDB::bind_method(godot::D_METHOD("getChildrenCount"), &slang_DeclReflection::getChildrenCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getChild", "index"), &slang_DeclReflection::getChild);
            godot::ClassDB::bind_method(godot::D_METHOD("getType"), &slang_DeclReflection::getType);
            godot::ClassDB::bind_method(godot::D_METHOD("asVariable"), &slang_DeclReflection::asVariable);
            godot::ClassDB::bind_method(godot::D_METHOD("asFunction"), &slang_DeclReflection::asFunction);
            godot::ClassDB::bind_method(godot::D_METHOD("asGeneric"), &slang_DeclReflection::asGeneric);
            godot::ClassDB::bind_method(godot::D_METHOD("getParent"), &slang_DeclReflection::getParent);
        }
    public:
        Kind getKind() {
            return (Kind) this->value->getKind();
        }
        unsigned int getChildrenCount(){
            return this->value->getChildrenCount();
        }
        slang_DeclReflection_HEAP_PTR* getChild(unsigned int index) {
            auto* a = memnew(slang_DeclReflection(this->value->getChild(index)));
            auto* ptr = memnew(slang_DeclReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_TypeReflection_HEAP_PTR* getType();
        slang_VariableReflection_HEAP_PTR* asVariable() {
            auto* a = memnew(slang_VariableReflection(this->value->asVariable()));
            auto* ptr = memnew(slang_VariableReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_FunctionReflection_HEAP_PTR* asFunction() {
            auto* a = memnew(slang_FunctionReflection(this->value->asFunction()));
            auto* ptr = memnew(slang_FunctionReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_GenericReflection* asGeneric();
        slang_DeclReflection_HEAP_PTR* getParent() {
            auto* a = memnew(slang_DeclReflection(this->value->getParent()));
            auto* ptr = memnew(slang_DeclReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
    };


    MAKE_VALUE_TEMPLATE(DeclReflection)


    class slang_GenericReflection : public slang::GenericReflection, public slang_SlangObject{
    GDCLASS(slang_GenericReflection, slang_SlangObject)
    private:
        static void _bind_methods() {}
    public:
    };



    class slang_TypeReflection : public slang_SlangObject{
    GDCLASS(slang_TypeReflection, slang_SlangObject)
    public:
        slang::TypeReflection* value;
        bool heap = 1;
        slang::TypeReflection duplicate(){
            return *value;
        }
        bool has_value(){
            return value;
        }
        slang_TypeReflection(): value(memnew(slang::TypeReflection())){}
        slang_TypeReflection(slang::TypeReflection* ref):value(ref),heap(0){}
        void operator=(slang::TypeReflection* ref){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = ref;
        }
        operator slang::TypeReflection*(){
            return value;
        }
        ~slang_TypeReflection(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    public:
        enum Kind
        {
            None    = SLANG_TYPE_KIND_NONE,
            Struct  = SLANG_TYPE_KIND_STRUCT,
            Array   = SLANG_TYPE_KIND_ARRAY,
            Matrix  = SLANG_TYPE_KIND_MATRIX,
            Vector  = SLANG_TYPE_KIND_VECTOR,
            Scalar  = SLANG_TYPE_KIND_SCALAR,
            ConstantBuffer = SLANG_TYPE_KIND_CONSTANT_BUFFER,
            Resource = SLANG_TYPE_KIND_RESOURCE,
            SamplerState = SLANG_TYPE_KIND_SAMPLER_STATE,
            TextureBuffer = SLANG_TYPE_KIND_TEXTURE_BUFFER,
            ShaderStorageBuffer = SLANG_TYPE_KIND_SHADER_STORAGE_BUFFER,
            ParameterBlock = SLANG_TYPE_KIND_PARAMETER_BLOCK,
            GenericTypeParameter = SLANG_TYPE_KIND_GENERIC_TYPE_PARAMETER,
            Interface = SLANG_TYPE_KIND_INTERFACE,
            OutputStream = SLANG_TYPE_KIND_OUTPUT_STREAM,
            Specialized = SLANG_TYPE_KIND_SPECIALIZED,
            Feedback = SLANG_TYPE_KIND_FEEDBACK,
            Pointer = SLANG_TYPE_KIND_POINTER,
            DynamicResource = SLANG_TYPE_KIND_DYNAMIC_RESOURCE,
        };
        enum ScalarType : SlangScalarTypeIntegral
        {
            None_S    = SLANG_SCALAR_TYPE_NONE,
            Void    = SLANG_SCALAR_TYPE_VOID,
            Bool    = SLANG_SCALAR_TYPE_BOOL,
            Int32   = SLANG_SCALAR_TYPE_INT32,
            UInt32  = SLANG_SCALAR_TYPE_UINT32,
            Int64   = SLANG_SCALAR_TYPE_INT64,
            UInt64  = SLANG_SCALAR_TYPE_UINT64,
            Float16 = SLANG_SCALAR_TYPE_FLOAT16,
            Float32 = SLANG_SCALAR_TYPE_FLOAT32,
            Float64 = SLANG_SCALAR_TYPE_FLOAT64,
            Int8    = SLANG_SCALAR_TYPE_INT8,
            UInt8   = SLANG_SCALAR_TYPE_UINT8,
            Int16   = SLANG_SCALAR_TYPE_INT16,
            UInt16  = SLANG_SCALAR_TYPE_UINT16,
        };
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_TypeReflection::has_value);
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::None)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Struct)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Array)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Matrix)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Vector)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Scalar)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::ConstantBuffer)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Resource)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::SamplerState)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::TextureBuffer)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::ShaderStorageBuffer)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::ParameterBlock)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::GenericTypeParameter)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Interface)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::OutputStream)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Specialized)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Feedback)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::Pointer)
            BIND_ENUM_CONSTANT(slang_TypeReflection::Kind::DynamicResource)

            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::None_S)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::Void)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::Bool)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::Int32)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::UInt32)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::Int64)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::UInt64)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::Float16)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::Float32)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::Float64)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::Int8)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::UInt8)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::Int16)
            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::UInt16)

            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_RESOURCE_BASE_SHAPE_MASK)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_RESOURCE_NONE)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_1D)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_2D)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_3D)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_CUBE)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_BUFFER)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_STRUCTURED_BUFFER)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_BYTE_ADDRESS_BUFFER)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_RESOURCE_UNKNOWN)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_ACCELERATION_STRUCTURE)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_SUBPASS)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_RESOURCE_EXT_SHAPE_MASK)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_FEEDBACK_FLAG)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_SHADOW_FLAG)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_ARRAY_FLAG)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_MULTISAMPLE_FLAG)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_1D_ARRAY)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_2D_ARRAY)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_CUBE_ARRAY)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_2D_MULTISAMPLE)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_2D_MULTISAMPLE_ARRAY)
            BIND_ENUM_CONSTANT(slang_SlangResourceShape::SLANG_TEXTURE_SUBPASS_MULTISAMPLE)

            BIND_ENUM_CONSTANT(slang_SlangResourceAccess::SLANG_RESOURCE_ACCESS_NONE)
            BIND_ENUM_CONSTANT(slang_SlangResourceAccess::SLANG_RESOURCE_ACCESS_READ)
            BIND_ENUM_CONSTANT(slang_SlangResourceAccess::SLANG_RESOURCE_ACCESS_READ_WRITE)
            BIND_ENUM_CONSTANT(slang_SlangResourceAccess::SLANG_RESOURCE_ACCESS_RASTER_ORDERED)
            BIND_ENUM_CONSTANT(slang_SlangResourceAccess::SLANG_RESOURCE_ACCESS_APPEND)
            BIND_ENUM_CONSTANT(slang_SlangResourceAccess::SLANG_RESOURCE_ACCESS_CONSUME)
            BIND_ENUM_CONSTANT(slang_SlangResourceAccess::SLANG_RESOURCE_ACCESS_WRITE)
            BIND_ENUM_CONSTANT(slang_SlangResourceAccess::SLANG_RESOURCE_ACCESS_FEEDBACK)
            BIND_ENUM_CONSTANT(slang_SlangResourceAccess::SLANG_RESOURCE_ACCESS_UNKNOWN)

            godot::ClassDB::bind_method(godot::D_METHOD("getKind"), &slang_TypeReflection::getKind);
            godot::ClassDB::bind_method(godot::D_METHOD("getFieldCount"), &slang_TypeReflection::getFieldCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getFieldByIndex", "index"), &slang_TypeReflection::getFieldByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("isArray"), &slang_TypeReflection::isArray);
            godot::ClassDB::bind_method(godot::D_METHOD("unwrapArray"), &slang_TypeReflection::unwrapArray);
            godot::ClassDB::bind_method(godot::D_METHOD("getElementCount"), &slang_TypeReflection::getElementCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getTotalArrayElementCount"), &slang_TypeReflection::getTotalArrayElementCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getElementType"), &slang_TypeReflection::getElementType);
            godot::ClassDB::bind_method(godot::D_METHOD("getRowCount"), &slang_TypeReflection::getRowCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getColumnCount"), &slang_TypeReflection::getColumnCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getScalarType"), &slang_TypeReflection::getScalarType);
            godot::ClassDB::bind_method(godot::D_METHOD("getResourceResultType"), &slang_TypeReflection::getResourceResultType);
            godot::ClassDB::bind_method(godot::D_METHOD("getResourceShape"), &slang_TypeReflection::getResourceShape);
            godot::ClassDB::bind_method(godot::D_METHOD("getResourceAccess"), &slang_TypeReflection::getResourceAccess);
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_TypeReflection::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getFullName", "outNameBlob"), &slang_TypeReflection::getFullName);
            godot::ClassDB::bind_method(godot::D_METHOD("getUserAttributeCount"), &slang_TypeReflection::getUserAttributeCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getUserAttributeByIndex", "index"), &slang_TypeReflection::getUserAttributeByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("findUserAttributeByName", "name"), &slang_TypeReflection::findUserAttributeByName);
            godot::ClassDB::bind_method(godot::D_METHOD("getGenericContainer"), &slang_TypeReflection::getGenericContainer);
        }

    public:
        Kind getKind(slang_NULL *null){
            return (Kind) this->value->getKind();
        }
        unsigned int getFieldCount() {
            return this->value->getFieldCount();
        }
        slang_VariableReflection_HEAP_PTR* getFieldByIndex(unsigned int index) {
            auto* a = memnew(slang_VariableReflection(this->value->getFieldByIndex(index)));
            auto* ptr = memnew(slang_VariableReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        bool isArray(){
            return this->value->isArray();
        }
        slang_TypeReflection_HEAP_PTR* unwrapArray(){
            auto* a = memnew(slang_TypeReflection(this->value->unwrapArray()));
            auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        size_t getElementCount(){
            return this->value->getElementCount();
        }
        size_t getTotalArrayElementCount(){
            return this->value->getTotalArrayElementCount();
        }
        slang_TypeReflection_HEAP_PTR* getElementType(){
            auto* a = memnew(slang_TypeReflection(this->value->getElementType()));
            auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        unsigned getRowCount(){
            return this->value->getRowCount();
        }
        unsigned getColumnCount()
        {
            return this->value->getColumnCount();
        }
        ScalarType getScalarType()
        {
            return (ScalarType)this->value->getScalarType();
        }
        slang_TypeReflection_HEAP_PTR* getResourceResultType()
        {
            auto* a = memnew(slang_TypeReflection(this->value->getResourceResultType()));
            auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_SlangResourceShape getResourceShape(){
            return static_cast<slang_SlangResourceShape>(this->value->getResourceShape());
        }
        slang_SlangResourceAccess getResourceAccess(){
            return static_cast<slang_SlangResourceAccess>(this->value->getResourceAccess());
        }
        godot::String getName(){
            auto a =this->value->getName();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        SlangResult getFullName(slang_IBlob* outNameBlob){
            return this->value->getFullName(&outNameBlob->value);
        }
        unsigned int getUserAttributeCount(){
            return this->value->getUserAttributeCount();
        }
        slang_UserAttribute_HEAP_PTR* getUserAttributeByIndex(unsigned int index){
            auto* a = memnew(slang_UserAttribute(this->value->getUserAttributeByIndex(index)));
            auto* ptr = memnew(slang_UserAttribute_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_UserAttribute_HEAP_PTR* findUserAttributeByName(godot::String name){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto* a = memnew(slang_UserAttribute(this->value->findUserAttributeByName(name.utf8().get_data())));
            auto* ptr = memnew(slang_UserAttribute_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_SlangReflectionGeneric* getGenericContainer(){
            this->value->getGenericContainer();
            return nullptr;
        }
    };


    MAKE_VALUE_TEMPLATE(TypeReflection)


    class slang_SlangReflectionGeneric : public slang_SlangObject{
    GDCLASS(slang_SlangReflectionGeneric, slang_SlangObject)
    private:
        static void _bind_methods() {}

    public:
    };


    class slang_TypeLayoutReflection : public slang_SlangObject{
    GDCLASS(slang_TypeLayoutReflection, slang_SlangObject)
    public:
        slang::TypeLayoutReflection* value;
        bool heap = 1;
        slang_TypeLayoutReflection():value(memnew(slang::TypeLayoutReflection())){}
        slang_TypeLayoutReflection(slang::TypeLayoutReflection* refl): value(refl),heap(0){};
        void operator= (slang::TypeLayoutReflection* refl){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            this->value = refl;
        }
        operator slang::TypeLayoutReflection*(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang::TypeLayoutReflection duplicate(){
            return *value;
        }
        ~slang_TypeLayoutReflection(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_TypeLayoutReflection::has_value);
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_NONE)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_MIXED)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_CONSTANT_BUFFER)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_SHADER_RESOURCE)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_UNORDERED_ACCESS)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_VARYING_INPUT)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_VARYING_OUTPUT)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_SAMPLER_STATE)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_UNIFORM)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_DESCRIPTOR_TABLE_SLOT)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_SPECIALIZATION_CONSTANT)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_PUSH_CONSTANT_BUFFER)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_REGISTER_SPACE)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_GENERIC)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_RAY_PAYLOAD)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_HIT_ATTRIBUTES)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_CALLABLE_PAYLOAD)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_SHADER_RECORD)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_EXISTENTIAL_TYPE_PARAM)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_EXISTENTIAL_OBJECT_PARAM)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_SUB_ELEMENT_REGISTER_SPACE)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_SUBPASS)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_METAL_TEXTURE)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_METAL_SAMPLER)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_METAL_BUFFER)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_METAL_ARGUMENT_BUFFER_ELEMENT)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_METAL_ATTRIBUTE)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_METAL_PAYLOAD)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_COUNT)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_COUNT_V1)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_VERTEX_INPUT)
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_FRAGMENT_OUTPUT)

            godot::ClassDB::bind_method(godot::D_METHOD("getType"), &slang_TypeLayoutReflection::getType);
            godot::ClassDB::bind_method(godot::D_METHOD("getKind"), &slang_TypeLayoutReflection::getKind);
            godot::ClassDB::bind_method(godot::D_METHOD("getSize", "category"), &slang_TypeLayoutReflection::getSize);
            godot::ClassDB::bind_method(godot::D_METHOD("getStride", "category"), &slang_TypeLayoutReflection::getStride);
            godot::ClassDB::bind_method(godot::D_METHOD("getAlignment", "category"), &slang_TypeLayoutReflection::getAlignment);
            godot::ClassDB::bind_method(godot::D_METHOD("getFieldCount"), &slang_TypeLayoutReflection::getFieldCount);
        }

    public:
        slang_TypeReflection_HEAP_PTR* getType(){
            auto* a = memnew(slang_TypeReflection(this->value->getType()));
            auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_TypeReflection::Kind getKind() {
            return (slang_TypeReflection::Kind) this->value->getKind();
        }
        size_t getSize(slang_SlangParameterCategory category = SLANG_PARAMETER_CATEGORY_UNIFORM) {
            return this->value->getSize(static_cast<SlangParameterCategory>(category));
        }
        size_t getStride(slang_SlangParameterCategory category = SLANG_PARAMETER_CATEGORY_UNIFORM) {
            return this->value->getStride(static_cast<SlangParameterCategory>(category));
        }
        int32_t getAlignment(slang_SlangParameterCategory category = SLANG_PARAMETER_CATEGORY_UNIFORM) {
            return this->value->getAlignment(static_cast<SlangParameterCategory>(category));
        }
        unsigned int getFieldCount() {
            return this->value->getFieldCount();
        }

    };


    MAKE_VALUE_TEMPLATE(TypeLayoutReflection)



    class slang_TypeParameterReflection : public  slang_SlangObject{
    GDCLASS(slang_TypeParameterReflection, slang_SlangObject)
    public:
        slang::TypeParameterReflection* value;
        bool heap = 1;
        slang_TypeParameterReflection():value(memnew(slang::TypeParameterReflection())){}
        slang_TypeParameterReflection(slang::TypeParameterReflection* refl):value(refl),heap(0){}
        void operator=(slang::TypeParameterReflection* refl){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = refl;
        }
        operator slang::TypeParameterReflection*(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang::TypeParameterReflection duplicate(){
            return *value;
        }
        ~slang_TypeParameterReflection(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_TypeParameterReflection::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_TypeParameterReflection::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getIndex"), &slang_TypeParameterReflection::getIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("getConstraintCount"), &slang_TypeParameterReflection::getConstraintCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getConstraintByIndex", "index"), &slang_TypeParameterReflection::getConstraintByIndex);
        }
    public:
        godot::String getName() {
            auto a = this->value->getName();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        unsigned getIndex() {
            return this->value->getIndex();
        }
        unsigned getConstraintCount(){
            return this->value->getConstraintCount();
        }
        slang_TypeReflection_HEAP_PTR* getConstraintByIndex(unsigned index){
            auto* a = memnew(slang_TypeReflection(this->value->getConstraintByIndex(index)));
            auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
    };


    MAKE_VALUE_TEMPLATE(TypeParameterReflection)


    class slang_EntryPointReflection : public  slang_SlangObject{
    GDCLASS(slang_EntryPointReflection, slang_SlangObject)
    public:
        slang::EntryPointReflection* value;
        bool heap = 1;
        slang_EntryPointReflection():value(memnew(slang::EntryPointReflection())){}
        slang_EntryPointReflection(slang::EntryPointReflection* refl):value(refl),heap(0){}
        void operator=(slang::EntryPointReflection* refl){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = refl;
        }
        operator slang::EntryPointReflection*(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang::EntryPointReflection duplicate(){
            return *value;
        }
        ~slang_EntryPointReflection(){

            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_EntryPointReflection::has_value);
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_NONE)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_VERTEX)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_HULL)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_DOMAIN)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_GEOMETRY)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_FRAGMENT)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_COMPUTE)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_RAY_GENERATION)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_INTERSECTION)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_ANY_HIT)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_CLOSEST_HIT)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_MISS)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_CALLABLE)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_MESH)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_AMPLIFICATION)
            BIND_ENUM_CONSTANT(slang_SlangStage::SLANG_STAGE_PIXEL)

            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_EntryPointReflection::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getNameOverride"), &slang_EntryPointReflection::getNameOverride);
            godot::ClassDB::bind_method(godot::D_METHOD("getParameterCount"), &slang_EntryPointReflection::getParameterCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getParameterByIndex", "index"), &slang_EntryPointReflection::getParameterByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("getStage"), &slang_EntryPointReflection::getStage);
            godot::ClassDB::bind_method(godot::D_METHOD("getComputeThreadGroupSize", "axisCount"), &slang_EntryPointReflection::getComputeThreadGroupSize);
            godot::ClassDB::bind_method(godot::D_METHOD("getComputeWaveSize", "outWaveSize"), &slang_EntryPointReflection::getComputeWaveSize);
            godot::ClassDB::bind_method(godot::D_METHOD("usesAnySampleRateInput"), &slang_EntryPointReflection::usesAnySampleRateInput);
            godot::ClassDB::bind_method(godot::D_METHOD("getVarLayout"), &slang_EntryPointReflection::getVarLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("getTypeLayout"), &slang_EntryPointReflection::getTypeLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("getResultVarLayout"), &slang_EntryPointReflection::getResultVarLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("hasDefaultConstantBuffer"), &slang_EntryPointReflection::hasDefaultConstantBuffer);
        }

    public:
        godot::String getName() {
            auto a = this->value->getName();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        godot::String getNameOverride(){
            auto a = this->value->getNameOverride();
            if(a == 0)
                return "";
            return godot::String::utf8(a);
        }
        unsigned getParameterCount() {
            return this->value->getParameterCount();
        }
        slang_FunctionReflection_HEAP_PTR* getFunction() {
            auto* a = memnew(slang_FunctionReflection(this->value->getFunction()));
            auto* ptr = memnew(slang_FunctionReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_VariableLayoutReflection_HEAP_PTR* getParameterByIndex(unsigned index){
            auto* a = memnew(slang_VariableLayoutReflection(this->value->getParameterByIndex(index)));
            auto* ptr = memnew(slang_VariableLayoutReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_SlangStage getStage() {
            return (slang_SlangStage) this->value->getStage();
        }
        godot::TypedArray<SlangUInt> getComputeThreadGroupSize(SlangUInt axisCount) {
            SlangUInt sizeAlongAxis[3] = {0,0,0};
            this->value->getComputeThreadGroupSize(axisCount, sizeAlongAxis);
            godot::TypedArray<SlangUInt> outSizeAlongAxis;
            outSizeAlongAxis.resize(3);
            outSizeAlongAxis[0] = sizeAlongAxis[0];
            outSizeAlongAxis[1] = sizeAlongAxis[1];
            outSizeAlongAxis[2] = sizeAlongAxis[2];
            return outSizeAlongAxis;
        }
        void getComputeWaveSize(slang_SIZE* outWaveSize){
            SlangUInt waveSize = 0;
            this->value->getComputeWaveSize(&waveSize);
            outWaveSize->set_value(waveSize);
        }
        bool usesAnySampleRateInput(){
            return this->value->usesAnySampleRateInput();
        }
        slang_VariableLayoutReflection_HEAP_PTR* getVarLayout(){
            auto* a = memnew(slang_VariableLayoutReflection(this->value->getVarLayout()));
            auto* ptr = memnew(slang_VariableLayoutReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_TypeLayoutReflection_HEAP_PTR* getTypeLayout(){
            auto* a = memnew(slang_TypeLayoutReflection(this->value->getTypeLayout()));
            auto* ptr = memnew(slang_TypeLayoutReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_VariableLayoutReflection_HEAP_PTR* getResultVarLayout(){
            auto* a = memnew(slang_VariableLayoutReflection(this->value->getResultVarLayout()));
            auto* ptr = memnew(slang_VariableLayoutReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        bool hasDefaultConstantBuffer(){
            return this->value->hasDefaultConstantBuffer();
        }
    };


    MAKE_VALUE_TEMPLATE(EntryPointReflection)


    class slang_ShaderReflection : public slang_SlangObject{
    GDCLASS(slang_ShaderReflection, slang_SlangObject)
    public:
        slang::ShaderReflection* value = nullptr;
        bool heap = 1;
        slang_ShaderReflection():value(memnew(slang::ShaderReflection())){}
        slang_ShaderReflection(slang::ShaderReflection* refl):value(refl),heap(0){}
        void operator=(slang::ShaderReflection* refl){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = refl;
        }
        bool has_value(){
            return value;
        }
        operator slang::ShaderReflection*(){
            return value;
        }
        slang::ShaderReflection duplicate(){
            return *value;
        }
        ~slang_ShaderReflection(){
            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_ShaderReflection::has_value);
            godot::ClassDB::bind_method(godot::D_METHOD("getParameterCount"), &slang_ShaderReflection::getParameterCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getTypeParameterCount"), &slang_ShaderReflection::getTypeParameterCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getSession"), &slang_ShaderReflection::getSession);
            godot::ClassDB::bind_method(godot::D_METHOD("getTypeParameterByIndex", "index"), &slang_ShaderReflection::getTypeParameterByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("findTypeParameter", "name"), &slang_ShaderReflection::findTypeParameter);
            godot::ClassDB::bind_method(godot::D_METHOD("getParameterByIndex", "index"), &slang_ShaderReflection::getParameterByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("get", "request"), &slang_ShaderReflection::get);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointCount"), &slang_ShaderReflection::getEntryPointCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointIndex", "index"), &slang_ShaderReflection::getEntryPointIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("getGlobalConstantBufferBinding"), &slang_ShaderReflection::getGlobalConstantBufferBinding);
            godot::ClassDB::bind_method(godot::D_METHOD("getGlobalConstantBufferSize"), &slang_ShaderReflection::getGlobalConstantBufferSize);
            godot::ClassDB::bind_method(godot::D_METHOD("findTypeByName", "name"), &slang_ShaderReflection::findTypeByName);
            godot::ClassDB::bind_method(godot::D_METHOD("findFunctionByName", "name"), &slang_ShaderReflection::findFunctionByName);
            godot::ClassDB::bind_method(godot::D_METHOD("findFunctionByNameInType", "type", "name"), &slang_ShaderReflection::findFunctionByNameInType);
            godot::ClassDB::bind_method(godot::D_METHOD("findVarByNameInType", "type", "name"), &slang_ShaderReflection::findVarByNameInType);
            godot::ClassDB::bind_method(godot::D_METHOD("getTypeLayout", "type", "rules"), &slang_ShaderReflection::getTypeLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("findEntryPointByName", "name"), &slang_ShaderReflection::findEntryPointByName);
            godot::ClassDB::bind_method(godot::D_METHOD("specializeType", "type", "specializationArgCount", "specializationArgs", "outDiagnostics"), &slang_ShaderReflection::specializeType);
            godot::ClassDB::bind_method(godot::D_METHOD("getHashedStringCount"), &slang_ShaderReflection::getHashedStringCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getHashedString", "index","outCount"), &slang_ShaderReflection::getHashedString);
            godot::ClassDB::bind_method(godot::D_METHOD("getGlobalParamsTypeLayout"), &slang_ShaderReflection::getGlobalParamsTypeLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("getGlobalParamsVarLayout"), &slang_ShaderReflection::getGlobalParamsVarLayout);
        }
    public:
        unsigned getParameterCount(){
            return this->value->getParameterCount();
        }
        unsigned getTypeParameterCount() {
            return this->value->getTypeParameterCount();
        }
        slang_ISession_HEAP_PTR* getSession() {
            auto* a = memnew(slang_ISession(this->value->getSession()));
            auto* ptr = memnew(slang_ISession_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_TypeParameterReflection_HEAP_PTR* getTypeParameterByIndex(unsigned index) {
            auto* a = memnew(slang_TypeParameterReflection(this->value->getTypeParameterByIndex(index)));
            auto* ptr = memnew(slang_TypeParameterReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_TypeParameterReflection_HEAP_PTR* findTypeParameter(godot::String name) {
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto* a = memnew(slang_TypeParameterReflection(this->value->findTypeParameter(name.utf8().get_data())));
            auto* ptr = memnew(slang_TypeParameterReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_VariableLayoutReflection_HEAP_PTR* getParameterByIndex(unsigned index){
            auto* a = memnew(slang_VariableLayoutReflection(this->value->getParameterByIndex(index)));
            auto* ptr = memnew(slang_VariableLayoutReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_ShaderReflection_HEAP_PTR* get(slang_ICompileRequest* request){
            auto* a = memnew(slang_ShaderReflection(this->value->get(request->value)));
            auto* ptr = memnew(slang_ShaderReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        SlangUInt getEntryPointCount() {
            return this->value->getEntryPointCount();
        }
        slang_EntryPointReflection_HEAP_PTR* getEntryPointIndex(SlangUInt index) {
            auto* a = memnew(slang_EntryPointReflection(this->value->getEntryPointByIndex(index)));
            auto* ptr = memnew(slang_EntryPointReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        SlangUInt getGlobalConstantBufferBinding(){
            return this->value->getGlobalConstantBufferBinding();
        }
        size_t getGlobalConstantBufferSize(){
            return this->value->getGlobalConstantBufferSize();
        }
        slang_TypeReflection_HEAP_PTR* findTypeByName(godot::String name){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto* a = memnew(slang_TypeReflection(this->value->findTypeByName(name.utf8().get_data())));
            auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_FunctionReflection_HEAP_PTR* findFunctionByName(godot::String name) {
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto* a = memnew(slang_FunctionReflection(this->value->findFunctionByName(name.utf8().get_data())));
            auto* ptr = memnew(slang_FunctionReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_FunctionReflection_HEAP_PTR* findFunctionByNameInType(slang_TypeReflection* type, godot::String name) {
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto* a = memnew(slang_FunctionReflection(this->value->findFunctionByNameInType(
                    type->value, name.utf8().get_data())));
            auto* ptr = memnew(slang_FunctionReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_VariableReflection_HEAP_PTR* findVarByNameInType(slang_TypeReflection* type, godot::String name){
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto* a = memnew(slang_VariableReflection(this->value->findVarByNameInType(
                    type->value, name.utf8().get_data())));
            auto* ptr = memnew(slang_VariableReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_TypeLayoutReflection_HEAP_PTR* getTypeLayout(slang_TypeReflection* type,slang_LayoutRules rules = slang_LayoutRules::Default){
            auto* a = memnew(slang_TypeLayoutReflection(this->value->getTypeLayout(
                    type->value,
                    static_cast<slang::LayoutRules>(rules))));
            auto* ptr = memnew(slang_TypeLayoutReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_EntryPointReflection_HEAP_PTR* findEntryPointByName(godot::String name) {
            name = godot::ProjectSettings::get_singleton()->globalize_path(name);
            auto* a = memnew(slang_EntryPointReflection(this->value->findEntryPointByName(name.utf8().get_data())));
            auto* ptr = memnew(slang_EntryPointReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_TypeReflection_HEAP_PTR* specializeType(slang_TypeReflection* type, SlangInt specializationArgCount, slang_TypeReflection_VECTOR* specializationArgs,slang_IBlob* outDiagnostics){
            size_t size = specializationArgs->size();
            slang::TypeReflection** refs = new slang::TypeReflection*[size];

            for(int i = 0;i!=size;++i){
                refs[i] = specializationArgs->at(i)->value;
            }

            auto* a = memnew(slang_TypeReflection(this->value->specializeType(
                    type->value, specializationArgCount,
                    refs,
                    &outDiagnostics->value)));
            auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            delete[] refs;
            return ptr;
        }
        SlangUInt getHashedStringCount(){
            return this->value->getHashedStringCount();
        }
        godot::String getHashedString(SlangUInt index,slang_SIZE* outCount){
            size_t count = 0;
            auto str = this->value->getHashedString(index, &count);
            outCount->set_value(count);
            if(str == 0)
                return "";
            return godot::String::utf8(str);
        }
        slang_TypeLayoutReflection_HEAP_PTR* getGlobalParamsTypeLayout(){
            auto* a = memnew(slang_TypeLayoutReflection(this->value->getGlobalParamsTypeLayout()));
            auto* ptr = memnew(slang_TypeLayoutReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        slang_VariableLayoutReflection_HEAP_PTR* getGlobalParamsVarLayout(){
            auto* a = memnew(slang_VariableLayoutReflection(this->value->getGlobalParamsVarLayout()));
            auto* ptr = memnew(slang_VariableLayoutReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
    };


    MAKE_VALUE_TEMPLATE(ShaderReflection)

}
VARIANT_ENUM_CAST(slang_cpp::slang_DeclReflection::Kind)
VARIANT_ENUM_CAST(slang_cpp::slang_TypeReflection::Kind)
VARIANT_ENUM_CAST(slang_cpp::slang_TypeReflection::ScalarType)
namespace slang_cpp {
    class slang_SpecializationArg : public slang_SlangObject{
    GDCLASS(slang_SpecializationArg, slang_SlangObject)
    public:
        slang::SpecializationArg* value = nullptr;
        bool heap = 1;
        slang_SpecializationArg():value(memnew(slang::SpecializationArg())){}
        slang_SpecializationArg(slang::SpecializationArg* arg): value(arg),heap(0){}
        void operator=(slang::SpecializationArg* arg){
            if(heap){
                memdelete(value);
                heap = 0;
            }
            value = arg;
        }
        operator slang::SpecializationArg*(){
            return value;
        }
        bool has_value(){
            return value;
        }
        slang::SpecializationArg duplicate(){
            return *value;
        }
        ~slang_SpecializationArg(){
            if(heap){
                memdelete(value);
                heap = 0;
            }
        }
    public:
        enum Kind : int32_t
        {
            Unknown,    /**< An invalid specialization argument. */
            Type,       /**< Specialize to a type. */
        };
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("has_value"),&slang_SpecializationArg::has_value);
            BIND_ENUM_CONSTANT(Unknown)
            BIND_ENUM_CONSTANT(Type)

            godot::ClassDB::bind_method(godot::D_METHOD("getType"), &slang_SpecializationArg::getType);
            godot::ClassDB::bind_method(godot::D_METHOD("setType", "type"), &slang_SpecializationArg::setType);
        }

    public:
        slang_TypeReflection_HEAP_PTR* getType(){
            auto* a = memnew(slang_TypeReflection(this->value->type));
            auto* ptr = memnew(slang_TypeReflection_HEAP_PTR(a));
            ptr->set_shouldFreeData(true);
            return ptr;
        }
        void setType(slang_TypeReflection* type) {
            this->value->type = type->value;
        }
        static slang_SpecializationArg fromType(slang_TypeReflection* inType){
            slang_SpecializationArg arg;
            arg.value->kind = static_cast<slang::SpecializationArg::Kind>(Kind::Type);
            arg.value->type = inType->value;
            return arg;
        }
    };


    MAKE_VALUE_TEMPLATE(SpecializationArg)



    class slang_global : public slang_SlangObject{
    GDCLASS(slang_global,slang_SlangObject)
        static void _bind_methods() {
            godot::ClassDB::bind_static_method("slang_global",godot::D_METHOD("createGlobalSession", "outGlobalSession"), &slang_global::createGlobalSession);
            godot::ClassDB::bind_static_method("slang_global",godot::D_METHOD("IComponentType_shiftToComponent", "ptr"), &slang_global::shiftToComponent<slang_IComponentType>);
            godot::ClassDB::bind_static_method("slang_global",godot::D_METHOD("ITypeConformance_shiftToComponent", "ptr"), &slang_global::shiftToComponent<slang_ITypeConformance>);
            godot::ClassDB::bind_static_method("slang_global",godot::D_METHOD("IEntryPoint_shiftToComponent", "ptr"), &slang_global::shiftToComponent<slang_IEntryPoint>);
            godot::ClassDB::bind_static_method("slang_global",godot::D_METHOD("IModule_shiftToComponent", "ptr"), &slang_global::shiftToComponent<slang_IModule>);
        }
    public:
        static SlangResult createGlobalSession(slang_IGlobalSession* outGlobalSession){
            return slang::createGlobalSession(&outGlobalSession->value);
        }
        template<typename T>
        static slang_IComponentType_HEAP_PTR* shiftToComponent(T* ptr){
            auto* a = memnew(slang_IComponentType(static_cast<slang::IComponentType *>(ptr->value)));
            auto* mptr = memnew(slang_IComponentType_HEAP_PTR(a));
            mptr->set_shouldFreeData(true);
            return mptr;
        }
    };

}
VARIANT_ENUM_CAST(slang_cpp::slang_SpecializationArg::Kind)
#endif