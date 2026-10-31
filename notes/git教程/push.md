# push：把本地改动上传到 GitHub

> 完整流程见 [Git详细教程：push和pull.md](Git详细教程：push和pull.md) 的核心概念部分。
> 本文只讲 **push** 的每一步。

---

## 完整流程（可以直接照抄）

```bash
cd /d/Study            # ① 进到仓库根目录
git status             # ② 先看：现在有哪些改动？
# ③ 用 VS 2026 改文件，Ctrl+S 保存
git add .              # ④ 放进暂存区（成功时没有任何输出）
git status             # ⑤ 再看一眼：应该出现 Changes to be committed
git commit -m "docs: 说清楚这次干了什么"    # ⑥ 打包成一个版本
git log --oneline -3   # ⑦ 确认新版本在最上面
git push               # ⑧ 真正上传
# ⑨ 浏览器打开 https://github.com/sqs6/study 验收
```

**换仓库只改第 ① 行。**

---

## 第 ① 步：进到仓库

```bash
cd /d/Study
```

**Git Bash 里路径用正斜杠，盘符前面加斜杠** —— `/d/Study` 就是 `D:\Study`。

**确认进对了**：看提示符会变成

```
孙卿单@LAPTOP-46VKQ4OI UCRT64 /d/study (main)
                                       ↑在这  ↑在这个分支
```

不确定的话敲 `pwd` 看当前在哪。

| 仓库 | `cd` |
|---|---|
| 学习代码库 | `cd /d/Study` |
| 主页 | `cd /d/Repos/sqs6` |
| 技术笔记 | `cd /d/Repos/articles` |
| CTF 题解 | `cd /d/Repos/ctf-writeups` |
| 自研工具 | `cd /d/Repos/tools` |
| 比赛参赛 | `cd /d/miniob/miniob` |

---

## 第 ② 步：先看一眼

```bash
git status
```

### 输出逐行解读

```
On branch main
```
👉 你在 **main** 分支上。

```
Your branch is up to date with 'origin/main'.
```
👉 `origin/main` = GitHub 上的 main。**"up to date" = 你和 GitHub 完全同步**，没落后。

```
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        "notes/C基础笔记.md"
```
👉 ★ 这是 git **还不认识**的新文件。
注意路径 `notes/C基础笔记.md` —— **这就是它将来在 GitHub 上的位置**（相对仓库根的路径）。

```
nothing added to commit but untracked files present (use "git add" to track)
```
👉 翻译："有改动但还没提交。目前只有未跟踪的新文件，所以啥也没加进去 —— 用 `git add` 来加。"

> 💡 **`git status` 是安全带。** 每次不确定下一步干什么就敲它 —— **git 每次都会直接写出该敲的命令**。

---

## 第 ③ 步：改文件

用 **VS 2026** 打开仓库里的文件，改完 **Ctrl+S**。

⚠️ **编码坑**：如果文件是 GBK 编码，保存时要改成 UTF-8，否则推上去中文乱码。
改法：**文件 → 另存为 → 保存按钮右边的小箭头 → 编码保存 → Unicode (UTF-8 无签名)**（`.md` 用无签名，`.c` 用带签名）。

---

## 第 ④ 步：放进暂存区

```bash
git add .
```

| | 意思 |
|---|---|
| `git` | Git 这个程序 |
| `add` | 添加（放进暂存区）|
| `.` | **当前目录下的所有东西**（递归，包括子目录）|

⚠️ **两个空格都不能少**：`git add .` 不是 `git add.` 也不是 `gitadd .`
⚠️ 少打 `.` 的话，只会加当前目录**顶层**的文件，子目录里的不会进去。

**输出：什么都没有 —— 这就是成功**（`git add` 成功时是静默的）。

---

## 第 ⑤ 步：再确认一次

```bash
git status
```

### 应该变成

```
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	new file:   notes/C基础笔记.md
```

```
Untracked files:
 （这一段应该消失了）
```

