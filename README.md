# D:\Study —— 我的学习代码库（2026.11.01 起）

| 目录                    | 内容                                                          |
| --------------------- | ----------------------------------------------------------- |
| `C/week01 … week11`   | C 语言阶段（2026-11-02 → 2027-01-17），week01 里是 type-table 类型实验工程 |
| `CPP/week12 … week35` | C++ + 算法 + 网安阶段（2027-01-18 → 2027-07-04）                    |
| `python/`             | Python 副线（每天 20–30 分钟，10 个阶段）                               |
| `notes/`              | 跨周笔记：c-notes / cpp-notes / python-notes / 错误清单              |
| `.gitignore`          | 忽略编译产物、VS 配置、Python 缓存                                      |
| `网安相关/`               | 一些与网安相关的信息与知识                                               |

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

> 完整的 push / pull 流程、概念说明、报错处理和冲突解决，见 **[notes/git教程/](notes/git教程/)**
> （入口：[Git详细教程：push和pull](notes/git教程/Git详细教程：push和pull.md)）

```bash
# 进仓库（Git Bash 用正斜杠；PowerShell 用 cd D:\Study）
cd /d/Study

# 提交并推送（改完文件之后）
git status                                      # 先看有哪些改动
git add .                                       # 放进暂存区
git commit -m "docs: 说清楚这次干了什么"          # 打包成一个版本
git push                                        # 上传到 GitHub

# 取回 GitHub 上的改动（网页上改过就先 pull）
git pull --rebase origin main

# 看提交历史
git log --oneline --graph -20
```

```powershell
# 一次性建好全部 35 周骨架（可重复执行，会覆盖 README/mistakes）
powershell -ExecutionPolicy Bypass -File "D:\学习计划\工具\generate_weeks.ps1"
```

## 编译（MSVC）

```powershell
& "D:\develop\vs2026\Community\VC\Auxiliary\Build\vcvars64.bat"   # 在 cmd 里执行
cl /nologo /W4 /std:c++17 hello.cpp /Fe:hello.exe
```

- C++ 统一用 `/std:c++17`；第 22 周（现代 C++）改用 `/std:c++latest`
- 调试用的 ASan 版本：`cl /fsanitize=address`（VS 2026 已装 AddressSanitizer 组件）

---

## 进度（打勾区，每完成一项改一次并提交）

> 这张表是这个仓库最有价值的部分：它证明"持续在学"，而且完全公开、HR 一眼可见。
> 每完成一项 → 改状态 → `git add . && git commit -m "docs: 更新进度 weekXX"` → `git push`。

**状态图例**：⬜ 未开始　🟡 进行中（已有准备产出，正式任务未完成）　✅ 本周全部产出已完成

### C 语言阶段（2026-11-02 → 2027-01-17）

| 周      | 主题                | 状态  | 产出                                                                       |
| ------ | ----------------- | --- | ------------------------------------------------------------------------ |
| week01 | 类型表实验             | 🟡  | [type-table](C/week01/type-table.c/)（已编译运行通过；正式课程 11-02 启动，其余 4 个 .c 待补） |
| week02 | 循环嵌套 + 一维数组       | ⬜   |                                                                          |
| week03 | 二维数组 + 字符与字符串     | ⬜   |                                                                          |
| week04 | 函数与递归             | ⬜   |                                                                          |
| week05 | 指针（一）             | ⬜   |                                                                          |
| week06 | 指针（二）+ 函数指针       | ⬜   |                                                                          |
| week07 | 结构体 / 联合体 / 枚举    | ⬜   |                                                                          |
| week08 | 链表                | ⬜   |                                                                          |
| week09 | 文件 IO + 动态内存      | ⬜   |                                                                          |
| week10 | 位运算 + 预处理器 + 总复习  | ⬜   |                                                                          |
| week11 | C 语言收官 + C++ 语法起步 | ⬜   |                                                                          |

### C++ / 算法 / 网安阶段（2027-01-18 → 2027-07-04）

| 周         | 主题                                      | 状态  | 产出  |
| --------- | --------------------------------------- | --- | --- |
| week12–16 | C++ 语法地基（类型系统 / 类 / 继承多态）               | ⬜   |     |
| week17–24 | C++ 进阶（模板 / STL / 现代 C++ / 工程化 / 并发）    | ⬜   |     |
| week25–29 | 算法与数据结构强化                               | ⬜   |     |
| week30–33 | 网安融合（汇编 / PE-ELF / 栈溢出 / Web+Python 工具） | ⬜   |     |
| week34–35 | 项目收官                                    | ⬜   |     |

### 里程碑（达成即打勾，面试时这是你的进度证据）

- [ ] **G1 通过**：C 语言十条全过 → 准开始 C++（清单见 `D:\学习计划\学习计划总纲_知识清单与晋级标准.md` §4）
- [ ] **G2 通过**：C++ 十一条全过 → 准系统学 Python（同上 §6）
- [ ] **G3 通过**：Python 能干活（同上 §8）
- [ ] 第一件完整作品（陌生人 3 分钟能跑起来）+ GitHub Release
- [ ] CTF 题解 ≥5 篇 + 一场正式赛成绩
- [ ] 技术文章 ≥2 篇（GitHub Pages 可访问）
- [ ] 一个被合并的开源 PR
- [ ] 大赛：官方评测通过记录 + 题型地图

## 我的其他成果（链接随建随补）

| 成果         | 链接                                     |
| ---------- | -------------------------------------- |
| 个人主页       | <https://github.com/sqs6>              |
| 学习代码库（本仓库） | <https://github.com/sqs6/study>        |
| CTF 题解与成绩  | <https://github.com/sqs6/ctf-writeups> |
| 技术笔记 / 文章  | <https://github.com/sqs6/articles>     |
| 大赛题型地图     | `notes/OceanBase_题型地图.md`              |

## 提交规范

```powershell
git add .
git commit -m "feat(week01): xxx"     # feat 功能 / fix 修 bug / docs 文档 / chore 杂务 / refactor 重构 / test 测试
git push
```

- 范围写周号或模块名：`feat(week03): 二维数组矩阵转置`
- 一天 1–3 次提交，别一次提交 20 个文件
- 提交前 `git status` 看一眼，别把密钥、成绩单、`.vs/`、`x64/`、`*.exe` 带上去
