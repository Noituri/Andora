import sys
import shutil
import os
import requests

targets = [
    "mingw",
    "msvc",
    "linux"
]

raylib_version = "3.0.0"
raylib_url = "https://github.com/raysan5/raylib/releases/download/{}/".format(raylib_version)

def main():
    global raylib_url
    if len(sys.argv) != 2:
        print("Expected one of these arguments: mingw, msvc, linux")
        exit(1)
    target = sys.argv[1]
    if target not in targets:
        print("Invalid target provided: " + target)
        exit(1)

    dest_path = os.path.join("..", "third_party", "raylib")
    if os.path.exists(dest_path):
        return

    file_name = "raylib-{}-".format(raylib_version)
    ext = ".zip"
    if target == "mingw":
        file_name += "Win64-mingw"
    if target == "msvc":
        file_name += "Win64-msvc15"
    if target == "linux":
        file_name += "Linux-amd64"
        ext = ".tar.gz"
    
    r = requests.get(raylib_url + file_name + ext)
    os.makedirs("tmp", exist_ok=True)
    path = os.path.join("tmp", "raylib" + ext)
    open(path, "wb").write(r.content)

    shutil.unpack_archive(path, "tmp")
    shutil.move(os.path.join("tmp", file_name), dest_path)

if __name__ == "__main__":
    main()