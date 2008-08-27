files := $(shell ls *.ltx)
pdfs := $(files:.ltx=.pdf)

all : $(pdfs)
big: test/ga.pdf

$(pdfs) : ../peeters_macros.tex

include ../make.rules

ordered :=
ordered += ga_grade_dot_wedge.pdf
ordered += wedge_norm_vs_ga_norm.pdf
ordered += pythagoras.pdf
ordered += angular_velocity.pdf 
ordered += ga_wiki.pdf
ordered += ga_wiki_cramers.pdf
ordered += ga_wiki_torque.pdf
ordered += ga_wiki_unit_derivative.pdf
ordered += radial_vector_derivatives.pdf
ordered += plane.pdf
ordered += legendre.pdf
ordered += inertial_tensor.pdf
ordered += quaternion.pdf
ordered += rotor.pdf
ordered += maxwells_ga.pdf
ordered += trivector.pdf
ordered += kvector_exponential.pdf
ordered += laplace.pdf
ordered += scalar_commutes.pdf
ordered += angle_between_line_and_plane.pdf
ordered += bivector.pdf
ordered += bladegradereduction.pdf
ordered += reciprocal_frame.pdf
ordered += orthodecomp.pdf
ordered += gradient_and_forms.pdf
skipit += glossary.pdf
semiordered := $(ordered) $(filter-out $(ordered) $(skipit),$(pdfs))

test/ga.pdf: $(semiordered)
	pdftk $(semiordered) cat output test/ga.pdf
