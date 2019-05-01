newoption {
  trigger = "SFML_INSTALL_DIR",
  value = "path",
  description = "Path to SFML install directory"
}

newoption {
  trigger = "TGUI_INSTALL_DIR",
  value = "path",
  description = "Path to TGUI install directory"
}

newoption {
  trigger = "THOR_INSTALL_DIR",
  value = "path",
  description = "Path to Thor install directory"
}

SFML_INSTALL_DIR = _OPTIONS["SFML_INSTALL_DIR"]
TGUI_INSTALL_DIR = _OPTIONS["TGUI_INSTALL_DIR"]
THOR_INSTALL_DIR = _OPTIONS["THOR_INSTALL_DIR"]

if _ACTION and string.startswith(_ACTION, "vs20") then
  if not SFML_INSTALL_DIR then
    error("Please specify path to SFML install directory via SFML_INSTALL_DIR")
  elseif not TGUI_INSTALL_DIR then
    error("Please specify path to TGUI install directory via TGUI_INSTALL_DIR")
  elseif not THOR_INSTALL_DIR then
    error("Please specify path to Thor install directory via THOR_INSTALL_DIR")
  end
end

workspace "SpaceShooter"
  configurations {"Debug", "Release"}

project "Game"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"

  files {"src/**.hpp", "src/**.cpp"}
  
  includedirs (path.join(SFML_INSTALL_DIR, "include"))
  includedirs (path.join(TGUI_INSTALL_DIR, "include"))
  includedirs (path.join(THOR_INSTALL_DIR, "include"))

  libdirs (path.join(SFML_INSTALL_DIR, "lib"))
  libdirs (path.join(TGUI_INSTALL_DIR, "lib"))
  libdirs (path.join(THOR_INSTALL_DIR, "lib"))

  filter "configurations:Release"
    defines "NDEBUG"
    optimize "On"
    links {"sfml-audio", "sfml-graphics", "sfml-system", "sfml-window", "sfml-network", "tgui", "thor"}

  filter "configurations:Debug"
    defines "DEBUG"
    symbols "On"
    links {"sfml-audio-d", "sfml-graphics-d", "sfml-system-d", "sfml-window-d", "sfml-network-d", "tgui-d", "thor-d"}