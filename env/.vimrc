set nocompatible

"source /cygdrive/c/vim/vim64/vimrc_example.vim
"source $VIMRUNTIME/vimrc_example.vim
"source $VIMRUNTIME/mswin.vim

"behave mswin
" --- Peeter ---
set nocompatible
set nobackup
set expandtab               " expand tabs to spaces
set shiftwidth=4            " for >> indenting
set tabstop=4               " the amount of space a tab moves
set fileformat=unix
set notitle
set noerrorbells
set textwidth=0
set modeline
set modelines=3             " search 3 lines at beginning or end of file for a modeline
set history=200
set autoindent              " enable auto-indentation
set smartindent             " or use 'set cindent' for C++-specific indentation
filetype plugin indent on   " enable filetype-specific plugins and indentation
syntax on

augroup filetypedetect
  autocmd!
  autocmd BufNewFile,BufRead *.cxx,*.cpp,*.cc,*.c++,*.hpp,*.c,*.h setfiletype cpp
  autocmd BufNewFile,BufRead *.py setfiletype python
augroup END

"------------------------
" Tell vim where to find tags (searches up directory tree)
set tags=./tags;,tags;

" Open tag in vertical split with Ctrl-]
map <C-\> :vsp <CR>:exec("tag ".expand("<cword>"))<CR>

" Open tag in horizontal split
map <A-]> :sp <CR>:exec("tag ".expand("<cword>"))<CR>
"------------------------

"map <C-K> :pyf /usr/share/clang/clang-format.py<cr>
"imap <C-K> <c-o>:pyf /usr/share/clang/clang-format.py<cr>
"map <C-K> :!mycformat<cr>
"imap <C-K> <c-o>:!mycformat<cr>
" --- Peeter ---

"git clone git@github.com:vim-scripts/Cpp11-Syntax-Support.git
"mkdir -p .vim/syntax
"cd .vim/syntax
"for i in Cpp11-Syntax-Support/syntax/*.vim ; do ln -s $i ; done
"au BufNewFile,BufRead *.cpp *.cc *.h *.hpp set syntax=cpp11

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
