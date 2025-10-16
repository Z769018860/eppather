import os
import time
from openai import OpenAI

# === API 配置 ===
api_key = "sk-yq2oZ7K1VAVYBOT4qTICVThcaimfcRbc8UHm08K0guYWuq9s"  # ← 替换为你的真实 API 密钥
base_url = "https://api.ifopen.ai/v1"  # ← 替换为你的 API 网关地址

# === System Prompt（用于指导 ChatGPT 生成目标代码）===
system_prompt = (
    "You are an assistant for rewriting single-function C benchmark code. "
    "Rewrite the user-provided C function according to the following rules:\n"
    "1. Keep and rewrite only the essential function body. Do not include main() or test code. "
    "If there are multiple functions, merge them into a single function. Do not output comments or explanations.\n"
    "2. The code must not use printf, scanf, malloc, free, exit, assert, system, or any system calls or I/O operations.\n"
    "3. Only int variables, fixed-length arrays (e.g., int arr[5] — not arr[] or arr[n]), and pointers are allowed. "
    "Do not use macros, dynamic arrays, structs, unions, typedefs, global variables, enums, or floating-point types; rewrite them into equivalent forms.\n"
    "4. Do not use shorthand operators like i++, i--, i+=. Write them explicitly as i = i + 1; i = i - 1.\n"
    "5. All if, else, for, and switch statements must use braces — no omitted forms are allowed.\n"
    "6. Prefer for-loops over while or do-while loops.\n"
    "7. Always add a return; statement at the end of the function, even if the return type is void.\n"
    "8. Ensure the code is well-formatted, readable, and preserves the original core logic.\n"
    "9. Do not directly substitute numeric macros. Replace static numeric macros (e.g., MAXLEN, BUF_SIZE, N) with int variables or parameters. "
    "Prefer converting them to function parameters, or declare new int variables at the beginning of the function body. "
    "Make sure new variable names do not conflict with existing ones (use suffixes like n1, n2 if needed). Example: i<MAXLEN; becomes int n; i<n;.\n"
    "10. If a loop iterates a fixed number of times (constant bound), rewrite it to iterate exactly 5 times using a for-loop.\n"
    "11. If the code has no arrays, pointers, or structs, convert scalar variables into simple fixed-length arrays (e.g., int x → int x[5]) "
    "and rewrite accesses as x[0] where appropriate.\n"
    "12. Do not use hexadecimal literals. Convert all 0x/0X constants to decimal equivalents.\n"
    "Here is the C function to rewrite:"
)

# === 输入输出路径 ===
input_dir = './rosetta-c'
output_dir = './output_c_files_gpt'
os.makedirs(output_dir, exist_ok=True)

# === 调用 GPT-4 Turbo 处理函数 ===
def call_gpt41_api(prompt, system_prompt, api_key, base_url):
    try:
        client = OpenAI(api_key=api_key, base_url=base_url)
        response = client.chat.completions.create(
            model="gpt-4-turbo",
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
