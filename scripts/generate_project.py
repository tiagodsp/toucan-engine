# this script will generate a new project folder calling conan to install the dependencies first, then it will generate the project files for the specified IDE using cmake

import os
import sys
import subprocess
import shutil
import argparse

def run_command(command):
    print("Running command: " + command)
    process = subprocess.Popen(command, shell=True)
    process.wait()
    return process.returncode

def generate_project(generator, build_type, path):
    if not os.path.exists(path):
        os.makedirs(path)
    else:
        print("Project folder already exists")

    # Install dependencies
    run_command("conan install . -of " + path + " --build missing")

    toolchainfile = os.path.join(path, "conan_toolchain.cmake")

    # Generate project files
    if generator == "vs2017":
        run_command("cmake -G \"Visual Studio 15 2017\" -DCMAKE_BUILD_TYPE=" + build_type + " -DCMAKE_TOOLCHAIN_FILE=" + toolchainfile + " . -B " + path)
    elif generator == "vs2019":
        run_command("cmake -G \"Visual Studio 16 2019\" -DCMAKE_BUILD_TYPE=" + build_type + " -DCMAKE_TOOLCHAIN_FILE=" + toolchainfile + " . -B " + path)
    elif generator == "vs2022":
        run_command("cmake -G \"Visual Studio 17 2022\" -DCMAKE_BUILD_TYPE=" + build_type + " -DCMAKE_TOOLCHAIN_FILE=" + toolchainfile + " . -B " + path)
    elif generator == "xcode":
        run_command("cmake -G \"Xcode\" -DCMAKE_BUILD_TYPE=" + build_type + " -DCMAKE_TOOLCHAIN_FILE=" + toolchainfile + " . -B " + path)
    elif generator == "make":
        run_command("cmake -G \"Unix Makefiles\" -DCMAKE_BUILD_TYPE=" + build_type + " -DCMAKE_TOOLCHAIN_FILE=" + toolchainfile + " . -B " + path)
    elif generator == "ninja":
        run_command("cmake -G \"Ninja\" -DCMAKE_BUILD_TYPE=" + build_type + " -DCMAKE_TOOLCHAIN_FILE=" + toolchainfile + " . -B " + path)
    else:
        print("Invalid generator")
        return
        
    print("Project generated successfully")

def main():
    # check if conan is installed
    if run_command("conan --version") != 0:
        print("Conan is not installed. Please install it first.")
        return
    
    # check if cmake is installed
    if run_command("cmake --version") != 0:
        print("CMake is not installed. Please install it first.")
        return

    # setup arguments with default values
    parser = argparse.ArgumentParser(description='Generate a new project folder with conan dependencies and cmake project files')
    parser.add_argument('-p', '--path', type=str, help='Path to the new project folder', default='build')
    parser.add_argument('-g', '--generator', type=str, help='Generator to use (vs2017, vs2019, xcode, make)', default='make')
    parser.add_argument('-b', '--build_type', type=str, help='Build type to use (Debug, Release)', default='Debug')
    args = parser.parse_args()

    generate_project(args.generator, args.build_type, args.path)

if __name__ == "__main__":
    main()