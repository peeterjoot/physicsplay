syntax on
syntax enable

set hlsearch            " highlight search

" try avoid having to press escape twice to get out of insert mode
set timeoutlen=0

"set nobackup

set backupdir=~/.config/nvim/backup
set directory=~/.config/nvim/backup

set fileformat=unix

set showcmd             " Show (partial) command in status line.
set showmatch           " Show matching brackets.
set showmode            " Show current mode.
set ruler               " Show the line and column numbers of the cursor.
"set number              " Show the line numbers on the left side.
set formatoptions+=o    " Continue comment marker in new lines.
set textwidth=0         " Hard-wrap long lines as you type them.
set expandtab           " Insert spaces when TAB is pressed.
set tabstop=3           " Render TABs using this many spaces.
set shiftwidth=3        " Indentation amount for < and > commands.

set noerrorbells        " No beeps.
set modeline            " Enable modeline.
set esckeys             " Cursor keys in insert mode.
set linespace=0         " Set line-spacing to minimum.
set nojoinspaces        " Prevents inserting two spaces after punctuation on a join (J)

" More natural splits
set splitbelow          " Horizontal split below current.
set splitright          " Vertical split to right of current.

if !&scrolloff
  set scrolloff=3       " Show next 3 lines while scrolling.
endif
if !&sidescrolloff
  set sidescrolloff=5   " Show next 5 columns while side-scrolling.
endif
set display+=lastline
set nostartofline       " Do not jump to first character with page
"set termguicolors

map <C-K> :!mycformat<cr>

"" Tell Vim which characters to show for expanded TABs,
"" trailing whitespace, and end-of-lines. VERY useful!
"if &listchars ==# 'eol:$'
"  set listchars=tab:>\ ,trail:-,extends:>,precedes:<,nbsp:+
"endif
"set list                " Show problematic characters.

"" Also highlight all tabs and trailing whitespace characters.
"highlight ExtraWhitespace ctermbg=darkgreen guibg=darkgreen
"match ExtraWhitespace /\s\+$\|\t/

let g:airline#extensions#tabline#enabled = 2
let g:airline#extensions#tabline#fnamemod = ':t'
let g:airline#extensions#tabline#left_sep = ' '
let g:airline#extensions#tabline#left_alt_sep = '|'
let g:airline#extensions#tabline#right_sep = ' '
let g:airline#extensions#tabline#right_alt_sep = '|'
let g:airline_left_sep = ' '
let g:airline_left_alt_sep = '|'
let g:airline_right_sep = ' '
let g:airline_right_alt_sep = '|'
let g:airline_theme= 'serene'

"" Start interactive EasyAlign in visual mode (e.g. vipga)
"xmap ga <Plug>(EasyAlign)
""
"" Start interactive EasyAlign for a motion/text object (e.g. gaip)
"nmap ga <Plug>(EasyAlign)

call plug#begin('~/.vim/plugged')

" https://github.com/airblade/vim-gitgutter
"Plug 'airblade/vim-gitgutter'

"" Colors:
"" https://github.com/morhetz/gruvbox
"Plug 'morhetz/gruvbox'
"
"Plug 'altercation/vim-colors-solarized'
"Plug 'NLKNguyen/papercolor-theme'

" ?
" Plug 'valloric/youcompleteme'

" git status:
"Plug 'tpope/vim-fugitive'
Plug 'vim-airline/vim-airline'

" component specific .vimrc overrides:
Plug 'embear/vim-localvimrc'

" https://github.com/plasticboy/vim-markdown
"Plug 'plasticboy/vim-markdown'

" c++ highlighting:
"Plug 'ChaiScript/vim-chaiscript'
"Plug 'ChaiScript/vim-cpp'
"Plug 'Mizuchi/STL-Syntax'
"
" https://github.com/octol/vim-cpp-enhanced-highlight :
Plug 'octol/vim-cpp-enhanced-highlight'

" https://github.com/kien/rainbow_parentheses.vim
"Plug 'kien/rainbow_parentheses.vim'

" https://github.com/arecarn/crunch.vim (a calculator in vim)
"Plug 'arecarn/crunch.vim'

" no idea:
"Plug 'tpope/vim-liquid'

" makefile generator:
"Plug 'rdnetto/YCM-Generator', { 'branch': 'stable'}

" Plug 'nathanaelkane/vim-indent-guides'



" Make sure you use single quotes

