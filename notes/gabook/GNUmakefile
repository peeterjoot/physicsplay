THISDIR := gabook

include ../make.vars

SOURCE_DIRS += appendix
SOURCE_DIRS += basics
SOURCE_DIRS += calculus
SOURCE_DIRS += electrodynamics
SOURCE_DIRS += emstress
SOURCE_DIRS += figures
SOURCE_DIRS += fourier
SOURCE_DIRS += lagrangian
SOURCE_DIRS += lorentzforce
SOURCE_DIRS += mathematica
SOURCE_DIRS += physics
SOURCE_DIRS += projection
SOURCE_DIRS += qm
SOURCE_DIRS += relativity
SOURCE_DIRS += rotation

ORIG_FILES += ../algebra/levi.pl

ORIG_FIGURE_FILES += ../geometric-algebra/Projection_line.png
ORIG_FIGURE_FILES += ../geometric-algebra/Projection_plane.png
ORIG_FIGURE_FILES += ../calculus/bivectorDot.png
ORIG_FIGURE_FILES += ../geometric-algebra/charge_line_element_figure.png
ORIG_FIGURE_FILES += ../geometric-algebra/cube_unfolded_004.png
ORIG_FIGURE_FILES += ../geometric-algebra/imaginaryorientation.png
ORIG_FIGURE_FILES += ../geometric-algebra/normalRot.png
ORIG_FIGURE_FILES += ../geometric-algebra/p41.png
ORIG_FIGURE_FILES += ../geometric-algebra/parallelogram_parameterized.png
ORIG_FIGURE_FILES += ../geometric-algebra/parallelogramvec.png
ORIG_FIGURE_FILES += ../geometric-algebra/parallelopiped_parameterized.png
ORIG_FIGURE_FILES += ../geometric-algebra/planeParameterization.png
ORIG_FIGURE_FILES += ../geometric-algebra/planerejection.png
ORIG_FIGURE_FILES += ../calculus/rotationGen.png
ORIG_FIGURE_FILES += ../geometric-algebra/rotor.png
ORIG_FIGURE_FILES += ../geometric-algebra/satellite.png
ORIG_FIGURE_FILES += ../geometric-algebra/spherical_polar.png
ORIG_FIGURE_FILES += ../calculus/surface_area_element.png
ORIG_FIGURE_FILES += ../geometric-algebra/surface_flux_element.png
ORIG_FIGURE_FILES += ../differential_forms/tangent_area_form.png
ORIG_FIGURE_FILES += ../geometric-algebra/visualize_subspace_projection.png
ORIG_FIGURE_FILES += ../calculus/volume_element.png
ORIG_FIGURE_FILES += ../nonga/figures/pendulumDouble.png

GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += cronology.tex

include ../make.rules

peeters_macros.sty : ../peeters_macros.tex $(THISDIR).sty
	cat ../peeters_macros.tex $(THISDIR).sty > $@
