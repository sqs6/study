# Git 详细教程：cmd 与 Git Bash 对比

> 这份文档回答一个问题：**同样是「把代码推到 GitHub」，在 Windows 的 cmd 和 Git Bash 里敲的命令有什么区别？**
>
> 文档里所有命令和报错都是**在这台机器上实测过的**（2026-10-31），不是凭印象写的。
>
> 配套阅读：[Git详细教程：push和pull.md](git教程/Git详细教程：push和pull.md)（push / pull 的完整流程）、
> [Git使用指南.md](Git使用指南.md)（总纲）、[push.md](git教程/push.md)、[pull.md](git教程/pull.md)。

---

## 一句话结论

> **git 命令一个字都不用改，改的只有「路径怎么写」和「敲命令前先看清楚自己在哪个终端」。**

两个终端跑的是**同一个 git**（都是 `git version 2.56.0.windows.2`），
`git add` / `git commit` / `git push` 完全一致。真正会咬人的是三处：

| #   | 坑              | 一句话                                                |
| --- | -------------- | -------------------------------------------------- |
| 1   | **路径写法**       | cmd 用 `D:\Repos\tools`，Git Bash 用 `/d/Repos/tools` |
| 2   | **`/d` 的两种含义** | cmd 里 `/d` 是「顺便换盘」的开关；Git Bash 里 `/d` 是路径的一部分      |
| 3   | **反斜杠和反引号**    | Git Bash 里 `\` 是转义符、`` ` `` 是命令替换 —— cmd 里它们没这个意思  |

---

## 一、这两个东西分别是什么

