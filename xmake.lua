set_project("fahangte")
set_version(version)
set_xmakever("2.8.7")
abbr_name = "fat"
version = "0.0.1"
add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {
    outputdir = "."
})
set_languages("c++17")

src_dir = "$(projectdir)/src/"
include_dir = src_dir .. "include/"
lex_dir= src_dir.."lex/"
parse_dir = src_dir .. "parse/"
vm_dir = src_dir .. "vm/"
code_dir = vm_dir .. "code/"
impl_dir = vm_dir .. "impl/"

test_dir=src_dir.. "test/"

toolchain("clang4fahangte")
    set_toolset("cxx", "clang++")
    set_toolset("ld", "clang++")
    add_includedirs(include_dir)
toolchain_end()

target("fat")
    set_kind("binary")
    set_filename(abbr_name .. "v" .. version)
    add_deps("main", "lex","parse")
target_end()

target("lex")
    set_kind("static")
    add_includedirs(lex_dir .. "include/")
    add_files(lex_dir.."**.cpp")
target_end()

target("parse")
    set_kind("static")
    add_includedirs(lex_dir .. "include/")
    add_includedirs(parse_dir .. "include/")
    add_files(parse_dir .. "impl/**.cpp")
target_end()

target("main")
    set_kind("object")
    add_files(src_dir .. "main.cpp")
    add_deps("vm")
target_end()

target("vm")
    set_kind("static")
    add_deps("vm-code", "vm-impl")
target_end()

target("vm-code")
    set_kind("object")
    add_headerfiles(code_dir .. "*.hpp")
target_end()

target("vm-impl")
    set_kind("object")
-- add_files(impl_dir .. "*.cpp")
    add_headerfiles(impl_dir .. "*.hpp")
    add_deps("vm-code")
target_end()

target("test_lex")
    set_kind("binary")
    add_includedirs(lex_dir .. "include/")
    add_files(test_dir.."lex/**.cpp")
    add_deps("lex")
target_end()

target("test_parse")
    set_kind("binary")
    add_includedirs(lex_dir .. "include/")
    add_includedirs(parse_dir .. "include/")
    add_files(test_dir.."parse/**.cpp")
    add_deps("parse","lex")
target_end()


--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

