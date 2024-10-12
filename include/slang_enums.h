#ifndef SLANG_CPP_SLANG_ENUMS_H
#define SLANG_CPP_SLANG_ENUMS_H
namespace slang_cpp {

    enum slang_CompilerOptionValueKind {
        Int, String
    };

    enum slang_CompilerOptionName {
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
    enum slang_SlangCompileTarget : SlangCompileTargetIntegral {
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
    enum slang_SlangProfileID : SlangProfileIDIntegral {
        SLANG_PROFILE_UNKNOWN,
    };
    enum slang_SlangFloatingPointMode : SlangFloatingPointModeIntegral {
        SLANG_FLOATING_POINT_MODE_DEFAULT = 0,
        SLANG_FLOATING_POINT_MODE_FAST,
        SLANG_FLOATING_POINT_MODE_PRECISE,
    };
    enum slang_SlangLineDirectiveMode : SlangLineDirectiveModeIntegral {
        SLANG_LINE_DIRECTIVE_MODE_DEFAULT = 0,  /**< Default behavior: pick behavior base on target. */
        SLANG_LINE_DIRECTIVE_MODE_NONE,         /**< Don't emit line directives at all. */
        SLANG_LINE_DIRECTIVE_MODE_STANDARD,     /**< Emit standard C-style `#line` directives. */
        SLANG_LINE_DIRECTIVE_MODE_GLSL,         /**< Emit GLSL-style directives with file *number* instead of name */
        SLANG_LINE_DIRECTIVE_MODE_SOURCE_MAP,   /**< Use a source map to track line mappings (ie no #line will appear in emitting source) */
    };
    enum slang_SlangMatrixLayoutMode : SlangMatrixLayoutModeIntegral {
        SLANG_MATRIX_LAYOUT_MODE_UNKNOWN = 0,
        SLANG_MATRIX_LAYOUT_ROW_MAJOR,
        SLANG_MATRIX_LAYOUT_COLUMN_MAJOR,
    };
    enum slang_SlangPassThrough : SlangPassThroughIntegral {
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
    enum slang_SlangCapabilityID : SlangCapabilityIDIntegral {
        SLANG_CAPABILITY_UNKNOWN = 0,
    };
    enum slang_SlangResourceShape : SlangResourceShapeIntegral {
        SLANG_RESOURCE_BASE_SHAPE_MASK = 0x0F,

        SLANG_RESOURCE_NONE = 0x00,

        SLANG_TEXTURE_1D = 0x01,
        SLANG_TEXTURE_2D = 0x02,
        SLANG_TEXTURE_3D = 0x03,
        SLANG_TEXTURE_CUBE = 0x04,
        SLANG_TEXTURE_BUFFER = 0x05,

        SLANG_STRUCTURED_BUFFER = 0x06,
        SLANG_BYTE_ADDRESS_BUFFER = 0x07,
        SLANG_RESOURCE_UNKNOWN = 0x08,
        SLANG_ACCELERATION_STRUCTURE = 0x09,
        SLANG_TEXTURE_SUBPASS = 0x0A,

        SLANG_RESOURCE_EXT_SHAPE_MASK = 0xF0,

        SLANG_TEXTURE_FEEDBACK_FLAG = 0x10,
        SLANG_TEXTURE_SHADOW_FLAG = 0x20,
        SLANG_TEXTURE_ARRAY_FLAG = 0x40,
        SLANG_TEXTURE_MULTISAMPLE_FLAG = 0x80,

        SLANG_TEXTURE_1D_ARRAY = SLANG_TEXTURE_1D | SLANG_TEXTURE_ARRAY_FLAG,
        SLANG_TEXTURE_2D_ARRAY = SLANG_TEXTURE_2D | SLANG_TEXTURE_ARRAY_FLAG,
        SLANG_TEXTURE_CUBE_ARRAY = SLANG_TEXTURE_CUBE | SLANG_TEXTURE_ARRAY_FLAG,

