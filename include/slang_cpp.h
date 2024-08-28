#ifndef SLANG_CPP
#define SLANG_CPP
#include<functional>
#include <slang/include/slang.h>
#include <slang/source/core/slang-common.h>
#include <slang/source/core/slang-file-system.h>
#include <slang/source/core/slang-shared-library.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/dictionary.hpp>
namespace slang_cpp{
    enum slang_CompilerOptionValueKind{
        Int,String
    };
    enum slang_CompilerOptionName{
        MacroDefine,        // stringValue0: macro name;  stringValue1: macro value
        DepFile,
        EntryPointName,
        Specialize,
        Help,
        HelpStyle,
        Include,            // stringValue: additional include path.
        Language,
        MatrixLayoutColumn, // bool
        MatrixLayoutRow,    // bool
        ZeroInitialize,     // bool
        IgnoreCapabilities, // bool
        RestrictiveCapabilityCheck, // bool
        ModuleName,         // stringValue0: module name.
        Output,
        Profile,            // intValue0: profile
        Stage,              // intValue0: stage
        Target,             // intValue0: CodeGenTarget
        Version,
        WarningsAsErrors,   // stringValue0: "all" or comma separated list of warning codes or names.
        DisableWarnings,    // stringValue0: comma separated list of warning codes or names.
        EnableWarning,      // stringValue0: warning code or name.
        DisableWarning,     // stringValue0: warning code or name.
        DumpWarningDiagnostics,
        InputFilesRemain,
        EmitIr,                // bool
        ReportDownstreamTime,  // bool
        ReportPerfBenchmark,   // bool
        SkipSPIRVValidation,   // bool
        SourceEmbedStyle,
        SourceEmbedName,
        SourceEmbedLanguage,
        DisableShortCircuit,   // bool
        MinimumSlangOptimization, // bool
        DisableNonEssentialValidations, // bool
        DisableSourceMap,       // bool
        UnscopedEnum,           // bool
        PreserveParameters,       // bool: preserve all resource parameters in the output code.

        // Target

        Capability,                 // intValue0: CapabilityName
        DefaultImageFormatUnknown,  // bool
        DisableDynamicDispatch,     // bool
        DisableSpecialization,      // bool
        FloatingPointMode,          // intValue0: FloatingPointMode
        DebugInformation,           // intValue0: DebugInfoLevel
        LineDirectiveMode,
        Optimization,               // intValue0: OptimizationLevel
        Obfuscate,                  // bool

        VulkanBindShift,            // intValue0 (higher 8 bits): kind; intValue0(lower bits): set; intValue1: shift
        VulkanBindGlobals,          // intValue0: index; intValue1: set
        VulkanInvertY,              // bool
        VulkanUseDxPositionW,       // bool
        VulkanUseEntryPointName,    // bool
        VulkanUseGLLayout,          // bool
        VulkanEmitReflection,       // bool

        GLSLForceScalarLayout,      // bool
        EnableEffectAnnotations,    // bool

        EmitSpirvViaGLSL,           // bool
        EmitSpirvDirectly,          // bool
        SPIRVCoreGrammarJSON,       // stringValue0: json path
        IncompleteLibrary,          // bool, when set, will not issue an error when the linked program has unresolved extern function symbols.

        // Downstream

        CompilerPath,
        DefaultDownstreamCompiler,
        DownstreamArgs,             // stringValue0: downstream compiler name. stringValue1: argument list, one per line.
        PassThrough,

        // Repro

        DumpRepro,
        DumpReproOnError,
        ExtractRepro,
        LoadRepro,
        LoadReproDirectory,
        ReproFallbackDirectory,

        // Debugging

        DumpAst,
        DumpIntermediatePrefix,
        DumpIntermediates,      // bool
        DumpIr,                 // bool
        DumpIrIds,
        PreprocessorOutput,
        OutputIncludes,
        ReproFileSystem,
        SerialIr,               // bool
        SkipCodeGen,            // bool
        ValidateIr,             // bool
        VerbosePaths,
        VerifyDebugSerialIr,
        NoCodeGen,              // Not used.

        // Experimental

        FileSystem,
        Heterogeneous,
        NoMangle,
        NoHLSLBinding,
        NoHLSLPackConstantBufferElements,
        ValidateUniformity,
        AllowGLSL,
        EnableExperimentalPasses,

        // Internal

        ArchiveType,
        CompileStdLib,
        Doc,
        IrCompression,
        LoadStdLib,
        ReferenceModule,
        SaveStdLib,
        SaveStdLibBinSource,
        TrackLiveness,
        LoopInversion,              // bool, enable loop inversion optimization

        // Deprecated
        ParameterBlocksUseRegisterSpaces,

        CountOfParsableOptions,

        // Used in parsed options only.
        DebugInformationFormat,     // intValue0: DebugInfoFormat
        VulkanBindShiftAll,         // intValue0: kind; intValue1: shift
        GenerateWholeProgram,       // bool
        UseUpToDateBinaryModule,    // bool, when set, will only load
        // precompiled modules if it is up-to-date with its source.

        EmbedDXIL,                  // bool
        CountOf,
    };
    enum slang_SlangCompileTarget : SlangCompileTargetIntegral
    {
        SLANG_TARGET_UNKNOWN,
        SLANG_TARGET_NONE,
        SLANG_GLSL,
        SLANG_GLSL_VULKAN_DEPRECATED,              //< deprecated and removed: just use `SLANG_GLSL`.
        SLANG_GLSL_VULKAN_ONE_DESC_DEPRECATED,     //< deprecated and removed.
        SLANG_HLSL,
        SLANG_SPIRV,
        SLANG_SPIRV_ASM,
        SLANG_DXBC,
        SLANG_DXBC_ASM,
        SLANG_DXIL,
        SLANG_DXIL_ASM,
        SLANG_C_SOURCE,                 ///< The C language
        SLANG_CPP_SOURCE,               ///< C++ code for shader kernels.
        SLANG_HOST_EXECUTABLE,          ///< Standalone binary executable (for hosting CPU/OS)
        SLANG_SHADER_SHARED_LIBRARY,    ///< A shared library/Dll for shader kernels (for hosting CPU/OS)
        SLANG_SHADER_HOST_CALLABLE,     ///< A CPU target that makes the compiled shader code available to be run immediately
        SLANG_CUDA_SOURCE,              ///< Cuda source
        SLANG_PTX,                      ///< PTX
        SLANG_CUDA_OBJECT_CODE,         ///< Object code that contains CUDA functions.
        SLANG_OBJECT_CODE,              ///< Object code that can be used for later linking
        SLANG_HOST_CPP_SOURCE,          ///< C++ code for host library or executable.
        SLANG_HOST_HOST_CALLABLE,       ///< Host callable host code (ie non kernel/shader)
        SLANG_CPP_PYTORCH_BINDING,      ///< C++ PyTorch binding code.
        SLANG_METAL,                    ///< Metal shading language
        SLANG_METAL_LIB,                ///< Metal library
        SLANG_METAL_LIB_ASM,            ///< Metal library assembly
        SLANG_HOST_SHARED_LIBRARY,      ///< A shared library/Dll for host code (for hosting CPU/OS)
        SLANG_TARGET_COUNT_OF,
    };
    enum slang_SlangProfileID : SlangProfileIDIntegral
    {
        SLANG_PROFILE_UNKNOWN,
    };
    enum slang_SlangFloatingPointMode : SlangFloatingPointModeIntegral
    {
        SLANG_FLOATING_POINT_MODE_DEFAULT = 0,
        SLANG_FLOATING_POINT_MODE_FAST,
        SLANG_FLOATING_POINT_MODE_PRECISE,
    };
    enum slang_SlangLineDirectiveMode : SlangLineDirectiveModeIntegral
    {
        SLANG_LINE_DIRECTIVE_MODE_DEFAULT = 0,  /**< Default behavior: pick behavior base on target. */
        SLANG_LINE_DIRECTIVE_MODE_NONE,         /**< Don't emit line directives at all. */
        SLANG_LINE_DIRECTIVE_MODE_STANDARD,     /**< Emit standard C-style `#line` directives. */
        SLANG_LINE_DIRECTIVE_MODE_GLSL,         /**< Emit GLSL-style directives with file *number* instead of name */
        SLANG_LINE_DIRECTIVE_MODE_SOURCE_MAP,   /**< Use a source map to track line mappings (ie no #line will appear in emitting source) */
    };
    enum slang_SlangMatrixLayoutMode : SlangMatrixLayoutModeIntegral
    {
        SLANG_MATRIX_LAYOUT_MODE_UNKNOWN = 0,
        SLANG_MATRIX_LAYOUT_ROW_MAJOR,
        SLANG_MATRIX_LAYOUT_COLUMN_MAJOR,
    };
    enum slang_SlangPassThrough : SlangPassThroughIntegral
    {
        SLANG_PASS_THROUGH_NONE,
        SLANG_PASS_THROUGH_FXC,
        SLANG_PASS_THROUGH_DXC,
        SLANG_PASS_THROUGH_GLSLANG,
        SLANG_PASS_THROUGH_SPIRV_DIS,
        SLANG_PASS_THROUGH_CLANG,                   ///< Clang C/C++ compiler
        SLANG_PASS_THROUGH_VISUAL_STUDIO,           ///< Visual studio C/C++ compiler
        SLANG_PASS_THROUGH_GCC,                     ///< GCC C/C++ compiler
        SLANG_PASS_THROUGH_GENERIC_C_CPP,           ///< Generic C or C++ compiler, which is decided by the source type
        SLANG_PASS_THROUGH_NVRTC,                   ///< NVRTC Cuda compiler
        SLANG_PASS_THROUGH_LLVM,                    ///< LLVM 'compiler' - includes LLVM and Clang
        SLANG_PASS_THROUGH_SPIRV_OPT,               ///< SPIRV-opt
        SLANG_PASS_THROUGH_METAL,                   ///< Metal compiler
        SLANG_PASS_THROUGH_COUNT_OF,
    };
    enum slang_SlangCapabilityID : SlangCapabilityIDIntegral
    {
        SLANG_CAPABILITY_UNKNOWN = 0,
    };
    enum slang_SlangResourceShape : SlangResourceShapeIntegral
    {
        SLANG_RESOURCE_BASE_SHAPE_MASK      = 0x0F,

        SLANG_RESOURCE_NONE                 = 0x00,

        SLANG_TEXTURE_1D                    = 0x01,
        SLANG_TEXTURE_2D                    = 0x02,
        SLANG_TEXTURE_3D                    = 0x03,
        SLANG_TEXTURE_CUBE                  = 0x04,
        SLANG_TEXTURE_BUFFER                = 0x05,

        SLANG_STRUCTURED_BUFFER             = 0x06,
        SLANG_BYTE_ADDRESS_BUFFER           = 0x07,
        SLANG_RESOURCE_UNKNOWN              = 0x08,
        SLANG_ACCELERATION_STRUCTURE        = 0x09,
        SLANG_TEXTURE_SUBPASS               = 0x0A,

        SLANG_RESOURCE_EXT_SHAPE_MASK       = 0xF0,

        SLANG_TEXTURE_FEEDBACK_FLAG         = 0x10,
        SLANG_TEXTURE_SHADOW_FLAG           = 0x20,
        SLANG_TEXTURE_ARRAY_FLAG            = 0x40,
        SLANG_TEXTURE_MULTISAMPLE_FLAG      = 0x80,

        SLANG_TEXTURE_1D_ARRAY              = SLANG_TEXTURE_1D   | SLANG_TEXTURE_ARRAY_FLAG,
        SLANG_TEXTURE_2D_ARRAY              = SLANG_TEXTURE_2D   | SLANG_TEXTURE_ARRAY_FLAG,
        SLANG_TEXTURE_CUBE_ARRAY            = SLANG_TEXTURE_CUBE | SLANG_TEXTURE_ARRAY_FLAG,

        SLANG_TEXTURE_2D_MULTISAMPLE        = SLANG_TEXTURE_2D | SLANG_TEXTURE_MULTISAMPLE_FLAG,
        SLANG_TEXTURE_2D_MULTISAMPLE_ARRAY  = SLANG_TEXTURE_2D | SLANG_TEXTURE_MULTISAMPLE_FLAG | SLANG_TEXTURE_ARRAY_FLAG,
        SLANG_TEXTURE_SUBPASS_MULTISAMPLE   = SLANG_TEXTURE_SUBPASS | SLANG_TEXTURE_MULTISAMPLE_FLAG,
    };
    enum slang_SlangResourceAccess : SlangResourceAccessIntegral
    {
        SLANG_RESOURCE_ACCESS_NONE,
        SLANG_RESOURCE_ACCESS_READ,
        SLANG_RESOURCE_ACCESS_READ_WRITE,
        SLANG_RESOURCE_ACCESS_RASTER_ORDERED,
        SLANG_RESOURCE_ACCESS_APPEND,
        SLANG_RESOURCE_ACCESS_CONSUME,
        SLANG_RESOURCE_ACCESS_WRITE,
        SLANG_RESOURCE_ACCESS_FEEDBACK,
        SLANG_RESOURCE_ACCESS_UNKNOWN = 0x7FFFFFFF,
    };
    enum slang_SlangParameterCategory : SlangParameterCategoryIntegral
    {
        SLANG_PARAMETER_CATEGORY_NONE,
        SLANG_PARAMETER_CATEGORY_MIXED,
        SLANG_PARAMETER_CATEGORY_CONSTANT_BUFFER,
        SLANG_PARAMETER_CATEGORY_SHADER_RESOURCE,
        SLANG_PARAMETER_CATEGORY_UNORDERED_ACCESS,
        SLANG_PARAMETER_CATEGORY_VARYING_INPUT,
        SLANG_PARAMETER_CATEGORY_VARYING_OUTPUT,
        SLANG_PARAMETER_CATEGORY_SAMPLER_STATE,
        SLANG_PARAMETER_CATEGORY_UNIFORM,
        SLANG_PARAMETER_CATEGORY_DESCRIPTOR_TABLE_SLOT,
        SLANG_PARAMETER_CATEGORY_SPECIALIZATION_CONSTANT,
        SLANG_PARAMETER_CATEGORY_PUSH_CONSTANT_BUFFER,

        // HLSL register `space`, Vulkan GLSL `set`
        SLANG_PARAMETER_CATEGORY_REGISTER_SPACE,

        // TODO: Ellie, Both APIs treat mesh outputs as more or less varying output,
        // Does it deserve to be represented here??

        // A parameter whose type is to be specialized by a global generic type argument
        SLANG_PARAMETER_CATEGORY_GENERIC,

        SLANG_PARAMETER_CATEGORY_RAY_PAYLOAD,
        SLANG_PARAMETER_CATEGORY_HIT_ATTRIBUTES,
        SLANG_PARAMETER_CATEGORY_CALLABLE_PAYLOAD,
        SLANG_PARAMETER_CATEGORY_SHADER_RECORD,

        // An existential type parameter represents a "hole" that
        // needs to be filled with a concrete type to enable
        // generation of specialized code.
        //
        // Consider this example:
        //
        //      struct MyParams
        //      {
        //          IMaterial material;
        //          ILight lights[3];
        //      };
        //
        // This `MyParams` type introduces two existential type parameters:
        // one for `material` and one for `lights`. Even though `lights`
        // is an array, it only introduces one type parameter, because
        // we need to hae a *single* concrete type for all the array
        // elements to be able to generate specialized code.
        //
        SLANG_PARAMETER_CATEGORY_EXISTENTIAL_TYPE_PARAM,

        // An existential object parameter represents a value
        // that needs to be passed in to provide data for some
        // interface-type shader paameter.
        //
        // Consider this example:
        //
        //      struct MyParams
        //      {
        //          IMaterial material;
        //          ILight lights[3];
        //      };
        //
        // This `MyParams` type introduces four existential object parameters:
        // one for `material` and three for `lights` (one for each array
        // element). This is consistent with the number of interface-type
        // "objects" that are being passed through to the shader.
        //
        SLANG_PARAMETER_CATEGORY_EXISTENTIAL_OBJECT_PARAM,

        // The register space offset for the sub-elements that occupies register spaces.
        SLANG_PARAMETER_CATEGORY_SUB_ELEMENT_REGISTER_SPACE,

        // The input_attachment_index subpass occupancy tracker
        SLANG_PARAMETER_CATEGORY_SUBPASS,

        // Metal tier-1 argument buffer element [[id]].
        SLANG_PARAMETER_CATEGORY_METAL_ARGUMENT_BUFFER_ELEMENT,

        // Metal [[attribute]] inputs.
        SLANG_PARAMETER_CATEGORY_METAL_ATTRIBUTE,

        // Metal [[payload]] inputs
        SLANG_PARAMETER_CATEGORY_METAL_PAYLOAD,

        //
        SLANG_PARAMETER_CATEGORY_COUNT,

        // Aliases for Metal-specific categories.
        SLANG_PARAMETER_CATEGORY_METAL_BUFFER = SLANG_PARAMETER_CATEGORY_CONSTANT_BUFFER,
        SLANG_PARAMETER_CATEGORY_METAL_TEXTURE = SLANG_PARAMETER_CATEGORY_SHADER_RESOURCE,
        SLANG_PARAMETER_CATEGORY_METAL_SAMPLER = SLANG_PARAMETER_CATEGORY_SAMPLER_STATE,

        // DEPRECATED:
        SLANG_PARAMETER_CATEGORY_VERTEX_INPUT = SLANG_PARAMETER_CATEGORY_VARYING_INPUT,
        SLANG_PARAMETER_CATEGORY_FRAGMENT_OUTPUT = SLANG_PARAMETER_CATEGORY_VARYING_OUTPUT,
        SLANG_PARAMETER_CATEGORY_COUNT_V1 = SLANG_PARAMETER_CATEGORY_SUBPASS,
    };
    enum slang_LayoutRules : SlangLayoutRulesIntegral
    {
        Default = SLANG_LAYOUT_RULES_DEFAULT,
        MetalArgumentBufferTier2 = SLANG_LAYOUT_RULES_METAL_ARGUMENT_BUFFER_TIER_2,
    };
    enum slang_ContainerType
    {
        None, UnsizedArray, StructuredBuffer, ConstantBuffer, ParameterBlock
    };
    enum slang_SlangPathType : SlangPathTypeIntegral
    {
        SLANG_PATH_TYPE_DIRECTORY,      /**< Path specified specifies a directory. */
        SLANG_PATH_TYPE_FILE,           /**< Path specified is to a file. */
    };
    enum slang_PathKind
    {
        /// Given a path, returns a simplified version of that path.
        /// This typically means removing '..' and/or '.' from the path.
        /// A simplified path must point to the same object as the original.
        Simplified,

