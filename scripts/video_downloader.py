import requests
import os
from dotenv import load_dotenv

load_dotenv()  # .env を読み込む

PEXELS_API_KEY = os.getenv("PEXELS_API_KEY")

if not PEXELS_API_KEY:
    raise RuntimeError("PEXELS_API_KEY is not set. Please define it in a .env file.")


SEARCH_QUERY = "nature"
DOWNLOAD_PATH = "video.mp4"
TARGET_DURATION = 30  # 目標秒数

headers = {
    "Authorization": PEXELS_API_KEY
}

params = {
    "query": SEARCH_QUERY,
    "per_page": 5
}

response = requests.get("https://api.pexels.com/videos/search", headers=headers, params=params)
data = response.json()
data = response.json()
print(data)  # 🔍 ← これを追加


video_url = None

for video in data["videos"]:
    duration = video["duration"]
    if abs(duration - TARGET_DURATION) < 10:  # ±10秒の範囲で許容
        # 適当な高画質動画ファイルを選択
        video_url = video["video_files"][0]["link"]
        break

if video_url:
    print("Downloading from:", video_url)
    video_data = requests.get(video_url)
    with open(DOWNLOAD_PATH, "wb") as f:
        f.write(video_data.content)
    print("Downloaded to", DOWNLOAD_PATH)
else:
    print("No suitable video found.")