|       | **cmd**（命令提示符）                   | **Git Bash**                                      |
| ----- | -------------------------------- | ------------------------------------------------- |
| 本质    | Windows 自带的 DOS 命令行              | Git for Windows 自带的 **Linux 壳**（MSYS2/Cygwin 模拟层） |
| 路径观   | Windows 风格：`D:\Repos\tools`      | Unix 风格：`/d/Repos/tools`                          |
| 盘符    | 是独立的一层（C 盘、D 盘各是一个根）             | 变成根目录下的一个**文件夹**（`/c`、`/d`）                       |
| 自带命令  | `dir` `type` `copy` `move` `del` | `ls` `cat` `cp` `mv` `rm` `head` `tail` `grep`    |
| 通配符   | `*` `?`                          | `*` `?` `[]`（更强）                                  |
| 环境变量  | `%OS%`                           | `$OS`（`$OSTYPE` = `cygwin`）                       |
| 路径分隔符 | `\`                              | `/`                                               |
| 删文件   | `del` / `rmdir`                  | `rm` / `rmdir`                                    |
| 历史记录  | `↑` 键（doskey）                    | `↑` 键 + `history`                                 |
| 清屏    | `cls`                            | `clear`                                           |

**它们都只是「壳」** —— 真正干活的 `git.exe` 是同一个文件（`D:\git\Git\cmd\git.exe`，在系统 PATH 里）。
所以推代码这件事，**两个终端的能力完全一样**。

---

## 二、怎么打开

### 方式 A：Win + R（最快）

| 要开       | Win+R 里输入                              |
| -------- | -------------------------------------- |
| cmd      | `cmd`                                  |
| Git Bash | `D:\git\Git\git-bash.exe --cd-to-home` |

> `--cd-to-home` = 启动时回到用户主目录（相当于 `~`）。

### 方式 B：开始菜单

`Win` → 输入「Git Bash」→ 回车。图标是那个黑色带 `>_` 的。

### 方式 C：⭐ 右键菜单（最省事，强烈推荐）

在**任意文件夹**里 → 空白处点右键 → 选 **「Open Git Bash here」**。

- 本机已注册（`HKLM\SOFTWARE\Classes\Directory\shell\git_shell` → `"D:\git\Git\git-bash.exe" "--cd=%1"`）
- **效果**：终端直接开在那个文件夹里，提示符已经是 `.../d/Repos/tools (main)`
- **好处**：`cd` 这一步直接省掉，也不会敲错路径

> 提示：cmd 没有这个右键菜单（除非装第三方工具）。

---

## 三、⭐ 坑 1：路径写法

### 对照表

| Windows 实际路径     | cmd 里写           | Git Bash 里写      |
| ---------------- | ---------------- | ---------------- |
| `D:\`            | `D:\`            | `/d/`            |
| `D:\Repos`       | `D:\Repos`       | `/d/Repos`       |
| `D:\Repos\tools` | `D:\Repos\tools` | `/d/Repos/tools` |
| `D:\Study\网安相关`  | `D:\Study\网安相关`  | `/d/Study/网安相关`  |
| `C:\Users\17550` | `C:\Users\17550` | `/c/Users/17550` |

**两条规则**：

1. 盘符 `D:` → 变成一级文件夹 `d`（前面加斜杠）
2. 分隔符 `\` → 全部换成 `/`

### 实测：在 Git Bash 里误用 Windows 写法

```
$ cd D:\Repos\tools
/usr/bin/bash: line 1: cd: D:Repostools: No such file or directory
```

👀 **注意报错里的 `D:Repostools` —— 反斜杠和字母被吃掉了**。
原因：bash 里 `\` 是**转义符**，`\R` → `R`，`\t` → **制表符 TAB**。

### 实测：在 cmd 里误用 Git Bash 写法

```
> cd /d/Repos/tools
The syntax of the command is incorrect.
```

### 快速自检

| 终端       | 看哪里        | 应该显示                                               |
| -------- | ---------- | -------------------------------------------------- |
| cmd      | 提示符        | `D:\Repos\tools>`                                  |
| Git Bash | 提示符        | `孙卿单@LAPTOP-46VKQ4OI UCRT64 /d/Repos/tools (main)` |
| Git Bash | 敲 `pwd`    | `/d/Repos/tools`                                   |
| Git Bash | 敲 `pwd -W` | `D:/Study` ← **反斜杠版的 Windows 路径**，非常好用             |

> `pwd -W` 是 Git Bash 独有的小彩蛋：把 Unix 路径翻译成 Windows 路径。

---

## 四、⭐ 坑 2：`/d` 的两种含义

**同一个 `/d`，在两个终端里是完全不同的东西。**

| cd是切换目录      | `cd /d D:\Repos\tools` | `cd /d/Repos/tools`         |
| ------------ | ---------------------- | --------------------------- |
| **cmd**      | `/d` 是**开关** =「顺便切换盘符」 | ❌ 语法错误                      |
| **Git Bash** | ❌ 路径不存在                | `/d` 是**路径的一部分** = D 盘这个文件夹 |

**为什么 cmd 需要 `/d`**：
`cd` 默认只切换**当前盘**的目录。你在 `C:` 盘时敲 `cd D:\Repos\tools` 会失败，
加 `/d` 才是「切换目录 **并且** 换盘」。

**为什么 Git Bash 不需要**：
它所有路径都从根 `/` 算起，压根没有「换盘」这回事。

---

## 五、git 命令对照：**完全一样**

| 操作   | cmd                             | Git Bash                    |
| ---- | ------------------------------- | --------------------------- |
| 进仓库  | `cd /d D:\Study`                | `cd /d/Study`               |
| 看状态  | `git status`                    | `git status`                |
| 暂存   | `git add .`                     | `git add .`                 |
| 提交   | `git commit -m "docs: xxx"`     | `git commit -m "docs: xxx"` |
| 推送   | `git push`                      | `git push`                  |
| 看历史  | `git log --oneline -3`          | `git log --oneline -3`      |
| 看差异  | `git diff`                      | `git diff`                  |
| 撤销暂存 | `git restore --staged <文件>`     | 同左                          |
| 拉取   | `git pull --rebase origin main` | 同左                          |

**一字不差。** 唯一区别是**第一条 `cd`**。

---

## 六、常用命令对照表

| 干什么     | cmd                   | Git Bash                 |
| ------- | --------------------- | ------------------------ |
| 列目录     | `dir` / `dir /b`      | `ls` / `ls -1`           |
| 看文件内容   | `type 文件`             | `cat 文件` / `head -20 文件` |
| 复制      | `copy 源 目标`           | `cp 源 目标`                |
| 移动 / 改名 | `move 源 目标` / `ren`   | `mv 源 目标`                |
| 删除      | `del 文件` / `rmdir 目录` | `rm 文件` / `rm -r 目录`     |
| 新建目录    | `mkdir 名字`            | `mkdir 名字`               |
| 清屏      | `cls`                 | `clear`                  |
| 我在哪     | `cd`（无参数）             | `pwd`                    |
| 找命令在哪   | `where git`           | `which git`              |
| 上一个目录   | （无）                   | `cd -`                   |
| 根目录     | `cd \`                | `cd /`                   |
| 上一级     | `cd ..`               | `cd ..`                  |
| 搜索文本    | `findstr "词" 文件`      | `grep "词" 文件`            |
| 补全文件名   | Tab（弱）                | Tab（强，能补全整个路径）           |

> 实测：cmd 里敲 `ls` / `cat` / `pwd` 都会报
> `'xxx' is not recognized as an internal or external command`。

---

## 七、实战：同一个 push 流程

### 在 cmd 里

```cmd
cd /d D:\Repos\tools
git status
git add .
git commit -m "chore: .gitignore 补密钥规则（.env / *.key / *.pem / secrets/）"
git push
```

### 在 Git Bash 里

```bash
cd /d/Repos/tools
git status
git add .
git commit -m "chore: .gitignore 补密钥规则（.env / *.key / *.pem / secrets/）"
git push
```

### 或者：连 `cd` 都不要（右键大法）

1. 打开 `D:\Repos\tools` 文件夹
2. 空白处右键 → **Open Git Bash here**
3. 直接敲：

```bash
git status
git add .
git commit -m "chore: .gitignore 补密钥规则（.env / *.key / *.pem / secrets/）"
git push
```

---

## 八、⚠️ 操作注意事项（真踩过的坑）

### 1. 引号必须是**英文半角** `"`

