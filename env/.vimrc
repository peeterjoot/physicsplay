set nocompatible

"source /cygdrive/c/vim/vim64/vimrc_example.vim
"source $VIMRUNTIME/vimrc_example.vim
"source $VIMRUNTIME/mswin.vim

"behave mswin
" --- Peeter ---
set nobackup
set et			" expand tabs to spaces.
set shiftwidth=3        " for >> indenting
set tabstop=3           " the amount of space a tab moves.
set fileformat=unix
set notitle
set noerrorbells
set textwidth=0
" --- Peeter ---

"git clone git@github.com:vim-scripts/Cpp11-Syntax-Support.git
"mkdir -p .vim/syntax
"cd .vim/syntax
"for i in Cpp11-Syntax-Support/syntax/*.vim ; do ln -s $i ; done
au BufNewFile,BufRead *.cpp *.cc *.h *.hpp set syntax=cpp11

"set diffexpr=MyDiff()
"function MyDiff()
"  let opt = '-a --binary '
"  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
"  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
"  let arg1 = v:fname_in
"  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
"  let arg2 = v:fname_new
"  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
"  let arg3 = v:fname_out
"  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
"  silent execute '!c:\vim\vim64\diff ' . opt . arg1 . ' ' . arg2 . ' > ' . arg3
"endfunction
"
