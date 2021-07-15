import datetime
from datetime import datetime


while(True):
    now = datetime.now().strftime("%H:%M:%S")
    if now == "12:54:00":
        print(now)
        break