> **看到 `Changes to be committed` = 成功。**
>
> 顺带学一条后悔药：`git restore --staged <文件>` = 把文件退回"未跟踪"（等于没 add）。

---

## 第 ⑥ 步：打包成一个版本

```bash
git commit -m "docs: 添加 C 语言基础笔记（数据类型/运算符/流程控制，2026-10-24）"
```

| 部分 | 意思 |
|---|---|
| `commit` | 提交 = 把暂存区打包成一个**版本**（有编号、有说明、有时间、有你）|
| `-m` | message，后面跟说明文字 |
| `"..."` | 说明内容，**必须用英文半角引号** `"`，不能用中文引号 `“”` |

⚠️ **中文引号会报错** `unexpected EOF`。输入法切到英文再敲引号。

### 输出

```
[main 998f1d3] docs: 添加 C 语言基础笔记（数据类型/运算符/流程控制，2026-10-24）
 1 file changed, 437 insertions(+)
 create mode 100644 notes/C基础笔记.md
```

| 输出 | 意思 |
|---|---|
| `[main 998f1d3]` | 分支名 + **新版本的短编号** |
| `docs: ...` | 你写的说明（原样回显）|
| `1 file changed` | 1 个文件变了 |
| `437 insertions(+)` | 新增了 437 行 |
| `create mode 100644 notes/...` | 新建了这个文件 |

---

## 第 ⑦ 步：确认历史（建议）

```bash
git log --oneline -3
```

```
998f1d3 (HEAD -> main)     docs: 添加 C 语言基础笔记（数据类型/运算符/流程控制，2026-10-24）
bc681c2 (origin/main, origin/HEAD)  docs: 35 个周 README 与 Python 副线改为清单制口径
94ab8e9                     docs: 进度表加状态图例；week01 标为进行中
```

### ⭐ 这段输出说明了 push 要干什么

```
998f1d3  ←←← 你在本地，新版本在这里（还没上传）
   │
 │  ← 这段差就是 push 要送的 ↓
bc681c2  ←←← GitHub 上停在这
```

> `origin/main` 里的 `origin` = 远程仓库的别名（`git remote -v` 里那个地址的简称）
> `HEAD -> main` = "你当前所在的版本"

---

## 第 ⑧ 步：推送 ⬆️

```bash
git push
```

### 输出

```
Enumerating objects: 6, done.
Counting objects: 100% (6/6), done.
Delta compression using up to 4 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 5.94 KiB | 2.97 MiB/s, done.
Total 4 (delta 2), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/sqs6/study.git
   bc681c2..998f1d3  main -> main
```

**只看最后两行：**

```
   bc681c2..998f1d3  main -> main
      ↑         ↑
    从这版     推到这版

   ↑ 双箭头 = 远程前进（fast-forward）
   ↑ main -> main = 本地 main 推送到了远程 main
```

---

## 第 ⑨ 步：去浏览器验收

打开 **<https://github.com/sqs6/study/tree/main/notes>**

应该能看到你改的文件，**点进去中文正常显示**。

---

## push 失败了怎么办

### 最常见：`Updates were rejected`

```
error: failed to push some refs
hint: Updates were rejected because the remote contains work that you don't have locally.
```

**原因**：GitHub 上有你没有的提交（多半是你在网页上改过）。

**解法**：
```bash
git pull --rebase origin main
git push
```
> 详见 [pull.md](pull.md)。

### 其他

| 报错 | 解法 |
|---|---|
| `fatal: Authentication failed` / 要密码 | 凭据没命中，告诉我，我查 Windows 凭据管理器 |
| `error: failed to push some refs` 且提示 hint 是 non-fast-forward | 同上，先 pull |
| `remote: Permission to sqs6/xxx.git denied` | 这个仓库的权限/remote 配错了，告诉我 |

---

## 一句话总结

> **push = 把"暂存区里的改动"打包成版本，再上传到 GitHub。**
> **四步：`add` → `commit` → `push`（加上 `status` 保命）。**
> **换仓库只改 `cd` 那一行。**
