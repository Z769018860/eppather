import os
import requests

# 设置 ChatGPT API 配置
API_URL = "https://api.openai.com/v1/completions"  # 替换为您的实际 API URL
API_KEY = "sk-idx1Y0hoJ8vfL29V1Lal1S_97-EZyE4MRdKTrarEudT3BlbkFJQVqvlwi1KbXM0Fb7CYZ54gYx8n9tUQ3hSGCd3zgj8A"  # 替换为您的 API 密钥
MODEL = "gpt-4o-mini"  # 根据实际情况设置模型名称

# 创建 kleetest 文件夹，如果不存在的话
def create_output_directory():
    output_directory = 'kleetest'
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

# 调用 ChatGPT API 获取插桩后的代码
def get_klee_instrumented_code(input_code):
    headers = {
        "Authorization": f"Bearer {API_KEY}",
        "Content-Type": "application/json",
    }

    data = {
        "model": MODEL,
        "prompt": f"请生成一个klee自动插桩后的代码，以下是C代码:\n\n{input_code}\n\n生成代码时不需要任何说明。",
        "max_tokens": 2048,  # 设置合理的最大令牌数
    }

    try:
        response = requests.post(API_URL, headers=headers, json=data)
        response.raise_for_status()  # 如果请求失败，抛出异常
        response_data = response.json()
        generated_code = response_data.get("choices", [{}])[0].get("text", "").strip()
        return generated_code
    except Exception as e:
        print(f"Error while calling the API: {e}")
        return None

# 处理 .c 文件并生成插桩后的代码
def process_c_file(input_file):
    with open(input_file, 'r') as f:
        input_code = f.read()

    instrumented_code = get_klee_instrumented_code(input_code)
    
    if instrumented_code:
        # 获取文件名并生成输出路径
        output_file = os.path.join('kleetest', os.path.basename(input_file))

        # 保存生成的代码到 kleetest 文件夹
        with open(output_file, 'w') as f:
            f.write(instrumented_code)
        print(f"Processed and saved: {output_file}")
    else:
        print(f"Failed to process file: {input_file}")

# 批量处理当前文件夹下所有的 .c 文件
def process_all_c_files():
    create_output_directory()

    current_directory = os.getcwd()
    files = [f for f in os.listdir(current_directory) if f.endswith('.c')]

    for file in files:
        input_file = os.path.join(current_directory, file)
        process_c_file(input_file)

# 运行批量处理函数
process_all_c_files()
