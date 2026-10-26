# D:\Study —— 我的学习代码库（2026.11.01 起）

| 目录 | 内容 |
|---|---|
| `C/week01 … week11` | C 语言阶段（2026-11-02 → 2027-01-17），week01 里是 type-table 类型实验工程 |
| `CPP/week12 … week35` | C++ + 算法 + 网安阶段（2027-01-18 → 2027-07-04） |
| `python/` | Python 副线（每天 20–30 分钟，10 个阶段） |
| `notes/` | 跨周笔记：c-notes / cpp-notes / python-notes / 错误清单 |
| `.gitignore` | 忽略编译产物、VS 配置、Python 缓存 |

## 每个周目录里有什么

- `README.md`：本周目标 / 核心知识点 / 视频清单 / 7 天任务表 / 产出 / 验收清单
- `mistakes.md`：错题本模板（卡在哪 + 一句话正确思路 + 二刷打勾）
- 自己的代码、笔记、实验报告直接放这个周目录里

## 每天怎么用

1. 打开当周 `README.md`，看「每日任务」表里今天那一行
2. 代码写在当周目录下，文件名带上日期，例如 `w01_20261102_sort.c`
3. 卡住的题写进 `mistakes.md`
4. 当天结束：`git add .` → `git commit -m "w01 day1: 数组排序"`

## 常用命令

```powershell
# 一次性建好全部 35 周骨架（可重复执行，会覆盖 README/mistakes）
powershell -ExecutionPolicy Bypass -File "D:\学习计划\工具\generate_weeks.ps1"

# 提交
cd D:\Study
git add .
git commit -m "w01 day1: xxx"

# 看提交历史
git log --oneline --graph -20
```

## 编译（MSVC）

```powershell
& "D:\develop\vs2026\Community\VC\Auxiliary\Build\vcvars64.bat"   # 在 cmd 里执行
cl /nologo /W4 /std:c++17 hello.cpp /Fe:hello.exe
```

- C++ 统一用 `/std:c++17`；第 22 周（现代 C++）改用 `/std:c++latest`
- 调试用的 ASan 版本：`cl /fsanitize=address`（VS 2026 已装 AddressSanitizer 组件）
