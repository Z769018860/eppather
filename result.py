import os
import openpyxl
from openpyxl.styles import Alignment

def read_last_lines(file_path, lines_count=10):
    with open(file_path, 'r', encoding='utf-8') as file:
        return ''.join(file.readlines()[-lines_count:])

def read_final_result(file_path):
    # 尝试打开final.txt并读取内容，如果文件不存在，则返回"Not Found"
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read().replace('\n', '\r\n')  # 保持原有换行
    except FileNotFoundError:
        return 'Not Found'

# 创建新的Excel工作簿
wb = openpyxl.Workbook()
ws = wb.active
# 增加一列用于记录最终结果
ws.append(['File Name', 'Content', 'Last 10 lines of Debug.txt', 'Passed?', 'Final Result'])

# 设置单元格自动换行
ws.column_dimensions['B'].width = 100  # 调整列宽以便于查看
ws.column_dimensions['C'].width = 100
ws.column_dimensions['E'].width = 100  # 为新列设置宽度
for column in ['B', 'C', 'E']:
    ws.column_dimensions[column].alignment = Alignment(wrapText=True)

# 遍历testcase目录下的.c文件
for root, dirs, files in os.walk('testcase'):
    for file in files:
        if file.endswith('.c'):
            file_path = os.path.join(root, file)
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read().replace('\n', '\r\n')  # 保持原有换行
                # 查找对应的debug.txt文件
                debug_txt_path = os.path.join('testresult', file.split('.')[0], 'debug.txt')
                if os.path.exists(debug_txt_path):
                    debug_content = read_last_lines(debug_txt_path)
                    passed = '否' if 'Segmentation fault' in debug_content else '是'
                else:
                    debug_content = 'Not Found'
                    passed = 'N/A'
                
                # 查找对应的final.txt文件
                final_txt_path = os.path.join('testresult', file.split('.')[0], 'final.txt')
                final_result = read_final_result(final_txt_path)
                
                # 将结果写入Excel
                ws.append([file, content, debug_content.replace('\n', '\r\n'), passed, final_result])

# 保存Excel文件
wb.save('output.xlsx')