        /// Given a path, returns a 'canonical path' to the item.
        /// This may be the operating system 'canonical path' that is the unique path to the item.
        ///
        /// If the item exists the returned canonical path should always be usable to access the item.
        ///
        /// If the item the path specifies doesn't exist, the canonical path may not be returnable
        /// or be a path simplification.
        /// Not all file systems support canonical paths.
        Canonical,

        /// Given a path returns a path such that it is suitable to be displayed to the user.
        ///
        /// For example if the file system is a zip file - it might include the path to the zip
        /// container as well as the path to the specific file.
        ///
        /// NOTE! The display path won't necessarily work on the file system to access the item
        Display,

        /// Get the path to the item on the *operating system* file system, if available.
        OperatingSystem,

        CountOf_
    };
    enum slang_OSPathKind : uint8_t
    {
        None_,                ///< Paths do not map to the file system
        Direct,              ///< Paths map directly to the file system
        OperatingSystem_,     ///< Only paths gained via PathKind::OperatingSystem map to the operating system file system
    };
    enum slang_SlangStage : SlangStageIntegral
    {
        SLANG_STAGE_NONE,
        SLANG_STAGE_VERTEX,
        SLANG_STAGE_HULL,
        SLANG_STAGE_DOMAIN,
        SLANG_STAGE_GEOMETRY,
        SLANG_STAGE_FRAGMENT,
        SLANG_STAGE_COMPUTE,
        SLANG_STAGE_RAY_GENERATION,
        SLANG_STAGE_INTERSECTION,
        SLANG_STAGE_ANY_HIT,
        SLANG_STAGE_CLOSEST_HIT,
        SLANG_STAGE_MISS,
        SLANG_STAGE_CALLABLE,
        SLANG_STAGE_MESH,
        SLANG_STAGE_AMPLIFICATION,

        // alias:
        SLANG_STAGE_PIXEL = SLANG_STAGE_FRAGMENT,
    };
    enum slang_SlangCompileFlags{
        /* Do as little mangling of names as possible, to try to preserve original names */
        SLANG_COMPILE_FLAG_NO_MANGLING          = 1 << 3,

        /* Skip code generation step, just check the code and generate layout */
        SLANG_COMPILE_FLAG_NO_CODEGEN           = 1 << 4,

        /* Obfuscate shader names on release products */
        SLANG_COMPILE_FLAG_OBFUSCATE = 1 << 5,

        /* Deprecated flags: kept around to allow existing applications to
        compile. Note that the relevant features will still be left in
        their default state. */
        SLANG_COMPILE_FLAG_NO_CHECKING          = 0,
        SLANG_COMPILE_FLAG_SPLIT_MIXED_TYPES    = 0,
    };
    enum slang_SlangTargetFlags
    {
        /* When compiling for a D3D Shader Model 5.1 or higher target, allocate
           distinct register spaces for parameter blocks.

           @deprecated This behavior is now enabled unconditionally.
        */
        SLANG_TARGET_FLAG_PARAMETER_BLOCKS_USE_REGISTER_SPACES = 1 << 4,

        /* When set, will generate target code that contains all entrypoints defined
           in the input source or specified via the `spAddEntryPoint` function in a
           single output module (library/source file).
        */
        SLANG_TARGET_FLAG_GENERATE_WHOLE_PROGRAM = 1 << 8,

        /* When set, will dump out the IR between intermediate compilation steps.*/
        SLANG_TARGET_FLAG_DUMP_IR = 1 << 9,

        /* When set, will generate SPIRV directly rather than via glslang. */
        SLANG_TARGET_FLAG_GENERATE_SPIRV_DIRECTLY = 1 << 10,
    };
    enum slang_SlangDebugInfoLevel : SlangDebugInfoLevelIntegral
    {
        SLANG_DEBUG_INFO_LEVEL_NONE = 0,    /**< Don't emit debug information at all. */
        SLANG_DEBUG_INFO_LEVEL_MINIMAL,     /**< Emit as little debug information as possible, while still supporting stack trackes. */
        SLANG_DEBUG_INFO_LEVEL_STANDARD,    /**< Emit whatever is the standard level of debug information for each target. */
        SLANG_DEBUG_INFO_LEVEL_MAXIMAL,     /**< Emit as much debug infromation as possible for each target. */
    };
    enum slang_SlangOptimizationLevel : SlangOptimizationLevelIntegral
    {
        SLANG_OPTIMIZATION_LEVEL_NONE = 0,  /**< Don't optimize at all. */
        SLANG_OPTIMIZATION_LEVEL_DEFAULT,   /**< Default optimization level: balance code quality and compilation time. */
        SLANG_OPTIMIZATION_LEVEL_HIGH,      /**< Optimize aggressively. */
        SLANG_OPTIMIZATION_LEVEL_MAXIMAL,   /**< Include optimizations that may take a very long time, or may involve severe space-vs-speed tradeoffs */
    };
    enum slang_SlangContainerFormat : SlangContainerFormatIntegral
    {
        /* Don't generate a container. */
        SLANG_CONTAINER_FORMAT_NONE,

        /* Generate a container in the `.slang-module` format,
        which includes reflection information, compiled kernels, etc. */
        SLANG_CONTAINER_FORMAT_SLANG_MODULE,
    };
    enum slang_SlangWriterChannel : SlangWriterChannelIntegral
    {
        SLANG_WRITER_CHANNEL_DIAGNOSTIC,
        SLANG_WRITER_CHANNEL_STD_OUTPUT,
        SLANG_WRITER_CHANNEL_STD_ERROR,
        SLANG_WRITER_CHANNEL_COUNT_OF,
    };
    enum slang_SlangWriterMode : SlangWriterModeIntegral
    {
        SLANG_WRITER_MODE_TEXT,
        SLANG_WRITER_MODE_BINARY,
    };
    enum slang_SlangSourceLanguage : SlangSourceLanguageIntegral
    {
        SLANG_SOURCE_LANGUAGE_UNKNOWN,
        SLANG_SOURCE_LANGUAGE_SLANG,
        SLANG_SOURCE_LANGUAGE_HLSL,
        SLANG_SOURCE_LANGUAGE_GLSL,
        SLANG_SOURCE_LANGUAGE_C,
        SLANG_SOURCE_LANGUAGE_CPP,
        SLANG_SOURCE_LANGUAGE_CUDA,
        SLANG_SOURCE_LANGUAGE_SPIRV,
        SLANG_SOURCE_LANGUAGE_METAL,
        SLANG_SOURCE_LANGUAGE_COUNT_OF,
    };
    enum slang_SlangSeverity : SlangSeverityIntegral
    {
        SLANG_SEVERITY_DISABLED = 0, /**< A message that is disabled, filtered out. */
        SLANG_SEVERITY_NOTE,         /**< An informative message. */
        SLANG_SEVERITY_WARNING,      /**< A warning, which indicates a possible proble. */
        SLANG_SEVERITY_ERROR,        /**< An error, indicating that compilation failed. */
        SLANG_SEVERITY_FATAL,        /**< An unrecoverable error, which forced compilation to abort. */
        SLANG_SEVERITY_INTERNAL,     /**< An internal error, indicating a logic error in the compiler. */
    };
    enum slang_SlangDebugInfoFormat : SlangDebugInfoFormatIntegral
    {
        SLANG_DEBUG_INFO_FORMAT_DEFAULT,         ///< Use the default debugging format for the target
        SLANG_DEBUG_INFO_FORMAT_C7,              ///< CodeView C7 format (typically means debugging infomation is embedded in the binary)
        SLANG_DEBUG_INFO_FORMAT_PDB,             ///< Program database

        SLANG_DEBUG_INFO_FORMAT_STABS,          ///< Stabs
        SLANG_DEBUG_INFO_FORMAT_COFF,           ///< COFF debug info
        SLANG_DEBUG_INFO_FORMAT_DWARF,          ///< DWARF debug info (we may want to support specifying the version)

        SLANG_DEBUG_INFO_FORMAT_COUNT_OF,
    };
}
VARIANT_ENUM_CAST(slang_cpp::slang_CompilerOptionValueKind)
VARIANT_ENUM_CAST(slang_cpp::slang_CompilerOptionName)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangCompileTarget)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangProfileID)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangFloatingPointMode)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangLineDirectiveMode)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangMatrixLayoutMode)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangPassThrough)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangCapabilityID)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangResourceShape)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangResourceAccess)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangParameterCategory)
VARIANT_ENUM_CAST(slang_cpp::slang_LayoutRules)
VARIANT_ENUM_CAST(slang_cpp::slang_ContainerType)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangPathType)
VARIANT_ENUM_CAST(slang_cpp::slang_PathKind)
VARIANT_ENUM_CAST(slang_cpp::slang_OSPathKind)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangStage)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangCompileFlags)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangTargetFlags)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangDebugInfoLevel)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangOptimizationLevel)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangContainerFormat)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangWriterChannel)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangWriterMode)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangSourceLanguage)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangSeverity)
VARIANT_ENUM_CAST(slang_cpp::slang_SlangDebugInfoFormat)

namespace Slang{
    typedef ISlangFileSystem IFileSystem;
    typedef ISlangFileSystemExt IFileSystemExt;
    typedef ISlangMutableFileSystem IMutableFileSystem;
    typedef ISlangSharedLibrary ISharedLibrary;
}

namespace slang_cpp {

    class slang_SlangObject;

    class slang_NULL;

    class slang_SIZE;

    class slang_BOOL;

    class slang_DOUBLE;

    class slang_SlangRef;

    class slang_IUnknown;

    class slang_IGlobalSession;

    class slang_ISession;

    class slang_IBlob;

    class slang_ICastable;

    class slang_IFileSystem;

    class slang_IFileSystemExt;

    class slang_IMutableFileSystem;

    class slang_ISharedLibrary;

    class slang_ISharedLibraryLoader;

    class slang_IComponentType;

    class slang_ITypeConformance;

    class slang_IEntryPoint;

    class slang_IModule;

    class slang_IWriter;

    class slang_IProfiler;

    class slang_ICompileRequest;

    class slang_UUID;

    class slang_CompilerOptionValue;

    class slang_CompilerOptionEntry;

    class slang_PreprocessorMacroDesc;

    class slang_TargetDesc;

    class slang_SessionDesc;

    class slang_Modifier;

    class slang_UserAttribute;

    class slang_FunctionReflection;

    class slang_DeclReflection;

    class slang_GenericReflection;

    class slang_VariableReflection;

    class slang_VariableLayoutReflection;

    class slang_TypeReflection;

    class slang_SlangReflectionGeneric;

    class slang_TypeLayoutReflection;

    class slang_TypeParameterReflection;

    class slang_EntryPointReflection;

    class slang_ShaderReflection;

    typedef slang_ShaderReflection slang_ProgramLayout;

    class slang_SpecializationArg;


    class slang_SlangObject : public godot::Object {
    GDCLASS(slang_SlangObject, godot::Object)

        static void _bind_methods() {}
    };

    class slang_NULL : public slang_SlangObject {
    GDCLASS(slang_NULL, slang_SlangObject)

        static void _bind_methods() {}
    };

    template<typename Type>
    class slang_PTR : public slang_SlangObject {
    GDCLASS(slang_PTR, slang_SlangObject)

