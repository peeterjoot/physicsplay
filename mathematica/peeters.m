(* ::Package:: *)

Begin["peeters`"]

exportForLatex::usage = "This seems to be the most compact way to export for latex that still retains good resolution.  Use the epstopdf program to convert the resulting .eps file.  Also generate a .png for wordpress posts at the same time. \[IndentingNewLine]Note that the .png displays with some software having a checkerboard background, but that doesn't show up in the eventual web view.\[IndentingNewLine]\[IndentingNewLine]This png file is generated with a different basename so that latex includegraphics doesn't find it."

exportForLatex[filename_, image_]  := Module[{},

{Export[filename  <> ".eps",First[ImportString[ExportString[image,"PDF",Background->None],"PDF"]]]

,Export[filename  <> "pn.png", image ,Background->None, ImageResolution->72*4]
(*,Export[filename  <> ".pdf", image]*)
}
]

End[]



