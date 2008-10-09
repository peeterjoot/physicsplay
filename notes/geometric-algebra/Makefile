files := $(shell ls *.ltx)
pdfs := $(files:.ltx=.pdf)
ppdfs := $(shell ls ../*/*.pdf)

all : $(pdfs)
big: test/ga.pdf

$(pdfs) : ../peeters_macros.tex

include ../make.rules

ordered :=
ordered += ../cross_1_15/cross_1_15.pdf
ordered += ../maxwell/maxwell.pdf
ordered += ../cross/cross.pdf
ordered += ../geometric_algebra/ga_grade_dot_wedge.pdf
ordered += ../geometric_algebra/wedge_norm_vs_ga_norm.pdf
ordered += ../geometric_algebra/pythagoras.pdf
ordered += ../geometric_algebra/angular_velocity.pdf
ordered += ../geometric_algebra/ga_wiki.pdf
ordered += ../geometric_algebra/ga_wiki_cramers.pdf
ordered += ../geometric_algebra/ga_wiki_torque.pdf
ordered += ../geometric_algebra/ga_wiki_unit_derivative.pdf
ordered += ../geometric_algebra/radial_vector_derivatives.pdf
ordered += ../taylors/taylors.pdf
ordered += ../geometric_algebra/plane.pdf
ordered += ../geometric_algebra/legendre.pdf
ordered += ../geometric_algebra/inertial_tensor.pdf
ordered += ../geometric_algebra/quaternion.pdf
ordered += ../geometric_algebra/rotor.pdf
ordered += ../geometric_algebra/laplace.pdf
ordered += ../geometric_algebra/maxwells_ga.pdf
ordered += ../geometric_algebra/bivector.pdf
ordered += ../geometric_algebra/trivector.pdf
ordered += ../geometric_algebra/kvector_exponential.pdf
ordered += ../geometric_algebra/scalar_commutes.pdf
ordered += ../geometric_algebra/angle_between_line_and_plane.pdf
ordered += ../geometric_algebra/bladegradereduction.pdf
ordered += ../geometric_algebra/reciprocal_frame.pdf
ordered += ../geometric_algebra/orthodecomp.pdf
ordered += ../geometric_algebra/gradient_and_forms.pdf
ordered += ../geometric_algebra/shear.pdf
ordered += ../geometric_algebra/mp_inverse_svd_rough_notes.pdf
ordered += ../geometric_algebra/projection_with_matrix_comparison.pdf
ordered += ../geometric_algebra/ke_rotation.pdf
ordered += ../maxwell/lorentz_rotation.pdf
ordered += ../geometric_algebra/gacs_q8_8.pdf
ordered += ../geometric_algebra/locate_satellite.pdf
ordered += ../geometric_algebra/matrix_of_linear_tx.pdf
ordered += ../geometric_algebra/proj_generalized_dot_prod.pdf
ordered += ../geometric_algebra/projection_and_moore_penrose_vector_inverse.pdf
ordered += ../geometric_algebra/oblique_proj.pdf
ordered += ../geometric_algebra/em_tensor.pdf
ordered += ../geometric_algebra/angular_acc.pdf
ordered += ../geometric_algebra/fvec.pdf
ordered += ../geometric_algebra/lorentz.pdf
ordered += ../tensor/tensor.pdf
ordered += ../geometric_algebra/angular_acc_cross.pdf
ordered += ../geometric_algebra/ga_maxwell.pdf
ordered += ../geometric_algebra/spacetimegrad.pdf
ordered += ../geometric_algebra/sg_mx_41.pdf
ordered += ../geometric_algebra/pe.pdf
ordered += ../geometric_algebra/fourvec_dotinvariance.pdf
ordered += ../geometric_algebra/newtonian_lagrangian_and_gradient.pdf
ordered += ../geometric_algebra/cauchy_gradient.pdf
ordered += ../geometric_algebra/velocity_tx.pdf
ordered += ../geometric_algebra/em_potential.pdf
ordered += ../geometric_algebra/gafp_lorentz.pdf
ordered += ../geometric_algebra/sr_lagrangian.pdf
ordered += ../geometric_algebra/tong_mf1.pdf
ordered += ../geometric_algebra/lorentz_metric_tensor.pdf
ordered += ../geometric_algebra/mass_vary_lagrangian.pdf 

ordered += ../geometric_algebra/canonical_momentum.pdf
ordered += ../geometric_algebra/outermorphism_det.pdf

ordered += ../mechanics/goldstein_ch1_2.pdf

ordered += ../geometric_algebra/em_bivector_metric_dependencies.pdf
ordered += ../geometric_algebra/maxwell_to_tensor.pdf
ordered += ../geometric_algebra/vector_maxwells_projection.pdf
ordered += ../geometric_algebra/lagrangian_field_density.pdf
ordered += ../geometric_algebra/vector_integral_relations.pdf

skipit += ../geometric_algebra/glossary.pdf
skipit += ../geometric_algebra/long_wire_q.pdf
skipit += ../feynman/star_distance.pdf
skipit += ../lut/rindler.pdf
skipit += ../toc/gabookmark.pdf
skipit += ../geometric_algebra/usebib.pdf
skipit += ../geometric_algebra/q.pdf
skipit += ../matteo/m.pdf
skipit += ../lut/Rindler-eom.pdf

#ordered +=
ordered += ../geometric_algebra/stokes_maxwell_application.pdf
ordered += ../geometric_algebra/stokes_revisited.pdf

ordered += ../lut/schwartzchild_metric.pdf
ordered += ../geometric_algebra/lorentz_force.pdf

semiordered := $(ordered) $(unordered)
unordered := $(filter-out $(ordered) $(skipit),$(ppdfs))

showu :
	@echo $(unordered)

test/ga.pdf: $(semiordered)
	pdftk $(semiordered) cat output test/ga.pdf
