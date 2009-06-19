\ProvidesClass{eliblog}[2009/03/05 Eli Lansey, Copyright (c) 2009]
\NeedsTeXFormat{LaTeX2e}[1999/09/01]
\typeout{}
\typeout{ ==========> Assignment Class (assignment.cls) 2002 <============= }
\typeout{ Eli Lansey (c) 2009 }
\typeout{ In case of questions, contact elansey@gmail.com }
\typeout{}


\DeclareOption*{%
  \PassOptionsToClass{\CurrentOption}{article}%
}
\ProcessOptions\relax
\LoadClass[11pt]{article}

\usepackage{color}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{graphicx}
% this mangles urls with underscores:
%\usepackage{url}
% fixes the url underscores:
%\usepackage{hyperref}
% remove the side panel:
\usepackage[bookmarks=false]{hyperref}
\usepackage{subfigure}
\usepackage{titlesec}
\usepackage{indentfirst}




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
      {\large{Originally appeared at: \texttt{\@blogpage}}\par}%
      \medskip
}
      {\large\@author\ ---\ \@email\par}%
         {\itshape\@date\par}%
         \medskip
         {\includegraphics[height=1em]{ccl2}\par}
      \bigskip\hrule\vspace*{0.5pc}%
   \end{flushleft}%
}
%\includegraphics[totalheight=0.4\textheight]{picturepath}

\newcommand{\methodology}[1]{\textbf{#1}}

\RequirePackage{ifthen}
\setlength{\textwidth}{\paperwidth}
\addtolength{\textwidth}{-2in}
\setlength{\oddsidemargin}{0pt}
\setlength{\evensidemargin}{0pt}

\setlength{\headheight}{15pt}
\setlength{\headsep}{15pt}
\setlength{\topmargin}{0in}
\addtolength{\topmargin}{-\headheight}
\addtolength{\topmargin}{-\headsep}
\setlength{\footskip}{29pt}
\setlength{\textheight}{\paperheight}
\addtolength{\textheight}{-2.2in}

\setlength{\marginparwidth}{.5in}
\setlength{\marginparsep}{5pt}


\newcommand{\@blogpage}{0}
\newcommand{\blogpage}[1]{\renewcommand{\@blogpage}{#1}}

\newcommand{\@email}{{\em No email address given}}
\newcommand{\email}[1]{\renewcommand{\@email}{{#1}}}



\newcommand{\lorem}{{Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas diam est, mollis lacinia, tempor vel, condimentum in, augue. Nunc sapien arcu, interdum in, accumsan sit amet, tristique vel, diam. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Vestibulum nec dui. Nullam ac ligula tincidunt risus porttitor gravida. Maecenas orci velit, accumsan ac, auctor vitae, vehicula in, lacus. Pellentesque vehicula aliquet nisi. Vestibulum laoreet. Mauris pretium vulputate dui. 

Phasellus cursus, erat sit amet blandit semper, justo enim lobortis justo, vitae sagittis dolor nisl non est. Donec tortor nisl, placerat at, luctus sit amet, aliquet ut, leo. Donec a eros a diam iaculis mattis. In volutpat metus et nisi. Suspendisse potenti. Morbi lobortis arcu eu lacus. Nulla dapibus, nulla a vehicula vestibulum, diam sapien tincidunt odio, ac consectetur tellus massa nec nunc. Aliquam sed quam quis turpis suscipit gravida. Suspendisse potenti. Duis eget lectus. Praesent eleifend felis.

Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. In non mi ac leo scelerisque eleifend. Proin fringilla nisl dapibus mi. Aliquam mollis aliquet justo. Sed vulputate. Maecenas imperdiet. Sed sollicitudin justo at felis. Vivamus vitae felis. Aenean nisl enim, pellentesque a, tempor sed, sollicitudin ac, neque. In hac habitasse platea dictumst. Mauris vel nisl mollis libero interdum fringilla. Curabitur suscipit fermentum neque. 
}}


\endinput