        SLANG_TEXTURE_2D_MULTISAMPLE = SLANG_TEXTURE_2D | SLANG_TEXTURE_MULTISAMPLE_FLAG,
        SLANG_TEXTURE_2D_MULTISAMPLE_ARRAY =
        SLANG_TEXTURE_2D | SLANG_TEXTURE_MULTISAMPLE_FLAG | SLANG_TEXTURE_ARRAY_FLAG,
        SLANG_TEXTURE_SUBPASS_MULTISAMPLE = SLANG_TEXTURE_SUBPASS | SLANG_TEXTURE_MULTISAMPLE_FLAG,
    };
    enum slang_SlangResourceAccess : SlangResourceAccessIntegral {
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
    enum slang_SlangParameterCategory : SlangParameterCategoryIntegral {
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
    enum slang_LayoutRules : SlangLayoutRulesIntegral {
        Default = SLANG_LAYOUT_RULES_DEFAULT,
        MetalArgumentBufferTier2 = SLANG_LAYOUT_RULES_METAL_ARGUMENT_BUFFER_TIER_2,
    };
    enum slang_ContainerType {
        None, UnsizedArray, StructuredBuffer, ConstantBuffer, ParameterBlock
    };
    enum slang_SlangPathType : SlangPathTypeIntegral {
        SLANG_PATH_TYPE_DIRECTORY,      /**< Path specified specifies a directory. */
        SLANG_PATH_TYPE_FILE,           /**< Path specified is to a file. */
    };
    enum slang_PathKind {
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
    enum slang_OSPathKind : uint8_t {
        None_,                ///< Paths do not map to the file system
        Direct,              ///< Paths map directly to the file system
        OperatingSystem_,     ///< Only paths gained via PathKind::OperatingSystem map to the operating system file system
    };
    enum slang_SlangStage : SlangStageIntegral {
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
    enum slang_SlangCompileFlags {
        /* Do as little mangling of names as possible, to try to preserve original names */
        SLANG_COMPILE_FLAG_NO_MANGLING = 1 << 3,

        /* Skip code generation step, just check the code and generate layout */
        SLANG_COMPILE_FLAG_NO_CODEGEN = 1 << 4,

        /* Obfuscate shader names on release products */
        SLANG_COMPILE_FLAG_OBFUSCATE = 1 << 5,

        /* Deprecated flags: kept around to allow existing applications to
        compile. Note that the relevant features will still be left in
        their default state. */
        SLANG_COMPILE_FLAG_NO_CHECKING = 0,
        SLANG_COMPILE_FLAG_SPLIT_MIXED_TYPES = 0,
    };
    enum slang_SlangTargetFlags {
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
    enum slang_SlangDebugInfoLevel : SlangDebugInfoLevelIntegral {
        SLANG_DEBUG_INFO_LEVEL_NONE = 0,    /**< Don't emit debug information at all. */
        SLANG_DEBUG_INFO_LEVEL_MINIMAL,     /**< Emit as little debug information as possible, while still supporting stack trackes. */
        SLANG_DEBUG_INFO_LEVEL_STANDARD,    /**< Emit whatever is the standard level of debug information for each target. */
        SLANG_DEBUG_INFO_LEVEL_MAXIMAL,     /**< Emit as much debug infromation as possible for each target. */
    };
    enum slang_SlangOptimizationLevel : SlangOptimizationLevelIntegral {
        SLANG_OPTIMIZATION_LEVEL_NONE = 0,  /**< Don't optimize at all. */
        SLANG_OPTIMIZATION_LEVEL_DEFAULT,   /**< Default optimization level: balance code quality and compilation time. */
        SLANG_OPTIMIZATION_LEVEL_HIGH,      /**< Optimize aggressively. */
        SLANG_OPTIMIZATION_LEVEL_MAXIMAL,   /**< Include optimizations that may take a very long time, or may involve severe space-vs-speed tradeoffs */
    };
    enum slang_SlangContainerFormat : SlangContainerFormatIntegral {
        /* Don't generate a container. */
        SLANG_CONTAINER_FORMAT_NONE,

        /* Generate a container in the `.slang-module` format,
        which includes reflection information, compiled kernels, etc. */
        SLANG_CONTAINER_FORMAT_SLANG_MODULE,
    };
    enum slang_SlangWriterChannel : SlangWriterChannelIntegral {
        SLANG_WRITER_CHANNEL_DIAGNOSTIC,
        SLANG_WRITER_CHANNEL_STD_OUTPUT,
        SLANG_WRITER_CHANNEL_STD_ERROR,
        SLANG_WRITER_CHANNEL_COUNT_OF,
    };
    enum slang_SlangWriterMode : SlangWriterModeIntegral {
        SLANG_WRITER_MODE_TEXT,
        SLANG_WRITER_MODE_BINARY,
    };
    enum slang_SlangSourceLanguage : SlangSourceLanguageIntegral {
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
    enum slang_SlangSeverity : SlangSeverityIntegral {
        SLANG_SEVERITY_DISABLED = 0, /**< A message that is disabled, filtered out. */
        SLANG_SEVERITY_NOTE,         /**< An informative message. */
        SLANG_SEVERITY_WARNING,      /**< A warning, which indicates a possible proble. */
        SLANG_SEVERITY_ERROR,        /**< An error, indicating that compilation failed. */
        SLANG_SEVERITY_FATAL,        /**< An unrecoverable error, which forced compilation to abort. */
        SLANG_SEVERITY_INTERNAL,     /**< An internal error, indicating a logic error in the compiler. */
    };
    enum slang_SlangDebugInfoFormat : SlangDebugInfoFormatIntegral {
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

#endif //SLANG_CPP_SLANG_ENUMS_H
