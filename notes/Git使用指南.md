# Git 使用指南（我自己的学习仓库怎么维护）

> 这份文档写给**三个月后的我**看 —— 到时候我只记得"我改了点东西"，
> 但看到这里的命令和坑，就能立刻想起来当时在干嘛、踩了什么。
>
> 配套仓库：[sqs6/study](https://github.com/sqs6/study) ｜ 本文在 `notes/` 目录下。

## 📚 这是总纲，实操分册在 [git教程/](git教程/)

| 我想做的事 | 去哪看 |
|---|---|
| **先搞懂概念**（三个区、路径对应、谁最后改谁同步） | 👉 **本文**（第一节 ~ 第十节） |
| **照着一步步推**（Win+R 之后每一行敲什么） | 👉 [git教程/push.md](git教程/push.md) |
| **从网页取回改动 / 处理冲突** | 👉 [git教程/pull.md](git教程/pull.md) |
| **一句话速查** | 👉 [git教程/Git详细教程：push和pull.md](git教程/Git详细教程：push和pull.md)（速查表 + 报错对照） |

> **本文** = 概念 + 我的踩坑 + 我的日常流程（**长期沉淀**）
> **git教程/** = 逐步实操（**照着敲就行**，2026-10-31 写）

---

## 目录

- [一、先记这四句话](#一先记这四句话)
- [二、三个区 + 四个动作（最核心的概念）](#二三个区--四个动作最核心的概念)
- [三、日常推送流程（完整示例）](#三日常推送流程完整示例)
- [四、路径对应：文件会去哪儿](#四路径对应文件会去哪儿)
- [五、提交说明怎么写](#五提交说明怎么写)
- [六、网页编辑 vs 本地编辑](#六网页编辑-vs-本地编辑)
- [七、常见报错速查表](#七常见报错速查表)
- [八、撤销与回退](#八撤销与回退)
- [九、中文文件编码（血泪教训）](#九中文文件编码血泪教训)
- [十、本机环境备忘](#十本机环境备忘)
- [十一、我踩的坑（待补）](#十一我踩的坑待补)
- [十二、我现在的日常流程（待补）](#十二我现在的日常流程待补)

---

## 一、先记这四句话

1. **GitHub 不知道我电脑上有东西，我电脑也不知道 GitHub 上变了** —— 两边靠 `push`（送）和 `pull`（取）手动对接。
2. **改完文件只在本地**，`git push` 之后才算数。
3. **路径决定文件去哪儿**，不是文件名。
4. **每次动手前先 `git status`** —— git 每次都会直接告诉你下一步该敲什么。

---

## 二、三个区 + 四个动作（最核心的概念）

### 三个区

```
┌──────────────────────────────────────────┐
│  工作区（working tree）                   │  ← 我硬盘上的实际文件
│  D:\Study\notes\Git使用指南.md            │
├──────────────────────────────────────────┤
│  暂存区（staging area）                  │  ← git add 之后
│  ★ 挑选这次要提交的改动                     │
├──────────────────────────────────────────┤
│  本地仓库（.git 目录）                    │  ← git commit 之后
│  ★ 打包成一个版本（有编号、有说明）          │
└──────────────────────────────────────────┘
                    │
                    │  git push
                    ▼
             GitHub 远程仓库
```

### 四个动作

| 命令 | 干什么 | 类比 |
|---|---|---|
| `git add .` | 把改动放进**暂存区** | 放进购物车 |
| `git commit -m "说明"` | 把暂存区打包成**一个版本** | 结账，打快照 |
| `git push` | 把本地版本**上传到 GitHub** | 把货送出去 |
| `git pull` | 把 GitHub 的改动**取回本地** | 取货 |

**`git status` 是安全带** —— 随时看它，它会写明下一步该敲什么。

---

## 三、日常推送流程（完整示例）

以"往 study 仓库加一份笔记"为例。

```bash
cd /d/Study            # ① 进到仓库根目录
git status              # ② 先看：有哪些改动？（习惯性动作）
# ③ 改文件（用 VS 2026 编辑，然后 Ctrl+S 保存）
git add .               # ④ 把改动放进暂存区（成功时没有任何输出）
git status              # ⑤ 再看一眼：应该变成 Changes to be committed
git commit -m "docs: 添加 C 语言基础笔记（数据类型/运算符/流程控制，2026-10-24）"
git log --oneline -3    # ⑥ 确认新版本在最上面
git push                # ⑦ 真正上传
```

### 每一步该看到什么

**② 第一次 `git status`（文件还是新的）**
```
On branch main
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        "notes/C\345\237\272\347\241\200\347\254\224\350\256\260.md"

nothing added to commit but untracked files present (use "git add" to track)
```

**⑤ add 之后 `git status`（进了暂存区）**
```
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	new file:   notes/C基础笔记.md
```
> `Untracked files:` 那一段消失，`Changes to be committed:` 出现 = 成功。

**⑥ commit 的输出**
```
[main 998f1d3] docs: 添加 C 语言基础笔记（数据类型/运算符/流程控制，2026-10-24）
 1 file changed, 437 insertions(+)
 create mode 100644 notes/C基础笔记.md
```

**⑦ push 的输出（重点看最后一行）**
```
To https://github.com/sqs6/study.git
   bc681c2..998f1d3  main -> main
```
> `bc681c2..998f1d3` = 从旧版本推到新版本；`main -> main` = 本地 main 推到了远程 main。
> **看到这行就成功了。**

---

## 四、路径对应：文件会去哪儿

**这是最容易搞错的地方：git 记的是"相对仓库根的路径"，不是文件名。**

```
D:\Study\notes\Git使用指南.md
     └────┬────┘
      仓库根目录        相对路径
```

这个相对路径 `notes/Git使用指南.md` 就是 GitHub 上的位置：

```
github.com/sqs6/study  →  notes  →  Git使用指南.md
```

### 同名 ≠ 同一个东西

| 情况 | 结果 |
|---|---|
| 同路径 + 内容改了 | **覆盖更新** |
| 同路径 + 文件是新的 | **新建** |
| **同名但不同路径** | **两个不同的文件**，互不覆盖 |
| 删了本地文件 | GitHub 上也**会消失**（历史里还查得到）|

> 例：`D:\Study\c-notes.md` 和 `D:\Study\notes\c-notes.md` 同名，
> 但在 GitHub 上是两个不同的文件（根目录一个、notes/ 一个）。

### Windows 下看到的一串八进制

```
"notes/C\345\237\272\347\241\200\347\254\224\350\256\260.md"
```
这是 git 把「C基础笔记.md」的 UTF-8 字节**转义成八进制**显示。
`345`=0xE5 `237`=0x9F `272`=0xBA … 拼起来就是「C基」…
**实际文件没有任何问题，GitHub 页面上也是正常中文。**

---

## 五、提交说明怎么写

### 格式

```
<类型>(<范围>): <一句话说明这次干了什么>
```

### 六个类型（够用了）

| 类型 | 什么时候用 | 例子 |
|---|---|---|
| `feat` | 新功能 / 新代码 | `feat(week01): 冒泡排序实现` |
| `fix` | 修 bug | `fix(week01): 修复 %llu 格式化警告` |
| `docs` | **改文档 / 笔记 / README** | `docs: 添加 C 语言基础笔记` |
| `chore` | 杂活（改配置、加 .gitignore、初始化） | `chore: 忽略 .env 和编译产物` |
| `refactor` | 重构（结构变了，功能没变） | `refactor(week05): 链表操作拆成独立函数` |
| `test` | 加测试 | `test(week02): 补排序正确性测试` |

### 范围（括号里）

`week01` ｜ `week03` ｜ `readme` ｜ `notes` ｜ `profile` ｜ `articles`

### 三条实用规则

1. **中文完全没问题**（GitHub 正常显示）
2. **别写没信息量的**：`update` / `修改代码` / `fix bug` ← 三个月后完全看不出发生了什么
3. **一句话就够**，但要写清"哪个模块 + 干了什么"

### 我的真实提交历史（可以照这个风格）

```
998f1d3  docs: 添加 C 语言基础笔记（数据类型/运算符/流程控制，2026-10-24）
bc681c2  docs: 35 个周 README 与 Python 副线改为清单制口径（不设每日时长）
94ab8e9  docs: 进度表加状态图例；week01 标为进行中（类型表实验已编译运行通过）
9f0f04e  docs: README 加进度打勾区与里程碑；新增 MiniOB 题型地图
be3f259  chore: 初始化 35 周学习骨架（C/CPP week01-35、错题本模板、.gitignore）
```

---

## 六、网页编辑 vs 本地编辑

**两条路都可行，GitHub 网页上每个文件右上角有 ✏️ Edit file，改完点 Commit changes 就自动提交+推送了。**

| | 网页编辑 | 本地 push |
|---|---|---|
| 适合 | README、小文档、改错别字 | 代码、多文件、要改很多遍 |
| 一次改多个文件 | ❌ 一个一个来 | ✅ 一次全加 |
| 大文件 / 二进制 | ❌ 只能上传 | ✅ 无所谓 |

### 混用规则：**谁最后动，就由谁同步**

| 谁改了 | 我要做什么 |
|---|---|
| **我在本地**改了 | `git add .` → `git commit` → `git push` |
| **我在网页**改了 | 本地要先 `git pull`，才能看到网页的改动 |
| 别人给我提了 PR | `git pull` |

> **踩过的坑**：我在网页上改了 study 的 README，然后直接 push，git 拒绝了。
> 因为远程有改动、本地没有。**先 `git pull --rebase origin main` 把云端的取下来，再 push。**

---

## 七、常见报错速查表

| 报错 | 原因 | 解法 |
|---|---|---|
| `Updates were rejected because the remote contains work that you don't have locally` | 远程有改动、本地没有 | `git pull --rebase origin main` → `git push` |
| `error: failed to push some refs` | 同上（概括性错误） | 看上面那行提示，多半也是要先 pull |
| `fatal: pathspec '.' did not match any files` | `git add .` 少了空格，或不在仓库根目录 | 敲 `pwd` 确认位置；`git add .`（add 后面有空格、点前面有空格） |
| `Author identity unknown` | 没配身份 | `git config --global user.name "孙卿单"` 和 `git config --global user.email "343853210+sqs6@users.noreply.github.com"` |
| `git: 'bash' is not a git command` | 新版 Git 没有 `git bash` 子命令了 | 直接跑 `D:\git\Git\git-bash.exe` |
| `git` 不是内部或外部命令 | git 不在当前终端的 PATH 里 | 用完整路径 `D:\git\Git\cmd\git.exe`，或换 Git Bash |
| 推送要你输用户名密码 | 凭据没命中 | 检查 Windows 凭据管理器里有没有 `git:https://github.com` |
| 页面上中文全是 `鎴戠殑` 之类 | **文件是 GBK，GitHub 只认 UTF-8** | 见第九节 |

---

## 八、撤销与回退

| 想撤销 | 敲什么 | 效果 |
|---|---|---|
| 撤销刚 `add` 的 | `git restore --staged <文件>` | 文件退回"未跟踪"（等于没 add） |
| 撤销刚 `commit` 的（**还没 push**） | `git reset --soft HEAD~1` | 改动回到暂存区，提交记录消失 |
| 撤销刚 `commit` 的（还没 push），想丢掉改动 | `git reset --hard HEAD~1` | ⚠️ **改动全丢，慎用** |
| 改上一次提交的说明 | `git commit --amend -m "新的说明"` | 只改说明，内容不变 |
| 已经 push 了，想改 | `git push --force-with-lease` | ⚠️ 改写历史，已 push 的要慎用 |

> **建议**：除非明确知道后果，否则别用 `--hard` 和 `--force`。
> 记不住就**先 `git log` 看看现状**，再决定。

---

## 九、中文文件编码（血泪教训）

### 问题

Windows 中文版默认把 `.c` 文件存成 **GBK**（代码页 936），而 **GitHub 只认 UTF-8**。
直接推上去 → 页面上满屏乱码，而且**改后缀救不回来**（信息在误解码时已经丢了）。

### 怎么转

**VS 2026 里**（我最常用）：

```
文件 → 另存为
  → 点「保存」按钮右边的小箭头（不是点保存本身）
  → 选「编码保存」
  → 编码选：Unicode (UTF-8 带签名)   ← .c 源码要带 BOM，MSVC 才不报 warning C4819
            Unicode (UTF-8 无签名)   ← .md 文档不用 BOM
```

> **状态栏显示的 `18030` / `936` 是"当前文件是什么编码"的信息，不是让你去选它。**
> 你要改的是**保存时**用的编码。

**VS Code 里**：右下角点编码 → 「Save with Encoding」→ UTF-8。

**PowerShell 一行**：

```powershell
$c = Get-Content "文件路径.c" -Raw -Encoding Default        # Default = 系统 ANSI(中文=GBK)
[System.IO.File]::WriteAllText("文件路径.c", $c, (New-Object System.Text.UTF8Encoding($true)))
```
> `UTF8Encoding($true)` = 带 BOM（.c 用）；`$false` = 不带 BOM（.md 用）。

### 后缀和 Markdown 的关系（另一个常见误解）

**改后缀 ≠ 变成 Markdown。** 后缀只是告诉 GitHub"用哪个渲染器"：

| 后缀 | 渲染器 | 效果 |
|---|---|---|
| `.c` | C 语法高亮 | 注释显示成代码 |
| `.md` | Markdown | 注释变成普通文字（因为 `//` 在 Markdown 里没意义） |

**真正起作用的是内容里有没有 Markdown 语法**：`# 标题`、`**粗体**`、`- 列表`、`` `代码` ``、``` 代码块 ```。

---

## 十、本机环境备忘

| 项 | 值 |
|---|---|
| Git 安装位置 | `D:\git\Git`（**注意**：曾装在 `D:\develop\git\Git`，后来搬过来，开始菜单快捷方式一度失效） |
| 开 Git Bash | 开始菜单 → Git → Git Bash，或 Win+R 跑 `D:\git\Git\git-bash.exe` |
| git 可执行文件 | `D:\git\Git\cmd\git.exe`（系统 PATH 里有，CMD/PowerShell 里能直接敲 `git`） |
| Git Bash 里的路径写法 | `cd /d/Study`（**正斜杠**，盘符前加斜杠） |
| PowerShell 里的路径写法 | `cd D:\Study`（反斜杠） |
| 全局身份 | `孙卿单 <343853210+sqs6@users.noreply.github.com>` |
| 远程地址 | `https://github.com/sqs6/<仓库名>.git`（用 HTTPS；本机 22 端口不通，SSH 走不了） |
| 凭据 | Windows 凭据管理器里存着 `git:https://github.com`（用户 sqs6），push 不会问密码 |

---

## 十一、我踩的坑（待补）

> 这一节留给我自己写 —— **当时的感受比事后的描述有用得多。**
> 建议按"坑 → 现象 → 原因 → 以后怎么避免"来写。

**坑 1（待补）**

**坑 2（待补）**

---

## 十二、我现在的日常流程（待补）

> 这一节也留给我自己写。写清楚我实际每天是怎么做的，
> 免得三个月后看着这份文档还要重新想一遍流程。

**我的一天（待补）：**

---

*这份文档本身也用 git 维护 —— 改完记得 `git add .` → `git commit` → `git push`。*
