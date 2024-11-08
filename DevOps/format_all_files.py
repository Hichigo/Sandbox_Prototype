import os
import subprocess

files = subprocess.check_output('git diff --staged --name-only', encoding='cp866')
files = files.split('\n')

apply_clang_ext = [".cpp", ".h", ".cs"]

for file in files:
    name, ext = os.path.splitext(file)
    if ext in apply_clang_ext:
        if os.path.exists(file):
            subprocess.check_output(f'clang-format -i {file}')
            subprocess.check_output(f'git add {file}')