import os
import sys

def rename_files(folder_path, current_name, new_name):
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            if file == current_name:
                old_file_path = os.path.join(root, file)
                new_file_path = os.path.join(root, new_name)
                os.rename(old_file_path, new_file_path)
                print(f"Renamed '{old_file_path}' to '{new_file_path}'")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python rename_files.py folder_path current_name new_name")
    else:
        folder_path = sys.argv[1]
        current_name = sys.argv[2]
        new_name = sys.argv[3]
        rename_files(folder_path, current_name, new_name)
