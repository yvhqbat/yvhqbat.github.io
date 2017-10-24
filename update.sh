#########################################################################
# File Name: update.sh
# Author: ld
# mail: yvhqbat@126.com
# Created Time: 2017年10月24日 星期二 22时48分26秒
#########################################################################
#!/bin/bash
git remote -v
git fetch origin master:temp
git diff temp
git merge temp
git branch
git branch -d temp

