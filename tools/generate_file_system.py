import os
import shutil

import json
import bson


game_resources_directory = "resources"
game_data_directory = "data"


def generate_binary_asset(asset_file_path: str, target_binary_file_path: str) -> None:
    if asset_file_path.endswith(".json"):
        bsonified = ""
        with open(asset_file_path, "r") as file:
            document = json.load(file)
            bsonified = bson.dumps(document)

        target_binary_file_directory = os.path.dirname(target_binary_file_path)
        if not os.path.exists(target_binary_file_directory):
            os.makedirs(target_binary_file_directory, exist_ok = True)

        with open(target_binary_file_path, "wb") as file:
            file.write(bsonified)


def generate_binary_assets() -> None:
    if not os.path.exists(game_data_directory):
        os.mkdir(game_data_directory)

    # Sprite animations
    for path, current_directory, files in os.walk("%s/sprite_animations" % (game_resources_directory)):
        for file in files:
            asset_file_path = os.path.join(path, file)
            target_binary_file_path = os.path.join(game_data_directory, "sprite_animations", file)
            target_binary_file_path = os.path.splitext(target_binary_file_path)[0] + '.bin'
            generate_binary_asset(asset_file_path, target_binary_file_path)


def copy_asset(source: str, destination: str) -> None:
    dir_name = os.path.dirname(destination)
    if not os.path.exists(dir_name):
        os.makedirs(dir_name, exist_ok = True)
    shutil.copy(source, destination)


# For assets that only need to be copied over for distribution
def copy_other_assets() -> None:
    # Shaders
    for path, current_directory, files in os.walk("%s/shaders" % (game_resources_directory)):
        for file in files:
            asset_file_path = os.path.join(path, file)
            target_asset_file_path = os.path.join(path, file)
            target_asset_file_path = target_asset_file_path.replace(game_resources_directory, game_data_directory)
            copy_asset(asset_file_path, target_asset_file_path)

    # Textures
    for path, current_directory, files in os.walk("%s/textures" % (game_resources_directory)):
        for file in files:
            asset_file_path = os.path.join(path, file)
            target_asset_file_path = os.path.join(path, file)
            target_asset_file_path = target_asset_file_path.replace(game_resources_directory, game_data_directory)
            copy_asset(asset_file_path, target_asset_file_path)


def main() -> None:
    generate_binary_assets()
    copy_other_assets()


if __name__ == "__main__":
    main()