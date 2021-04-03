import numpy
import openpyxl
#存excel
# 建立 NumPy 陣列
myArr = numpy.array([[1, 2, 3], [4, 5, 6]])

# 建立 Excel 活頁簿
wb = openpyxl.Workbook()

# 取得作用中的工作表
ws = wb.active

# 設定工作表名稱
ws.title = "NumPy_Arr"

# 將 NumPy 陣列寫入 Excel 工作表
for x in myArr:
    ws.append(x.tolist())

# 儲存 Excel 活頁簿至檔案
wb.save(filename='test.xlsx')