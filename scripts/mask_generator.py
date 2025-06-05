# mask_generator.py
import pydenticon
from PIL import Image

# 入力文字列（ランダム性に使う）
input_string = "my-random-avatar"
output_path = "mask.png"
size_px = 768

# identiconの設定（GitHubと同じ5x5グリッド）
generator = pydenticon.Generator(
    5, 5,  # rows, columns
    foreground=["#ffffff"],  # 白: 表示
    background="#000000"     # 黒: 透過とする
)

# identicon画像をバイナリとして生成し保存
with open(output_path, "wb") as f:
    png = generator.generate(input_string, size_px, size_px, output_format="png")
    f.write(png)

print("Generated mask image:", output_path)
