add_rules("mode.debug", "mode.release")

package("slang_local")
    set_sourcedir("ext/slang")
    add_configs("shared", { description = "Build shared library", default = true, type = "boolean", readonly = true })
    add_configs("embed_stdlib_source", { description = "Embed stdlib source in the binary", default = true, type = "boolean" })
    add_configs("embed_stdlib", { description = "Build slang with an embedded version of the stdlib", default = false, type = "boolean" })
    add_configs("full_ir_validation", { description = "Enable full IR validation (SLOW!)", default = false, type = "boolean" })
    add_configs("gfx", { description = "Enable gfx targets", default = false, type = "boolean" })
    add_configs("slangd", { description = "Enable language server target", default = false, type = "boolean" })
    add_configs("slangc", { description = "Enable standalone compiler target", default = false, type = "boolean" })
    add_configs("slangrt", { description = "Enable runtime target", default = false, type = "boolean" })
    add_configs("slang_glslang", { description = "Enable glslang dependency and slang-glslang wrapper target", default = false, type = "boolean" })
    add_configs("slang_llvm_flavor", { description = "How to get or build slang-llvm (available options: FETCH_BINARY, USE_SYSTEM_LLVM, DISABLE)", default = "DISABLE", type = "string" })

    add_deps("cmake")

    on_install("windows|x64", "macosx", "linux|x86_64", function (package)
        local configs = {"-DSLANG_ENABLE_TESTS=OFF", "-DSLANG_ENABLE_EXAMPLES=OFF"}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:is_debug() and "Debug" or "Release"))
        table.insert(configs, "-DSLANG_LIB_TYPE=" .. (package:config("shared") and "SHARED" or "STATIC"))
        table.insert(configs, "-DSLANG_EMBED_STDLIB_SOURCE=" .. (package:config("embed_stdlib_source") and "ON" or "OFF"))
        table.insert(configs, "-DSLANG_EMBED_STDLIB=" .. (package:config("embed_stdlib") and "ON" or "OFF"))
        table.insert(configs, "-DSLANG_ENABLE_FULL_IR_VALIDATION=" .. (package:config("full_ir_validation") and "ON" or "OFF"))
        table.insert(configs, "-DSLANG_ENABLE_ASAN=" .. (package:config("asan") and "ON" or "OFF"))
        table.insert(configs, "-DSLANG_ENABLE_GFX=" .. (package:config("gfx") and "ON" or "OFF"))
        table.insert(configs, "-DSLANG_ENABLE_SLANGD=" .. (package:config("slangd") and "ON" or "OFF"))
        table.insert(configs, "-DSLANG_ENABLE_SLANGC=" .. (package:config("slangc") and "ON" or "OFF"))
        table.insert(configs, "-DSLANG_ENABLE_SLANGRT=" .. (package:config("slangrt") and "ON" or "OFF"))
        table.insert(configs, "-DSLANG_ENABLE_SLANG_GLSLANG=" .. (package:config("slang_glslang") and "ON" or "OFF"))
        table.insert(configs, "-DSLANG_SLANG_LLVM_FLAVOR=" .. package:config("slang_llvm_flavor"))

        import("package.tools.cmake").install(package, configs)
        package:addenv("PATH", "bin")
    end)
package_end()

add_requires("slang_local", "godotcpp4 4.2")

PROJECT_NAME = "slang_cpp"
OUTPUT_DIR = "test/addons/slang/"

target(PROJECT_NAME)
    set_kind("shared")
    add_cxflags("/bigobj", "/MT")
    add_files("src/*.cpp")
    add_defines("TYPED_METHOD_BIND")
    add_includedirs("include","ext")
    add_packages("slang_local", "godotcpp4")
    set_basename(PROJECT_NAME .. "_$(mode)_$(plat)_$(arch)")
    set_targetdir(OUTPUT_DIR .. "bin/$(os)")
    set_languages("c++20")
