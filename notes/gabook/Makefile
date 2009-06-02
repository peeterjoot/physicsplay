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
TEXFILES += eulerangle.tex
TEXFILES += spherical_polar.tex
TEXFILES += slerp.tex
TEXFILES += kvector_exponential.tex
TEXFILES += cauchy_gradient.tex
TEXFILES += gradient_and_forms.tex
TEXFILES += vector_integral_relations.tex
TEXFILES += stokes_revisited.tex
TEXFILES += nvolume.tex
TEXFILES += legendre.tex
TEXFILES += angular_acc.tex
TEXFILES += angular_acc_cross.tex
TEXFILES += gabookmark.tex
TEXFILES += tensor.tex
TEXFILES += ke_rotation.tex
TEXFILES += radial.tex
TEXFILES += gaussian_surface.tex
TEXFILES += newtonian_lagrangian_and_gradient.tex
TEXFILES += canonical_momentum.tex
TEXFILES += inertial_tensor.tex
TEXFILES += locate_satellite.tex
TEXFILES += 

gabook.pdf :: $(TEXFILES)

%.pdf : %.tex
	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc
TEXFILES += bohr.tex
TEXFILES += euler_lagrange.tex
