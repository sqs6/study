# pull：把 GitHub 上的改动取回本地

> 完整流程见 [Git详细教程：push和pull.md](Git详细教程：push和pull.md) 的核心概念部分。
> 本文只讲 **pull**。
>
> ⚠️ **本文所有报错文本都是我在本机真实跑出来的**（用临时仓库模拟"网页改了 / 本地也改"的场景），
> 不是凭记忆写的。

---

## 什么时候需要 pull

| 情况 | 要不要 pull |
|---|---|
| 你**在网页上**改过东西，想在本地继续改 | ✅ **必须先 pull** |
| 别人给你提了 PR / 提交了 commit | ✅ pull |
| 你只在**本地**改，没碰网页 | ❌ 不用（pull 了也只是"已经是最新"）|
| push 被拒（`Updates were rejected`）| ✅ 必须 pull |

> 💡 **省事的习惯**：每次准备在本地改文件之前，先 `git pull --rebase origin main` 一下，
> 成本几秒，能避免后面一堆麻烦。

---

## 完整流程

```bash
cd /d/Study              # ① 进到仓库根目录
git status               # ② 先看：我本地有没有还没提交的改动？
git pull --rebase origin main   # ③ 把 GitHub 上的改动取回来
git log --oneline -3     # ④ 确认取回来了
```

**第 ③ 步的两个参数是什么意思：**
- `--rebase` = 把你的本地提交"接在"远程提交**后面**，历史是一条直线（推荐）
- `origin main` = 从 `origin`（GitHub）这个远程的 `main` 分支取

---

## 第 ② 步为什么要先看

因为**本地有没提交的改动时，pull 可能失败**。实测报错：

```
error: Your local changes to the following files would be overwritten by merge:
	f.txt
Please commit your changes or stash them before you merge.
Aborting
Updating a912df2..922b500
```

**解法二选一：**

**A. 先提交（推荐）** —— 反正你本地改动也是要提交的
```bash
git add .
git commit -m "docs: 我这边的改动"
git pull --rebase origin main
git push
```

**B. 先收起来（stash）** —— 改动还想留着但暂时不想提交
```bash
git stash                  # 把本地改动收进"暂存柜"
git pull --rebase origin main
git stash pop              # 再把改动取回来
```

> 💡 **好消息**：如果**本地没提交的改动和远程改的不是同一个文件**，pull 是能成功的。
> 实测：本地改了 `h.txt` 没提交，远程新增了 `g.txt`，pull 直接成功：
> ```
> Updating a912df2..97d76b5
> Fast-forward
>  f.txt | 2 +-
>  g.txt | 1 +
>  2 files changed, 2 insertions(+), 1 deletion(-)
>  create mode 100644 g.txt
> ```

---

## 第 ③ 步：三种结果

### 情况 A · 快进（最常见，远程有更新、你没有）

```
From https://github.com/sqs6/study
 * branch            main       -> FETCH_HEAD
   0734d17..6005aac  main       -> origin/main
Updating 0734d17..6005aac
Fast-forward
 f.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```

| 输出 | 意思 |
|---|---|
| `* branch main -> FETCH_HEAD` | 正在从远程的 main 取东西 |
| `0734d17..6005aac main -> origin/main` | **远程的 main 前进到了 6005aac**，同时记下了远程现在在哪 |
| `Updating 0734d17..6005aac` | 我要从哪个版本更新到哪个版本 |
| `Fast-forward` | ✅ **无冲突，直接快进**（你的本地没有分叉）|

**看到 `Fast-forward` 就完事了。**

---

### 情况 B · 已经是最新的

```
From https://github.com/sqs6/study
 * branch            main       -> FETCH_HEAD
Current branch main is up to date.
```

**"already up to date" = 没什么可拉的。** 正常。

---

### 情况 C · 真冲突 ⚠️（两边改了同一个文件的同一处）

实测输出：

```
From https://github.com/sqs6/study
 * branch            main       -> FETCH_HEAD
   f45983a..d98cae6  main       -> origin/main
Auto-merging f.txt
CONFLICT (content): Merge conflict in f.txt
Rebasing (1/1)
error: could not apply ec773a5... A change line2
hint: Resolve all conflicts manually, mark them as resolved with
hint: "git add/rm <conflicted_files>", then run "git rebase --continue".
hint: You can instead skip this commit: run "git rebase --skip".
hint: To abort and get back to the state before "git rebase", run "git rebase --abort".
hint: Disable this message with "git config set advice.mergeConflict false"
Could not apply ec773a5... # A change line2
```

