# Configures some of the install files for denarii.
# This assumes that denarii has been cloned into your %HOMEDRIVE%%HOMEPATH% repository.
# To see what that is try 'printenv HOMEDRIVE' and 'printenve HOMEPATH'
# This is only for windows

import os
import pathlib
import shutil
import workspace_path_finder

import common


class LibraryInfo:

    def __init__(self, libname, foldername="", get_includes=True):
        self.libname = libname
        self.foldername = foldername
        self.folderpath = ""
        self.relevant_paths = []
        self.get_includes = get_includes


# windows only uses the bare number of libraries needed to get everything to build...
win_library_info = [LibraryInfo("liblzma", "liblzma"), LibraryInfo("libsodium", "libsodium"),
                    LibraryInfo("libreadline", "libreadline"), LibraryInfo("libhidapi", "libhidapi"),
                    LibraryInfo("libusb", "libusb"), LibraryInfo("libunbound", "libunbound"),
                    LibraryInfo("libopenssl", "openssl"), LibraryInfo("libzmq", "libzmq"),
                    LibraryInfo("liblmdb", "db_drivers", False),
                    LibraryInfo("libunwind", "libunwind", False)]

workspace_path = pathlib.Path()


def get_libunwind():
    common.print_something("Getting libunwind")

    # libunwind wants to be special so we need to download its source files first
    raw_path = str(workspace_path / "external")

    common.chdir(raw_path)

    clone_command = "git clone https://github.com/llvm-mirror/libunwind.git"
    common.system(clone_command)

    # need to modify the libunwind.h we are using
    source = str(workspace_path) + "/libunwind.h"
    dest = raw_path + "/libunwind/include/libunwind.h"

    move_command = "move " + source + " " + dest
    common.system(move_command)

    # Need to modify an include of libunwind to use "" instead of <>
    # opening the file in read mode
    file = open(dest, "r")
    replacement = ""
    # using the for loop
    for line in file:
        line = line.strip()
        changes = line.replace("<__libunwind_config.h>", "\"__libunwind_config.h\"")
        replacement = replacement + changes + "\n"

    file.close()
    # opening the file in write mode
    fout = open(dest, "w")
    fout.write(replacement)
    fout.close()

    libunwind_path = workspace_path / "external" / "libunwind"
    common.check_exists(libunwind_path)


def get_zlib():
    common.print_something("Getting Zlib")
    raw_path = str(workspace_path / "external")

    common.chdir(raw_path)

    clone_command = "git clone git@github.com:andrewkatson/zlib.git"
    common.system(clone_command)

    zlib_path = workspace_path / "external" / "zlib"
    common.check_exists(zlib_path)


def create_build_file_win(libraries):
    external_dir_path = workspace_path / "external"

    common.print_something("Creating BUILD files for Windows libraries")
    for library in libraries:

        build_file_name = "BUILD." + library.foldername

        path = os.path.join(external_dir_path, build_file_name)

        if not os.path.exists(path):
            with open(path, 'w'):
                pass

        common.check_exists(path)


def create_folder_win(libraries):
    external_dir_path = workspace_path / "external"

    common.print_something("Creating folders for Windows libraries")
    for library in libraries:

        foldername = library.foldername

        path = os.path.join(external_dir_path, foldername)

        if not os.path.exists(path):
            os.makedirs(path)

        library.folderpath = path

        common.check_exists(path)


def get_relevant_paths_win(libraries):
    common.print_something("Getting relevant paths for Windows libraries")
    base_path = pathlib.Path(R"C:\msys64\mingw64")
    includes_path = os.path.join(base_path, "include")
    src_path = os.path.join(base_path, "lib")

    for library in libraries:
        names = [library.libname]

        # zlib has weird files we can just include the path to
        if "zlib" in names:
            library.relevant_paths.append(str(base_path / "lib/libz.a"))
            continue

        names = [name.replace("lib", "") for name in names]

        # openssl has .a files that go by different names
        if "openssl" in names:
            names = ["openssl", "libssl", "libcrypto"]

        for name in names:
            for subdir, dirs, files in os.walk(includes_path):
                for directory in dirs:
                    if name in directory:
                        library.relevant_paths.append(os.path.join(includes_path, directory))
                for file in files:
                    if name in file and file.endswith(".h"):
                        library.relevant_paths.append(os.path.join(includes_path, file))
            for subdir, dirs, files in os.walk(src_path):
                for file in files:
                    if name in file and file.endswith(".a") or file.endswith(".so"):
                        library.relevant_paths.append(os.path.join(src_path, file))


