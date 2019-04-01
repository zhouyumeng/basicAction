文章目标：总结Git的常规操作，包括在Linux系统上进行Git的版本控制指令和Github配置操作

### 1.  Git安装
由于各个系统上的Git安装过程都十分简单，基本不涉及什么操作，唯一要考虑的无非就是输入账号和密码

### 2. Github配置——SSH连接Github
- Windows系统：安装客户端即可，无需进行任何其他复杂的，一切自动完成。
- Mac系统和Linux系统是类似的操作，也是此次写文章的目的之一

进行SSH连接Github操作的原因是避免每次访问Github都需要输入密码，测试指令
```
$ ssh -T git@github.com
 //终端输出如下，表明连接成功
$ Hi user! You've successfully authenticated, but GitHub does not provide shell access.
Connection to github.com closed.
//如果连接失败，则需要输入密码和账号
```

1. 设置git参数
- 设置参数指令
```
$ git config --global user.name "Zhou Yu"
$ git config --global user.email "zhouyumeng152@gmail.com"
```
- 查看参数指令
```
$ git config --system --list        //查看当前系统配置信息
$ git config --global --list        //查看当前用户配置信息
$ git config --local --list         //查看当前仓库配置信息
```
2. 生成SSH密钥

- 首先查看系统是否存在SSH密钥：
  
  + 密钥文件一般保存在`~/.ssh`目录下
    
    - 私钥：id_rsa
    - 公钥：id_rsa.pub
  + 检查密钥指令
    - `$ ls -al ~/.ssh`
      
      ```
      //如果存在密钥
      id_rsa
      id_rsa.pub
      //如果不存在密钥
      No such file or directory
      ```   
    也许你存在密钥，只是密钥所在位置不对,比如密钥不在`~/.ssh`文件夹下，而是`~/`根目录下,之所以会产生这中情况的原因是，当初生成密钥的指令便是在根目录下进行的
- 如果您已有相关密钥，请直接跳过此步
```
//生成新的密钥，按三次回车即可
$ ssh-keygen -t rsa -C "zhouyumeng152@gmail.com"
//可以添加`-f name`指定密钥名,如下
$ ssh-keygen -t rsa -f test -C "name_key"
//-f:文件名
//-C:文件备注
```
运行上述指令时，请在`~/.ssh`文件夹下运行，否则密钥将会在生成在当前文件夹下。
运行上述指令之后，将在`~/.ssh`文件夹看到`id_rsa`和`id_rsa.pub`两个文件

3. 进行密钥部署

- 加载私钥
  ```
  $ ssh-add id_rsa
  //或者
  $ ssh-add ~/.ssh/id_rsa
  //终端显示
  Identity added: ~/.ssh/id_rsa
  ```
- 部署公钥
  ```
  $ cat ~/.ssh/id_rsa.pub
  //终端显示SSH key，SSH公钥如下:
    ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAklOUpkDHrfHY17SbrmTIpNLTGK9Tjom/BWDSU
    GPl+nafzlHDTYW7hdI4yZ5ew18JH4JW9jbhUFrviQzM7xlELEVf4h9lFX5QVkbPppSwg0cda3
    Pbv7kOdJ/MTyBlWXFCR+HAo3FXRitBqxiX1nKhXpHAZsMciLq8V6RjsNAQwdsdMFvSlVK/7XA
    t3FaoJoAsncM1Q9x5+3V0Ww68/eIFmb1zuUFljQJKprrX88XypNDvjYNby6vw/Pb0rwert/En
    mZ+AW4OZPnTPI89ZPmVMLuayrD2cE86Z/il8b+gw3r3+1nKatmIkjn2so1d01QraTlMqVSsbx
    NrRFi9wrf+M7Q== schacon@mylaptop.local
  ```
  复制上述输出复制，将公钥添加到Github的[`setting-key`](https://github.com/settings/keys)配置页面

4. 测试连接
```
$ ssh git@github.com
//终端输出如下，表明连接成功
$ Hi user! You've successfully authenticated, but GitHub does not provide shell access.
Connection to github.com closed.
//如果连接失败，则需要输入密码和账号
```

5. 注意事项

    提醒:问题是多样的，但表现形式是一样的，那便是每次操作均需要进行输入账号和密码，不管遇到什么问题，请多谷歌和百度，查找相关解决方案。

- 权限问题
    
    由于需要远程访问，所以需要使用进行权限设定

    ```
    $ chmod 600 authorized_keys
    $ chmod 700 -R .ssh
    ```
    
- 连接问题
    
    有些系统即便连接测试的指令表明测试通过，但还是需要输入账号和密码。如果使用HTTPS连接远程仓库失败，请使用SSH进行连接和仓库克隆,即修改`/.git/config`文件夹中的`url`为SSH链接，当然也有可能相反

### 3. Git基本操作
该节的基本操作，主要围绕Github上的远程仓库和本地Git工具开展的。git仓库分为远程仓库和本地。
1. 本地操作
    - 创建新仓库：`git init`
    - 检出仓库：
        + 克隆本地仓库：`git clone /path/to/repository`
        + 克隆远程仓库：`git clone https://github.com/zhouyumeng/basicAction.git`，即`https`地址
        + 克隆远程服务器仓库：`git clone username@host:/path/to/repository` 
2. 将改动添加到缓存区
    - `git add .`:添加所有改动到缓存区
    - `git add <filename>`:添加指定文件到缓存区
3. 提交改动
    - `git commit -m "commonts"`
4. 推送改动到远端仓库
    - `git push origin master`:推送改动到远端仓库的主分支
    - `git push origin branch_name`:推送改动到远端仓库的指定分支
5. 推送改动到远程服务器(远程服务器仓库没有克隆该仓库时)
    - 将本地仓库连接到远程服务器仓库:`git remote add origin <server>`
6. 分支操作
    - 显示分支:`git branch`
    - 创建分支:`git checkout -b branch_name`
    - 切换分支:`git checkout branch_name`
    - 删除本地分支:`git branch -d branch_name`
    - 推送分支到远端仓库:`git push origin branch_name`
    - 查看所有分支<本地分支|远程分支>:`git branch -a`
    - 查看远程地址、远程分支、与本地分支的对应信息:`git remote show origin`
    - 查看远程仓库不存在的分支:`git remote prune origin`
    - 删除远程分支:`git push origin --delete branch_name`
7. 更新与合并
    - 更新本地仓库至最新改动:`git pull`,在工作目录获取(fetch)并合并(merge)远程改动
    - 合并其他分支到当前分支:`git merge <branch>`
    - 比较差异:`git add <source_branch> <target_branch>`
    - 目前UBUNTU系统需要人肉合并冲突
8. 获取改动状态
    - 确定当前文件状态:`git status`
    - 输出日志信息:`git log`
9. 可视化输出
    - 彩色git输出:git config color.ui true
    - 各分支信息:`git log --graph --decorate --oneline --simplify-by-decoration --all`
    - 使用gitk工具:`gitk --simplify-by-decoration --all`
