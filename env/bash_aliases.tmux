#alias tat='tmux at'
alias tp='tmux select-window -p'
alias tl='tmux select-window -l'
alias tn='tmux select-window -n'
alias tnew='tmux new-window'
alias tre='tmux rename-window'
function tnd
{
   tmux rename-window `pwd | sed 's,.*/,,'`
}
