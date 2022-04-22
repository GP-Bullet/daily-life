/*
*main 与 o/main 是相关的
远程分支 main 和本地的 main 分支进行了关联。
这种关联在以下两种情况下可以清楚地得到展示：

pull 操作时, 提交记录会被先下载到 o/main 上，之后再合并到本地的 main 分支。
隐含的合并目标由这个关联确定的。


push 操作时, 我们把工作从 main 推到远程仓库中的 main 分支(同时会更新远程分支 o/main) 。
这个推送的目的地也是由这种关联确定的！

*当你克隆时, Git 会为远程仓库中的每个分支在本地仓库中创建一个远程分支（比如 o/main）。
*然后再创建一个跟踪远程仓库中活动分支的本地分支，
*默认情况下这个本地分支会被命名为 main。



*自定义追踪
这意味着你可以在分支 totallyNotMain 上执行 git push，将工作推送到远程仓库的 main 分支上。
有两种方法设置这个属性，第一种就是通过远程分支检出一个新的分支，执行:
*git checkout -b totallyNotMain o/main
就可以创建一个名为 totallyNotMain 的分支，它跟踪远程分支 o/main。


*1.git checkout -b foo o/main; git pull

正如你所看到的, 我们使用了隐含的目标 o/main 来更新 foo 分支。
需要注意的是 main 并未被更新！

*1.git checkout -b foo o/main;
git commit;
git push;
我们将一个并不叫 main 的分支上的工作推送到了远程仓库中的 main 分支上


*2.设置远程追踪分支的方法就是使用：git branch -u 命令，执行：

git branch -u o/main foo

这样 foo 就会跟踪 o/main 了。如果当前就在 foo 分支上, 还可以省略 foo：

git branch -u o/main








*/
