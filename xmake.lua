add_requires("gtest", "luajit", "swig")

add_defines("_GLIBCXX_USE_CXX11_ABI=0")

add_includedirs("./deps/hlsdk/engine")
add_includedirs("./deps/hlsdk/common")
add_includedirs("./deps/hlsdk/pm_shared")
add_includedirs("./deps/hlsdk/dlls")
add_includedirs("./deps/hlsdk/public")
add_includedirs("./deps/metamod/metamod")
add_includedirs("./source")

local lua_wrapper = "$(buildir)/lua_wrapper.cc"

target("luambda")
    add_packages("luajit", "swig")
    set_kind("shared")
    set_symbols("debug")
    set_prefixname("")
    add_files("./source/**.cc")
    add_files(lua_wrapper)
    -- add_shflags("-nodefaultlibs -fno-rtti -fno-exceptions -lc -lm -ldl")
    before_build(function(target)
        os.exec(
            "swig -c++ -lua %s -o %s -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS %s",
            table.concat(
                {
                    "-I$(projectdir)/deps/hlsdk/engine",
                    "-I$(projectdir)/deps/hlsdk/common",
                    "-I$(projectdir)/deps/hlsdk/pm_shared",
                    "-I$(projectdir)/deps/hlsdk/dlls",
                    "-I$(projectdir)/deps/hlsdk/public",
                    "-I$(projectdir)/deps/metamod/metamod",
                    "-I$(projectdir)/source"
                },
                " "
            ),
            lua_wrapper,
            "$(projectdir)/source/bindings/lua.swig"
        )
    end)
    after_build(function(target)
        os.cp(target:targetfile(), "$(projectdir)/bin/")
    end)
