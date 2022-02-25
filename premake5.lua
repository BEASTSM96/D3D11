require "lua/init"
require "lua/project"
require "lua/workspace"
require "lua/third_party_include"

_workspace( "D3D11-Engine", "D3D11-Engine" )

third_party_include "third_party/glfw"
third_party_include "third_party/imgui"

_project( "D3D11-Engine", "ConsoleApp" )
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"D3D11-Engine/src",
		"third_party",
		"third_party/glfw/include",
		"third_party/ImGui/"
		--"%{IncludeDir.glm}"
	}

	defines 
	{
		"GLFW_INCLUDE_NONE"
	}

	links 
	{
		"d3d11",
		"glfw",
		"d3dcompiler"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"

	filter "system:macosx"
		systemversion "11"

	filter "configurations:Debug"
		defines "_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "_RELEASE"
		runtime "Release"
		optimize "on"