import os.path
import sys

binary_folder = ""


def main() -> None:
    embedded_shaders_header_path = os.path.join(binary_folder, "../src/Generated/GL3/Shaders.hpp")
    embedded_shaders_header_code = ""
    with open(embedded_shaders_header_path, "r") as file:
        embedded_shaders_header_code = file.read()

    vertex_shader_path = os.path.join(binary_folder, "../resources/shaders/gl3/VertexShader.glsl")
    vertex_shader_code = ""
    with open(vertex_shader_path, "r") as file:
        vertex_shader_code = file.read()
    vertex_shader_code = vertex_shader_code.replace("\n", "\\n")

    fragment_shader_path = os.path.join(binary_folder, "../resources/shaders/gl3/FragmentShader.glsl")
    fragment_shader_code = ""
    with open(fragment_shader_path, "r") as file:
        fragment_shader_code = file.read()
    fragment_shader_code = fragment_shader_code.replace("\n", "\\n")

    embedded_shaders_header_code = embedded_shaders_header_code.replace("#VERTEX_SHADER_CODE#", vertex_shader_code)
    embedded_shaders_header_code = embedded_shaders_header_code.replace("#FRAGMENT_SHADER_CODE#", fragment_shader_code)

    embedded_shaders_header_path = os.path.join(binary_folder, "src/Generated/GL3/Shaders.hpp")
    if not (os.path.exists(os.path.dirname(embedded_shaders_header_path))):
        os.makedirs(os.path.dirname(embedded_shaders_header_path), exist_ok=True)
    with open(embedded_shaders_header_path, "w") as file:
        file.write(embedded_shaders_header_code)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 generate_shader_headers.py <binary_dir>")
        exit()

    binary_folder = sys.argv[1]
    main()