def find_src_files_win(libraries):
    common.print_something("Finding source files for Windows libraries")
    for library in libraries:

        for path in library.relevant_paths:

            if ".a" in path or ".so" in path:

                filename = path.split("\\")[-1]
                new_path = os.path.join(library.folderpath, filename)

                if os.path.exists(path):
                    print("Moving: " + path + " to " + library.folderpath)
                    try:
                        if not os.path.exists(new_path):
                            with open(new_path, 'w'):
                                pass
                    except:
                        print("weird this shouldnt happen but is ok")
                    finally:
                        print(" ALREADY EXISTS " + new_path)
                    shutil.copyfile(path, new_path)

                else:
                    print(path + " does not exist")


def copy_file(path, library):
    common.print_something("Copying files for Windows libraries")
    if "include" in path:
        try:
            filename = path.split("\\")[-1]
            new_path = os.path.join(library.folderpath + "/include", filename)

            new_path_wo_filename = ""
            # openssl requires it be in a directory called openssl
            if "openssl" in library.libname:
                new_path_wo_filename = os.path.join(library.folderpath, "openssl")
            elif "readline" in library.libname:
                new_path_wo_filename = os.path.join(library.folderpath, "readline")
            elif "sodium" in library.libname:
                new_path_wo_filename = os.path.join(library.folderpath, "sodium")
            else:
                new_path_wo_filename = os.path.join(library.folderpath, "include")

            # the path plus include directory might not exist
            if not os.path.exists(new_path_wo_filename):
                os.makedirs(new_path_wo_filename)

            try:
                if not os.path.exists(new_path):
                    with open(new_path, 'w'):
                        pass
            except Exception as e:
                print("ALREADY EXISTS " + new_path)

            shutil.copyfile(path, new_path)
        except Exception as e:
            print("Could not copy file " + path)
            print(e)


def find_includes_win(libraries):
    common.print_something("Finding include files for Windows libraries")
    for library in libraries:

        if library.get_includes:

            for path in library.relevant_paths:

                if os.path.isdir(path):
                    for subdir, dirs, files in os.walk(path):
                        for file in files:
                            full_path = os.path.join(path, file)
                            copy_file(full_path, library)
                else:
                    copy_file(path, library)


def import_dependencies_win():
    common.print_something("Importing dependencies for Windows")
    get_libunwind()
    get_zlib()
    create_folder_win(win_library_info)
    create_build_file_win(win_library_info)
    get_relevant_paths_win(win_library_info)
    find_includes_win(win_library_info)
    find_src_files_win(win_library_info)


def randomx_win(external_dir_path):
    common.print_something("Getting randomx")
    raw_path = str(external_dir_path)

    randomx_path = raw_path + "/randomx"

    common.chdir(randomx_path)

    build_path = randomx_path + "/build"
    common.chdir(build_path)
    command = "cmake -DARCH=native -G \"MinGW Makefiles\" .. && mingw32-make"
    common.system(command)

    common.check_exists(randomx_path)


def miniupnp_win(external_dir_path):
    common.print_something("Gettign miniupnp")
    raw_path = str(external_dir_path)

    # remove the empty directory
    remove_command = "rm -rf " + raw_path + "/external/miniupnp"
    common.system(remove_command)

    # For now we have to clone this because miniupnp fails to download :(
    clone_command = "git clone https://github.com/miniupnp/miniupnp.git"
    common.system(clone_command)

    # we only need to build one of the subdirectories
    miniupnp_path = raw_path + "/external/miniupnp/miniupnpc"

    common.chdir(miniupnp_path)

    command = "cmake -G \"MinGW Makefiles\" . && mingw32-make"
    common.system(command)

    common.check_exists(miniupnp_path)


workspace_path = workspace_path_finder.find_workspace_path()
print(workspace_path)

import_dependencies_win()

external_dir_path = workspace_path / "external"
randomx_win(external_dir_path)

miniupnp_win(external_dir_path)
