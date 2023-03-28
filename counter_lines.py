import os

def count_c_lines_in_directory(directory):
    total_lines = 0

    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".c") or file.endswith(".h"):
                file_path = os.path.join(root, file)

                with open(file_path, "r") as f:
                    lines = f.readlines()
                    total_lines += len(lines)

    return total_lines

directory_path = os.path.dirname(os.path.abspath(__file__))
total_lines = count_c_lines_in_directory(directory_path)
print(f"Lines written in C language: {total_lines}")
