import os
import time
from openai import OpenAI

# === API 配置 ===
api_key = "sk-yq2oZ7K1VAVYBOT4qTICVThcaimfcRbc8UHm08K0guYWuq9s"  # ← 替换为你的真实 API 密钥
base_url = "https://api.ifopen.ai/v1"  # ← 替换为你的 API 网关地址

# === System Prompt（用于指导 ChatGPT 生成目标代码）===
system_prompt = (
    "You are an assistant for rewriting C-language unit functions for benchmarking. Please rewrite the user-provided C program according to the following constraints:"
    "1. Only retain and rewrite the essential function body. Do not include the main function or any test code. There must be only one function; if multiple functions are present, merge them into a single one. Do not output any comments or explanations;"
    "2. The code must not contain any system calls or library functions such as printf, scanf, malloc, free, exit, assert, system, or any file or input/output-related operations;"
    "3. Only int type variables, fixed-length arrays (e.g., int arr[5]; usage of arr[] or arr[n] is not allowed), and pointers are permitted. Do not use macros, dynamic arrays, structs, unions, typedefs, global variables, enums, floating-point types, or any other disallowed syntax. Rewrite them into equivalent forms or expand them when necessary;"
    "4. Do not use shorthand expressions like i++, i--, i+=, etc. Always use the full form such as i = i + 1; i = i - 1;"
    "5. All control structures such as if, else, for, and switch must use full curly braces {}; shorthand or omitted brace forms are not allowed;"
    "6. Use for-loops whenever possible; avoid using while and do-while loops;"
    "7. Every function must end with a return; statement, even if the return type is void;"
    "8. Ensure that the code formatting is clean and standardized, with proper line breaks and indentation. The rewritten code must preserve the original logic and behavior in an equivalent form;"
    "Below is the original C function source code to be rewritten:"
)

# === 输入输出路径 ===
input_dir = './input_c_files'
output_dir = './output_c_files_gemini'
os.makedirs(output_dir, exist_ok=True)

# === 调用 GPT-4 Turbo 处理函数 ===
def call_gpt41_api(prompt, system_prompt, api_key, base_url):
    try:
        client = OpenAI(api_key=api_key, base_url=base_url)
        response = client.chat.completions.create(
            model="gemini-2.5-pro",
            messages=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": prompt}
            ],
            temperature=0.1,
            max_tokens=20480
        )
        return response.choices[0].message.content
    except Exception as e:
        return f"请求失败：{str(e)}"

# === 批量重写 C 文件函数 ===
def batch_rewrite_c_files():
    for filename in os.listdir(input_dir):
        if filename.endswith('.c'):
            input_path = os.path.join(input_dir, filename)
            output_path = os.path.join(output_dir, filename)
            with open(input_path, 'r', encoding='utf-8') as fin:
                code = fin.read()

            print(f'正在处理：{filename}')
            rewritten_code = call_gpt41_api(code, system_prompt, api_key, base_url)

            if rewritten_code is None or rewritten_code.startswith("请求失败"):
                print(f"❌ 文件 {filename} 处理失败：{rewritten_code}")
                continue

            # 去除 markdown 代码块包装
            if '```c' in rewritten_code:
                rewritten_code = rewritten_code.split('```c')[1].split('```')[0]
            elif '```' in rewritten_code:
                rewritten_code = rewritten_code.split('```')[1].split('```')[0]

            with open(output_path, 'w', encoding='utf-8') as fout:
                fout.write(rewritten_code.strip() + '\n')

            print(f'✅ 输出至：{output_path}')

# === 主函数入口 ===
if __name__ == '__main__':
    print("🚀 开始批量处理 C 函数文件...\n")
    batch_rewrite_c_files()
    print("\n✅ 全部处理完成！")
