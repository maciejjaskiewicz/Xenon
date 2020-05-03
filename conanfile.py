from conans import ConanFile, CMake

class Xenon(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "fmt/6.1.2",
        "spdlog/1.5.0",
        "gtest/1.10.0",
        "glad/0.1.33",
        "glm/0.9.9.7"
    )
    generators = (
        "cmake", 
        "cmake_multi"
    )
    default_options = {
        "glad:gl_profile": "core", 
        "glad:gl_version": 4.1
    }

    def configure(self):
        if self.settings.os == "Windows":
            self.requires.add("dirent/1.23.2")