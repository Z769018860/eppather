import os
import time
from openai import OpenAI

# === API 配置 ===
api_key = "7f8df9e78ab05908095ef6257ce1a83059e45636c1311a396e31725ef9172e82"  # ← 替换为你的真实 API 密钥
base_url = "https://uni-api.cstcloud.cn/v1"  # ← 替换为你的 API 网关地址


system_prompt = (
    "你是一个C语言单元函数基准代码重写助手。请将用户输入的 C 语言程序改写为如下要求："
    "1. 只保留并改写重要函数本体，无需包含 main 函数或测试代码，只存在一个函数，多个函数也需要合并成一个函数，不允许输出注释和解释说明；"
    "2. 代码不能包含 printf、scanf、malloc、free、exit、assert、system 等任何系统调用或库函数，也不能包含文件或输入输出相关操作；"
    "3. 只允许 int 类型变量、定长数组（如 int arr[5]，不可使用 arr[] 和 arr[n]）、指针，禁止使用宏定义、动态数组、结构体、联合体、typedef、全局变量、枚举、浮点型等类型和语法，请改写成等价的形式或进行展开；"
    "4. 不使用 i++、i--、i+= 等类似的简写，写成完整的如 i=i+1；i=i-1 等形式；"
    "5. 所有 if、else、for、switch 等语句都必须加大括号，禁止任何省略形式；"
    "6. 所有循环尽量用 for，避免使用 while 和 do-while；"
    "7. 所有函数最后必须加 return; 语句，即使返回类型是 void；"
    "8. 保证代码格式工整、规范，换行合理，并且改写前后的代码核心逻辑一致，具有等价性；"
    "9. 宏定义不要直接代入：凡是静态数字的宏（如 MAXLEN、BUF_SIZE、N 等）一律改为可变参数。优先将其改写为该函数的 int 形参并用该形参替换所有引用；如不便修改函数签名，则在函数体开头新增对应的 int 局部变量。新增名称不得与已有标识符冲突，若冲突请使用带序号的名称（如 n1、n2）。例如：i<MAXLEN 改为先新增 int n; 然后 i<n;。"
    "10. 若循环次数为固定常量而非变量控制，则将其统一改写为固定执行 5 次（for 形式），例如 for(i=0;i<常量;i=i+1) 改为上界 5。"
    "11. 若整个代码中不存在数组、指针或结构体，则将普通标量变量改写为长度为 5 的简单定长数组（如将 int x 改为 int x[5]），并将对该变量的单点读写改为对 x[0] 的读写（必要时对数组做相应遍历或索引调整）。"
    "12. 不使用十六进制字面量，所有 0x/0X 开头的常量必须等值改写为十进制字面量。"
    "下面是用户需要改写的 C 函数源代码："
)



# === 输入输出路径 ===
input_dir = './rosetta-c'
output_dir = './output_c_files_ds2'
os.makedirs(output_dir, exist_ok=True)

# === 调用 GPT-4 Turbo 处理函数 ===
def call_gpt41_api(prompt, system_prompt, api_key, base_url):
    try:
        client = OpenAI(api_key=api_key, base_url=base_url)
        response = client.chat.completions.create(
            model="deepseek-v3:671b",
            messages=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": prompt}
            ],
            temperature=0.1,
            max_tokens=2048
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
