import os

def remove_comments_from_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        text = file.read()

    new_text = []
    in_multiline_comment = False
    in_string = False
    i = 0

    while i < len(text):
        # 多行注释开始
        if text[i:i+2] == "/*" and not in_string:
            in_multiline_comment = True
            i += 2
            continue
        # 多行注释结束
        elif text[i:i+2] == "*/" and in_multiline_comment:
            in_multiline_comment = False
            i += 2
            if i < len(text) and text[i] == '\n':  # 保持注释后的换行
                i += 1
            continue
        
        # 单行注释开始
        if text[i:i+2] == "//" and not in_string and not in_multiline_comment:
            while i < len(text) and text[i] != '\n':  # 跳过至行末，不删除换行符
                i += 1
            continue

        # 字符串开始/结束标记
        if text[i] == '"' and not in_multiline_comment:
            if i == 0 or text[i-1] != '\\':  # 忽略转义引号
                in_string = not in_string

        if not in_multiline_comment:
            new_text.append(text[i])
        i += 1

    # 将处理后的内容写回文件
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(''.join(new_text))

def process_directory(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.c') or file.endswith('.cpp'):
                file_path = os.path.join(root, file)
                remove_comments_from_file(file_path)

if __name__ == "__main__":
    process_directory('.')  # 处理当前目录
    print("Comments removed from .c and .cpp files, trying to preserve formatting.")
