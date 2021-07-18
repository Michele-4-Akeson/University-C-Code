# ~/.bash_logout: executed by bash(1) when login shell exits.

# when leaving the console clear the screen to increase privacy

if [ "$SHLVL" = 1 ]; then
    [ -x /usr/bin/clear_console ] && /usr/bin/clear_console -q
fi


########################################
## CS1XC3 L06 bash logout script added
#######################################

cd /home/yekim416/CS1XC3/
git add --all
git commit -m "Shell Logout Commit"
git push -u origin master