**别慌，这不是错误，是 git 在问你"这两边不一样，你要哪个"。**

---

## 冲突怎么解决

### 第 1 步：看冲突长什么样

冲突文件里会出现三个标记：

```
line1
<<<<<<< HEAD
line2-B版本
=======
line2-A版本
>>>>>>> ec773a5 (A change line2)
line3
```

| 标记 | 含义 |
|---|---|
| `<<<<<<< HEAD` | **分隔线的上半部分** —— HEAD = **远程**的版本（刚才 pull 下来的）|
| `=======` | 中间分隔线 |
| `>>>>>>> ec773a5 (A change line2)` | **下半部分** —— `ec773a5` = **你本地**那个提交的版本 |
| 中间夹着的两行 | 冲突的两个内容 |

> 记住：**上面是远端的，下面是你本地的。**

### 第 2 步：手动改成你要的样子

用 VS 2026 打开那个文件，**把三个标记行全删掉**，中间只留你要的内容：

```
line1
line2-最终版本（我合并的）
line3
```

> ⚠️ **标记行必须全部删干净** —— 留一个 `<<<<<<<` 在文件里，下次 commit 会报错。

### 第 3 步：告诉 git "我解决好了"

```bash
git add f.txt              # 标记这个文件已解决
git rebase --continue      # 继续（可能还会弹编辑器让你确认说明，敲 :wq 或直接保存退出）
```

实测输出：
```
[detached HEAD 339f4f7] A change line2
 1 file changed, 1 insertion(+), 1 deletion(-)
Successfully rebased and updated refs/heads/main.
```

### 第 4 步：确认干净了

```bash
git status --short          # 应该什么都不输出（= 干净）
git log --oneline --graph -6
```

```
* 339f4f7 A change line2
* d98cae6 B change line2
* f45983a init
```

> ⭐ **注意历史变成了直线** —— 这就是 `--rebase` 的好处。
> 不加 `--rebase` 的话会多一个 `Merge branch ...` 的合并节点，历史会变"树"状。

---

## 中途反悔

冲突还没解决、想放弃这次 pull，回到 pull 之前的状态：

```bash
git rebase --abort
```

实测输出：
```
$ git rebase --abort
（无输出 = 成功）
```

**效果**：本地完全回到 pull 之前，你的改动一个不丢。

还有一个：
```bash
git rebase --skip        # 跳过当前这个有冲突的提交
```

> 💡 **建议**：解冲突前先 `git status` 看清楚现在的状态；
> 实在搞不定就 `git rebase --abort` 重来 —— **abort 永远能救你**。

---

## `git status` 在冲突时说什么

```
interactive rebase in progress; onto d98cae6
Last command done (1 command done):
   pick ec773a5 # A change line2
No commands remaining.
You are currently rebasing branch 'main' on 'd98cae6'.
  (fix conflicts and then run "git rebase --continue")
  (use "git rebase --skip" to skip this patch)
  (use "git rebase --abort" to check out the original branch)

Unmerged paths:
  (use "git restore --staged <file>..." to unstage)
  (use "git add <file>..." to mark resolution)
	both modified:   f.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

**重点看这两行：**
- `(fix conflicts and then run "git rebase --continue")` ← git 告诉你下一步
- `both modified: f.txt` ← 哪个文件冲突了

快速看哪些文件冲突：
```bash
git status --short
```
```
UU f.txt
```
> `UU` = **U**nmerged **U**nmerged（两边都改过，还没解决）
> 其它常见标记：`M` = 已修改、`A` = 新增、`??` = 未跟踪

---

## pull 完之后要 push 吗？

**看你 pull 的目的：**

| 目的 | 之后要不要 push |
|---|---|
| 只是把网页上的改动拿下来看看 | **不用** |
| pull 过程中你自己也改了东西 | ✅ 要 `git add . && git commit && git push` |
| 解决冲突时把你的版本合并进来了 | ✅ 要 push（不然你的合并只在你本地）|

---

## 一句话总结

> **pull = 从 GitHub 取回改动，本质是 `fetch`（下载）+ `rebase`（接到我的提交后面）。**
> **三种结果：`Fast-forward`（最常见）、`already up to date`（没更新）、`CONFLICT`（两边改了同一处）。**
> **冲突三步：改文件（删标记）→ `git add 文件` → `git rebase --continue`。**
> **搞不定就 `git rebase --abort` 重来。**
