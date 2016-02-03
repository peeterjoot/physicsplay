\ProvidesClass{peeterblog}[Peeter Joot, Copyright (c) 2012]
\typeout{ Latex class for Peeter's blog posts. peeterjoot@protonmail.com }

\LoadClass[ twoside,openright,numbers=noenddot,headinclude,
            footinclude=true,cleardoublepage=empty,abstractoff,
            fontsize=11pt,%
            ngerman,american,%
          ]{article}

\usepackage{color}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{graphicx}

% this mangles urls with underscores:
%\usepackage{url}

\usepackage{subfigure}
\usepackage{titlesec}
\usepackage{indentfirst}

%\usepackage{listings}
%\usepackage{txfonts} % for ointctr... (also appears to make "prettier" \int and \sum's)
% makes \grad look funny though (almost like spacegrad, but narrower)
%\usepackage[bookmarks=true]{hyperref}
%\usepackage{cite,graphicx}
   % use colour in the document, put your citations as [1-4]
   % rather than [1,2,3,4] (it looks nicer, and the extended LaTeX2e
   % graphics package. 
%\usepackage{latexsym,amssymb,epsf} % what did these provide?

% 
% hyperref fixes the url underscores.  Latex web companion says to put 
% hyperref last since it overrides a lot of commands.
%
\usepackage[
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% I like the colour instead of boxes better.  Keep this one:
% 
colorlinks=true,
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% remove the side panel (better for small docs)
%
bookmarks=false,
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% this is unfriendly, and generates viewer popup:
%
%pdfpagemode=FullScreen,
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% More screen real estate by default:
%
%pdftoolbar=false,
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Avoid control-2 in acrobat?
%
%pdffitwindow=true,
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Blech:
%
%pdfpagelayout=TwoColumnLeft,
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Try this:
%
%pdfwindowui=false,
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% NOTE: backref takes multiple build passes to take effect:
%
backref 
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
]{hyperref}

% FIXME: this is something that ought to be configurable with \author
\hypersetup{%
pdfauthor={Peeter Joot}
% 
% Again: have my title/chapter info.  For article mode use the title.
% 
%pdftitle={\title}
%pdfsubject={}
%pdfkeywords={}
}

%------------------------------------------------------------
% this part came from Eli's eliblog.cls
%

\RequirePackage{ifthen}

\titleformat{\section}[hang]
{\normalfont\sffamily}
{\thesection .}{.5em}{\bfseries}

\titleformat{\subsection}[hang]
{\normalfont\itshape}
{\thesubsection .}{.5em}{\bfseries}

\renewcommand{\maketitle}{%
   \begin{flushleft}%
      {\sffamily\Large\bfseries\@title\par}%
      \medskip
\ifthenelse{\equal{\@blogpage}{0}}{}{
      {\large{\texttt{\@blogpage}}\par}%
      \medskip
}
      {\large\@author\ ---\ \@email\par}%
         {\itshape\@revisionInfo\@gitRevisionInfo\par}%
         \medskip\@useCCL
      \@keywords
      \bigskip\hrule\vspace*{0.5pc}%
   \end{flushleft}%
}
%------------------------------------------------------------

% book vs. article abstraction macros:

\newcommand{\chapter}[1]{\title{#1}}
\newcommand{\beginArtWithToc}[0]{\begin{document}\maketitle{}\tableofcontents}
\newcommand{\beginArtNoToc}[0]{\begin{document}\maketitle{}}
\newcommand{\EndNoBibArticle}[0]{\end{document}}
\newcommand{\EndArticle}[0]{\bibliography{myrefs}\bibliographystyle{unsrturl}\end{document}}

% this one in standalong articles is a plain old cite, but within a book that contains the chapter
% is a \ref{chap:#1}.  That requires the chapter label to have the same name.
\newcommand{\chapcite}[1]{\cite{#1}}

% make this one a citation to an external notes compilation, but an actual formula reference 
% when that 'chapter' is eventually included in the notes compilation.
\newcommand{\inbookref}[2]{\cite{#1}}

\newcommand{\urlchapcite}[3]{\href{#1}{#2} \cite{#3}}
%\newcommand{\keywords}[1]{\par\noindent {\small{\em Keywords\/}: #1}}

\newcommand{\@revisionInfo}{}
\newcommand{\revisionInfo}[1]{\renewcommand{\@revisionInfo}{@date\quad{#1}}}

\newcommand{\@gitRevisionInfo}{}
\newcommand{\gitRevisionInfo}[1]{\renewcommand{\@gitRevisionInfo}{\input{./.revinfo/lastCommit.tex} #1.tex}}

\newcommand{\@useCCL}{}
\newcommand{\useCCL}[0]{\renewcommand{\@useCCL}{
         {\includegraphics[height=1em]{ccl2}\par}
}}

\newcommand{\@blogpage}{0}
\newcommand{\blogpage}[1]{\renewcommand{\@blogpage}{#1}}

\newcommand{\@email}{{\em No email address given}}
\newcommand{\email}[1]{\renewcommand{\@email}{{#1}}}

\newcommand{\@keywords}[1]{}
\newcommand{\keywords}[1]{\renewcommand{\@keywords}{{\par\noindent {\small{\em Keywords\/}: {#1}}}}}


% for compatability for natbib, used by journals.
%
\newcommand{\citep}[1]{\cite{#1}}
\newcommand{\citet}[1]{\cite{#1}}

% more journal stubs:
\newcommand{\altaffiltext}[2]{}
\newcommand{\altaffilmark}[1]{}

%------------------------------------------------------------

%\newcommand{\methodology}[1]{\textbf{#1}}

%\setlength{\textwidth}{\paperwidth}
%\addtolength{\textwidth}{-2in}
%\setlength{\oddsidemargin}{0pt}
%\setlength{\evensidemargin}{0pt}

% use geometry class instead of this mess.
%\setlength{\headheight}{15pt}
%\setlength{\headsep}{15pt}
%\setlength{\topmargin}{0in}
%\addtolength{\topmargin}{-\headheight}
%\addtolength{\topmargin}{-\headsep}
%\setlength{\footskip}{29pt}
%\setlength{\textheight}{\paperheight}
%\addtolength{\textheight}{-2.2in}
%
%\setlength{\marginparwidth}{.5in}
%\setlength{\marginparsep}{5pt}

%------------------------------------------------------------
\endinput
