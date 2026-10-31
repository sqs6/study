# Git 详细教程：push 和 pull

> 这份教程写给**三个月后的我**。
> 到时候我只记得"我改了点东西"，但照着这里敲一遍就能想起来当时在干嘛、踩了什么坑。
>
> 配套仓库：[sqs6/study](https://github.com/sqs6/study) ｜ 本目录在 `notes/git教程/` 下。

## 📎 相关文档

| 我想做的事 | 去哪看 |
|---|---|
| **逐步实操**（push / pull 每一行敲什么） | 👉 本目录的 [push.md](push.md) / [pull.md](pull.md) |
| **一句话速查 + 报错对照表** | 👉 **本文**（第七、八节） |
| **概念总纲 + 我踩的坑 + 我的日常流程** | 👉 [../Git使用指南.md](../Git使用指南.md) |

> **本文** = 速查表 + 报错处理（**出问题查这里**）
> **push.md / pull.md** = 逐步实操（**照着敲就行**）
> **[../Git使用指南.md](../Git使用指南.md)** = 概念 + 我的长期沉淀（**慢慢写**）

---

## 目录

| 文件 | 内容 |
|---|---|
| **[push.md](push.md)** | 把本地改动上传到 GitHub —— 完整 9 步，每步含义 + 真实输出 |
| **[pull.md](pull.md)** | 把 GitHub 上的改动取回本地 —— 三种情况 + 冲突解决 |

---

## 一、先记这四句话

1. **GitHub 不知道我电脑上有东西，我电脑也不知道 GitHub 上变了** —— 两边靠 `push`（送）和 `pull`（取）手动对接。
2. **改完文件只在本地**，`git push` 之后才算数。
3. **路径决定文件去哪儿**，不是文件名。
4. **每次动手前先 `git status`** —— git 每次都会直接写出下一步该敲什么。

---

## 二、核心概念（不懂这个，命令就只是背）

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
│  ★ 打包成一个版本（有编号、有说明、有时间）    │
└──────────────────────────────────────────┘
                    │
                    │  git push
                    ▼
             GitHub 远程仓库
                    ▲
                    │  git pull
                    │
```

### 四个动作

| 命令 | 干什么 | 类比 |
|---|---|---|
| `git add .` | 把改动放进**暂存区** | 放进购物车 |
| `git commit -m "说明"` | 把暂存区打包成**一个版本** | 结账，打快照 |
| `git push` | 把本地版本**上传到 GitHub** | 把货送出去 |
| `git pull` | 把 GitHub 的改动**取回本地** | 取货 |

---

## 三、路径对应：文件会去哪儿

**git 记的是"相对仓库根的路径"，不是文件名。**

```
D:\Study\notes\git教程\push.md
     └────┬────┘
      仓库根目录        相对路径
```

这个相对路径就是 GitHub 上的位置：

```
github.com/sqs6/study  →  notes  →  git教程  →  push.md
```

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

## 四、核心规则：**谁最后改，就由谁同步**

| 谁改了 | 我要做什么 |
|---|---|
| **我在本地**改了 | `git add .` → `git commit` → `git push` |
| **我在网页**改了 | 本地要先 `git pull`，才能看到网页的改动 |
| 别人给我提了 PR | `git pull` |

> ⚠️ **踩过的坑**：我在网页上改了 study 的 README，然后直接 push，git 拒绝了：
> ```
> error: failed to push some refs
> hint: Updates were rejected because the remote contains work that you don't have locally.
> ```
> 因为远程有改动、本地没有。**先 `git pull --rebase origin main` 把云端的取下来，再 push。**

---

## 五、开 Git Bash（所有操作的起点）

**按 `Win + R`** → 粘贴：

```
D:\git\Git\git-bash.exe
```

**回车。** 会出现一个黑窗口，标题 `UCRT64:/c/Users/17550`，里面是这样一行提示符：

```
孙卿单@LAPTOP-46VKQ4OI UCRT64 ~/ ← 开窗时在家目录
```

> 💡 **为什么用 Git Bash 不用 CMD / VS2026 的终端？**
> | | `cd` 写法 | `git` 能直接敲吗 |
> |---|---|---|
> | **Git Bash** ✅ | `cd /d/Study` | ✅ 自带 PATH |
> | CMD / PowerShell | `cd D:\Study` | ⚠️ 得写全路径 `D:\git\Git\cmd\git.exe` |
>
> **Git Bash 里路径用正斜杠，盘符前加斜杠** —— `/d/Study` = `D:\Study`。

### 你的 6 个仓库（换这一行就能切仓库）

| 要推的仓库 | `cd` |
|---|---|
| 学习代码库 | `cd /d/Study` |
| 主页 | `cd /d/Repos/sqs6` |
| 技术笔记 | `cd /d/Repos/articles` |
| CTF 题解 | `cd /d/Repos/ctf-writeups` |
| 自研工具 | `cd /d/Repos/tools` |
| 比赛参赛 | `cd /d/miniob/miniob` |

> 不确定自己在哪？敲 `pwd`。

---

## 六、提交说明怎么写

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

### 三条规则

1. **中文完全没问题**（GitHub 正常显示）
2. **别写没信息量的**：`update` / `修改代码` / `fix bug` ← 三个月后完全看不出发生了什么
3. **一句话就够**，但要写清"哪个模块 + 干了什么"

---

## 七、一页速查

### push（送）

```bash
cd /d/Study
git status
# 改文件…
git add .
git commit -m "docs: 说清楚这次干了什么"
git push
```

### pull（取）

```bash
cd /d/Study
git status
git pull --rebase origin main
```

> **在本地改文件之前，如果不确定网页上有没有被改过，先 pull 一次。**

### 常用查询

```bash
git status                    # 现在有哪些改动
git log --oneline -3          # 最近 3 个版本
git log --oneline --graph -20 # 带分支图的历史
git remote -v                 # 这个文件夹对应 GitHub 上哪个仓库
git diff                      # 具体改了什么（还没 add 时）
```

---

## 八、报错速查表

| 报错 | 原因 | 解法 |
|---|---|---|
| `Updates were rejected because the remote contains work that you don't have locally` | 远程有改动、本地没有 | `git pull --rebase origin main` → `git push` |
| `error: failed to push some refs` | 同上（概括性错误） | 看上面那行提示 |
| `error: Your local changes to the following files would be overwritten by merge` | 本地有**没提交**的改动，pull 会覆盖它 | 先 `git add . && git commit`，或 `git stash` |
| `CONFLICT (content): Merge conflict in xxx` | 同一个文件两边都改了 | 见 [pull.md](pull.md) 的冲突处理 |
| `fatal: pathspec '.' did not match any files` | `git add .` 少了空格，或不在仓库根目录 | 敲 `pwd` 确认位置；`git add .`（两个空格都不能少）|
| `Author identity unknown` | 没配身份 | `git config --global user.name "孙卿单"` 和 `git config --global user.email "343853210+sqs6@users.noreply.github.com"` |
| `git: 'bash' is not a git command` | 新版 Git 没有 `git bash` 子命令 | 直接跑 `D:\git\Git\git-bash.exe` |
| `git` 不是内部或外部命令 | 不在 Git Bash 里 | 回第五节重开 Git Bash |
| 推送要你输用户名密码 | 凭据没命中 | 检查 Windows 凭据管理器里有没有 `git:https://github.com` |
| 页面上中文全是 `鎴戠殑` | **文件是 GBK，GitHub 只认 UTF-8** | 见第九节 |

---

## 九、中文文件编码（血泪教训）

### 问题

Windows 中文版默认把 `.c` 文件存成 **GBK**（代码页 936），而 **GitHub 只认 UTF-8**。
直接推上去 → 满屏乱码，而且**改后缀救不回来**（信息在误解码时已经丢了）。

### 怎么转（VS 2026）

```
文件 → 另存为
  → 点「保存」按钮右边的小箭头（不是点保存本身）
  → 选「编码保存」
  → 编码选：Unicode (UTF-8 带签名)   ← .c 源码要带 BOM，MSVC 才不报 warning C4819
            Unicode (UTF-8 无签名)   ← .md 文档不用 BOM
```

> **状态栏显示的 `18030` / `936` 是"当前文件是什么编码"的信息，不是让你去选它。**
> 你要改的是**保存时**用的编码。

### 后缀和 Markdown 的关系（另一个常见误解）

**改后缀 ≠ 变成 Markdown。** 后缀只是告诉 GitHub"用哪个渲染器"：

| 后缀 | 渲染器 | 效果 |
|---|---|---|
| `.c` | C 语法高亮 | 注释显示成代码 |
| `.md` | Markdown | 注释变成普通文字（因为 `//` 在 Markdown 里没意义）|

**真正起作用的是内容里有没有 Markdown 语法**：`# 标题`、`**粗体**`、`- 列表`、`` `代码` ``、``` 代码块 ```。

---

## 十、本机环境备忘

| 项 | 值 |
|---|---|
| Git 安装位置 | `D:\git\Git`（**注意**：曾装在 `D:\develop\git\Git`，后来搬过来，开始菜单快捷方式一度失效）|
| 开 Git Bash | Win+R 跑 `D:\git\Git\git-bash.exe` |
| git 可执行文件 | `D:\git\Git\cmd\git.exe`（**已在 PATH**，CMD 里也能直接敲 `git`）|
| Git Bash 里的路径写法 | `cd /d/Study`（**正斜杠**，盘符前加斜杠）|
| PowerShell 里的路径写法 | `cd D:\Study`（反斜杠）|
| 全局身份 | `孙卿单 <343853210+sqs6@users.noreply.github.com>` |
| 远程地址 | `https://github.com/sqs6/<仓库名>.git`（**用 HTTPS**；本机 22 端口不通，SSH 走不了）|
| 凭据 | Windows 凭据管理器里存着 `git:https://github.com`（用户 sqs6），push 不会问密码 |

---

*这份教程本身也用 git 维护 —— 改完记得 `git add .` → `git commit` → `git push`。*
