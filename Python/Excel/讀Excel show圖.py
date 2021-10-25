from openpyxl import load_workbook
from matplotlib import pyplot as plt
Y_current = load_workbook('C:\\Users\\user\\Desktop\\研究\\研究紀錄By泓舉\\7碩一上第七周\\cncdata2.xlsx')['工作表2']['F26':'F63121']
y_data = [ int(c.value) for row in Y_current for c in row]
x_data = [i for i in range(0, len(y_data))]
plt.plot(x_data,y_data)
plt.show()