        Type *value = nullptr;

        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_PTR::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_PTR::get_value);
            if constexpr (std::is_pointer_v<Type>){
                godot::ClassDB::add_property("slang_PTR", godot::PropertyInfo(godot::Variant::OBJECT, "value"),
                                             "set_value", "get_value");
            }else if constexpr (std::is_integral_v<Type>){
                godot::ClassDB::add_property("slang_PTR", godot::PropertyInfo(godot::Variant::INT, "value"),
                                             "set_value", "get_value");
            }else if constexpr (std::is_floating_point_v<Type>){
                godot::ClassDB::add_property("slang_PTR", godot::PropertyInfo(godot::Variant::FLOAT, "value"),
                                             "set_value", "get_value");
            }
        }

    public:
        slang_PTR(Type *v = nullptr) : value(v) {}

        operator Type *() const {
            return value;
        }

        void set_value(Type *v) {
            value = v;
        }

        Type *get_value() const {
            return value;
        }
    };



    class slang_global : public slang_SlangObject{
    GDCLASS(slang_global,slang_SlangObject)
        static void _bind_methods() {}
        static slang_global* single_ptr;
    public:
        slang_global(){
            single_ptr = this;
        }
        static slang_global* get_singleton(){
            return single_ptr;
        }
        ~slang_global(){
            single_ptr = nullptr;
        }

        SlangResult createGlobalSession(slang_PTR<slang_IGlobalSession*>* outGlobalSession){
            return slang::createGlobalSession(reinterpret_cast<slang::IGlobalSession **>(outGlobalSession->get_value()));
        }
    };

    template<typename Int> requires std::is_integral_v<Int>
    class slang_INT : public slang_SlangObject {
    GDCLASS(slang_INT, slang_SlangObject)

        Int value = 0;

        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_INT::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_INT::get_value);
            godot::ClassDB::add_property("slang_INT", godot::PropertyInfo(godot::Variant::INT, "value"),
                                         "set_value", "get_value");
        }

    public:
        slang_INT(Int v = 0) : value(v) {}

        operator Int() const {
            return value;
        }

        void set_value(Int v) {
            value = v;
        }

        Int get_value() const {
            return value;
        }
    };
    class slang_BOOL : public slang_SlangObject {
    GDCLASS(slang_BOOL, slang_SlangObject)

        bool value : 1 = 0;

        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_BOOL::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_BOOL::get_value);
            godot::ClassDB::add_property("slang_INT", godot::PropertyInfo(godot::Variant::BOOL, "value"),
                                         "set_value", "get_value");
        }

    public:
        slang_BOOL(bool v = 0) : value(v) {}

        operator bool() const {
            return value;
        }

        void set_value(bool v) {
            value = v;
        }

        bool get_value() const {
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
    GDCLASS(slang_ENUM, slang_SlangObject)
        Type value = 0;
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("set_value", "value"), &slang_ENUM::set_value);
            godot::ClassDB::bind_method(godot::D_METHOD("get_value"), &slang_ENUM::get_value);
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
        GDCLASS(slang_Callable, slang_SlangObject)
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

    class slang_SlangRef : public godot::RefCounted {
    GDCLASS(slang_SlangRef, godot::RefCounted)
    public:
        static void _bind_methods() {}
    };

    class slang_IUnknown : public slang_SlangRef, public ISlangUnknown {
    GDCLASS(slang_IUnknown, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("query_interface", "guid", "outObj"),
                                        &slang_IUnknown::query_interface);
            godot::ClassDB::bind_method(godot::D_METHOD("add_ref"), &slang_IUnknown::add_ref);
            godot::ClassDB::bind_method(godot::D_METHOD("release"), &slang_IUnknown::release);
        }

        SlangResult query_interface(slang_UUID *guid, slang_PTR<void> *outObj) {
            void *obj = nullptr;
            SlangResult res = this->ISlangUnknown::queryInterface(reinterpret_cast<const Slang::Guid &>(*guid), &obj);
            outObj->set_value(obj);
            return res;
        }

        uint32_t add_ref() {
            return this->ISlangUnknown::addRef();
        }

        uint32_t release() {
            return this->ISlangUnknown::release();
        }
    };

    class slang_IGlobalSession : public slang_SlangRef, public slang::IGlobalSession {
    GDCLASS(slang_IGlobalSession, slang_SlangRef)
    private:
        static void _bind_methods() {
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
                                        &slang_IGlobalSession::createSession);
            godot::ClassDB::bind_method(godot::D_METHOD("findProfile", "name"), &slang_IGlobalSession::findProfile);
            godot::ClassDB::bind_method(godot::D_METHOD("setDownstreamCompilerPath", "passThrough", "path"),
                                        &slang_IGlobalSession::setDownstreamCompilerPath);
            godot::ClassDB::bind_method(godot::D_METHOD("setDownstreamCompilerPrelude", "passThrough", "preludeText"),
                                        &slang_IGlobalSession::setDownstreamCompilerPrelude);
            godot::ClassDB::bind_method(godot::D_METHOD("getDownstreamCompilerPrelude", "passThrough", "outPrelude"),
                                        &slang_IGlobalSession::getDownstreamCompilerPrelude);
            godot::ClassDB::bind_method(godot::D_METHOD("getBuildTagString","null"), &slang_IGlobalSession::getBuildTagString);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("setDefaultDownstreamCompiler", "sourceLanguage", "defaultCompiler"),
                    &slang_IGlobalSession::setDefaultDownstreamCompiler);
            godot::ClassDB::bind_method(godot::D_METHOD("getDefaultDownstreamCompiler", "sourceLanguage"),
                                        &slang_IGlobalSession::getDefaultDownstreamCompiler);
            godot::ClassDB::bind_method(godot::D_METHOD("setLanguagePrelude", "sourceLanguage", "preludeText"),
                                        &slang_IGlobalSession::setLanguagePrelude);
            godot::ClassDB::bind_method(godot::D_METHOD("getLanguagePrelude", "sourceLanguage", "outPrelude"),
                                        &slang_IGlobalSession::getLanguagePrelude);
            godot::ClassDB::bind_method(godot::D_METHOD("createCompileRequest", "outCompileRequest"),
                                        &slang_IGlobalSession::createCompileRequest);
            godot::ClassDB::bind_method(godot::D_METHOD("addBuiltins", "sourcePath", "sourceString"),
                                        &slang_IGlobalSession::addBuiltins);
            godot::ClassDB::bind_method(godot::D_METHOD("setSharedLibraryLoader", "loader"),
                                        &slang_IGlobalSession::setSharedLibraryLoader);
            godot::ClassDB::bind_method(godot::D_METHOD("getSharedLibraryLoader"),
                                        &slang_IGlobalSession::getSharedLibraryLoader);
            godot::ClassDB::bind_method(godot::D_METHOD("checkCompileTargetSupport", "target"),
                                        &slang_IGlobalSession::checkCompileTargetSupport);
            godot::ClassDB::bind_method(godot::D_METHOD("checkPassThroughSupport", "passThrough"),
                                        &slang_IGlobalSession::checkPassThroughSupport);
            godot::ClassDB::bind_method(godot::D_METHOD("compileStdLib", "flags"),
                                        &slang_IGlobalSession::compileStdLib);
            BIND_ENUM_CONSTANT(slang_SlangCapabilityID::SLANG_CAPABILITY_UNKNOWN)
            godot::ClassDB::bind_method(godot::D_METHOD("findCapability", "name"),
                                        &slang_IGlobalSession::findCapability);
            godot::ClassDB::bind_method(godot::D_METHOD("setDownstreamCompilerForTransition", "source", "tartget"),
                                        &slang_IGlobalSession::setDownstreamCompilerForTransition);
            godot::ClassDB::bind_method(godot::D_METHOD("getDownstreamCompilerForTransition", "source", "target"),
                                        &slang_IGlobalSession::getDownstreamCompilerForTransition);
            godot::ClassDB::bind_method(godot::D_METHOD("getCompilerElapsedTime", "outTotalTime", "outDownstreamTime"),
                                        &slang_IGlobalSession::getCompilerElapsedTime);
            godot::ClassDB::bind_method(godot::D_METHOD("setSPIRVCoreGrammar", "jsonPath"),
                                        &slang_IGlobalSession::setSPIRVCoreGrammar);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("parseCommandLineArguments", "argc", "argv", "outSessionDesc", "outAuxAllocation"),
                    &slang_IGlobalSession::parseCommandLineArguments);
            godot::ClassDB::bind_method(godot::D_METHOD("getSessionDescDigest", "sessionDesc", "outBlob"),
                                        &slang_IGlobalSession::getSessionDescDigest);
        }

    public:
        SlangResult createSession(slang_SessionDesc *desc, slang_PTR<slang_ISession *>* outSession) {
            return this->slang::IGlobalSession::createSession((const slang::SessionDesc &) *desc,
                                                                   reinterpret_cast<slang::ISession **>(outSession->get_value()));
        }

        int findProfile(godot::String name) noexcept {
            return (int) this->slang::IGlobalSession::findProfile(name.utf8().get_data());
        }

        void setDownstreamCompilerPath(slang_SlangPassThrough passThrough, godot::String path) {
            return this->slang::IGlobalSession::setDownstreamCompilerPath((SlangPassThrough) passThrough,
                                                                          path.utf8().get_data());
        }

        void setDownstreamCompilerPrelude(slang_SlangPassThrough passThrough, godot::String preludeText) {
            return this->slang::IGlobalSession::setDownstreamCompilerPrelude((SlangPassThrough) passThrough,
                                                                             preludeText.utf8().get_data());
        }

        void getDownstreamCompilerPrelude(slang_SlangPassThrough passThrough, slang_PTR<slang_IBlob *>*outPrelude) {
            return this->slang::IGlobalSession::getDownstreamCompilerPrelude((SlangPassThrough) passThrough,
                                                                             reinterpret_cast<ISlangBlob **>(outPrelude->get_value()));
        }

        godot::String getBuildTagString(slang_NULL *null) {
            return godot::String().utf8(this->slang::IGlobalSession::getBuildTagString());
        }

        SlangResult setDefaultDownstreamCompiler(slang_SlangSourceLanguage sourceLanguage, slang_SlangPassThrough defaultCompiler) {
            return this->slang::IGlobalSession::setDefaultDownstreamCompiler(
                    static_cast<SlangSourceLanguage>(sourceLanguage), static_cast<SlangPassThrough>(defaultCompiler));
        }

        int getDefaultDownstreamCompiler(slang_SlangSourceLanguage sourceLanguage) {
            return this->slang::IGlobalSession::getDefaultDownstreamCompiler(
                    static_cast<SlangSourceLanguage>(sourceLanguage));
        }

        void setLanguagePrelude(slang_SlangSourceLanguage sourceLanguage, godot::String preludeText) {
            return this->slang::IGlobalSession::setLanguagePrelude(
                    static_cast<SlangSourceLanguage>(sourceLanguage), preludeText.utf8().get_data());
        }

        void getLanguagePrelude(slang_SlangSourceLanguage sourceLanguage, slang_PTR<slang_IBlob *>*outPrelude) {
            return this->slang::IGlobalSession::getLanguagePrelude(
                    static_cast<SlangSourceLanguage>(sourceLanguage),
                    reinterpret_cast<ISlangBlob **>(outPrelude->get_value()));
        }

        SlangResult createCompileRequest(slang_PTR<slang_ICompileRequest *>*outCompileRequest) {
            return this->slang::IGlobalSession::createCompileRequest(
                    reinterpret_cast<slang::ICompileRequest **>(outCompileRequest->get_value()));
        }

        void addBuiltins(godot::String sourcePath, godot::String sourceString) {
            return this->slang::IGlobalSession::addBuiltins(sourcePath.utf8().get_data(),
                                                            sourceString.utf8().get_data());
        }

        void setSharedLibraryLoader(slang_ISharedLibraryLoader *loader) {
            return this->slang::IGlobalSession::setSharedLibraryLoader(
                    reinterpret_cast<ISlangSharedLibraryLoader *>(loader));
        }

        slang_ISharedLibraryLoader *getSharedLibraryLoader(slang_NULL *null);

        SlangResult checkCompileTargetSupport(slang_SlangCompileTarget target) {
            return this->slang::IGlobalSession::checkCompileTargetSupport(static_cast<SlangCompileTarget>(target));
        }

        SlangResult checkPassThroughSupport(slang_SlangPassThrough passThrough) {
            return this->slang::IGlobalSession::checkPassThroughSupport(static_cast<SlangPassThrough>(passThrough));
        }

        SlangResult compileStdLib(slang::CompileStdLibFlags flags) {
            return this->slang::IGlobalSession::compileStdLib(flags);
        }

        SlangResult loadStdLib(slang_PTR<void> stdLib, size_t stdLibSizeInBytes) {
            return this->slang::IGlobalSession::loadStdLib(stdLib.get_value(), stdLibSizeInBytes);
        }

        SlangResult saveStdLib(SlangArchiveType archiveType,slang_PTR< ISlangBlob *>*outBlob) {
            return this->slang::IGlobalSession::saveStdLib(archiveType, reinterpret_cast<ISlangBlob **>(outBlob->get_value()));
        }

        slang_SlangCapabilityID findCapability(godot::String name) {
            return static_cast<slang_SlangCapabilityID>(this->slang::IGlobalSession::findCapability(
                    name.utf8().get_data()));
        }

        void setDownstreamCompilerForTransition(slang_SlangCompileTarget source, slang_SlangCompileTarget target,
                                                slang_SlangPassThrough passThrough) {
            return this->slang::IGlobalSession::setDownstreamCompilerForTransition(
                    static_cast<SlangCompileTarget>(source),
                    static_cast<SlangCompileTarget>(target),
                    static_cast<SlangPassThrough>(passThrough));
        }

        slang_SlangPassThrough
        getDownstreamCompilerForTransition(slang_SlangCompileTarget source, slang_SlangCompileTarget target) {
            return static_cast<slang_SlangPassThrough>(this->slang::IGlobalSession::getDownstreamCompilerForTransition(
                    static_cast<SlangCompileTarget>(source), static_cast<SlangCompileTarget>(target)));
        }

        void getCompilerElapsedTime(slang_DOUBLE *outTotalTime, slang_DOUBLE *outDownstreamTime) {
            double totalTime, downstreamTime;
            this->slang::IGlobalSession::getCompilerElapsedTime(&totalTime, &downstreamTime);
            outTotalTime->set_value(totalTime);
            outDownstreamTime->set_value(downstreamTime);
        }

        SlangResult setSPIRVCoreGrammar(godot::String jsonPath) {
            return this->slang::IGlobalSession::setSPIRVCoreGrammar(jsonPath.utf8().get_data());
        }

        SlangResult
        parseCommandLineArguments(int argc, godot::TypedArray<godot::String> argv, slang_SessionDesc *outSessionDesc,
                                  slang_PTR<slang_IUnknown *>*outAuxAllocation);

        SlangResult getSessionDescDigest(slang_SessionDesc *sessionDesc, slang_PTR<slang_IBlob*>*outBlob);
    };

    class slang_ISession : public slang_SlangRef, public slang::ISession {
    GDCLASS(slang_ISession, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("loadModule", "moduleName", "outDiagnostics"),
                                        &slang_ISession::loadModule);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("loadModuleFromSource", "moduleName", "path", "source", "outDiagnostics"),
                    &slang_ISession::loadModuleFromSource);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("createCompositeComponentType", "componentTypes", "componentTypeCount",
                                    "outCompositeComponentType", "outDiagnostics"),
                    &slang_ISession::createCompositeComponentType);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("specializeType", "type_", "specializationArgs", "specializationArgCount",
                                    "outDiagnostics"), &slang_ISession::specializeType);
            BIND_ENUM_CONSTANT(slang_LayoutRules::Default)
            BIND_ENUM_CONSTANT(slang_LayoutRules::MetalArgumentBufferTier2)
            godot::ClassDB::bind_method(
                    godot::D_METHOD("getTypeLayout", "type_", "targetIndex", "rules", "outDiagnostics"),
                    &slang_ISession::getTypeLayout);
            BIND_ENUM_CONSTANT(slang_ContainerType::None)
            BIND_ENUM_CONSTANT(slang_ContainerType::UnsizedArray)
            BIND_ENUM_CONSTANT(slang_ContainerType::StructuredBuffer)
            BIND_ENUM_CONSTANT(slang_ContainerType::ConstantBuffer)
            BIND_ENUM_CONSTANT(slang_ContainerType::ParameterBlock)
            godot::ClassDB::bind_method(godot::D_METHOD("getContainerType","elementType","containerType","outDiagnostics"),&slang_ISession::getContainerType);
            godot::ClassDB::bind_method(godot::D_METHOD("getDynamicType"), &slang_ISession::getDynamicType);
            godot::ClassDB::bind_method(godot::D_METHOD("getTypeRTTIMangledName", "type_", "outNameBlob"),
                                        &slang_ISession::getTypeRTTIMangledName);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("getTypeConformanceWitnessMangledName", "type_", "interfaceType", "outNameBlob"),
                    &slang_ISession::getTypeConformanceWitnessMangledName);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("getTypeConformanceWitnessSequentialID", "type_", "interfaceType", "outId"),
                    &slang_ISession::getTypeConformanceWitnessSequentialID);
            godot::ClassDB::bind_method(godot::D_METHOD("createCompileRequest", "outCompileRequest"),
                                        &slang_ISession::createCompileRequest);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("createTypeConformanceComponentType", "type_", "interfaceType", "outConformance",
                                    "conformanceIdOverride", "outDiagnostics"),
                    &slang_ISession::createTypeConformanceComponentType);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("loadModuleFromIRBlob", "moduleName", "path", "source", "outDiagnostics"),
                    &slang_ISession::loadModuleFromIRBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("getLoadedModuleCount"), &slang_ISession::getLoadedModuleCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getLoadedModule", "null"), &slang_ISession::getLoadedModule);
            godot::ClassDB::bind_method(godot::D_METHOD("isBinaryModuleUpToDate", "modulePath", "binaryModuleBlob"),
                                        &slang_ISession::isBinaryModuleUpToDate);
            godot::ClassDB::bind_method(
                    godot::D_METHOD("loadModuleFromSourceString", "moduleName", "path", "string", "outDiagnostics"),
                    &slang_ISession::loadModuleFromSourceString);
        }

    public:
        slang_IModule *loadModule(godot::String moduleName, slang_PTR<slang_IBlob *> *outDiagnostics);

        slang_IModule *loadModuleFromSource(godot::String moduleName, godot::String path, slang_IBlob *source,
                                            slang_PTR<slang_IBlob *> *outDiagnostics);

        SlangResult createCompositeComponentType(slang_PTR<slang_IComponentType *>*componentTypes, SlangInt componentTypeCount,
                                                 slang_PTR<slang_IComponentType *>*outCompositeComponentType,
                                                         slang_PTR<slang_IBlob *>*outDiagnostics) {
            return this->slang::ISession::createCompositeComponentType(
                    reinterpret_cast<slang::IComponentType **>(componentTypes->get_value()), componentTypeCount,
                    reinterpret_cast<slang::IComponentType **>(outCompositeComponentType->get_value()),
                    reinterpret_cast<slang::IBlob **>(outDiagnostics->get_value()));

        }
        slang_TypeReflection* specializeType(slang_TypeReflection* type_, slang_SpecializationArg* specializationArgs, SlangInt specializationArgCount, slang_PTR<slang_IBlob *>* outDiagnostics);
        slang_TypeLayoutReflection* getTypeLayout(slang_TypeReflection* type_, SlangInt targetIndex, slang_LayoutRules rules, slang_PTR<slang_IBlob *>* outDiagnostics);
        slang_TypeReflection* getContainerType(slang_TypeReflection* elementType, slang_ContainerType containerType, slang_PTR<slang_IBlob *>* outDiagnostics);
        slang_TypeReflection* getDynamicType(slang_NULL*null);
        SlangResult getTypeRTTIMangledName(slang_TypeReflection* type, slang_PTR<slang_IBlob *>* outNameBlob);
        SlangResult getTypeConformanceWitnessMangledName(slang_TypeReflection* type, slang_TypeReflection* interfaceType, slang_PTR<slang_IBlob *>* outNameBlob);
        SlangResult getTypeConformanceWitnessSequentialID(slang_TypeReflection* type, slang_TypeReflection* interfaceType, slang_INT<uint32_t>* outId);
        SlangResult createCompileRequest(slang_PTR<slang_ICompileRequest *>*outCompileRequest) {
            return this->slang::ISession::createCompileRequest(
                    reinterpret_cast<slang::ICompileRequest **>(outCompileRequest->get_value()));
        }
        SlangResult createTypeConformanceComponentType(slang_TypeReflection* type, slang_TypeReflection* interfaceType, slang_PTR<slang_ITypeConformance*>* outConformance, SlangInt conformanceIdOverride, slang_PTR<slang_IBlob*>* outDiagnostics);
        slang_IModule *loadModuleFromIRBlob(godot::String moduleName, godot::String path, slang_IBlob *source, slang_PTR<slang_IBlob*> *outDiagnostics);
        SlangInt getLoadedModuleCount() {
            return this->slang::ISession::getLoadedModuleCount();
        }
        slang_IModule *getLoadedModule(SlangInt index, slang_NULL *null);
        bool isBinaryModuleUpToDate(godot::String modulePath, slang_IBlob *binaryModuleBlob);
        slang_IModule *loadModuleFromSourceString(godot::String moduleName, godot::String path, godot::String string, slang_PTR<slang_IBlob*> *outDiagnostics);
    };

    class slang_IBlob : public slang_SlangRef, public slang::IBlob {
    GDCLASS(slang_IBlob, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("getBufferPointer","null"), &slang_IBlob::getBufferPointer);
            godot::ClassDB::bind_method(godot::D_METHOD("getBufferSize"), &slang_IBlob::getBufferSize);
        }
    public:
        slang_PTR<void>* getBufferPointer(slang_NULL *null){
            return static_cast<slang_PTR<void> *>(const_cast<void *>(this->slang::IBlob::getBufferPointer()));
        }
        size_t getBufferSize() override{
            return this->slang::IBlob::getBufferSize();
        }
    };

    class slang_ICastable : public slang_SlangRef, public Slang::ICastable {
    GDCLASS(slang_ICastable, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("castAs", "uuid", "null"), &slang_ICastable::castAs);
        }
    public:
        slang_PTR<void>* castAs(slang_UUID* uuid,slang_NULL *null){
            return static_cast<slang_PTR<void> *>(const_cast<void *>(this->ISlangCastable::castAs(reinterpret_cast<const SlangUUID&>(*uuid))));
        }
    };

    class slang_IFileSystem : public slang_SlangRef, public Slang::IFileSystem {
    GDCLASS(slang_IFileSystem, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("loadFile", "path", "outBlob"), &slang_IFileSystem::loadFile);
        }
    public:
        SlangResult loadFile(godot::String path, slang_PTR<slang_IBlob*>* outBlob){
            return this->Slang::IFileSystem::loadFile(path.utf8().get_data(), reinterpret_cast<ISlangBlob **>(outBlob->get_value()));
        }
    };

    class slang_IFileSystemExt : public slang_SlangRef, public Slang::IFileSystemExt {
    GDCLASS(slang_IFileSystemExt, slang_SlangRef)
    private:
        static void _bind_methods() {
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

            godot::ClassDB::bind_method(godot::D_METHOD("getFileUniqueIdentity", "path", "outBlob"), &slang_IFileSystemExt::getFileUniqueIdentity);
            godot::ClassDB::bind_method(godot::D_METHOD("calcCombinedPath", "pathType", "fromPath", "path", "pathOut"), &slang_IFileSystemExt::calcCombinedPath);
            godot::ClassDB::bind_method(godot::D_METHOD("getPathType", "path", "pathTypeOut"), &slang_IFileSystemExt::getPathType);
            godot::ClassDB::bind_method(godot::D_METHOD("getPath", "kind", "path", "pathOut"), &slang_IFileSystemExt::getPath);
            godot::ClassDB::bind_method(godot::D_METHOD("getOSPathKind", "null"), &slang_IFileSystemExt::getOSPathKind);
        }
    public:
        SlangResult getFileUniqueIdentity(godot::String path, slang_PTR<slang_IBlob*>* outBlob){
            return this->Slang::IFileSystemExt::getFileUniqueIdentity(path.utf8().get_data(), reinterpret_cast<ISlangBlob **>(outBlob->get_value()));
        }
        SlangResult calcCombinedPath(slang_SlangPathType pathType, godot::String fromPath, godot::String path, slang_PTR<slang_IBlob*>* pathOut){
            return this->Slang::IFileSystemExt::calcCombinedPath(static_cast<SlangPathType>(pathType), fromPath.utf8().get_data(), path.utf8().get_data(), reinterpret_cast<ISlangBlob **>(pathOut->get_value()));
        }
        SlangResult getPathType(godot::String path, slang_ENUM<slang_SlangPathType>* pathTypeOut){
            SlangPathType pathType;
            SlangResult res = this->Slang::IFileSystemExt::getPathType(path.utf8().get_data(), &pathType);
            pathTypeOut->set_value(static_cast<slang_SlangPathType>(pathType));
            return res;
        }
        SlangResult getPath(slang_PathKind kind, godot::String path, slang_PTR<slang_IBlob*>* pathOut){
            return this->Slang::IFileSystemExt::getPath(static_cast<PathKind>(kind), path.utf8().get_data(), reinterpret_cast<ISlangBlob **>(pathOut->get_value()));
        }
        SlangResult enumeratePathContents(godot::String path,void(*callback)(SlangPathType pathType, const char* name, void* userData) , slang_PTR<void> userData){
            return this->Slang::IFileSystemExt::enumeratePathContents(path.utf8().get_data(), callback, userData);
        }
        slang_OSPathKind getOSPathKind(slang_NULL*null){
            return static_cast<slang_OSPathKind>(this->Slang::IFileSystemExt::getOSPathKind());
        }
    };

    class slang_IMutableFileSystem : public slang_SlangRef, public Slang::IMutableFileSystem {
    GDCLASS(slang_IMutableFileSystem, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("saveFile", "path", "data", "size"), &slang_IMutableFileSystem::saveFile);
            godot::ClassDB::bind_method(godot::D_METHOD("saveFileBlob", "path", "blob"), &slang_IMutableFileSystem::saveFileBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("remove", "path"), &slang_IMutableFileSystem::remove);
            godot::ClassDB::bind_method(godot::D_METHOD("createDirectory", "path"), &slang_IMutableFileSystem::createDirectory);
        }

    public:
        SlangResult saveFile(godot::String path, slang_PTR<void>* data, size_t size){
            return this->Slang::IMutableFileSystem::saveFile(path.utf8().get_data(), data->get_value(), size);
        }
        SlangResult saveFileBlob(godot::String path, slang_IBlob* blob){
            return this->Slang::IMutableFileSystem::saveFileBlob(path.utf8().get_data(), static_cast<ISlangBlob *>(blob));
        }
        SlangResult remove(godot::String path){
            return this->Slang::IMutableFileSystem::remove(path.utf8().get_data());
        }
        SlangResult createDirectory(godot::String path) {
            return this->Slang::IMutableFileSystem::createDirectory(path.utf8().get_data());
        }
    };

    class slang_ISharedLibrary : public slang_SlangRef, public Slang::ISharedLibrary {
    GDCLASS(slang_ISharedLibrary, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("findSymbolAddressByName", "name", "outAddress"), &slang_ISharedLibrary::findSymbolAddressByName);
        }
    public:
        SlangFuncPtr findFuncByName(godot::String name){
            return this->Slang::ISharedLibrary::findFuncByName(name.utf8().get_data());
        }
        slang_PTR<void>* findSymbolAddressByName(godot::String name){
            return static_cast<slang_PTR<void> *>(const_cast<void *>(this->Slang::ISharedLibrary::findSymbolAddressByName(name.utf8().get_data())));
        }
    };

    class slang_ISharedLibraryLoader : public slang_SlangRef, public ISlangSharedLibraryLoader {
    GDCLASS(slang_ISharedLibraryLoader, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("loadSharedLibrary", "path", "sharedLibraryOut"),
                                        &slang_ISharedLibraryLoader::loadSharedLibrary);
        }

    public:
        SlangResult loadSharedLibrary(godot::String path, slang_PTR<slang_ISharedLibrary *>*sharedLibraryOut) {
            return this->ISlangSharedLibraryLoader::loadSharedLibrary(path.utf8().get_data(),
                                                                      reinterpret_cast<ISlangSharedLibrary **>(sharedLibraryOut->get_value()));
        }
    };

    class slang_IComponentType : public slang_SlangRef, public slang::IComponentType {
    GDCLASS(slang_IComponentType, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("getSession"), &slang_IComponentType::getSession);
            godot::ClassDB::bind_method(godot::D_METHOD("getLayout", "targetIndex", "blob"), &slang_IComponentType::getLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("getSpecializationParamCount"), &slang_IComponentType::getSpecializationParamCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointCode", "entryPointIndex", "targetIndex", "outCode", "outDiagnostics"), &slang_IComponentType::getEntryPointCode);
            godot::ClassDB::bind_method(godot::D_METHOD("getResultAsFileSystem", "entryPointIndex", "targetIndex", "outFileSystem"), &slang_IComponentType::getResultAsFileSystem);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointHash", "entryPointIndex", "targetIndex", "outHash"), &slang_IComponentType::getEntryPointHash);
            godot::ClassDB::bind_method(godot::D_METHOD("specialize", "specializationArgs", "specializationArgCount", "specializedOut", "outDiagnostics"), &slang_IComponentType::specialize);
            godot::ClassDB::bind_method(godot::D_METHOD("link", "module", "outDiagnostics"), &slang_IComponentType::link);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointHostCallable", "entryPointIndex", "targetIndex", "outSharedLibrary", "outDiagnostics"), &slang_IComponentType::getEntryPointHostCallable);
            godot::ClassDB::bind_method(godot::D_METHOD("linkWithOptions", "outLinkedComponentType", "compilerOptionEntryCount", "compilerOptionEntries", "outDiagnostics"), &slang_IComponentType::linkWithOptions);
            godot::ClassDB::bind_method(godot::D_METHOD("getTargetCode", "targetIndex", "outCode", "outDiagnostics"), &slang_IComponentType::getTargetCode);
        }
    public:
        slang_ISession *getSession() override {
            return dynamic_cast<slang_ISession *>(this->IComponentType::getSession());
        }
        slang_ShaderReflection* getLayout(SlangInt targetIndex = 0,slang_PTR<slang_IBlob *>* blob = nullptr);
        SlangInt getSpecializationParamCount(){
            return this->IComponentType::getSpecializationParamCount();
        }
        SlangResult getEntryPointCode(SlangInt entryPointIndex,SlangInt targetIndex,slang_PTR<slang_IBlob*>* outCode,slang_PTR<slang_IBlob*>* outDiagnostics = nullptr){
            return this->IComponentType::getEntryPointCode(entryPointIndex,targetIndex,reinterpret_cast<ISlangBlob **>(outCode->get_value()),reinterpret_cast<ISlangBlob **>(outDiagnostics==nullptr?nullptr:outDiagnostics->get_value()));
        }
        SlangResult getResultAsFileSystem(SlangInt entryPointIndex,SlangInt targetIndex,slang_PTR<slang_IMutableFileSystem*>* outFileSystem){
            return this->IComponentType::getResultAsFileSystem(entryPointIndex,targetIndex,reinterpret_cast<ISlangMutableFileSystem **>(outFileSystem->get_value()));
        }
        void getEntryPointHash(SlangInt entryPointIndex,SlangInt targetIndex,slang_PTR<slang_IBlob*>* outHash){
            return this->IComponentType::getEntryPointHash(entryPointIndex,targetIndex,reinterpret_cast<ISlangBlob **>(outHash->get_value()));
        }
        SlangResult specialize(slang_SpecializationArg* specializationArgs,SlangInt specializationArgCount,slang_PTR<slang_IComponentType*>* specializedOut,slang_PTR<slang_IBlob *>* outDiagnostics = nullptr);
        SlangResult link(slang_PTR<slang_IComponentType*>* module,slang_PTR<slang_IBlob*>* outDiagnostics = nullptr){
            return this->IComponentType::link(reinterpret_cast<IComponentType **>(module->get_value()),reinterpret_cast<ISlangBlob **>(outDiagnostics==nullptr?nullptr:outDiagnostics->get_value()));
        }
        SlangResult getEntryPointHostCallable(int entryPointIndex,int targetIndex,slang_PTR<slang_ISharedLibrary*>* outSharedLibrary, slang_PTR<slang_IBlob*>* outDiagnostics = nullptr){
            return this->IComponentType::getEntryPointHostCallable(entryPointIndex,targetIndex,reinterpret_cast<ISlangSharedLibrary **>(outSharedLibrary->get_value()),reinterpret_cast<ISlangBlob **>(outDiagnostics==nullptr?nullptr:outDiagnostics->get_value()));
        }
        SlangResult linkWithOptions(slang_PTR<slang_IComponentType*>* outLinkedComponentType,uint32_t compilerOptionEntryCount,slang_CompilerOptionEntry* compilerOptionEntries,slang_PTR<slang_IBlob *>* outDiagnostics = nullptr);
        SlangResult getTargetCode(SlangInt targetIndex,slang_PTR<slang_IBlob*>* outCode,slang_PTR<slang_IBlob*>* outDiagnostics = nullptr){
            return this->IComponentType::getTargetCode(targetIndex,reinterpret_cast<ISlangBlob **>(outCode->get_value()),reinterpret_cast<ISlangBlob **>(outDiagnostics==nullptr?nullptr:outDiagnostics->get_value()));
        }
    };
    class slang_ITypeConformance : public slang_SlangRef, public slang::ITypeConformance {
    GDCLASS(slang_ITypeConformance, slang_SlangRef)
    private:
        static void _bind_methods() {

        }
    };
    class slang_IEntryPoint : public slang_SlangRef, public slang::IEntryPoint {
    GDCLASS(slang_IEntryPoint, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("getFunctionReflection","null"), &slang_IEntryPoint::getFunctionReflection);
        }
        slang_FunctionReflection* getFunctionReflection(slang_NULL*null);
    };

    class slang_IModule : public slang_SlangRef, public slang::IModule {
    GDCLASS(slang_IModule, slang_SlangRef)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("findEntryPointByName", "name", "outEntryPoint"), &slang_IModule::findEntryPointByName);
            godot::ClassDB::bind_method(godot::D_METHOD("getDefinedEntryPointCount"), &slang_IModule::getDefinedEntryPointCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getDefinedEntryPoint", "index", "outEntryPoint"), &slang_IModule::getDefinedEntryPoint);
            godot::ClassDB::bind_method(godot::D_METHOD("serialize", "outBlob"), &slang_IModule::serialize);
            godot::ClassDB::bind_method(godot::D_METHOD("writeToFile", "fileName"), &slang_IModule::writeToFile);
            godot::ClassDB::bind_method(godot::D_METHOD("getName","null"), &slang_IModule::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getFilePath","null"), &slang_IModule::getFilePath);
            godot::ClassDB::bind_method(godot::D_METHOD("getUniqueIdentity","null"), &slang_IModule::getUniqueIdentity);
            godot::ClassDB::bind_method(godot::D_METHOD("findAndCheckEntryPoint", "name", "stage", "outEntryPoint", "outDiagnostics"), &slang_IModule::findAndCheckEntryPoint);
            godot::ClassDB::bind_method(godot::D_METHOD("getDependencyFileCount"), &slang_IModule::getDependencyFileCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getDependencyFilePath", "index","null"), &slang_IModule::getDependencyFilePath);
            godot::ClassDB::bind_method(godot::D_METHOD("getModuleReflection","null"), &slang_IModule::getModuleReflection);
            godot::ClassDB::bind_method(godot::D_METHOD("precompileForTarget", "target", "outDiagnostics"), &slang_IModule::precompileForTarget);
        }
    public:
        SlangResult findEntryPointByName(godot::String name, slang_PTR<slang_IEntryPoint*>* outEntryPoint){
            return this->IModule::findEntryPointByName(name.utf8().get_data(),reinterpret_cast<slang::IEntryPoint **>(outEntryPoint->get_value()));
        }
        SlangInt32 getDefinedEntryPointCount(){
            return this->IModule::getDefinedEntryPointCount();
        }
        SlangResult getDefinedEntryPoint(SlangInt32 index, slang_PTR<slang_IEntryPoint*>* outEntryPoint){
            return this->IModule::getDefinedEntryPoint(index,reinterpret_cast<slang::IEntryPoint **>(outEntryPoint->get_value()));
        }
        SlangResult serialize(slang_PTR<slang_IBlob*>* outBlob){
            return this->IModule::serialize(reinterpret_cast<ISlangBlob **>(outBlob->get_value()));
        }
        SlangResult writeToFile(godot::String fileName){
            return this->IModule::writeToFile(fileName.utf8().get_data());
        }
        godot::String getName(slang_NULL*null){
            return godot::String().utf8(this->IModule::getName());
        }
        godot::String getFilePath(slang_NULL* null){
            return godot::String().utf8(this->IModule::getFilePath());
        }
        godot::String getUniqueIdentity(slang_NULL* null){
            return godot::String().utf8(this->IModule::getUniqueIdentity());
        }
        SlangResult findAndCheckEntryPoint(godot::String name,slang_SlangStage stage,slang_PTR<slang_IEntryPoint*>* outEntryPoint,slang_PTR<slang_IBlob*>* outDiagnostics){
            return this->IModule::findAndCheckEntryPoint(name.utf8().get_data(),static_cast<SlangStage>(stage),reinterpret_cast<slang::IEntryPoint **>(outEntryPoint->get_value()),reinterpret_cast<ISlangBlob **>(outDiagnostics->get_value()));
        }
        SlangInt32 getDependencyFileCount(){
            return this->IModule::getDependencyFileCount();
        }
        godot::String getDependencyFilePath(SlangInt32 index,slang_NULL*null){
            return godot::String().utf8(this->IModule::getDependencyFilePath(index));
        }
        slang_DeclReflection* getModuleReflection(slang_NULL*null);
        SlangResult precompileForTarget(slang_SlangCompileTarget target,slang_PTR<slang_IBlob*>* outDiagnostics){
            return this->IModule::precompileForTarget(static_cast<SlangCompileTarget>(target),reinterpret_cast<ISlangBlob **>(outDiagnostics->get_value()));
        }
    };

    class slang_IWriter : public slang_SlangRef, public ISlangWriter {
    GDCLASS(slang_IWriter, slang_SlangRef)
    private:
        static void _bind_methods() {
            BIND_ENUM_CONSTANT(slang_SlangWriterMode::SLANG_WRITER_MODE_TEXT)
            BIND_ENUM_CONSTANT(slang_SlangWriterMode::SLANG_WRITER_MODE_BINARY)

            godot::ClassDB::bind_method(godot::D_METHOD("beginAppendBuffer", "maxNumChars", "null"), &slang_IWriter::beginAppendBuffer);
            godot::ClassDB::bind_method(godot::D_METHOD("endAppendBuffer", "buffer", "numChars"), &slang_IWriter::endAppendBuffer);
            godot::ClassDB::bind_method(godot::D_METHOD("write", "chars", "numChars"), &slang_IWriter::write);
            godot::ClassDB::bind_method(godot::D_METHOD("flush"), &slang_IWriter::flush);
            godot::ClassDB::bind_method(godot::D_METHOD("isConsole"), &slang_IWriter::isConsole);
            godot::ClassDB::bind_method(godot::D_METHOD("setMode", "mode"), &slang_IWriter::setMode);
        }
    public:
        godot::String beginAppendBuffer(size_t maxNumChars, slang_NULL* null){
            return godot::String().utf8(this->ISlangWriter::beginAppendBuffer(maxNumChars));
        }
        SlangResult endAppendBuffer(godot::String buffer,size_t numChars){
            return this->ISlangWriter::endAppendBuffer(const_cast<char *>(buffer.utf8().get_data()), numChars);
        }
        SlangResult write(godot::String chars, size_t numChars){
            return this->ISlangWriter::write(const_cast<char *>(chars.utf8().get_data()), numChars);
        }
        void flush(){
            return this->ISlangWriter::flush();
        }
        bool isConsole(){
            return this->ISlangWriter::isConsole();
        }
        SlangResult setMode(slang_SlangWriterMode mode){
            return this->ISlangWriter::setMode(static_cast<SlangWriterMode>(mode));
        }
    };
    class slang_IProfiler : public slang_SlangRef, public ISlangProfiler{
    GDCLASS(slang_IProfiler, slang_SlangRef)
    private:
        static void _bind_methods(){
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryCount"), &slang_IProfiler::getEntryCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryName", "index", "null"), &slang_IProfiler::getEntryName);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryTimeMS", "index"), &slang_IProfiler::getEntryTimeMS);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryInvocationTimes", "index"), &slang_IProfiler::getEntryInvocationTimes);
        }
    public:
        size_t getEntryCount(){
            return this->ISlangProfiler::getEntryCount();
        }
        godot::String getEntryName(uint32_t index,slang_NULL*null){
            return godot::String().utf8(this->ISlangProfiler::getEntryName(index));
        }
        long getEntryTimeMS(uint32_t index){
            return this->ISlangProfiler::getEntryTimeMS(index);
        }
        uint32_t getEntryInvocationTimes(uint32_t index){
            return this->ISlangProfiler::getEntryInvocationTimes(index);
        }
    };
    class slang_ICompileRequest : public slang_SlangRef, public slang::ICompileRequest {
    GDCLASS(slang_ICompileRequest, slang_SlangRef)
    private:
        static void _bind_methods() {
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

            godot::ClassDB::bind_method(godot::D_METHOD("setFileSystem", "fileSystem"), &slang_ICompileRequest::setFileSystem);
            godot::ClassDB::bind_method(godot::D_METHOD("setCompileFlags", "compileFlags"), &slang_ICompileRequest::setCompileFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("getCompileFlags"), &slang_ICompileRequest::getCompileFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("setDumpIntermediates", "enable"), &slang_ICompileRequest::setDumpIntermediates);
            godot::ClassDB::bind_method(godot::D_METHOD("setDumpIntermediatePrefix", "prefix"), &slang_ICompileRequest::setDumpIntermediatePrefix);
            godot::ClassDB::bind_method(godot::D_METHOD("setLineDirectiveMode", "mode"), &slang_ICompileRequest::setLineDirectiveMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setCodeGenTarget", "target"), &slang_ICompileRequest::setCodeGenTarget);
            godot::ClassDB::bind_method(godot::D_METHOD("addCodeGenTarget", "target"), &slang_ICompileRequest::addCodeGenTarget);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetProfile", "targetIndex", "profile"), &slang_ICompileRequest::setTargetProfile);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetFlags", "targetIndex", "flags"), &slang_ICompileRequest::setTargetFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetFloatingPointMode", "targetIndex", "mode"), &slang_ICompileRequest::setTargetFloatingPointMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetMatrixLayoutMode", "targetIndex", "mode"), &slang_ICompileRequest::setTargetMatrixLayoutMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setMatrixLayoutMode", "mode"), &slang_ICompileRequest::setMatrixLayoutMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setDebugInfoLevel", "level"), &slang_ICompileRequest::setDebugInfoLevel);
            godot::ClassDB::bind_method(godot::D_METHOD("setOptimizationLevel", "level"), &slang_ICompileRequest::setOptimizationLevel);
            godot::ClassDB::bind_method(godot::D_METHOD("setOutputContainerFormat", "format"), &slang_ICompileRequest::setOutputContainerFormat);
            godot::ClassDB::bind_method(godot::D_METHOD("setPassThrough", "passThrough"), &slang_ICompileRequest::setPassThrough);
            godot::ClassDB::bind_method(godot::D_METHOD("setWriter", "channel", "writer"), &slang_ICompileRequest::setWriter);
            godot::ClassDB::bind_method(godot::D_METHOD("getWriter", "channel"), &slang_ICompileRequest::getWriter);
            godot::ClassDB::bind_method(godot::D_METHOD("addSearchPath", "path"), &slang_ICompileRequest::addSearchPath);
            godot::ClassDB::bind_method(godot::D_METHOD("addPreprocessorDefine", "key", "value"), &slang_ICompileRequest::addPreprocessorDefine);
            godot::ClassDB::bind_method(godot::D_METHOD("processCommandLineArguments", "args", "argCount"), &slang_ICompileRequest::processCommandLineArguments);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnit", "language", "name"), &slang_ICompileRequest::addTranslationUnit);
            godot::ClassDB::bind_method(godot::D_METHOD("setDefaultModuleName", "defaultModuleName"), &slang_ICompileRequest::setDefaultModuleName);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitPreprocessorDefine", "translationUnitIndex", "key", "value"), &slang_ICompileRequest::addTranslationUnitPreprocessorDefine);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitSourceFile", "translationUnitIndex", "path"), &slang_ICompileRequest::addTranslationUnitSourceFile);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitSourceString", "translationUnitIndex", "path", "source"), &slang_ICompileRequest::addTranslationUnitSourceString);
            godot::ClassDB::bind_method(godot::D_METHOD("addLibraryReference", "path", "libData", "libDataSize"), &slang_ICompileRequest::addLibraryReference);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitSourceStringSpan", "translationUnitIndex", "path", "sourceBegin", "sourceEnd"), &slang_ICompileRequest::addTranslationUnitSourceStringSpan);
            godot::ClassDB::bind_method(godot::D_METHOD("addTranslationUnitSourceBlob", "translationUnitIndex", "path", "sourceBlob"), &slang_ICompileRequest::addTranslationUnitSourceBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("addEntryPoint", "translationUnitIndex", "name", "stage"), &slang_ICompileRequest::addEntryPoint);
            godot::ClassDB::bind_method(godot::D_METHOD("addEntryPointEx", "translationUnitIndex", "name", "stage", "genericArgCount", "genericArgs"), &slang_ICompileRequest::addEntryPointEx);
            godot::ClassDB::bind_method(godot::D_METHOD("setGlobalGenericArgs", "genericArgCount", "genericArgs"), &slang_ICompileRequest::setGlobalGenericArgs);
            godot::ClassDB::bind_method(godot::D_METHOD("setTypeNameForGlobalExistentialTypeParam","slotIndex","typeName"),&slang_ICompileRequest::setTypeNameForGlobalExistentialTypeParam);
            godot::ClassDB::bind_method(godot::D_METHOD("setTypeNameForEntryPointExistentialTypeParam","entryPointIndex","slotIndex","typeName"),&slang_ICompileRequest::setTypeNameForEntryPointExistentialTypeParam);
            godot::ClassDB::bind_method(godot::D_METHOD("setAllowGLSLInput","bool"),&slang_ICompileRequest::setAllowGLSLInput);
            godot::ClassDB::bind_method(godot::D_METHOD("compile"), &slang_ICompileRequest::compile);
            godot::ClassDB::bind_method(godot::D_METHOD("getDiagnosticOutput"), &slang_ICompileRequest::getDiagnosticOutput);
            godot::ClassDB::bind_method(godot::D_METHOD("getDiagnosticOutputBlob","outBlob"), &slang_ICompileRequest::getDiagnosticOutputBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("getDependencyFileCount"),&slang_ICompileRequest::getDependencyFileCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getDependencyFilePath","index"),&slang_ICompileRequest::getDependencyFilePath);
            godot::ClassDB::bind_method(godot::D_METHOD("getTranslationUnitCount"),&slang_ICompileRequest::getTranslationUnitCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointSource","entryPointIndex"),&slang_ICompileRequest::getEntryPointSource);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointCodeBlob", "entryPointIndex","targetIndex","outBlob"), &slang_ICompileRequest::getEntryPointCodeBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPointHostCallable","entryPointIndex","targetIndex","outCallable"), &slang_ICompileRequest::getEntryPointHostCallable);
            godot::ClassDB::bind_method(godot::D_METHOD("getTargetCodeBlob","targetIndex","outBlob"), &slang_ICompileRequest::getTargetCodeBlob);
            godot::ClassDB::bind_method(godot::D_METHOD("getTargetHostCallable","targetIndex","outSharedLibrary"), &slang_ICompileRequest::getTargetHostCallable);
            godot::ClassDB::bind_method(godot::D_METHOD("getCompileRequestResultAsFileSystem"),&slang_ICompileRequest::getCompileRequestResultAsFileSystem);
            godot::ClassDB::bind_method(godot::D_METHOD("getContainerCode","outBlob"), &slang_ICompileRequest::getContainerCode);
            godot::ClassDB::bind_method(godot::D_METHOD("loadRepro","fileSystem","data","size"), &slang_ICompileRequest::loadRepro);
            godot::ClassDB::bind_method(godot::D_METHOD("saveRepro","outBlob"), &slang_ICompileRequest::saveRepro);
            godot::ClassDB::bind_method(godot::D_METHOD("enableReproCapture"), &slang_ICompileRequest::enableReproCapture);
            godot::ClassDB::bind_method(godot::D_METHOD("getProgram","outProgram"), &slang_ICompileRequest::getProgram);
            godot::ClassDB::bind_method(godot::D_METHOD("getEntryPoint", "entryPointIndex","outEntryPoint"), &slang_ICompileRequest::getEntryPoint);
            godot::ClassDB::bind_method(godot::D_METHOD("getModule","translationUnitIndex","outModule"),&slang_ICompileRequest::getModule);
            godot::ClassDB::bind_method(godot::D_METHOD("getSession","outSession"),&slang_ICompileRequest::getSession);
            godot::ClassDB::bind_method(godot::D_METHOD("getReflection"),&slang_ICompileRequest::getReflection);
            godot::ClassDB::bind_method(godot::D_METHOD("setCommandLineCompilerMode"),&slang_ICompileRequest::setCommandLineCompilerMode);
            godot::ClassDB::bind_method(godot::D_METHOD("addTargetCapability","targetIndex","capability"),&slang_ICompileRequest::addTargetCapability);
            godot::ClassDB::bind_method(godot::D_METHOD("getProgramWithEntryPoints","outProgram"),&slang_ICompileRequest::getProgramWithEntryPoints);
            godot::ClassDB::bind_method(godot::D_METHOD("isParameterLocationUsed","entryPointIndex","targetIndex","category","spaceIndex","registerIndex","outUsed"),&slang_ICompileRequest::isParameterLocationUsed);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetLineDirectiveMode","targetIndex","mode"),&slang_ICompileRequest::setTargetLineDirectiveMode);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetForceGLSLScalarBufferLayout","targetIndex","forceScalarLayout"),&slang_ICompileRequest::setTargetForceGLSLScalarBufferLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("overrideDiagnosticSeverity","messageID","overrideSeverity"),&slang_ICompileRequest::overrideDiagnosticSeverity);
            godot::ClassDB::bind_method(godot::D_METHOD("getDiagnosticFlags"),&slang_ICompileRequest::getDiagnosticFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("setDiagnosticFlags","flags"),&slang_ICompileRequest::setDiagnosticFlags);
            godot::ClassDB::bind_method(godot::D_METHOD("setDebugInfoFormat","format"),&slang_ICompileRequest::setDebugInfoFormat);
            godot::ClassDB::bind_method(godot::D_METHOD("setEnableEffectAnnotations","value"),&slang_ICompileRequest::setEnableEffectAnnotations);
            godot::ClassDB::bind_method(godot::D_METHOD("setReportDownstreamTime","value"),&slang_ICompileRequest::setReportDownstreamTime);
            godot::ClassDB::bind_method(godot::D_METHOD("setReportPerfBenchmark","value"),&slang_ICompileRequest::setReportPerfBenchmark);
            godot::ClassDB::bind_method(godot::D_METHOD("setSkipSPIRVValidation","value"),&slang_ICompileRequest::setSkipSPIRVValidation);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetUseMinimumSlangOptimization","targetIndex","value"),&slang_ICompileRequest::setTargetUseMinimumSlangOptimization);
            godot::ClassDB::bind_method(godot::D_METHOD("setIgnoreCapabilityCheck","value"),&slang_ICompileRequest::setIgnoreCapabilityCheck);
            godot::ClassDB::bind_method(godot::D_METHOD("getCompileTimeProfile","compileTimeProfile","shouldClear"),&slang_ICompileRequest::getCompileTimeProfile, &slang_ICompileRequest::getCompileTimeProfile);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetGenerateWholeProgram","targetIndex","value"),&slang_ICompileRequest::setTargetGenerateWholeProgram);
            godot::ClassDB::bind_method(godot::D_METHOD("setTargetEmbedDXIL","targetIndex","value"),&slang_ICompileRequest::setTargetEmbedDXIL);
        }
    public:
        void setFileSystem(slang_IFileSystem* fileSystem){
            return this->ICompileRequest::setFileSystem(static_cast<ISlangFileSystem *>(fileSystem));
        }
        void setCompileFlags(slang_SlangCompileFlags compileFlags){
            return this->ICompileRequest::setCompileFlags(static_cast<SlangCompileFlags>(compileFlags));
        }
        SlangCompileFlags getCompileFlags(){
            return this->ICompileRequest::getCompileFlags();
        }
        void setDumpIntermediates(int enable){
            return this->ICompileRequest::setDumpIntermediates(enable);
        }
        void setDumpIntermediatePrefix(godot::String prefix){
            return this->ICompileRequest::setDumpIntermediatePrefix(prefix.utf8().get_data());
        }
        void setLineDirectiveMode(slang_SlangLineDirectiveMode mode){
            return this->ICompileRequest::setLineDirectiveMode(static_cast<SlangLineDirectiveMode>(mode));
        }
        void setCodeGenTarget(slang_SlangCompileTarget target){
            return this->ICompileRequest::setCodeGenTarget(static_cast<SlangCompileTarget>(target));
        }
        int addCodeGenTarget(slang_SlangCompileTarget target){
            return this->ICompileRequest::addCodeGenTarget(static_cast<SlangCompileTarget>(target));
        }
        void setTargetProfile(int targetIndex,slang_SlangProfileID profile){
            return this->ICompileRequest::setTargetProfile(targetIndex,static_cast<SlangProfileID>(profile));
        }
        void setTargetFlags(int targetIndex,slang_SlangTargetFlags flags){
            return this->ICompileRequest::setTargetFlags(targetIndex,static_cast<SlangTargetFlags>(flags));
        }
        void setTargetFloatingPointMode(int targetIndex,slang_SlangFloatingPointMode mode){
            return this->ICompileRequest::setTargetFloatingPointMode(targetIndex,static_cast<SlangFloatingPointMode>(mode));
        }
        void setTargetMatrixLayoutMode(int targetIndex,slang_SlangMatrixLayoutMode mode){
            return this->ICompileRequest::setTargetMatrixLayoutMode(targetIndex,static_cast<SlangMatrixLayoutMode>(mode));
        }
        void setMatrixLayoutMode(slang_SlangMatrixLayoutMode mode){
            return this->ICompileRequest::setMatrixLayoutMode(static_cast<SlangMatrixLayoutMode>(mode));
        }
        void setDebugInfoLevel(slang_SlangDebugInfoLevel level){
            return this->ICompileRequest::setDebugInfoLevel(static_cast<SlangDebugInfoLevel>(level));
        }
        void setOptimizationLevel(slang_SlangOptimizationLevel level){
            return this->ICompileRequest::setOptimizationLevel(static_cast<SlangOptimizationLevel>(level));
        }
        void setOutputContainerFormat(slang_SlangContainerFormat format){
            return this->ICompileRequest::setOutputContainerFormat(static_cast<SlangContainerFormat>(format));
        }
        void setPassThrough(slang_SlangPassThrough passThrough){
            return this->ICompileRequest::setPassThrough(static_cast<SlangPassThrough>(passThrough));
        }
        void setDiagnosticCallback(SlangDiagnosticCallback callback, slang_PTR<void>* userData){
            return this->ICompileRequest::setDiagnosticCallback(callback,userData);
        }
        void setWriter(slang_SlangWriterChannel channel, slang_IWriter* writer){
            return this->ICompileRequest::setWriter(static_cast<SlangWriterChannel>(channel),static_cast<ISlangWriter *>(writer));
        }
        slang_IWriter* getWriter(slang_SlangWriterChannel channel) {
            return static_cast<slang_IWriter *>(this->ICompileRequest::getWriter(
                    static_cast<SlangWriterChannel>(channel)));
        }
        void addSearchPath(godot::String path){
            return this->ICompileRequest::addSearchPath(path.utf8().get_data());
        }
        void addPreprocessorDefine(godot::String key, godot::String value){
            return this->ICompileRequest::addPreprocessorDefine(key.utf8().get_data(),value.utf8().get_data());
        }
        SlangResult processCommandLineArguments(godot::TypedArray<godot::String> args, int argCount){
            const char* argv[argCount];
            for(int i = 0; i < argCount; i++){
                argv[i] = args[i].operator godot::String().utf8().get_data();
            }
            return this->ICompileRequest::processCommandLineArguments(argv,argCount);
        }
        int addTranslationUnit(slang_SlangSourceLanguage language,godot::String name){
            return this->ICompileRequest::addTranslationUnit(static_cast<SlangSourceLanguage>(language), name.utf8().get_data());
        }
        void setDefaultModuleName(godot::String defaultModuleName){
            return this->ICompileRequest::setDefaultModuleName(defaultModuleName.utf8().get_data());
        }
        void addTranslationUnitPreprocessorDefine(int translationUnitIndex,godot::String key, godot::String value){
            return this->ICompileRequest::addTranslationUnitPreprocessorDefine(translationUnitIndex,key.utf8().get_data(),value.utf8().get_data());
        }
        void addTranslationUnitSourceFile(int translationUnitIndex,godot::String path){
            return this->ICompileRequest::addTranslationUnitSourceFile(translationUnitIndex,path.utf8().get_data());
        }
        void addTranslationUnitSourceString(int translationUnitIndex,godot::String path,godot::String source){
            return this->ICompileRequest::addTranslationUnitSourceString(translationUnitIndex,path.utf8().get_data(),source.utf8().get_data());
        }
        SlangResult addLibraryReference(godot::String path, slang_PTR<void>* libData,size_t libDataSize){
            return this->ICompileRequest::addLibraryReference(path.utf8().get_data(),libData->get_value(),libDataSize);
        }
        void addTranslationUnitSourceStringSpan(int translationUnitIndex,godot::String path,godot::String sourceBegin,godot::String sourceEnd){
            return this->ICompileRequest::addTranslationUnitSourceStringSpan(translationUnitIndex,path.utf8().get_data(),sourceBegin.utf8().get_data(),sourceEnd.utf8().get_data());
        }
        void addTranslationUnitSourceBlob(int translationUnitIndex,godot::String path,slang_IBlob* sourceBlob){
            return this->ICompileRequest::addTranslationUnitSourceBlob(translationUnitIndex,path.utf8().get_data(),static_cast<ISlangBlob *>(sourceBlob));
        }
        int addEntryPoint(int translationUnitIndex,godot::String name,slang_SlangStage stage){
            return this->ICompileRequest::addEntryPoint(translationUnitIndex,name.utf8().get_data(),static_cast<SlangStage>(stage));
        }
        int addEntryPointEx(int translationUnitIndex,godot::String name,slang_SlangStage stage,int genericArgCount,godot::TypedArray<godot::String>genericArgs){
            const char* args[genericArgCount];
            for(int i = 0; i < genericArgCount; i++) {
                args[i] = genericArgs[i].operator godot::String().utf8().get_data();
            }
            return this->ICompileRequest::addEntryPointEx(translationUnitIndex,name.utf8().get_data(),static_cast<SlangStage>(stage),genericArgCount,args);
        }
        SlangResult setGlobalGenericArgs(int genericArgCount,godot::TypedArray<godot::String>genericArgs){
            const char* args[genericArgCount];
            for(int i = 0; i < genericArgCount; i++) {
                args[i] = genericArgs[i].operator godot::String().utf8().get_data();
            }
            return this->ICompileRequest::setGlobalGenericArgs(genericArgCount,args);
        }
        SlangResult setTypeNameForGlobalExistentialTypeParam(int typeParamIndex,godot::String typeName){
            return this->ICompileRequest::setTypeNameForGlobalExistentialTypeParam(typeParamIndex,typeName.utf8().get_data());
        }
        SlangResult setTypeNameForEntryPointExistentialTypeParam(int entryPointIndex,int slotIndex,godot::String typeName){
            return this->ICompileRequest::setTypeNameForEntryPointExistentialTypeParam(entryPointIndex,slotIndex,typeName.utf8().get_data());
        }
        void setAllowGLSLInput(bool value){
            return this->ICompileRequest::setAllowGLSLInput(value);
        }
        SlangResult compile(){
            return this->ICompileRequest::compile();
        }
        godot::String getDiagnosticOutput(slang_NULL* null){
            return godot::String().utf8(this->ICompileRequest::getDiagnosticOutput());
        }
        SlangResult getDiagnosticOutputBlob(slang_PTR<slang_IBlob*>* outBlob){
            return this->ICompileRequest::getDiagnosticOutputBlob(reinterpret_cast<ISlangBlob **>(outBlob->get_value()));
        }
        int SLANG_MCALL getDependencyFileCount(){
            return this->ICompileRequest::getDependencyFileCount();
        }
        godot::String getDependencyFilePath(int index,slang_NULL*null){
            return godot::String().utf8(this->ICompileRequest::getDependencyFilePath(index));
        }
        int getTranslationUnitCount(){
            return this->ICompileRequest::getTranslationUnitCount();
        }
        godot::String getEntryPointSource(int entryPointIndex,slang_NULL*null){
            return godot::String().utf8(this->ICompileRequest::getEntryPointSource(entryPointIndex));
        }
        const void* getEntryPointCode(int entryPointIndex,slang_INT<size_t>* outSize){
            size_t size = 0;
            auto res = this->ICompileRequest::getEntryPointCode(entryPointIndex, &size);
            outSize->set_value(size);
            return res;
        }
        SlangResult getEntryPointCodeBlob(int entryPointIndex,int targetIndex,slang_PTR<slang_IBlob*>* outBlob){
            return this->ICompileRequest::getEntryPointCodeBlob(entryPointIndex,targetIndex,reinterpret_cast<ISlangBlob **>(outBlob->get_value()));
        }
        SlangResult getEntryPointHostCallable(int entryPointIndex,int targetIndex,slang_PTR<slang_ISharedLibrary*>* outCallable){
            return this->ICompileRequest::getEntryPointHostCallable(entryPointIndex,targetIndex,reinterpret_cast<ISlangSharedLibrary **>(outCallable->get_value()));
        }
        SlangResult getTargetCodeBlob(int targetIndex,slang_PTR<slang_IBlob*>* outBlob){
            return this->ICompileRequest::getTargetCodeBlob(targetIndex,reinterpret_cast<ISlangBlob **>(outBlob->get_value()));
        }
        SlangResult getTargetHostCallable(int targetIndex,slang_PTR<slang_ISharedLibrary*>* outCallable){
            return this->ICompileRequest::getTargetHostCallable(targetIndex,reinterpret_cast<ISlangSharedLibrary **>(outCallable->get_value()));
        }
        const void* getCompileRequestCode(slang_INT<size_t>* outSize){
            size_t size = 0;
            auto res = this->ICompileRequest::getCompileRequestCode(&size);
            outSize->set_value(size);
            return res;
        }
        slang_IMutableFileSystem* getCompileRequestResultAsFileSystem(){
            return static_cast<slang_IMutableFileSystem *>(this->ICompileRequest::getCompileRequestResultAsFileSystem());
        }
        SlangResult getContainerCode(slang_PTR<slang_IBlob*>* outBlob){
            return this->ICompileRequest::getContainerCode(reinterpret_cast<ISlangBlob **>(outBlob->get_value()));
        }
        SlangResult loadRepro(slang_IFileSystem* fileSystem,slang_PTR<const void>* data,size_t size){
            return this->ICompileRequest::loadRepro(static_cast<ISlangFileSystem *>(fileSystem),data->get_value(),size);
        }
        SlangResult saveRepro(slang_PTR<slang_IBlob*>* blob){
            return this->ICompileRequest::saveRepro(reinterpret_cast<ISlangBlob **>(blob->get_value()));
        }
        SlangResult enableReproCapture(){
            return this->ICompileRequest::enableReproCapture();
        }
        SlangResult getProgram(slang_PTR<slang_IComponentType*>* outProgram){
            return this->ICompileRequest::getProgram(reinterpret_cast<slang::IComponentType **>(outProgram->get_value()));
        }
        SlangResult getEntryPoint(SlangInt entryPointIndex, slang_PTR<slang_IComponentType*>* outEntryPoint){
            return this->ICompileRequest::getEntryPoint(entryPointIndex, reinterpret_cast<slang::IComponentType **>(outEntryPoint->get_value()));
        }
        SlangResult getModule(SlangInt translationUnitIndex, slang_PTR<slang_IModule*>* outModule){
            return this->ICompileRequest::getModule(translationUnitIndex, reinterpret_cast<slang::IModule **>(outModule->get_value()));
        }
        SlangResult getSession(slang_PTR<slang_ISession*>* outSession){
            return this->ICompileRequest::getSession(reinterpret_cast<slang::ISession **>(outSession->get_value()));
        }
        slang_ProgramLayout* getReflection(slang_NULL* null){
            this->ICompileRequest::getReflection();
            return nullptr;
        }
        void setCommandLineCompilerMode(){
            return this->ICompileRequest::setCommandLineCompilerMode();
        }
        SlangResult addTargetCapability(SlangInt capability,slang_SlangCapabilityID capabilityID){
            return this->ICompileRequest::addTargetCapability(capability,static_cast<SlangCapabilityID>(capabilityID));
        }
        SlangResult getProgramWithEntryPoints(slang_PTR<slang_IComponentType*>* outProgram){
            return this->ICompileRequest::getProgramWithEntryPoints(reinterpret_cast<slang::IComponentType **>(outProgram->get_value()));
        }
        SlangResult isParameterLocationUsed(SlangInt entryPointIndex, SlangInt targetIndex, slang_SlangParameterCategory category,SlangUInt spaceIndex, SlangUInt registerIndex, slang_BOOL* outUsed){
            bool used = 0;
            auto res = this->ICompileRequest::isParameterLocationUsed(entryPointIndex, targetIndex, static_cast<SlangParameterCategory>(category), spaceIndex, registerIndex, used);
            outUsed->set_value(used);
            return res;
        }
        void setTargetLineDirectiveMode(SlangInt targetIndex, slang_SlangLineDirectiveMode mode){
            return this->ICompileRequest::setTargetLineDirectiveMode(targetIndex, static_cast<SlangLineDirectiveMode>(mode));
        }
        void setTargetForceGLSLScalarBufferLayout(int targetIndex, bool forceScalarLayout){
            return this->ICompileRequest::setTargetForceGLSLScalarBufferLayout(targetIndex, forceScalarLayout);
        }
        void overrideDiagnosticSeverity(SlangInt messageID, slang_SlangSeverity overrideSeverity){
            return this->ICompileRequest::overrideDiagnosticSeverity(messageID, static_cast<SlangSeverity>(overrideSeverity));
        }
        int getDiagnosticFlags(){
            return this->ICompileRequest::getDiagnosticFlags();
        }
        void setDiagnosticFlags(int flags){
            return this->ICompileRequest::setDiagnosticFlags(flags);
        }
        void setDebugInfoFormat(slang_SlangDebugInfoFormat debugFormat){
            return this->ICompileRequest::setDebugInfoFormat(static_cast<SlangDebugInfoFormat>(debugFormat));
        }
        void setEnableEffectAnnotations(bool value){
            return this->ICompileRequest::setEnableEffectAnnotations(value);
        }
        void setReportDownstreamTime(bool value){
            return this->ICompileRequest::setReportDownstreamTime(value);
        }
        void setReportPerfBenchmark(bool value){
            return this->ICompileRequest::setReportPerfBenchmark(value);
        }
        void setSkipSPIRVValidation(bool value){
            return this->ICompileRequest::setSkipSPIRVValidation(value);
        }
        void setTargetUseMinimumSlangOptimization(int targetIndex, bool value){
            return this->ICompileRequest::setTargetUseMinimumSlangOptimization(targetIndex, value);
        }
        void setIgnoreCapabilityCheck(bool value){
            return this->ICompileRequest::setIgnoreCapabilityCheck(value);
        }
        SlangResult getCompileTimeProfile(slang_PTR<slang_IProfiler*>* outProfile,bool shouldClear){
            return this->ICompileRequest::getCompileTimeProfile(reinterpret_cast<ISlangProfiler **>(outProfile->get_value()), shouldClear);
        }
        void setTargetGenerateWholeProgram(int targetIndex, bool value){
            return this->ICompileRequest::setTargetGenerateWholeProgram(targetIndex, value);
        }
        void setTargetEmbedDXIL(int targetIndex, bool value){
            return this->ICompileRequest::setTargetEmbedDXIL(targetIndex, value);
        }
    };

    class slang_UUID : public slang_SlangObject {
    GDCLASS(slang_UUID, slang_SlangObject)
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

    class slang_CompilerOptionValue : public slang_SlangObject, public slang::CompilerOptionValue {
    GDCLASS(slang_CompilerOptionValue, slang_SlangObject)

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
            this->kind = (slang::CompilerOptionValueKind) kind;
        }

        int get_intValue0() {
            return intValue0;
        }

        void set_intValue0(int intValue1) {
            this->intValue0 = intValue1;
        }

        int get_intValue1() {
            return intValue1;
        }

        void set_intValue1(int intValue1) {
            this->intValue1 = intValue1;
        }

        godot::String get_stringValue0() {
            return godot::String().utf8(stringValue0);
        }

        void set_stringValue0(godot::String str) {
            this->stringValue0 = str.utf8().get_data();
        }

        godot::String get_stringValue1() {
            return godot::String().utf8(stringValue1);
        }

        void set_stringValue1(godot::String str) {
            this->stringValue1 = str.utf8().get_data();
        }
    };

    class slang_CompilerOptionEntry : public slang_SlangObject, public slang::CompilerOptionEntry {
    GDCLASS(slang_CompilerOptionEntry, slang_SlangObject)
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
            godot::ClassDB::add_property("slang_CompilerOptionEntry",
                                         godot::PropertyInfo(godot::Variant::OBJECT, "value"), "set_value",
                                         "get_value");
        }

    public:
        slang_CompilerOptionName get_name() {
            return (slang_CompilerOptionName) name;
        }

        void set_name(slang_CompilerOptionName name) {
            this->name = (slang::CompilerOptionName) name;
        }

        slang_CompilerOptionValue *get_value();

        void set_value(slang_CompilerOptionValue *value);

    };

    class slang_PreprocessorMacroDesc : public slang_SlangObject, public slang::PreprocessorMacroDesc {
    GDCLASS(slang_PreprocessorMacroDesc, slang_SlangObject)
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
        godot::String get_name() {
            return name;
        }

        void set_name(godot::String name) {
            this->name = name.utf8().get_data();
        }

        godot::String get_value() {
            return godot::String().utf8(value);
        }

        void set_value(godot::String value) {
            this->value = value.utf8().get_data();
        }
    };

    class slang_TargetDesc : public slang_SlangObject, public slang::TargetDesc {
    GDCLASS(slang_TargetDesc, slang_SlangObject)
    private:
        static void _bind_methods() {

            godot::ClassDB::bind_method(godot::D_METHOD("set_structureSize", "structureSize"),
                                        &slang_TargetDesc::set_structureSize);
            godot::ClassDB::bind_method(godot::D_METHOD("get_structureSize"), &slang_TargetDesc::get_structureSize);
            godot::ClassDB::add_property("slang_TargetDesc", godot::PropertyInfo(godot::Variant::INT, "structureSize"),
                                         "set_structureSize", "get_structureSize");

            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_TARGET_UNKNOWN)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_TARGET_NONE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_GLSL)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_GLSL_VULKAN_DEPRECATED)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_GLSL_VULKAN_ONE_DESC_DEPRECATED)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_HLSL)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_SPIRV)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_SPIRV_ASM)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_DXBC)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_DXBC_ASM)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_DXIL)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_DXIL_ASM)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_C_SOURCE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_CPP_SOURCE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_HOST_EXECUTABLE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_SHADER_SHARED_LIBRARY)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_SHADER_HOST_CALLABLE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_CUDA_SOURCE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_PTX)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_CUDA_OBJECT_CODE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_OBJECT_CODE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_HOST_CPP_SOURCE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_HOST_HOST_CALLABLE)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_CPP_PYTORCH_BINDING)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_METAL)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_METAL_LIB)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_METAL_LIB_ASM)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_HOST_SHARED_LIBRARY)
            BIND_ENUM_CONSTANT(slang_SlangCompileTarget::SLANG_TARGET_COUNT_OF)

            godot::ClassDB::bind_method(godot::D_METHOD("set_format", "format"), &slang_TargetDesc::set_format);
            godot::ClassDB::bind_method(godot::D_METHOD("get_format"), &slang_TargetDesc::get_format);
            godot::ClassDB::add_property("slang_TargetDesc",
                                         godot::PropertyInfo(godot::Variant::INT, "format", godot::PROPERTY_HINT_ENUM,
                                                             "SLANG_TARGET_UNKNOWN,SLANG_TARGET_NONE,SLANG_GLSL,SLANG_GLSL_VULKAN_DEPRECATED,"
                                                             "SLANG_GLSL_VULKAN_ONE_DESC_DEPRECATED,SLANG_HLSL,SLANG_SPIRV,SLANG_SPIRV_ASM,"
                                                             "SLANG_DXBC,SLANG_DXBC_ASM,SLANG_DXIL,SLANG_DXIL_ASM,SLANG_C_SOURCE,SLANG_CPP_SOURCE,"
                                                             "SLANG_HOST_EXECUTABLE,SLANG_SHADER_SHARED_LIBRARY,SLANG_SHADER_HOST_CALLABLE,"
                                                             "SLANG_CUDA_SOURCE,SLANG_PTX,SLANG_CUDA_OBJECT_CODE,SLANG_OBJECT_CODE,"
                                                             "SLANG_HOST_CPP_SOURCE,SLANG_HOST_HOST_CALLABLE,SLANG_CPP_PYTORCH_BINDING,"
                                                             "SLANG_METAL,SLANG_METAL_LIB,SLANG_METAL_LIB_ASM,SLANG_HOST_SHARED_LIBRARY,"
                                                             "SLANG_TARGET_COUNT_OF"
                                         ), "set_format", "get_format");

            BIND_ENUM_CONSTANT(slang_SlangProfileID::SLANG_PROFILE_UNKNOWN)

            godot::ClassDB::bind_method(godot::D_METHOD("set_profile", "profile"), &slang_TargetDesc::set_profile);
            godot::ClassDB::bind_method(godot::D_METHOD("get_profile"), &slang_TargetDesc::get_profile);
            godot::ClassDB::add_property("slang_TargetDesc",
                                         godot::PropertyInfo(godot::Variant::INT, "profile", godot::PROPERTY_HINT_ENUM,
                                                             "SLANG_PROFILE_UNKNOWN"
                                         ), "set_profile", "get_profile");

            godot::ClassDB::bind_method(godot::D_METHOD("set_flags", "flags"), &slang_TargetDesc::set_flags);
            godot::ClassDB::bind_method(godot::D_METHOD("get_flags"), &slang_TargetDesc::get_flags);
            godot::ClassDB::add_property("slang_TargetDesc", godot::PropertyInfo(godot::Variant::INT, "flags"),
                                         "set_flags", "get_flags");

            BIND_ENUM_CONSTANT(slang_SlangFloatingPointMode::SLANG_FLOATING_POINT_MODE_DEFAULT)
            BIND_ENUM_CONSTANT(slang_SlangFloatingPointMode::SLANG_FLOATING_POINT_MODE_FAST)
            BIND_ENUM_CONSTANT(slang_SlangFloatingPointMode::SLANG_FLOATING_POINT_MODE_PRECISE)

            godot::ClassDB::bind_method(godot::D_METHOD("set_floatingPointMode", "floatingPointMode"),
                                        &slang_TargetDesc::set_floatingPointMode);
            godot::ClassDB::bind_method(godot::D_METHOD("get_floatingPointMode"),
                                        &slang_TargetDesc::get_floatingPointMode);
            godot::ClassDB::add_property("slang_TargetDesc",
                                         godot::PropertyInfo(godot::Variant::INT, "floatingPointMode",
                                                             godot::PROPERTY_HINT_ENUM,
                                                             "SLANG_FLOATING_POINT_MODE_DEFAULT,SLANG_FLOATING_POINT_MODE_FAST,SLANG_FLOATING_POINT_MODE_PRECISE"
                                         ), "set_floatingPointMode", "get_floatingPointMode");

            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_DEFAULT)
            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_NONE)
            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_STANDARD)
            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_GLSL)
            BIND_ENUM_CONSTANT(slang_SlangLineDirectiveMode::SLANG_LINE_DIRECTIVE_MODE_SOURCE_MAP)

            godot::ClassDB::bind_method(godot::D_METHOD("set_lineDirectiveMode", "lineDirectiveMode"),
                                        &slang_TargetDesc::set_lineDirectiveMode);
            godot::ClassDB::bind_method(godot::D_METHOD("get_lineDirectiveMode"),
                                        &slang_TargetDesc::get_lineDirectiveMode);
            godot::ClassDB::add_property("slang_TargetDesc",
                                         godot::PropertyInfo(godot::Variant::INT, "lineDirectiveMode",
                                                             godot::PROPERTY_HINT_ENUM,
                                                             "SLANG_LINE_DIRECTIVE_MODE_DEFAULT,SLANG_LINE_DIRECTIVE_MODE_NONE,SLANG_LINE_DIRECTIVE_MODE_STANDARD,"
                                                             "SLANG_LINE_DIRECTIVE_MODE_GLSL,SLANG_LINE_DIRECTIVE_MODE_SOURCE_MAP"
                                         ), "set_lineDirectiveMode", "get_lineDirectiveMode");

            godot::ClassDB::bind_method(
                    godot::D_METHOD("set_forceGLSLScalarBufferLayout", "forceGLSLScalarBufferLayout"),
                    &slang_TargetDesc::set_forceGLSLScalarBufferLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("get_forceGLSLScalarBufferLayout"),
                                        &slang_TargetDesc::get_forceGLSLScalarBufferLayout);
            godot::ClassDB::add_property("slang_TargetDesc",
                                         godot::PropertyInfo(godot::Variant::BOOL, "forceGLSLScalarBufferLayout"),
                                         "set_forceGLSLScalarBufferLayout", "get_forceGLSLScalarBufferLayout");

            godot::ClassDB::bind_method(godot::D_METHOD("set_compilerOptionEntries", "compilerOptionEntries"),
                                        &slang_TargetDesc::set_compilerOptionEntries);
            godot::ClassDB::bind_method(godot::D_METHOD("get_compilerOptionEntries"),
                                        &slang_TargetDesc::get_compilerOptionEntries);
            godot::ClassDB::add_property("slang_TargetDesc",
                                         godot::PropertyInfo(godot::Variant::OBJECT, "compilerOptionEntries"),
                                         "set_compilerOptionEntries", "get_compilerOptionEntries");

            godot::ClassDB::bind_method(godot::D_METHOD("set_compilerOptionEntryCount", "compilerOptionEntryCount"),
                                        &slang_TargetDesc::set_compilerOptionEntryCount);
            godot::ClassDB::bind_method(godot::D_METHOD("get_compilerOptionEntryCount"),
                                        &slang_TargetDesc::get_compilerOptionEntryCount);
            godot::ClassDB::add_property("slang_TargetDesc",
                                         godot::PropertyInfo(godot::Variant::INT, "compilerOptionEntryCount"),
                                         "set_compilerOptionEntryCount", "get_compilerOptionEntryCount");

        }

    public:
        size_t get_structureSize() {
            return structureSize;
        }

        void set_structureSize(size_t size) {
            this->structureSize = size;
        }

        slang_SlangCompileTarget get_format() {
            return (slang_SlangCompileTarget) format;
        }

        void set_format(slang_SlangCompileTarget format) {
            this->format = (SlangCompileTarget) format;
        }

        slang_SlangProfileID get_profile() {
            return (slang_SlangProfileID) profile;
        }

        void set_profile(slang_SlangProfileID profile) {
            this->profile = (SlangProfileID) profile;
        }

        unsigned int get_flags() {
            return flags;
        }

        void set_flags(unsigned int flags) {
            this->flags = flags;
        }

        int get_floatingPointMode() {
            return (int) floatingPointMode;
        }

        void set_floatingPointMode(int floatingPointMode) {
            this->floatingPointMode = (SlangFloatingPointMode) floatingPointMode;
        }

        slang_SlangLineDirectiveMode get_lineDirectiveMode() {
            return (slang_SlangLineDirectiveMode) lineDirectiveMode;
        }

        void set_lineDirectiveMode(slang_SlangLineDirectiveMode lineDirectiveMode) {
            this->lineDirectiveMode = (SlangLineDirectiveMode) lineDirectiveMode;
        }

        bool get_forceGLSLScalarBufferLayout() {
            return forceGLSLScalarBufferLayout;
        }

        void set_forceGLSLScalarBufferLayout(bool forceGLSLScalarBufferLayout) {
            this->forceGLSLScalarBufferLayout = forceGLSLScalarBufferLayout;
        }

        slang_CompilerOptionEntry *get_compilerOptionEntries();

        void set_compilerOptionEntries(slang_CompilerOptionEntry *compilerOptionEntries);

        uint32_t get_compilerOptionEntryCount() {
            return compilerOptionEntryCount;
        }

        void set_compilerOptionEntryCount(uint32_t compilerOptionEntryCount) {
            this->compilerOptionEntryCount = compilerOptionEntryCount;
        }
    };

    class slang_SessionDesc : public slang_SlangObject, public slang::SessionDesc {
    GDCLASS(slang_SessionDesc, slang_SlangObject)
    private:
        static void _bind_methods() {

            godot::ClassDB::bind_method(godot::D_METHOD("set_structureSize", "structureSize"),
                                        &slang_SessionDesc::set_structureSize);
            godot::ClassDB::bind_method(godot::D_METHOD("get_structureSize"), &slang_SessionDesc::get_structureSize);
            godot::ClassDB::add_property("slang_SessionDesc", godot::PropertyInfo(godot::Variant::INT, "structureSize"),
                                         "set_structureSize", "get_structureSize");

            godot::ClassDB::bind_method(godot::D_METHOD("set_targets", "targets"), &slang_SessionDesc::set_targets);
            godot::ClassDB::bind_method(godot::D_METHOD("get_targets"), &slang_SessionDesc::get_targets);
            godot::ClassDB::add_property("slang_SessionDesc", godot::PropertyInfo(godot::Variant::OBJECT, "targets"),
                                         "set_targets", "get_targets");

            godot::ClassDB::bind_method(godot::D_METHOD("set_targetCount", "targetCount"),
                                        &slang_SessionDesc::set_targetCount);
            godot::ClassDB::bind_method(godot::D_METHOD("get_targetCount"), &slang_SessionDesc::get_targetCount);
            godot::ClassDB::add_property("slang_SessionDesc", godot::PropertyInfo(godot::Variant::INT, "targetCount"),
                                         "set_targetCount", "get_targetCount");

            godot::ClassDB::bind_method(godot::D_METHOD("set_flags", "flags"), &slang_SessionDesc::set_flags);
            godot::ClassDB::bind_method(godot::D_METHOD("get_flags"), &slang_SessionDesc::get_flags);
            godot::ClassDB::add_property("slang_SessionDesc", godot::PropertyInfo(godot::Variant::INT, "flags"),
                                         "set_flags", "get_flags");

            BIND_ENUM_CONSTANT(slang_SlangMatrixLayoutMode::SLANG_MATRIX_LAYOUT_MODE_UNKNOWN)
            BIND_ENUM_CONSTANT(slang_SlangMatrixLayoutMode::SLANG_MATRIX_LAYOUT_ROW_MAJOR)
            BIND_ENUM_CONSTANT(slang_SlangMatrixLayoutMode::SLANG_MATRIX_LAYOUT_COLUMN_MAJOR)


            godot::ClassDB::bind_method(godot::D_METHOD("set_defaultMatrixLayoutMode", "defaultMatrixLayoutMode"),
                                        &slang_SessionDesc::set_defaultMatrixLayoutMode);
            godot::ClassDB::bind_method(godot::D_METHOD("get_defaultMatrixLayoutMode"),
                                        &slang_SessionDesc::get_defaultMatrixLayoutMode);
            godot::ClassDB::add_property("slang_SessionDesc",
                                         godot::PropertyInfo(godot::Variant::INT, "defaultMatrixLayoutMode",
                                                             godot::PROPERTY_HINT_ENUM,
                                                             "SLANG_MATRIX_LAYOUT_MODE_UNKNOWN,SLANG_MATRIX_LAYOUT_ROW_MAJOR,SLANG_MATRIX_LAYOUT_COLUMN_MAJOR"
                                         ), "set_defaultMatrixLayoutMode", "get_defaultMatrixLayoutMode");

            godot::ClassDB::bind_method(godot::D_METHOD("set_preprocessorMacros", "preprocessorMacros"),
                                        &slang_SessionDesc::set_preprocessorMacros);
            godot::ClassDB::bind_method(godot::D_METHOD("get_preprocessorMacros"),
                                        &slang_SessionDesc::get_preprocessorMacros);
            godot::ClassDB::add_property("slang_SessionDesc",
                                         godot::PropertyInfo(godot::Variant::OBJECT, "preprocessorMacros"),
                                         "set_preprocessorMacros", "get_preprocessorMacros");

            godot::ClassDB::bind_method(godot::D_METHOD("set_preprocessorMacroCount", "preprocessorMacroCount"),
                                        &slang_SessionDesc::set_preprocessorMacroCount);
            godot::ClassDB::bind_method(godot::D_METHOD("get_preprocessorMacroCount"),
                                        &slang_SessionDesc::get_preprocessorMacroCount);
            godot::ClassDB::add_property("slang_SessionDesc",
                                         godot::PropertyInfo(godot::Variant::INT, "preprocessorMacroCount"),
                                         "set_preprocessorMacroCount", "get_preprocessorMacroCount");

            godot::ClassDB::bind_method(godot::D_METHOD("set_fileSystem", "fileSystem"),
                                        &slang_SessionDesc::set_fileSystem);
            godot::ClassDB::bind_method(godot::D_METHOD("get_fileSystem"), &slang_SessionDesc::get_fileSystem);
            godot::ClassDB::add_property("slang_SessionDesc", godot::PropertyInfo(godot::Variant::OBJECT, "fileSystem"),
                                         "set_fileSystem", "get_fileSystem");

            godot::ClassDB::bind_method(godot::D_METHOD("set_enableEffectAnnotations", "enableEffectAnnotations"),
                                        &slang_SessionDesc::set_enableEffectAnnotations);
            godot::ClassDB::bind_method(godot::D_METHOD("get_enableEffectAnnotations"),
                                        &slang_SessionDesc::get_enableEffectAnnotations);
            godot::ClassDB::add_property("slang_SessionDesc",
                                         godot::PropertyInfo(godot::Variant::BOOL, "enableEffectAnnotations"),
                                         "set_enableEffectAnnotations", "get_enableEffectAnnotations");

            godot::ClassDB::bind_method(godot::D_METHOD("set_allowGLSLSyntax", "allowGLSLSyntax"),
                                        &slang_SessionDesc::set_allowGLSLSyntax);
            godot::ClassDB::bind_method(godot::D_METHOD("get_allowGLSLSyntax"),
                                        &slang_SessionDesc::get_allowGLSLSyntax);
            godot::ClassDB::add_property("slang_SessionDesc",
                                         godot::PropertyInfo(godot::Variant::BOOL, "allowGLSLSyntax"),
                                         "set_allowGLSLSyntax", "get_allowGLSLSyntax");

            godot::ClassDB::bind_method(godot::D_METHOD("set_compilerOptionEntries", "compilerOptionEntries"),
                                        &slang_SessionDesc::set_compilerOptionEntries);
            godot::ClassDB::bind_method(godot::D_METHOD("get_compilerOptionEntries"),
                                        &slang_SessionDesc::get_compilerOptionEntries);
            godot::ClassDB::add_property("slang_SessionDesc",
                                         godot::PropertyInfo(godot::Variant::OBJECT, "compilerOptionEntries"),
                                         "set_compilerOptionEntries", "get_compilerOptionEntries");
        }

    public:
        size_t get_structureSize() {
            return structureSize;
        }

        void set_structureSize(size_t size) {
            this->structureSize = size;
        }

        slang_TargetDesc *get_targets();

        void set_targets(const slang_TargetDesc *targets);

        int64_t get_targetCount() {
            return targetCount;
        }

        void set_targetCount(int64_t targetCount) {
            this->targetCount = targetCount;
        }

        uint32_t get_flags() {
            return flags;
        }

        void set_flags(uint32_t flags) {
            this->flags = flags;
        }

        slang_SlangMatrixLayoutMode get_defaultMatrixLayoutMode() {
            return (slang_SlangMatrixLayoutMode) defaultMatrixLayoutMode;
        }

        void set_defaultMatrixLayoutMode(slang_SlangMatrixLayoutMode defaultMatrixLayoutMode) {
            this->defaultMatrixLayoutMode = (SlangMatrixLayoutMode) defaultMatrixLayoutMode;
        }

        const char *const *get_searchPaths() {
            return searchPaths;
        }

        void set_searchPaths(const char *const *searchPaths) {
            this->searchPaths = searchPaths;
        }

        int64_t get_searchPathCount() {
            return searchPathCount;
        }

        void set_searchPathCount(int64_t searchPathCount) {
            this->searchPathCount = searchPathCount;
        }

        slang_PreprocessorMacroDesc *get_preprocessorMacros();

        void set_preprocessorMacros(const slang_PreprocessorMacroDesc *preprocessorMacros);

        int64_t get_preprocessorMacroCount() {
            return preprocessorMacroCount;
        }

        void set_preprocessorMacroCount(int64_t preprocessorMacroCount) {
            this->preprocessorMacroCount = preprocessorMacroCount;
        }

        slang_IFileSystem *get_fileSystem();

        void set_fileSystem(slang_IFileSystem *fileSystem);

        bool get_enableEffectAnnotations() {
            return enableEffectAnnotations;
        }

        void set_enableEffectAnnotations(bool enableEffectAnnotations) {
            this->enableEffectAnnotations = enableEffectAnnotations;
        }

        bool get_allowGLSLSyntax() {
            return allowGLSLSyntax;
        }

        void set_allowGLSLSyntax(bool allowGLSLSyntax) {
            this->allowGLSLSyntax = allowGLSLSyntax;
        }

        slang_CompilerOptionEntry *get_compilerOptionEntries();

        void set_compilerOptionEntries(slang_CompilerOptionEntry *compilerOptionEntries);

        uint32_t get_compilerOptionEntryCount() {
            return compilerOptionEntryCount;
        }

        void set_compilerOptionEntryCount(uint32_t compilerOptionEntryCount) {
            this->compilerOptionEntryCount = compilerOptionEntryCount;
        }
    };

    class slang_Modifier : public slang_SlangObject, public slang::Modifier {
    GDCLASS(slang_Modifier, slang_SlangObject)
    private:
        static void _bind_methods() {
            BIND_ENUM_CONSTANT(slang_Modifier::ID::Shared)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::NoDiff)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::Static)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::Const)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::Export)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::Extern)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::Differentiable)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::Mutating)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::In)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::Out)
            BIND_ENUM_CONSTANT(slang_Modifier::ID::InOut)
        }
    };
}
VARIANT_ENUM_CAST(slang_cpp::slang_Modifier::ID)
namespace slang_cpp {
    class slang_UserAttribute : public slang_SlangObject, public slang::UserAttribute {
    GDCLASS(slang_UserAttribute, slang_SlangObject)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_UserAttribute::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentCount"), &slang_UserAttribute::getArgumentCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentType", "index"), &slang_UserAttribute::getArgumentType);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentValueInt", "index", "outValue"), &slang_UserAttribute::getArgumentValueInt);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentValueFloat", "index", "outValue"), &slang_UserAttribute::getArgumentValueFloat);
            godot::ClassDB::bind_method(godot::D_METHOD("getArgumentValueString", "index", "outSize"), &slang_UserAttribute::getArgumentValueString);
        }
    public:
        godot::String getName() {
            return godot::String().utf8(this->slang::UserAttribute::getName());
        }
        uint32_t getArgumentCount() {
            return this->slang::UserAttribute::getArgumentCount();
        }
        slang_TypeReflection* getArgumentType(uint32_t index);
        SlangResult getArgumentValueInt(uint32_t index, slang_INT<int>* outValue){
            int value = 0;
            SlangResult res = this->slang::UserAttribute::getArgumentValueInt(index, &value);
            outValue->set_value(value);
            return res;
        }
        SlangResult getArgumentValueFloat(uint32_t index, slang_DOUBLE* outValue){
            float value = 0;
            SlangResult res = this->slang::UserAttribute::getArgumentValueFloat(index, &value);
            outValue->set_value(value);
            return res;
        }
        godot::String getArgumentValueString(uint32_t index,slang_SIZE* outSize){
            size_t size = 0;
            const char* value = this->slang::UserAttribute::getArgumentValueString(index, &size);
            return godot::String().utf8(value);
        }
    };
    class slang_VariableReflection : public slang_SlangObject, public slang::VariableReflection {
    GDCLASS(slang_VariableReflection, slang_SlangObject)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("getName", "null"), &slang_VariableReflection::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getType", "null"), &slang_VariableReflection::getType);
            godot::ClassDB::bind_method(godot::D_METHOD("findModifier", "id"), &slang_VariableReflection::findModifier);
            godot::ClassDB::bind_method(godot::D_METHOD("getUserAttributeCount"), &slang_VariableReflection::getUserAttributeCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getUserAttributeByIndex", "index"), &slang_VariableReflection::getUserAttributeByIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("findUserAttributeByName", "session", "name"), &slang_VariableReflection::findUserAttributeByName);
            godot::ClassDB::bind_method(godot::D_METHOD("hasDefaultValue"), &slang_VariableReflection::hasDefaultValue);
        }

    public:
        godot::String getName(slang_NULL *null) {
            return godot::String().utf8(this->slang::VariableReflection::getName());
        }
        slang_TypeReflection * getType(slang_NULL *null);
        slang_Modifier* findModifier(slang_Modifier::ID id){
            return static_cast<slang_Modifier *>(this->slang::VariableReflection::findModifier(id));
        }
        unsigned int getUserAttributeCount(){
            return this->slang::VariableReflection::getUserAttributeCount();
        }
        slang_UserAttribute* getUserAttributeByIndex(unsigned int index) {
            return static_cast<slang_UserAttribute *>(this->slang::VariableReflection::getUserAttributeByIndex(index));
        }
        slang_UserAttribute* findUserAttributeByName(slang_IGlobalSession* session,godot::String name) {
            return static_cast<slang_UserAttribute *>(this->slang::VariableReflection::findUserAttributeByName(session,name.utf8().get_data()));
        }
        bool hasDefaultValue(){
            return this->slang::VariableReflection::hasDefaultValue();
        }

    };
    class slang_VariableLayoutReflection : public slang_SlangObject, public slang::VariableLayoutReflection {
    GDCLASS(slang_VariableLayoutReflection, slang_SlangObject)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("getVariable"), &slang_VariableLayoutReflection::getVariable);
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_VariableLayoutReflection::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("findModifier", "id"), &slang_VariableLayoutReflection::findModifier);
            godot::ClassDB::bind_method(godot::D_METHOD("getTypeLayout"), &slang_VariableLayoutReflection::getTypeLayout);
            godot::ClassDB::bind_method(godot::D_METHOD("getCategory"), &slang_VariableLayoutReflection::getCategory);
        }

    public:
        slang_VariableReflection* getVariable() {
            return static_cast<slang_VariableReflection *>(this->slang::VariableLayoutReflection::getVariable());
        }
        godot::String getName(){
            return godot::String().utf8(this->slang::VariableLayoutReflection::getName());
        }
        slang_Modifier* findModifier(slang_Modifier::ID id){
            return static_cast<slang_Modifier *>(this->slang::VariableLayoutReflection::findModifier(id));
        }
        slang_TypeLayoutReflection* getTypeLayout();
        slang_SlangParameterCategory getCategory() {
            return (slang_SlangParameterCategory) this->slang::VariableLayoutReflection::getCategory();
        }

    };
    class slang_FunctionReflection : public slang_SlangObject, public slang::FunctionReflection {
    GDCLASS(slang_FunctionReflection, slang_SlangObject)
    private:
        static void _bind_methods() {
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
            return godot::String().utf8(this->slang::FunctionReflection::getName());
        }
        slang_TypeReflection * getReturnType();
        unsigned int getParameterCount() {
            return this->slang::FunctionReflection::getParameterCount();
        }
        slang_VariableReflection* getParameterByIndex(unsigned int index) {
            return static_cast<slang_VariableReflection *>(this->slang::FunctionReflection::getParameterByIndex(index));
        }
        unsigned int getUserAttributeCount() {
            return this->slang::FunctionReflection::getUserAttributeCount();
        }
        slang_UserAttribute* getUserAttributeByIndex(unsigned int index) {
            return static_cast<slang_UserAttribute *>(this->slang::FunctionReflection::getUserAttributeByIndex(index));
        }
        slang_UserAttribute* findUserAttributeByName(slang_IGlobalSession* session,godot::String name) {
            return static_cast<slang_UserAttribute *>(this->slang::FunctionReflection::findUserAttributeByName(session,name.utf8().get_data()));
        }
        slang_Modifier* findModifier(slang_Modifier::ID id) {
            return static_cast<slang_Modifier *>(this->slang::FunctionReflection::findModifier(id));
        }
        slang_GenericReflection* getGenericContainer();
    };
    class slang_DeclReflection : public slang_SlangObject, public slang::DeclReflection {
    GDCLASS(slang_DeclReflection, slang_SlangObject)
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
            return (Kind) this->slang::DeclReflection::getKind();
        }
        unsigned int getChildrenCount(){
            return this->slang::DeclReflection::getChildrenCount();
        }
        slang_DeclReflection* getChild(unsigned int index) {
            return static_cast<slang_DeclReflection *>(this->slang::DeclReflection::getChild(index));
        }
        slang_TypeReflection* getType();
        slang_VariableReflection* asVariable() {
            return static_cast<slang_VariableReflection *>(this->slang::DeclReflection::asVariable());
        }
        slang_FunctionReflection* asFunction() {
            return static_cast<slang_FunctionReflection *>(this->slang::DeclReflection::asFunction());
        }
        slang_GenericReflection* asGeneric();
        slang_DeclReflection* getParent() {
            return static_cast<slang_DeclReflection *>(this->slang::DeclReflection::getParent());
        }
    };
    class slang_GenericReflection : public slang_SlangObject, public slang::GenericReflection {
    GDCLASS(slang_GenericReflection, slang_SlangObject)
    private:
        static void _bind_methods() {}
    public:
    };
    class slang_TypeReflection : public slang_SlangObject, public slang::TypeReflection {
    GDCLASS(slang_TypeReflection, slang_SlangObject)
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
    private:
        static void _bind_methods() {
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

            BIND_ENUM_CONSTANT(slang_TypeReflection::ScalarType::None)
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
            return (Kind) this->slang::TypeReflection::getKind();
        }
        unsigned int getFieldCount() {
            return this->slang::TypeReflection::getFieldCount();
        }
        slang_VariableReflection* getFieldByIndex(unsigned int index) {
            return static_cast<slang_VariableReflection *>(this->slang::TypeReflection::getFieldByIndex(index));
        }
        bool isArray(){
            return this->slang::TypeReflection::isArray();
        }
        slang_TypeReflection* unwrapArray(){
            return static_cast<slang_TypeReflection *>(this->slang::TypeReflection::unwrapArray());
        }
        size_t getElementCount(){
            return this->slang::TypeReflection::getElementCount();
        }
        size_t getTotalArrayElementCount(){
            return this->slang::TypeReflection::getTotalArrayElementCount();
        }
        slang_TypeReflection* getElementType(){
            return static_cast<slang_TypeReflection *>(this->slang::TypeReflection::getElementType());
        }
        unsigned getRowCount(){
            return this->slang::TypeReflection::getRowCount();
        }
        unsigned getColumnCount()
        {
            return this->slang::TypeReflection::getColumnCount();
        }
        ScalarType getScalarType()
        {
            return this->slang::TypeReflection::getScalarType();
        }
        slang_TypeReflection* getResourceResultType()
        {
            return static_cast<slang_TypeReflection *>(this->slang::TypeReflection::getResourceResultType());
        }
        slang_SlangResourceShape getResourceShape(){
            return static_cast<slang_SlangResourceShape>(this->slang::TypeReflection::getResourceShape());
        }
        slang_SlangResourceAccess getResourceAccess(){
            return static_cast<slang_SlangResourceAccess>(this->slang::TypeReflection::getResourceAccess());
        }
        godot::String getName(){
            return godot::String().utf8(this->slang::TypeReflection::getName());
        }
        SlangResult getFullName(slang_PTR<slang_IBlob*>* outNameBlob){
            return this->slang::TypeReflection::getFullName(reinterpret_cast<ISlangBlob **>(outNameBlob->get_value()));
        }
        unsigned int getUserAttributeCount(){
            return this->slang::TypeReflection::getUserAttributeCount();
        }
        slang_UserAttribute* getUserAttributeByIndex(unsigned int index){
            return static_cast<slang_UserAttribute *>(this->slang::TypeReflection::getUserAttributeByIndex(index));
        }
        slang_UserAttribute* findUserAttributeByName(godot::String name){
            return static_cast<slang_UserAttribute *>(this->slang::TypeReflection::findUserAttributeByName(name.utf8().get_data()));
        }
        slang_SlangReflectionGeneric* getGenericContainer(){
            this->slang::TypeReflection::getGenericContainer();
            return nullptr;
        }
    };
    class slang_SlangReflectionGeneric : public slang_SlangObject{
    GDCLASS(slang_SlangReflectionGeneric, slang_SlangObject)
    private:
        static void _bind_methods() {}

    public:
    };
    class slang_TypeLayoutReflection : public slang_SlangObject, public slang::TypeLayoutReflection {
    GDCLASS(slang_TypeLayoutReflection, slang_SlangObject)
    private:
        static void _bind_methods() {
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
            BIND_ENUM_CONSTANT(slang_SlangParameterCategory::SLANG_PARAMETER_CATEGORY_CONSTANT_BUFFER)
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
        slang_TypeReflection* getType() {
            return static_cast<slang_TypeReflection *>(this->slang::TypeLayoutReflection::getType());
        }
        slang_TypeReflection::Kind getKind() {
            return (slang_TypeReflection::Kind) this->slang::TypeLayoutReflection::getKind();
        }
        size_t getSize(slang_SlangParameterCategory category = SLANG_PARAMETER_CATEGORY_UNIFORM) {
            return this->slang::TypeLayoutReflection::getSize(static_cast<SlangParameterCategory>(category));
        }
        size_t getStride(slang_SlangParameterCategory category = SLANG_PARAMETER_CATEGORY_UNIFORM) {
            return this->slang::TypeLayoutReflection::getStride(static_cast<SlangParameterCategory>(category));
        }
        int32_t getAlignment(slang_SlangParameterCategory category = SLANG_PARAMETER_CATEGORY_UNIFORM) {
            return this->slang::TypeLayoutReflection::getAlignment(static_cast<SlangParameterCategory>(category));
        }
        unsigned int getFieldCount() {
            return this->slang::TypeLayoutReflection::getFieldCount();
        }

    };
    class slang_TypeParameterReflection : public slang_SlangObject, public slang::TypeParameterReflection {
    GDCLASS(slang_TypeParameterReflection, slang_SlangObject)
    private:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("getName"), &slang_TypeParameterReflection::getName);
            godot::ClassDB::bind_method(godot::D_METHOD("getIndex"), &slang_TypeParameterReflection::getIndex);
            godot::ClassDB::bind_method(godot::D_METHOD("getConstraintCount"), &slang_TypeParameterReflection::getConstraintCount);
            godot::ClassDB::bind_method(godot::D_METHOD("getConstraintByIndex", "index"), &slang_TypeParameterReflection::getConstraintByIndex);
        }
    public:
        godot::String getName() {
            return godot::String().utf8(this->slang::TypeParameterReflection::getName());
        }
        unsigned getIndex() {
            return this->slang::TypeParameterReflection::getIndex();
        }
        unsigned getConstraintCount(){
            return this->slang::TypeParameterReflection::getConstraintCount();
        }
        slang_TypeReflection* getConstraintByIndex(unsigned index) {
            return static_cast<slang_TypeReflection *>(this->slang::TypeParameterReflection::getConstraintByIndex(index));
        }
    };
    class slang_EntryPointReflection : public slang_SlangObject, public slang::EntryPointReflection {
    GDCLASS(slang_EntryPointReflection, slang_SlangObject)
    private:
        static void _bind_methods() {
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
            return godot::String().utf8(this->slang::EntryPointReflection::getName());
        }
        godot::String getNameOverride(){
            return godot::String().utf8(this->slang::EntryPointReflection::getNameOverride());
        }
        unsigned getParameterCount() {
            return this->slang::EntryPointReflection::getParameterCount();
        }
        slang_FunctionReflection* getFunction() {
            return static_cast<slang_FunctionReflection *>(this->slang::EntryPointReflection::getFunction());
        }
        slang_VariableLayoutReflection* getParameterByIndex(unsigned index){
            return static_cast<slang_VariableLayoutReflection *>(this->slang::EntryPointReflection::getParameterByIndex(index));
        }
        slang_SlangStage getStage() {
            return (slang_SlangStage) this->slang::EntryPointReflection::getStage();
        }
        godot::TypedArray<SlangUInt> getComputeThreadGroupSize(SlangUInt axisCount) {
            SlangUInt sizeAlongAxis[3] = {0,0,0};
            this->slang::EntryPointReflection::getComputeThreadGroupSize(axisCount, sizeAlongAxis);
            godot::TypedArray<SlangUInt> outSizeAlongAxis;
            outSizeAlongAxis.resize(3);
            outSizeAlongAxis[0] = sizeAlongAxis[0];
            outSizeAlongAxis[1] = sizeAlongAxis[1];
            outSizeAlongAxis[2] = sizeAlongAxis[2];
            return outSizeAlongAxis;
        }
        void getComputeWaveSize(slang_INT<SlangUInt>* outWaveSize){
            SlangUInt waveSize = 0;
            this->slang::EntryPointReflection::getComputeWaveSize(&waveSize);
            outWaveSize->set_value(waveSize);
        }
        bool usesAnySampleRateInput(){
            return this->slang::EntryPointReflection::usesAnySampleRateInput();
        }
        slang_VariableLayoutReflection* getVarLayout(){
            return static_cast<slang_VariableLayoutReflection *>(this->slang::EntryPointReflection::getVarLayout());
        }
        slang_TypeLayoutReflection* getTypeLayout(){
            return static_cast<slang_TypeLayoutReflection *>(this->slang::EntryPointReflection::getTypeLayout());
        }
        slang_VariableLayoutReflection* getResultVarLayout(){
            return static_cast<slang_VariableLayoutReflection *>(this->slang::EntryPointReflection::getResultVarLayout());
        }
        bool hasDefaultConstantBuffer(){
            return this->slang::EntryPointReflection::hasDefaultConstantBuffer();
        }
    };
    class slang_ShaderReflection : public slang_SlangObject, public slang::ShaderReflection {
    GDCLASS(slang_ShaderReflection, slang_SlangObject)
    private:
        static void _bind_methods() {
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
            return this->slang::ShaderReflection::getParameterCount();
        }
        unsigned getTypeParameterCount() {
            return this->slang::ShaderReflection::getTypeParameterCount();
        }
        slang_ISession* getSession() {
            return static_cast<slang_ISession *>(this->slang::ShaderReflection::getSession());
        }
        slang_TypeParameterReflection* getTypeParameterByIndex(unsigned index) {
            return static_cast<slang_TypeParameterReflection *>(this->slang::ShaderReflection::getTypeParameterByIndex(index));
        }
        slang_TypeParameterReflection* findTypeParameter(godot::String name) {
            return static_cast<slang_TypeParameterReflection *>(this->slang::ShaderReflection::findTypeParameter(name.utf8().get_data()));
        }
        slang_VariableLayoutReflection* getParameterByIndex(unsigned index) {
            return static_cast<slang_VariableLayoutReflection *>(this->slang::ShaderReflection::getParameterByIndex(index));
        }
        slang_ProgramLayout* get(slang_ICompileRequest* request){
            return static_cast<slang_ProgramLayout *>(this->slang::ShaderReflection::get(request));
        }
        SlangUInt getEntryPointCount() {
            return this->slang::ShaderReflection::getEntryPointCount();
        }
        slang_EntryPointReflection* getEntryPointIndex(SlangUInt index) {
            return static_cast<slang_EntryPointReflection *>(this->slang::ShaderReflection::getEntryPointByIndex(
                    index));
        }
        SlangUInt getGlobalConstantBufferBinding(){
            return this->slang::ShaderReflection::getGlobalConstantBufferBinding();
        }
        size_t getGlobalConstantBufferSize(){
            return this->slang::ShaderReflection::getGlobalConstantBufferSize();
        }
        slang_TypeReflection* findTypeByName(godot::String name){
            return static_cast<slang_TypeReflection *>(this->slang::ShaderReflection::findTypeByName(name.utf8().get_data()));
        }
        slang_FunctionReflection* findFunctionByName(godot::String name) {
            return static_cast<slang_FunctionReflection *>(this->slang::ShaderReflection::findFunctionByName(
                    name.utf8().get_data()));
        }
        slang_FunctionReflection* findFunctionByNameInType(slang_TypeReflection* type, godot::String name){
            return static_cast<slang_FunctionReflection *>(this->slang::ShaderReflection::findFunctionByNameInType(
                    type, name.utf8().get_data()));
        }
        slang_VariableReflection* findVarByNameInType(slang_TypeReflection* type, godot::String name){
            return static_cast<slang_VariableReflection *>(this->slang::ShaderReflection::findVarByNameInType(
                    type, name.utf8().get_data()));
        }
        slang_TypeLayoutReflection* getTypeLayout(slang_TypeReflection* type,slang_LayoutRules rules = slang_LayoutRules::Default){
            return static_cast<slang_TypeLayoutReflection *>(this->slang::ShaderReflection::getTypeLayout(type,
                                                                                                          static_cast<slang::LayoutRules>(rules)));
        }
        slang_EntryPointReflection* findEntryPointByName(godot::String name) {
            return static_cast<slang_EntryPointReflection *>(this->slang::ShaderReflection::findEntryPointByName(
                    name.utf8().get_data()));
        }
        slang_TypeReflection* specializeType(slang_TypeReflection* type, SlangInt specializationArgCount, slang_PTR<slang_TypeReflection*>* specializationArgs,slang_PTR<slang_IBlob*>* outDiagnostics){
            return static_cast<slang_TypeReflection *>(this->slang::ShaderReflection::specializeType(type, specializationArgCount,
                                                                                                     reinterpret_cast<slang::TypeReflection *const *>(specializationArgs->get_value()),
                                                                                                     reinterpret_cast<ISlangBlob **>(outDiagnostics->get_value())));
        }
        SlangUInt getHashedStringCount(){
            return this->slang::ShaderReflection::getHashedStringCount();
        }
        godot::String getHashedString(SlangUInt index,slang_SIZE* outCount){
            size_t count = 0;
            auto str = godot::String().utf8(this->slang::ShaderReflection::getHashedString(index, &count));
            outCount->set_value(count);
            return str;
        }
        slang_TypeLayoutReflection* getGlobalParamsTypeLayout(){
            return static_cast<slang_TypeLayoutReflection *>(this->slang::ShaderReflection::getGlobalParamsTypeLayout());
        }
        slang_VariableLayoutReflection* getGlobalParamsVarLayout(){
            return static_cast<slang_VariableLayoutReflection *>(this->slang::ShaderReflection::getGlobalParamsVarLayout());
        }
    };

}
VARIANT_ENUM_CAST(slang_cpp::slang_DeclReflection::Kind)
VARIANT_ENUM_CAST(slang_cpp::slang_TypeReflection::Kind)
VARIANT_ENUM_CAST(slang_cpp::slang_TypeReflection::ScalarType)
namespace slang_cpp {
    class slang_SpecializationArg : public slang_SlangObject, public slang::SpecializationArg {
    GDCLASS(slang_SpecializationArg, slang_SlangObject)
    public:
        enum Kind : int32_t
        {
            Unknown,    /**< An invalid specialization argument. */
            Type,       /**< Specialize to a type. */
        };
    private:
        static void _bind_methods() {
            BIND_ENUM_CONSTANT(Unknown)
            BIND_ENUM_CONSTANT(Type)

            godot::ClassDB::bind_method(godot::D_METHOD("getType"), &slang_SpecializationArg::getType);
            godot::ClassDB::bind_method(godot::D_METHOD("setType", "type"), &slang_SpecializationArg::setType);
            godot::ClassDB::add_property("slang_SpecializationArg",
                                         godot::PropertyInfo(godot::Variant::OBJECT, "type"),
                                         "setType", "getType");
        }

    public:
        slang_TypeReflection* getType() {
            return static_cast<slang_TypeReflection *>(type);
        }
        void setType(slang_TypeReflection* type) {
            this->type = type;
        }
        static slang_SpecializationArg fromType(slang_TypeReflection* inType){
            slang_SpecializationArg arg;
            arg.kind = static_cast<SpecializationArg::Kind>(Kind::Type);
            arg.type = inType;
            return arg;
        }
    };
}
VARIANT_ENUM_CAST(slang_cpp::slang_SpecializationArg::Kind)
#endif