中文引号 `“”` 会直接报 `unexpected EOF`。

> **提交信息里可以用中文，但外面的那对引号必须是 `"`。**
> 敲引号前把输入法切到英文。

### 2. 提交信息的中文乱码

- **自己手敲**（交互式终端）→ 没问题，你推的 `00ccea7` / `fce8b8c` 中文标题在 GitHub 上都正常
- **脚本 / 工具里传中文** → 可能乱码。稳妥写法：把提交信息写进 **UTF-8 文件**，再
  `git commit -F 文件`
  （本机的 cmd 代码页是 936/GBK，命令行参数里的中文可能在传给 git 之前就被吃掉）

### 3. Git Bash 里反引号 `` ` `` 是**命令替换**

```bash
echo `pwd`      # 输出 /d/Study        ← 反引号里的内容被当成命令执行了
echo '`pwd`'    # 输出 `pwd`           ← 单引号里不替换
```

**推代码基本用不到反引号**，但要知道：**在 Git Bash 里敲反引号不是"打一个符号"，是"执行一段命令"**。
如果误敲了，会当场执行一段你没预期的命令。

### 4. Git Bash 里反斜杠是**转义符**

```bash
cd D:\Repos\tools     # ❌ 报错：cd: D:Repostools: No such file or directory
```

`\R` → `R`，`\t` → TAB。**Git Bash 里路径一律用正斜杠。**

### 5. 粘贴方式不同

| 终端       | 粘贴                            |
| -------- | ----------------------------- |
| cmd      | **右键**（老版本 cmd 不认 `Ctrl+V`）   |
| Git Bash | `Ctrl+V` 或 `Ctrl+Shift+V` 或右键 |

**在 cmd 里复制走「在消息里 `Ctrl+C` → 到窗口里 `Ctrl+V`」**；
**在 Git Bash 里直接 `Ctrl+V`**。

### 6. 路径大小写

- **cmd**：完全不敏感（`D:\REPOS\TOOLS` 能进）
- **Git Bash**：盘符部分不敏感（实测 `cd /D/REPOS/TOOLS` 能进），但**目录名和文件名建议严格按实际大小写写**
  （Windows 本身不区分，但 Git 的路径记录区分）

### 7. ⭐ 换行符（CRLF / LF）—— 中文 `.c` 文件的重灾区

本机实测配置：

| 位置                      | `core.autocrlf`             |
| ----------------------- | --------------------------- |
| 全局 `~/.gitconfig`       | **`false`**（覆盖了系统级的 `true`） |
| `D:\Study` 仓库级          | `false`                     |
| `D:\Repos\articles` 仓库级 | `false`                     |
| `.gitattributes`        | **两个仓库都没有**                 |

**含义**：`autocrlf=false` 意味着 **git 不做任何自动换行符转换**，文件里是什么就存什么。

**所以**：

- VS 存成 CRLF → GitHub 上就是 CRLF
- 别的工具存成 LF → GitHub 上就是 LF
- **同一个文件在两台机器上用不同编辑器存过 → diff 会显示「整个文件都变了」**（其实只是行尾不同）

### ⚠️ 本仓库的实测现状（2026-10-31）

`D:\Study` 里 85 个文本文件的换行符分布：

| 类型    | 换行符      | 数量       |
| ----- | -------- | -------- |
| `.md` | **CRLF** | **74 个** |
| `.md` | LF       | 10 个     |
| `.c`  | LF       | 1 个      |

**也就是说：仓库现在是混合状态**，74 个周 README 用 CRLF，而另外 10 个（包括 `README.md` 和几篇新写的笔记）用 LF。

**⚠️ 所以「现在加 `.gitattributes` 强制 `eol=lf`」这个动作不能随手做** ——
加了之后，git 会在你下次 `git add .` 时**把那 74 个 CRLF 文件全部规范化成 LF**，
`git diff` 会显示几十个文件「整文件都变了」，很难看也容易让人误以为改坏了什么。

**要规范化的话，正确姿势是**：

1. 先单独加 `.gitattributes` 并**单独提交一次**，提交信息写清楚意图：
   `chore: 加 .gitattributes 统一换行符为 LF（本次会规范化全部文本文件）`
