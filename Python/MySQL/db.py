
import pymysql
import charts

# refence from https://www.learncodewithmike.com/2020/02/python-mysql.html
# 資料庫參數設定
db_settings = {
    "host": "127.0.0.1",
    "port": 3306,
    "user": "root",
    "password": "a0929139952",
    "db": "kkbox",
    "charset": "utf8"
}

try:
    # 建立Connection物件
    conn = pymysql.connect(**db_settings)
    # 建立Cursor物件

    with conn.cursor() as cursor:
        command = "INSERT INTO charts(id, name, artist)VALUES(%s, %s, %s)"
        print("H")
        # 取得華語單曲日榜
        charts = charts.get_charts_tracks("H_PilcVhX-E8N0qr1-")

        for chart in charts:
            cursor.execute(
                command, (chart["id"], chart["name"], chart["album"]["artist"]["name"]))
        # 儲存變更
        conn.commit()
        print("H")
      #資料表相關操作
except Exception as ex:
    print(ex)