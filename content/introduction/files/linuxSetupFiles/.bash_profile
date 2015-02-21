# display > as prompt char, current directory in PuTTY window header
PS1='\[\033]0;\w\007\033[32m\]> \[\033[33m\033[0m\]'

# set locale so that GCC won't use smart quotes in error msgs
export LC_ALL=C

# add current directory to PATH so you
# don't have to type ./ to run something
PATH=".:${PATH}"

alias gdbt='gdb -q -tui'
alias ls='ls --color'