2. 这一次提交的 diff 会很大 —— **这是预期内的，不是 bug**
3. 之后再改文件，diff 就干净了（每个文件只显示你真正改的那几行）

**建议**：**先别动**。等到 CRLF 真的碍事了（比如某个文件在 diff 里老显示全变），再按上面三步做。

### 8. 中文文件名

两边都没问题，实测：

```bash
cd /d/Study && ls -1 "notes/git教程"
# Git详细教程：push和pull.md
```

> 但**路径里有空格或中文时，命令里最好加双引号**：`"notes/git教程"`
> ——不加的话 bash 会被空格拆成两个参数。

### 9. `.gitignore` 里别忽略掉该交的东西

`git add .` 是「当前目录 + 所有子目录」全加。
如果 `.gitignore` 写得太宽，`add .` 会**静默跳过**那些文件 —— 你以为提交了，其实没有。

**每次 commit 前跑一次 `git status`**，确认「Changes to be committed」里的文件清单跟你预期一致。

---

## 九、常见报错对照表

| 报错                                                 | 出现在      | 原因                               | 解法                                                                                             |
| -------------------------------------------------- | -------- | -------------------------------- | ---------------------------------------------------------------------------------------------- |
| `'ls' is not recognized...`                        | cmd      | cmd 没有 `ls`                      | 用 `dir`                                                                                        |
| `'cat' is not recognized...`                       | cmd      | cmd 没有 `cat`                     | 用 `type`                                                                                       |
| `'pwd' is not recognized...`                       | cmd      | cmd 没有 `pwd`                     | 敲 `cd`（无参数）看当前位置                                                                               |
| `The syntax of the command is incorrect.`          | cmd      | 在 cmd 里用了 Git Bash 的 `cd /d/xxx` | 改成 `cd /d D:\xxx`                                                                              |
| `cd: D:Repostools: No such file or directory`      | Git Bash | 在 bash 里用了 Windows 写法（`\` 被当转义符） | 改成 `cd /d/Repos/tools`                                                                         |
| `unexpected EOF`                                   | 两个终端     | 用了中文引号 `“”`                      | 换成英文半角 `"`                                                                                     |
| `Please tell me who you are`                       | 两个终端     | git 不知道你是谁                       | `git config --global user.name "孙卿单"` + `user.email "343853210+sqs6@users.noreply.github.com"` |
| `GH007: ... would publish a private email address` | 两个终端     | 提交邮箱是真实邮箱                        | 改用 `343853210+sqs6@users.noreply.github.com`                                                   |
| `Updates were rejected`                            | 两个终端     | 远端比你新                            | `git pull --rebase origin main` 然后 `git push`                                                  |
| `fatal: could not read Username`                   | 两个终端     | 凭据没命中                            | Windows 凭据管理器里确认 `git:https://github.com`                                                      |

---

## 十、我该用哪个？

| 场景                  | 推荐                                                      |
| ------------------- | ------------------------------------------------------- |
| **日常推代码**           | **Git Bash** —— 路径好写、`ls`/`cat`/`grep`/`pwd` 都有、Tab 补全强 |
| **想在某个文件夹直接开终端**    | **Git Bash + 右键「Open Git Bash here」** —— 连 `cd` 都省      |
| 已经有 cmd 窗口开着、不想再开一个 | cmd 也完全够用 —— **git 命令一模一样**                             |
| 教别人 / 写文档           | **两个都写出来**，标明路径写法不同（本文件）                                |

**我的建议**：**统一用 Git Bash**。

理由：

1. 你的 `push.md` / `pull.md` 教程已经按 Git Bash 写的（`cd /d/Study`），换终端会让教程和实际对不上
2. Git Bash 才是「一个终端打天下」—— 文件操作、搜索、管道都在
3. 右键「Open Git Bash here」能省掉整个 `cd` 步骤
4. cmd 的唯一优势是「Windows 自带、一定有」，但它没有第二个窗口就能用的优点

> ⚠️ **唯一的例外**：`D:\git\Git\cmd\git.exe` 必须在 PATH 里，否则 cmd 和 bash 都用不了 git。
> 本机已确认在 PATH（`where git` / `which git` 都能查到）。

---

## 十一、记住这五条

1. **git 命令两个终端一模一样**，只有 `cd` 的路径写法不同
2. **cmd 用 `D:\Repos\tools`，Git Bash 用 `/d/Repos/tools`**
3. **`/d` 在 cmd 里是开关，在 Git Bash 里是路径**
4. **Git Bash 里 `\` 是转义符、`` ` `` 是命令替换** —— cmd 里没这些讲究
5. **commit 前的安全带是 `git status`，后悔药是 `git diff`**

---