" Shorthand notation; fetches https://github.com/junegunn/vim-easy-align
" Select, then :EasyAlign
Plug 'junegunn/vim-easy-align'

" Any valid git URL is allowed
"Plug 'https://github.com/junegunn/vim-github-dashboard.git'

" Group dependencies, vim-snippets depends on ultisnips
"Plug 'SirVer/ultisnips' | Plug 'honza/vim-snippets'

" On-demand loading
"Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
"Plug 'tpope/vim-fireplace', { 'for': 'clojure' }

" Using a non-master branch
"Plug 'rdnetto/YCM-Generator', { 'branch': 'stable' }

" Using a tagged release; wildcard allowed (requires git 1.9.2 or above)
"Plug 'fatih/vim-go', { 'tag': '*' }

" Plugin options
"Plug 'nsf/gocode', { 'tag': 'v.20150303', 'rtp': 'vim' }

" Plugin outside ~/.vim/plugged with post-update hook
"Plug 'junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' }

"" eye candy
""Plug 'myusuf3/numbers.vim'
"Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
"Plug 'lilydjwg/colorizer', { 'on': 'ColorToggle' }

" Unmanaged plugin (manually installed and updated)
"Plug '~/my-prototype-plugin'


" Add plugins to &runtimepath
call plug#end()

source ~/.config/nvim/line.vimrc

" didn't work:
"" https://github.com/neovim/neovim/issues/583
"function! ClipboardYank()
"  call system('xclip -i -selection clipboard', @@)
"endfunction
"function! ClipboardPaste()
"  let @@ = system('xclip -o -selection clipboard')
"endfunction
"
"vnoremap <silent> y y:call ClipboardYank()<cr>
"vnoremap <silent> d d:call ClipboardYank()<cr>
"nnoremap <silent> p :call ClipboardPaste()<cr>

" mac-terminal+ssh(linux)+nvim:  command-C no longer works in nvim (although
" command-V does):
"
" Fix from:
"  https://github.com/neovim/neovim/issues/3702
set mouse=

""
"" From https://github.com/lefticus/nvim-config/blob/master/init.vim
"" (so are some of the plugins above)
""
""
"let g:doxygen_enhanced_color=1
"let g:load_doxygen_syntax=1
"
""set expandtab
""set shiftwidth=2
"set lcs=trail:·,tab:»·
"set list
"set cursorline
""set number
"
"let g:gitgutter_sign_column_always = 1
"
"let g:ycm_confirm_extra_conf = 0
"
"
"let g:airline_powerline_fonts=1

"" rainbow parens:
"let g:rbpt_max = 16
"let g:rbpt_loadcmd_toggle = 0


"
""set background=dark
""set background=dark
"let g:gruvbox_contrast_light="hard"
"let g:gruvbox_italic=1
"let g:gruvbox_invert_signs=0
"let g:gruvbox_improved_strings=0
"let g:gruvbox_improved_warnings=1
"let g:gruvbox_contrast_dark="hard"
"colorscheme gruvbox
"
""set t_Co=256
""colorscheme PaperColor
""let g:airline_theme='PaperColor'
"
""let g:solarized_termcolors = 256
""colorscheme solarized
"
"let g:vim_markdown_frontmatter = 1
"let g:vim_markdown_folding_disabled = 1
"
"
"let g:vim_indent_guides_start_level = 2
"
"
"set laststatus=2
"
"autocmd BufReadPost *
"    \ if line("'\"") > 1 && line("'\"") <= line("$") |
"    \   exe "normal! g`\"" |
"    \ endif
"
"au VimEnter * RainbowParenthesesActivate
"au Syntax * RainbowParenthesesLoadRound
"au Syntax * RainbowParenthesesLoadSquare
"au Syntax * RainbowParenthesesLoadBraces
" au Syntax * RainbowParenthesesLoadChevrons
"
""set backup
"

"let g:localvimrc_whitelist=[ '/home/pjoot/workspace/*/.lvimrc', '/home/pjoot/build/*/.lvimrc' ]
let g:localvimrc_whitelist=[ '/home/pjoot/workspace/*/.*', '/home/pjoot/build/*/.*', '/home/pjoot/freeware/llvm' ]
"let g:localvimrc_blacklist=[ '*akefile', '*.mk' ]

" http://unix.stackexchange.com/questions/88879/vim-better-colors-so-comments-arent-dark-blue
color desert
"set background=dark
