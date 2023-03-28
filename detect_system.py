import platform

def detect_os():
    os_name = platform.system()

    if os_name == "Windows":
        return "Windows"
    elif os_name == "Linux":
        return "Linux"
    elif os_name == "Darwin":
        return "macOS"
    else:
        return "Desconhecido"

current_os = detect_os()
print(f"Este script está sendo executado em: {current_os}")