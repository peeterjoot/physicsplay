all : gabook.pdf

# add here and as includes to gabook.tex:
TEXFILES += bivector.tex
TEXFILES += ga_wiki.tex
TEXFILES += ga_wiki_cramers.tex
TEXFILES += gabook.tex
TEXFILES += index.tex
TEXFILES += intro_ga.tex
TEXFILES += multivector_taylors.tex
TEXFILES += trivector.tex
TEXFILES += ga_wiki_torque.tex
TEXFILES += ga_wiki_unit_derivative.tex
TEXFILES += scalar_commutes.tex
TEXFILES += plane.tex
TEXFILES += quaternion.tex
TEXFILES += rotor.tex
TEXFILES += bladegradereduction.tex
TEXFILES += angular_velocity.tex
TEXFILES += radial_vector_derivatives.tex
TEXFILES += maxwells_ga.tex
TEXFILES += reciprocal_frame.tex
TEXFILES += projection_with_matrix_comparison.tex
TEXFILES += oblique_proj.tex
TEXFILES += projection_and_moore_penrose_vector_inverse.tex
TEXFILES += angle_between_line_and_plane.tex
TEXFILES += orthodecomp.tex
TEXFILES += 

gabook.pdf :: $(TEXFILES)

%.pdf : %.tex
	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc
