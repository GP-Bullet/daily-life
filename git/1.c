

/*

//*一、提交
git commit

//*二、分支
git branch <>
git checkout <>
git checkout -b< >

//*三、合并
1.git merge < >(被合并)
2.git rebase<>(被合并)
Rebase
实际上就是取出一系列的提交记录，“复制”它们，然后在另外一个地方逐个的放下去。
Rebase 的优势就是可以创造更线性的提交历史
代码库的提交历史将会变得异常清晰。


//*四、移动//?有啥用

如果想看 HEAD 指向，可以通过 cat .git/HEAD 查看， 
如果 HEAD 指向的是一个引用，还可以用 git symbolic-ref HEAD 查看它的指向。
但是该程序不支持这两个命令）
HEAD 指向了 main，随着提交向前移动。

分离的HEAD
分离的 HEAD 就是让其指向了某个具体的提交记录而不是分支名。
checkout c1(哈希值)
HEAD->C1


提交记录的哈希值（git log查看）

相对引用
^上移一个
~<num>
git checkout main^

git branch -f main HEAD~3
上面的命令会将 main 分支强制指向 HEAD 的第 3 级父提交。

强制修改分支位置 -f

//*五、撤销变更
撤销变更由底层部分（暂存区的独立文件或者片段）和
上层部分（变更到底是通过哪种方式被撤销的）组成。
我们这个应用主要关注的是后者。

1.git reset
你可以将这想象成“改写历史”。
git reset 向上移动分支，原来指向的提交记录就跟从来没有提交过一样。
git reset HEAD~1
在reset后， C2所做的变更还在，但是处于未加入暂存区状态。




2.git revert
git revert HEAD
虽然在你的本地分支中使用 git reset 很方便，但是这种“改写历史”的方法对大家一起使用的远程分支是无效的哦！
为了撤销更改并分享给别人，我们需要使用 git revert。来看演示：

奇怪！在我们要撤销的提交记录后面居然多了一个新提交！这是因为新提交记录 C2' 引入了更改 —— 
这些更改刚好是用来撤销 C2 这个提交的。也就是说 C2' 的状态与 C1 是相同的。

revert 之后就可以把你的更改推送到远程仓库与别人分享啦。


//*六、整理提交记录
git cherry-pick <提交号>...
(当前所在的位置（HEAD）)
如果你想将一些提交复制到当前所在的位置（HEAD）下面的话

git cherry-pick C2 C4抓过来复制到当前
（有选择性的复制）

交互式的 rebase
交互式 rebase 指的是使用带参数 --interactive 的 rebase 命令, 简写为 -i

git rebase -i HEAD~4
(jiaohu)


*/